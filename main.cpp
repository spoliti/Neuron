#include "neuron.h"
#include "network.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    //double time(0.0);
    int steps(0);                               // time (steps) counter
    int steps_total(2000);                      // time (steps) total
    int input_start(200);                       // time (steps) of start of current input
    int input_end(1200);                        // time (steps) of end of current input

    double current(75);                         // external current input

    Network brain;                              // create network
    brain.create_neurons();                     // create neurons in the network
    brain.create_connections();                 // create connection between neurons

    // increment the simulation time by one step (time = n*h, n = steps)
    while(steps < steps_total)
    {
        if((steps < input_start ) || (steps > input_end))
            brain.update_neurons(0.0);
        else brain.update_neurons(current);
        //time = steps * TIME_UNIT;
        ++steps;
    }

    brain.store_membrane_potentials();          // saves the value of each neurons membrane potential at each step of the simulation

    // display values
    for(int i(0); i < N; ++i)
    {
        cout << "Neuron #" << i+1 << endl;
        cout << " - Number of connections: " << brain.getNeuron_collection()[i].getConnections().size() << endl;
        cout << " - Membrane potential (mV): " << brain.getNeuron_collection()[i].getPotential() << endl;
        cout << " - Number of spikes emitted by the neuron: " << brain.getNeuron_collection()[i].getTotal_spikes_number() << endl;
        cout << " - Time (steps) of last spike emitted by the neuron: " << brain.getNeuron_collection()[i].getLast_spike_time() << endl;
    }

    return 0;
}
