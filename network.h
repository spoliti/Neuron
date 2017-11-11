#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "neuron.h"
#include <vector>

/*!
 *@Network
 *
 *@brief the class represent a network of neurons:
 *  - create neurons
 *  - create connections between neurons
 *  - update neurons through time
 *  - store the times at which individual neurons produce spikes
 *  - store the total number of spikes produced at each step
 */
class Network
{
    public:

        Network();          /*!< class constructor */
        ~Network();         /*!< class destructor */

        /*!
         *@brief the function creates all the neurons in the network (N):
         *  - excitatory neurons (N_E) are defined by an index from 1 to N_E
         *  - inhibitory neurons (N_I) are defined by an index from N_E to N_E+N_I
         *@brief parameters are defined in constants.h: N=12500, N_E=10000, N_I=2500)
         */
        void create_neurons();

        /*!
         *@brief the function adds a single connection to an individual neuron
         *
         *@param index of the neuron to whom a connection is to be added
         *@param pointer to the neuron to whom it will be connected
         */
        void add_connection(int index, Neuron* new_neuron);

        /*!
         *@brief the function creates all connections between the neurons in the network:
         *  - each neuron contains connections with random excitatory neurons in the network (C_E)
         *  - each neuron contains connections with random inhibitory neurons in the network (C_I)
         *@brief parameters are defined in constants.h: C_E=1000, C_I=250
         */
        void create_connections();

        /*!
         *@brief each neuron in the network is updated every step (TIME_UNIT).
         *@brief parameters are defined in constants.h: TIME_UNIT=0.1ms
         */
        void update_neurons();

        /*!
         *@brief allows to store information from the simulation:
         *  - the times (steps) at which a number of randomly chosen neurons have produced spikes
         *  - the total amount of spikes produced at each step
         *
         *@param number of neurons to be randomly chosen
         *@param starting time (step) to store information
         *@param ending time (step) to store information
         */
        void store_information(unsigned int number, unsigned int start_time, unsigned int end_time);

    private:

        int steps;                                            /*!< time (steps) of the simulation */
        std::vector<Neuron> neuron_collection;                /*!< collection of neurons in the network */
        std::vector<int> spikes_collection;                   /*!< collection of spikes produced at each step */
};

#endif // NETWORK_H_INCLUDED
