#include "network.h"
#include <iostream>
#include <fstream>
#include <random>

Network::Network():
    steps(0),
    neuron_collection()
{}

Network::~Network()
{}

std::vector<Neuron> Network::getNeuron_collection()
{
    return neuron_collection;
}

void Network::create_neurons()
{
    for(int i(0); i < N_E; ++i)
    {
        neuron_collection.push_back(Neuron(i, true));
    }
    for(int j(0); j < N_I; ++j)
    {
        neuron_collection.push_back(Neuron(N_E + j, false));
    }
}

void Network::update_neurons()
{
    spikes_collection.push_back(0);
    for(int i(0); i < N; ++i)
    {
        neuron_collection[i].update();
        if(neuron_collection[i].getHas_spiked())
            ++spikes_collection[steps];
    }
    ++steps;
}

void Network::add_connection(int index, Neuron* new_neuron)
{
    neuron_collection[index].add_connection(new_neuron);
}

void Network::create_connections()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_excitatory(0, N_E-1);
    std::uniform_int_distribution<int> distribution_inhibitory(N_E, N-1);

    for(int i(0); i < N; ++i)
    {
        for(int j(0); j < C_E; ++j)
        {
            int index = distribution_excitatory(generator);
            add_connection(i, &neuron_collection[index]);
        }
        for(int j(0); j < C_I; ++j)
        {
            int index = distribution_inhibitory(generator);
            add_connection(i, &neuron_collection[index]);
        }
    }
}

void Network::store_information(unsigned int number, unsigned int start_time, unsigned int end_time)
{
    // store the times (steps) at which spikes occur for n random neurons
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned int> distribution(0, N-1);
    int index(0);
    std::ofstream file;
    file.open("file.txt");
    for(unsigned int  i(1); i <= number; ++i)
    {
        index = distribution(generator);
        for(unsigned int k(0); k < neuron_collection[index].getSpikes_collection().size(); ++k)
        {
            unsigned int spike_time = neuron_collection[index].getSpikes_collection()[k];
            if((start_time <= spike_time) && (end_time >= spike_time))
                file << spike_time << ", ";
        }
        file << std::endl;
    }
    file.close();

    // store the number of spikes being produced in the network at each time (step)
    std::ofstream file_total;
    file_total.open("file_total.txt");
    for(unsigned int j(start_time); j <= end_time; ++j)
        file_total << spikes_collection[j] << ", ";
    file_total.close();
}
