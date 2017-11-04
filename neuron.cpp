#include "neuron.h"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

Neuron::Neuron(int index, bool type):
    index(index),
    is_excitatory(type),
    potential(V_RESET),
    is_active(true),
    potentials_collection(),
    spikes_collection(),
    connections(),
    buffer(TRANSMISSION_DELAY/TIME_UNIT),
    spikes_received(0),
    has_spiked(false),
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

std::vector<Neuron*> Neuron::getConnections()
{
    return connections;
}

bool Neuron::getHas_spiked()
{
    return has_spiked;
}

// if a spike is produced: the potential is reset and the neuron enters refractory period
void Neuron::reset()
{
    potential = V_RESET;
    is_active = false;
    steps_refractory = 0;
}

// if the neuron is inactive: verifies if the neurons has been in refractory period long enough, if so it returns to be active
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
    potential = (exp(-TIME_UNIT/TIME_CONST) * potential) + (spikes_received * SPIKE_AMP) + (num_ext * SPIKE_AMP);
}

// if a spike is produced: excitatory neuron -> positive impact on connections, inhibitory neuron -> negative impact on connections
void Neuron::spike()
{
    has_spiked = true;
    spikes_collection.push_back(steps_local);
    if(is_excitatory)
    {
        for(unsigned int i(0); i < connections.size(); ++i)
        {
            connections[i]->increment_buffer(1);
        }
    }
    if(!is_excitatory)
    {
        for(unsigned int i(0); i < connections.size(); ++i)
        {
            connections[i]->increment_buffer(-G_RATIO);
        }
    }
}

void Neuron::update()
{
    has_spiked = false;

    // determines the external input from outside the network
    external_connections();

    // the buffer vector to implement the spike's transmission delay: the last element contains the number of spikes that the neuron receives at this time (step)
    spikes_received = buffer[(TRANSMISSION_DELAY/TIME_UNIT)-1];
    buffer.pop_back();
    buffer.insert(buffer.begin(), 0);

    calculate_potential();
    potentials_collection.push_back(potential);
    if(potential>V_THR)
    {
        spike();
        reset();
    }

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

void Neuron::increment_buffer(int type)
{
    buffer[0] += type;
}

void Neuron::external_connections()
{
    double lambda(0.0);
    lambda = NU_RATIO * (V_THR/(SPIKE_AMP * TIME_CONST)) * TIME_UNIT;

    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::poisson_distribution<> distribution(lambda);
    num_ext = distribution(generator);
}
