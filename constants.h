#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

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
