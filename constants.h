#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define N 2                         // total number of neurons

//#define N_E 10000                   // number of excitatory neurons

//#define N_I 2500                    // number of inhibitory neurons

//#define g 5.0                       // connection strength ratio: g = J_I/J_E

//#define C_E 1000                    // number of excitatory connections for each neuron: C_E = 0.1 * N_E

//#define C_I 250                     // number of inhibitory connections for each neuron: C_I = 0.1 * N_I//

//#define C_EXT 1000                  // number of excitatory connections from outside the network: C_EXT = C_E

#define V_RESET 0.0                 // initial membrane potential: Vr (mV)

#define V_THR 20.0                  // firing threshold: theta (mV)

#define SPIKE_AMP 0.1               // spike amplitude: J (mV)

#define TIME_CONST 20.0             // time constant: tau (ms)

#define REFRACTORY_PERIOD 2.0       // refractory period: tau_rp (ms)

#define MEMBRANE_RES 20.0           // membrane resistance: R (Ohm)

#define TRANSMISSION_DELAY 1.5      // transmission delay: D (ms)

#define TIME_UNIT 0.1               // time unit: h (ms)

#define NU_THR 1.25                 // frequency threshold: Vthr=theta/(Ce*J*tau) (Hz)

#endif // CONSTANTS_H_INCLUDED
