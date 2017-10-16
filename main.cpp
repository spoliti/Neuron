#include "neuron.h"
#include "simulation.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    //double time(0.0);
    int steps(0);
    int steps_sim(2000);
    int a(200);
    int b(1200);
    double current_input(3.0);
    double current(0.0);
    //Simulation s(time_sim,current_input);
    Neuron n(current);

    // increment the simulation time by one step (time = n*h, n = steps)
    while(steps <= steps_sim)
        {
            if(a <= steps && steps <= b)
                current = current_input;
            else current = 0.0;
            n.update(current);
            //time += TIME_UNIT;
            ++steps;
        }

    // store membrane potential values
    if(!n.getPotentials_at_times().empty())
        {
            ofstream file;
            file.open("file.txt");
            for(unsigned int i(0); i <= n.getPotentials_at_times().size(); ++i)
                {
                    file << n.getPotentials_at_times()[i] << " ";
                }
            file.close();
        }

    // display values
    cout << "Membrane potential: " << n.getV() << endl;
    cout << "Number of spikes emitted by the neuron: " << n.getSpikes() << endl;
    cout << "Time steps of last spike emitted by the neuron: " << n.getLast_spike_time() << endl;

    cout << "Collection of spikes (time steps): ";
    if(!n.getSpikes_times().empty())
        {
            for(unsigned int i(0); i <= n.getSpikes_times().size(); ++i)
                {
                    cout << n.getSpikes_times()[i] << " | ";
                }
            cout << endl;
        }
    else cout << "- " << endl;

    cout << "Collection of membrane potentials: ";
    ifstream file;
    file.open("file.txt");
    if(file.is_open())
        {
            string line;
            while(getline(file,line))
                {
                    cout << line << endl;
                }
            file.close();
        }
    else cout << "Error opening file" << endl;

    return 0;
}
