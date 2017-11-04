
#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED

#include "constants.h"
#include <vector>

class Neuron
{
    public:

        Neuron(int index, bool type);                // class constructor
        ~Neuron();                                   // class destructor

        // getters
        int getIndex();
        double getPotential();
        std::vector<int> getSpikes_collection();
        std::vector<Neuron*> getConnections();
        bool getHas_spiked();

        void reset();                                       // reinitialize neuron characteristics after spike
        void refractory();                                  // the neuron remains inactive for a period of time after a spike
        void calculate_potential();                         // calculates the membrane potential at the current time
        void spike();                                       // records a new spike at the current time, if V > V_THR
        void update();                                      // update neuron characteristics after time_unit
        void receive_spike();                               // input of current, if a neighbouring neuron has sent a spike
        void add_connection(Neuron* new_neuron);            // adds a connection to the neuron
        void increment_buffer(int type);                    // adds a spike to be received
        void external_connections();                        // calculates the number of random spikes received from external connections

    private:

        int index;                                  // index number
        bool is_excitatory;                         // true if excitatory, false if inhibitory
        double potential;                           // membrane potential (mV)
        bool is_active;                             // true if active, false if in refractory period

        std::vector<double> potentials_collection;  // collection of the membrane potentials at each time step
        std::vector<int> spikes_collection;         // collection of times (steps) at which a spikes occurred
        std::vector<Neuron*> connections;           // neighbouring neurons, whose potential will be affected by the neuron's spike
        std::vector<int> buffer;                    // collection of spikes to be received by the neuron during a certain period of time (steps)
        int spikes_received;                        // number of spikes received by the neuron at a certain time (step)
        int num_ext;                                // firing rate for external neuron connections
        bool has_spiked;                            // true if the neuron produced a spike at a certain time (step)

        int steps_local;                            // time (steps), since the creation of the neuron
        int steps_refractory;                       // time (steps), since the last reset of the neuron

};

#endif // NEURON_H_INCLUDED
