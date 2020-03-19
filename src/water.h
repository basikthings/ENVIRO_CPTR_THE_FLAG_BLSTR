#ifndef __WATER_AGENT__H
#define __WATER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class WaterController : public Process, public AgentInterface {

    public:
    WaterController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        notice_collisions_with("map", [&](Event &e) {
            remove_agent(id());
        });           
    }
    void start() {}
    void update() {
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Water : public Agent {
    public:
    Water(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WaterController c;
};

DECLARE_INTERFACE(Water)

#endif