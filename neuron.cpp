#include "neuron.h"
#include <cmath>

Neuron::Neuron(double current):
    v(-70),
    isActive(true),
    spikes(0),
    spikes_times(),
    current_ext (current),
    steps_local (0),
    steps_refractory(0)
    {}

Neuron::~Neuron()
    {}

double Neuron::getV()
    {
        return v;
    }

void Neuron::setV(double new_v)
    {
        v = new_v;
    }

bool Neuron::getIsActive()
    {
        return isActive;
    }

void Neuron::setIsActive(bool isActive_)
    {
        isActive = isActive_;
    }

int Neuron::getSpikes()
    {
        return spikes;
    }

std::vector<int> Neuron::getSpikes_times()
    {
        return spikes_times;
    }

int Neuron::getLast_spike_time()
    {
        if(!spikes_times.empty())
            return spikes_times.back();
        else return 0;
    }

std::vector<double> Neuron::getPotentials_at_times()
    {
        return potentials_at_times;
    }

void Neuron::reset()
    {
        v = V_RESET;
        isActive = false;
        steps_refractory = 0;
    }

void Neuron::refractory()
    {
        if(!isActive)
        {
            if(steps_refractory==(int)(REFRACTORY_PERIOD/TIME_UNIT))
                setIsActive(true);
            ++steps_refractory;
        }
    }

void Neuron::calculate_potential()
    {
        v = (exp(-TIME_UNIT/TIME_CONST) * v) + ((1 - exp(-TIME_UNIT/TIME_CONST)) * current_ext * MEMBRANE_RES);
    }

void Neuron::spike()
    {
        ++spikes;
        spikes_times.push_back(steps_local);
    }

void Neuron::update(double current)
    {
        current_ext = current;
        calculate_potential();
        if(v>V_THR)
        {
            spike();
            reset();
        }
        refractory();
        potentials_at_times.push_back(v);
        ++steps_local;
    }
