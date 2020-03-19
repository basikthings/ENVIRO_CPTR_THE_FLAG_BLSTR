#ifndef __MAP_END_AGENT__H
#define __MAP_END_AGENT__H 

#include "enviro.h"

using namespace enviro;

class mapEndController : public Process, public AgentInterface {

    public:
    mapEndController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {
        damp_movement();
    }
    void stop() {}

};

class mapEnd : public Agent {
    public:
    mapEnd(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    mapEndController c;
};

DECLARE_INTERFACE(mapEnd)

#endif