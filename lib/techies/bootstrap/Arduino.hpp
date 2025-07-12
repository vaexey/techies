// File contains definitions - should only be included once
#include "techies.hpp"

// Components
techies::components::PrintLogger DefaultLogger(&Serial);

// Data types
struct DataState : public techies::core::State
{
    bool blink = false;
    techies::modules::TON ton;
    techies::modules::TOF tof;

    static void Cycle(const DataState* Old, DataState* New)
    {
        CycleFor(ton, !Old->blink, 500);
        CycleFor(tof, New->ton.Q, 500);
        New->blink = New->tof.Q;

        New->QX[0] = New->blink;
    }
};
techies::core::Program<DataState> Program;

// Bootstrap functions
void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);
    L = &DefaultLogger;
    L->Info("Booting techies...");
}

void loop()
{
    Program.Yield();
}