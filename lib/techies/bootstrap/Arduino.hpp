#include <bootstrap/Bootstrap.hpp>

#define BMain() \
    BProgram(); \
    void setup() { techies::bootstrap::Init<BOOTSTRAP_PROGRAM_TYPE>(&BOOTSTRAP_PROGRAM); }; \
    void loop() { techies::bootstrap::Yield<BOOTSTRAP_PROGRAM_TYPE>(&BOOTSTRAP_PROGRAM); };
