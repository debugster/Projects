#ifndef ATM_SIMULATION_DEPOSITSLOT_H
#define ATM_SIMULATION_DEPOSITSLOT_H

class DepositSlot {
public:
    bool isEnvelopeReceived();
};

bool DepositSlot::isEnvelopeReceived() {
    /// indicates whether envelope was received
    /// (always returns true, because this is only a software simulation of a real deposit slot)
    return true;
}

#endif //ATM_SIMULATION_DEPOSITSLOT_H
