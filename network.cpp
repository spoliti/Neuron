#include "network.h"
#include <iostream>
#include <fstream>
//#include <random>

Network::Network():
    steps(0),
    current(0),
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
    Neuron n(0, current);
    for (int i(0); i < N; ++i)
    {
        n = Neuron(i+1, current);
        neuron_collection.push_back(n);
    }
}

void Network::update_neurons(double current_)
{
    current = current_;
    for(int i(0); i < N; ++i)
    {
        neuron_collection[i].update(current);
    }
    ++steps;
}

void Network::add_connection(int i, Neuron* new_neuron)
{
    neuron_collection[i].add_connection(new_neuron);
}

void Network::create_connections()
{
    add_connection(0, &neuron_collection[1]);
}

void Network::store_membrane_potentials()
{
    std::ofstream file;
    file.open("file.txt");
        for(unsigned int  i(0); i < N; ++i)
        {
            file << "Neuron " << i+1 << ":" << std::endl;
            for(unsigned int j(0); j < neuron_collection[i].getPotentials_collection().size(); ++j)
            {
                file << neuron_collection[i].getPotentials_collection()[j] << " ";
            }
            file << std::endl;
        }
        file.close();
}
