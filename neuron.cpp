#include "neuron.h"
#include <iostream>
#include <cmath>
//#include <random>

Neuron::Neuron(int index, double current):
    index(index),
    potential(V_RESET),
    is_active(true),
    spikes_collection(),
    potentials_collection(),
    connections(),
    buffer(TRANSMISSION_DELAY/TIME_UNIT),
    spikes_received(0),
    current_ext(current),
    steps_local(0),
    steps_refractory(0)
{}

Neuron::~Neuron()
{}

int Neuron::getIndex()
{
    return index;
}

double Neuron::getPotential()
{
    return potential;
}

std::vector<int> Neuron::getSpikes_collection()
{
    return spikes_collection;
}

int Neuron::getTotal_spikes_number()
{
    if(!spikes_collection.empty())
        return spikes_collection.size();
    else return 0;
}

int Neuron::getLast_spike_time()
{
    if(!spikes_collection.empty())
        return spikes_collection.back();
    else return 0;
}

std::vector<double> Neuron::getPotentials_collection()
{
    return potentials_collection;
}

std::vector<Neuron*> Neuron::getConnections()
{
    return connections;
}

void Neuron::reset()
{
    potential = V_RESET;
    is_active = false;
    steps_refractory = 0;
}

void Neuron::refractory()
{
    if(steps_refractory==(int)(REFRACTORY_PERIOD/TIME_UNIT))
    {
        is_active = true;
        steps_refractory = 0;
    }
    else ++steps_refractory;
}

void Neuron::calculate_potential()
{
    if(index == 1)
    {
        potential = (exp(-TIME_UNIT/TIME_CONST) * potential) + ((1 - exp(-TIME_UNIT/TIME_CONST)) * current_ext * MEMBRANE_RES);
    }
    else potential = (exp(-TIME_UNIT/TIME_CONST) * potential) + ((1 - exp(-TIME_UNIT/TIME_CONST)) * spikes_received * SPIKE_AMP);
}

void Neuron::spike()
{
    spikes_collection.push_back(steps_local);
    for(unsigned int i(0); i < connections.size(); ++i)
    {
        connections[i]->increment_buffer();
    }
}

void Neuron::update(double current)
{
    current_ext = current;

    if(buffer.back() != 0)
    {
        spikes_received = buffer.back();
    }
    buffer.pop_back();
    std::vector<int>::iterator it;
    it = buffer.begin();
    it = buffer.insert(it,0);
    buffer.insert(it,0);

    calculate_potential();
    if(potential>V_THR)
    {
        spike();
        reset();
    }
    potentials_collection.push_back(potential);

    if(!is_active)
    {
        refractory();
    }
    ++steps_local;
}

void Neuron::add_connection(Neuron* new_neuron)
{
    connections.push_back(new_neuron);
}

void Neuron::increment_buffer()
{
    buffer[0] += 1;
}
