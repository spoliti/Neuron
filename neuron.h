
#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED

#include "constants.h"
#include <vector>

class Neuron
{
    public:

        Neuron(int index, double current);          // class constructor
        ~Neuron();                                   // class destructor

        // getters
        int getIndex();
        double getPotential();
        std::vector<int> getSpikes_collection();
        int getTotal_spikes_number();
        int getLast_spike_time();
        std::vector<double> getPotentials_collection();
        std::vector<Neuron*> getConnections();

        void reset();                                       // reinitialize neuron characteristics after spike
        void refractory();                                  // the neuron remains inactive for a period of time after a spike
        void calculate_potential();                         // calculates the membrane potential at the current time
        void spike();                                       // records a new spike at the current time, if V > V_THR
        void update(double current);                        // update neuron characteristics after time_unit
        void receive_spike();                               // input of current, if a neighbouring neuron has sent a spike
        void add_connection(Neuron* new_neuron);            // adds a connection to the neuron
        void increment_buffer();                            // adds a spike to be received

    private:

        int index;                                  // number of neuron
        double potential;                           // membrane potential (mV)
        bool is_active;                             // true if the neuron is active, false if it is in refractory period
        std::vector<int> spikes_collection;         // collection of times (steps) at which a spikes occurred
        std::vector<double> potentials_collection;  // collection of the membrane potentials at each time step
        std::vector<Neuron*> connections;           // neighbouring neurons, whose potential will be affected by the neuron's spike
        std::vector<int> buffer;                    // collection of spikes to be received by the neuron during a certain period of time (steps)
        int spikes_received;                        // number of spikes received by the neuron at a certain time (step)

        double current_ext;                         // current input from the environment
        int steps_local;                            // time (steps), since the creation of the neuron
        int steps_refractory;                       // time (steps), since the last reset of the neuron

};

#endif // NEURON_H_INCLUDED
