#include "neuron.h"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

Neuron::Neuron(int index, bool type):
    index(index),
    potential(V_RESET),
    is_excitatory(type),
    is_active(true),
    connections(),
    spikes_collection(),
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

std::vector<Neuron*> Neuron::getConnections()
{
    return connections;
}

std::vector<int> Neuron::getSpikes_collection()
{
    return spikes_collection;
}


bool Neuron::getHas_spiked()
{
    return has_spiked;
}


void Neuron::add_connection(Neuron* new_neuron)
{
    connections.push_back(new_neuron);
}

void Neuron::reset()
{
    potential = V_RESET;
    is_active = false;
    steps_refractory = 0;
}

// if the neuron is inactive
void Neuron::refractory()
{
    // verify if the neuron has been in refractory period for the given amount of time -> the neuron returns active
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

// if a spike is produced (potential > firing threshold)
void Neuron::spike()
{
    // store spike
    has_spiked = true;
    spikes_collection.push_back(steps_local);

    // if the neuron is excitatory: +1
    if(is_excitatory)
    {
        for(unsigned int i(0); i < connections.size(); ++i)
        {
            connections[i]->increment_buffer(1);
        }
    }

    // if the neuron is inhibitory: -g
    if(!is_excitatory)
    {
        for(unsigned int i(0); i < connections.size(); ++i)
        {
            connections[i]->increment_buffer(-G_RATIO);
        }
    }
}


void Neuron::increment_buffer(int type)
{
    buffer[0] += type;
}

void Neuron::update()
{
    has_spiked = false;

    // determines the external input from outside the network
    external_connections();

    // the buffer vector to implement the spike's transmission delay: the last element contains the number of spikes that the neuron receives at this time (step)
    spikes_received = buffer[(int)(TRANSMISSION_DELAY/TIME_UNIT)-1];
    buffer.pop_back();
    buffer.insert(buffer.begin(), 0);

    // update the membrane potential
    calculate_potential();

    // spike produced
    if(potential>V_THR)
    {
        spike();
        reset();
    }

    // refractory period
    if(!is_active)
    {
        refractory();
    }
    ++steps_local;
}

void Neuron::external_connections()
{
    // rate of distribution
    double lambda(0.0);
    lambda = NU_RATIO * (V_THR/(SPIKE_AMP * TIME_CONST)) * TIME_UNIT;

    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::poisson_distribution<> distribution(lambda);
    num_ext = distribution(generator);
}
