#include "network.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

Network::Network():
    steps(0),
    neuron_collection()
{}

Network::~Network()
{}

void Network::create_neurons()
{
    //creates N_E excitatory neurons
    for(int i(0); i < N_E; ++i)
    {
        neuron_collection.push_back(Neuron(i, true));
    }

    //creates N_I inhibitory neurons
    for(int j(0); j < N_I; ++j)
    {
        neuron_collection.push_back(Neuron(N_E + j, false));
    }
}

void Network::add_connection(int index, Neuron* new_neuron)
{
    neuron_collection[index].add_connection(new_neuron);
}

void Network::create_connections()
{
    // allows to generate connections randomly
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution_excitatory(0, N_E-1);
    std::uniform_int_distribution<int> distribution_inhibitory(N_E, N-1);

    // index (i) of the neuron to whom the connections will be created
    for(int i(0); i < N; ++i)
    {
        // creates C_E excitatory connections to the neuron
        for(int j(0); j < C_E; ++j)
        {
            int index = distribution_excitatory(generator);
            add_connection(i, &neuron_collection[index]);
        }

        // creates C_I inhibitory connections to the neuron
        for(int j(0); j < C_I; ++j)
        {
            int index = distribution_inhibitory(generator);
            add_connection(i, &neuron_collection[index]);
        }
    }
}

void Network::update_neurons()
{
    // at the moment no spikes have been produced by the network
    spikes_collection.push_back(0);

    // index (i) of the neuron to be updated
    for(int i(0); i < N; ++i)
    {
        // updates the neuron
        neuron_collection[i].update();

        // verify if the neuron has spiked -> the number of spikes at this step is incremented by one
        if(neuron_collection[i].getHas_spiked())
            ++spikes_collection[steps];
    }
    ++steps;
}

void Network::store_information(unsigned int number, unsigned int start_time, unsigned int end_time)
{
// store the variables
    const char *path = "C:/Users/Stefano/Documents/EPFL/SV II (2017-18)/Projet en Informatique/Files/Neuron/files/file_variables.txt";
    std::ofstream file_variables;
    file_variables.open(path);
    file_variables << number << ", " << start_time << ", " << end_time;
    file_variables.close();

// store the times (steps) at which spikes occur for n random neurons
    const char *path_2 = "C:/Users/Stefano/Documents/EPFL/SV II (2017-18)/Projet en Informatique/Files/Neuron/files/file.txt";
    std::ofstream file;
    file.open(path_2);

    // allows to generate random numbers
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned int> distribution(0, N-1);

    int index(0);                               // index of the neuron to be considered
    unsigned int counter(0);                    // will be incremented each time a neuron is determined to have no spikes within the given time-range
    bool written(false);                        // indicates whether the neuron [index] has at least one spike in the file

    // 50 randomly chosen neurons
    for(unsigned int  i(0); i < number; ++i)
    {
        index = distribution(generator);        // a random number is associated with the index of the neuron to be considered
        unsigned int counter_local(0);          // will be incremented each time a spike not within the given time-range

        // verify if the neuron has produced no spikes
        if(neuron_collection[index].getSpikes_collection().empty())
            ++counter;
        else
            // the collection of steps at which the neuron produced a spike
            for(unsigned int k(0); k < neuron_collection[index].getSpikes_collection().size(); ++k)
            {
                unsigned int spike_time = neuron_collection[index].getSpikes_collection()[k];

                // verify if the spike is within the time-range -> store the time of spike in the file
                if((start_time <= spike_time) && (end_time >= spike_time))
                {
                    file << spike_time << ", ";
                }
                else
                {
                    ++counter_local;
                }

                // verify if the neuron has not produced any spikes within the given time-range - > signal
                if(counter_local == neuron_collection[index].getSpikes_collection().size())
                {
                    ++counter;
                    written = false;
                }
                else written = true;
            }

            // verify if at least one spike from the neuron was stored in the file -> next line
            if(written)
                file << std::endl;
    }

    // WARNING: if no spikes were produced by the n neurons within the given time-ranges
    if(counter == number)
    {
        file << "0";
        std::cout << "WARNING: No spikes were produced (by the 50 randomly chosen neurons) between steps " << start_time << " and " << end_time << std::endl;
    }

    file.close();


// store the number of spikes produced in the network at each step
    const char *path_3 = "C:/Users/Stefano/Documents/EPFL/SV II (2017-18)/Projet en Informatique/Files/Neuron/files/file_total.txt";
    std::ofstream file_total;
    file_total.open(path_3);

    // WARNING: if no spikes were produced by the network within the given time-range
    if (spikes_collection.empty())
        std::cout << "WARGNING: No spikes were produced the the network between steps " << start_time << " and " << end_time << std::endl;

    else
        // steps within the time-range
        for(unsigned int j(start_time); j <= end_time; ++j)
            file_total << spikes_collection[j] << ", ";

    file_total.close();
}
