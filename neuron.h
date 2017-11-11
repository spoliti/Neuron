
#ifndef NEURON_H_INCLUDED
#define NEURON_H_INCLUDED

#include "constants.h"
#include <vector>

/*!
 *@Neuron
 *
 *@brief the class represents an individual neuron.
 *@brief the parameters necessary to the initialization and update of the neuron are defined in constants.h:
 *  - V_RESET=0mV: membrane potential (initialization), after a spike is produced (update)
 *  - TRANSMISSION DELAY=1.5ms: time to deliver a spike from the neuron it's connections (h)
 *  - REFRACTORY PERIOD=2ms: time that the neuron remains inactive, after producing a spike (D)
 *  - SPIKE_AMP=0.1mV: spike amplitude (J)
 *  - G_RATIO=5: ratio of strength between inhibitory and excitatory neurons (g=J_I/J_E)
 *  - NU_RATIO=2: ratio of potential between the network's exterior and the neurons membrane (NU=nu_ext/nu_thr)
 *  - V_THR=20mV: firing threshold (theta)
 *  - TIME_CONST=20ms: time constant (tau)
 *  - MEMBRANE_RES=20ohm: membrane resistance (R)
 */
class Neuron
{
    public:

        /*!
         *@param index
         *@param type: true if excitatory, false if inhibitory
         */
        Neuron(int index, bool type);                /*!< class constructor */
        ~Neuron();                                   /*!< class destructor */

        /*!
         *@brief the function allows to access a neuron's variable from outside the class: index
         */
        int getIndex();

        /*!
         *@brief the function allows to access a neuron's variable from outside the class: connections
         */
        std::vector<Neuron*> getConnections();

        /*!
         *@brief the function allows to access a neuron's variable from outside the class: membrane potential
         */
        double getPotential();

        /*!
         *@brief the function allows to access a neuron's variable from outside the class: spikes collection
         */
        std::vector<int> getSpikes_collection();

        /*!
         *@brief the function allows to access a neuron's variable from outside the class: true is the neuron has spiked, false if not
         */
        bool getHas_spiked();


        /*!
         *@brief the function adds a connection to the neuron
         */
        void add_connection(Neuron* new_neuron);

        /*!
         *@brief the function reinitializes the neuron after a spike:
         *  - potential = V_RESET
         *  - neuron enters refractory period (inactive)
         */
        void reset();

        /*!
         *@brief the function verifies if the neuron has been in refractory period long enough, if so it return to be active.
         *  - the neuron has to be inactive: is_active = false
         *  - steps_refractory = TRANSMISSION_DELAY * TIME_UNIT
         */
        void refractory();

        /*!
         *@brief the function calculates the membrane potential at the current time:
         *  - degradation in time: potential(t+h) = potential(t) * e^-(TIME_UNIT/TIME_CONST)
         *  - sum of spikes received by other neurons in the network: spikes_received * SPIKE_AMP
         *  - sum of spikes received by other neurons outside the network: num_ext * SPIKE_AMP
         */
        void calculate_potential();

        /*!
         *@brief the function stores a newly produced spike and informs the neuron's connection that they will receive a spike (spike stored in target buffer):
         *  - excitatory neuron: positive impact on connections (+1)
         *  - inhibitory neuron: negative impact on connections (-G_RATIO)
         *
         *@see increment_buffer()
         */
        void spike();

        /*!
         *@brief the function add a spike to the buffer, received by the neuron after a certain number of steps (buffer length: TRANSMISSION DELAY * TIME_UNIT)
         *
         *@param type: if excitatory (+1), if inhibitory (-G_RATIO)
         */
        void increment_buffer(int type);

        /*!
         *@brief the function updates the neuron each step:
         *  - determines the external input
         *  - determines the number of spikes being received
         *  - calculates the new potential
         *  - if the potential exceeds the firing threshold (V_THR): spike()
         *  - if the neuron is inactive: refractory()
         *
         *@see external_connections()
         *@see calculate_potential()
         *@see spike()
         *@see refractory()
         */
        void update();

        /*!
         *@brief the function calculates the number of random spikes received from external connections
         *  - Poisson distribution
         *  - rate depending of NU_RATIO
         */
        void external_connections();

    private:

        int index;                                  /*!< index number */
        double potential;                           /*!< membrane potential (mV) */
        bool is_excitatory;                         /*!< true if excitatory, false if inhibitory */
        bool is_active;                             /*!< true if active, false if in refractory period */

        std::vector<Neuron*> connections;           /*!< connections to other neurons in the network, potentials will be affected by the neuron's spike */
        std::vector<int> spikes_collection;         /*!< collection of times (steps) at which a spikes occurred */
        std::vector<int> buffer;                    /*!< collection of spikes to be received by the neuron during period of time: length of buffer (steps) */
        int spikes_received;                        /*!< number of spikes received by the neuron at a specific time (step) */
        int num_ext;                                /*!< firing rate for external neuron connections */
        bool has_spiked;                            /*!< true if the neuron produced a spike at a specific time (step) */

        int steps_local;                            /*!< time (steps), since the creation of the neuron */
        int steps_refractory;                       /*!< time (steps), since the last reset of the neuron */

};

#endif // NEURON_H_INCLUDED
