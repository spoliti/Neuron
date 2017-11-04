#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "neuron.h"
#include <vector>

class Network
{
    public:

        Network();                                            // class constructor
        ~Network();                                           // class destructor

        // getters
        std::vector<Neuron> getNeuron_collection();

        void create_neurons();                                      // creates all the neurons in the network
        void update_neurons();                                      // updates all the neurons in the network
        void add_connection(int index, Neuron* new_neuron);         // adds a new connection to a neuron
        void create_connections();                                  // creates all the neuron connections in the network
        void store_information(unsigned int number, unsigned int start_time, unsigned int end_time);                // allows to store relevant information
    private:

        int steps;                                            // time (steps) of the simulation
        std::vector<Neuron> neuron_collection;                // collection of neurons in the network
        std::vector<int> spikes_collection;                   // collection of spikes produced at each step

};

#endif // NETWORK_H_INCLUDED
