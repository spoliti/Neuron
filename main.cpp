#include "neuron.h"
#include "network.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int main()
{
    int steps(0);                                 // time (steps) counter
    int steps_total(2000);                        // time (steps) total

    Network brain;                                // create network
    brain.create_neurons();                       // create neurons in the network
    brain.create_connections();                   // create connection between neurons

    // increment the simulation time by one step (time = n*h, n = steps)
    while(steps < steps_total)
    {
        brain.update_neurons();
        ++steps;
    }

    // store information for a certain number of neurons (time at which spikes occur)
    unsigned int number(50);
    unsigned int start_time(1000);
    unsigned int end_time(2000);
    brain.store_information(number, start_time, end_time);

    return 0;
}
