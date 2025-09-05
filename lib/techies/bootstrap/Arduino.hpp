#include <bootstrap/Bootstrap.hpp>

#define BMain() \
    BProgram(); \
    void setup() BInit() \
    void loop() BYield()
