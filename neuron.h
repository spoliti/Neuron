
#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED

#include "simulation.h"
#include "constants.h"
#include <vector>

class Neuron
{
    public:

        Neuron(double current);             // class constructor
        ~Neuron();                          // class destructor

        // getters
        double getV();
        bool getIsActive();
        int getSpikes();
        std::vector<int> getSpikes_times();
        int getLast_spike_time();
        std::vector<double> getPotentials_at_times();

        // setters
        void setV(double new_v);
        void setIsActive(bool isActive_);

        void reset();                               // reinitialize neuron characteristics after spike
        void refractory();                          // the neuron remains inactive for a period of time after a spike
        void calculate_potential();                 // calculates the membrane potential at the current time
        void spike();                               // records a new spike at the current time, if V > V_THR
        void update(double current);                // update neuron characteristics after time_unit

    private:

        double v;                                   // membrane potential (mV)
        bool isActive;                              // true if the neuron is active, false if it is in refractory period
        int spikes;                                 // number of spikes (input activity)
        std::vector<int> spikes_times;              // collection of times at which the spikes occurred
        std::vector<double> potentials_at_times;   // collection of the membrane potentials at times of spikes

        double current_ext;                         // current input from the environment
        int steps_local;                            // time (steps), since the creation of the neuron
        int steps_refractory;                       // time (steps), since the last reset of the neuron

};

#endif // NEURON_H_INCLUDED
