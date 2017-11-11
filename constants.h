#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define N 12500                     // total number of neurons

#define N_E 10000                   // number of excitatory neurons

#define N_I 2500                    // number of inhibitory neurons

#define C_E 1000                    // number of excitatory connections for each neuron: C_E = 0.1 * N_E

#define C_I 250                     // number of inhibitory connections for each neuron: C_I = 0.1 * N_I//

#define TIME_UNIT 0.1               // time unit: h (ms)

#define V_RESET 0.0                 // initial membrane potential: Vr (mV)

#define TRANSMISSION_DELAY 1.5      // transmission delay: D (ms)

#define REFRACTORY_PERIOD 2.0       // refractory period: tau_rp (ms)

#define G_RATIO 4.5                 // connection strength ratio: g = J_I/J_E

#define NU_RATIO 0.9                // firing rate ration: NU=nu_ext/nu_thr

#define V_THR 20.0                  // firing threshold: theta (mV)

#define SPIKE_AMP 0.1               // spike amplitude: J (mV)

#define TIME_CONST 20.0             // time constant: tau (ms)

#define MEMBRANE_RES 20.0           // membrane resistance: R (Ohm)

#endif // CONSTANTS_H_INCLUDED
