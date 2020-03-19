#ifndef __WALL_AGENT__H
#define __WALL_AGENT__H 

#include "enviro.h"

using namespace enviro;

//! Walls are used to deflect and block the water
class WallController : public Process, public AgentInterface {

    public:
    WallController() : Process(), AgentInterface(), counter(0) {}

    void init() {             
    }
    void start() {}

    //! The walls last for 100 counts of updates
    void update() {
        if ( counter++ > 100 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Wall : public Agent {
    public:
    Wall(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WallController c;
};

DECLARE_INTERFACE(Wall)

#endif