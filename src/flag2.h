#ifndef __FLAG2_AGENT__H
#define __FLAG2_AGENT__H 

#include "enviro.h"

using namespace enviro;

//! Flag2 is the flag for player one. This uses the standard template from esm generate. 
class flag2Controller : public Process, public AgentInterface {

    public:
    flag2Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class flag2 : public Agent {
    public:
    flag2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    flag2Controller c;
};

DECLARE_INTERFACE(flag2)

#endif