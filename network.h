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

        void create_neurons();                                // creates all the neurons in the network
        void update_neurons(double current_);                 // updates all the neurons in the network
        void add_connection(int i, Neuron* new_neron);        // adds a new neuron connection
        void create_connections();                            // creates all the neuron connections in the network
        void store_membrane_potentials();                     // stores the membrane potentials of each neuron in the network

    private:

        int steps;                                            // time (steps) of the simulation
        double current;                                       // current input from the exterior
        std::vector<Neuron> neuron_collection;                // collection of neurons in the network

};

#endif // NETWORK_H_INCLUDED
