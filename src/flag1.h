#ifndef __FLAG_AGENT__H
#define __FLAG_AGENT__H 

#include "enviro.h"

using namespace enviro;

//! Flag1 is the flag for player one. This uses the standard template from esm generate. 
class flagController : public Process, public AgentInterface {

    public:
    flagController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class flag : public Agent {
    public:
    flag(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    flagController c;
};

DECLARE_INTERFACE(flag)

#endif