#ifndef __PLAYER1_AGENT__H
#define __PLAYER1_AGENT__H 

#include "enviro.h"
#include <stdio.h>

using namespace enviro;

//! Player1 is one of the players and is controlled using 'w' 'a' 's' 'd' 'c' 'f' 't' 
class Player1Controller : public Process, public AgentInterface {

    public:
    Player1Controller() : Process(), AgentInterface(), v(0), omega(0), firing(false), flag_state(MISSING) {}

    //! Initializes the agent iwth watchers to look for the keystroke events and collision events. 
    void init() {

        //! Watcher that executes when down stroke of a key press
        //! Conditional statements are used to set internal controller parameters
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "f" ) {
                firing = true;
            } else if (k=="c" && !walling_left){
                Agent& wall = add_agent("Wall", 
                    x() + 17*cos(angle()-PI_DEF/2), 
                    y() + 17*sin(angle()-PI_DEF/2), 
                    angle(), WATER_STYLE);
                wall.apply_force(70000,0);
                walls.push_front(wall);  
                walling_left = true; 
                if(walls.size()>max_wall){
                    remove_agent(walls[max_wall].get_id());
                }
            } else if (k=="t" && !walling_right){
                Agent& wall = add_agent("Wall", 
                    x() + 17*cos(angle()+PI_DEF/2), 
                    y() + 17*sin(angle()+PI_DEF/2), 
                    angle(), WATER_STYLE);
                wall.apply_force(70000,0);
                walls.push_front(wall);  
                walling_right = true; 
                if(walls.size()>max_wall){
                    remove_agent(walls[max_wall].get_id());
                }
            } else if ( k == "w" ) {
                v = vel_magnitude;              
            } else if ( k == "s" ) {
                v = -vel_magnitude;  
            } else if ( k == "a" ) {
                omega = -rot_magnitude;
            } else if ( k == "d" ) {
                omega = rot_magnitude;
            } 
        });       

        //! Watcher that executes when on the upstroke of a key press
        //! Conditional statements are used to set internal controller parameters
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "f" ) {
                firing = false;
            } else if ( k == "c" ) {
                walling_left = false;
            } else if ( k == "t" ) {
                walling_right = false;
            } else if ( k == "w" || k == "s" ) {
                v = 0;               
            } else if ( k == "a" ) {
                omega = 0;
            } else if ( k == "d" ) {
                omega = 0;
            } 
        });

        //! When the Player collides with the perimeter, the Player respawns back in the original position. 
        notice_collisions_with("map_end", [&](Event &e) {
            if (flag_state == CAPTURED){
                flag_state = MISSING; 
            }
            teleport(-700,0,0);
            decorate(""); 
        }); 

        //! When Player collides with the flag, 
        //! Flag is removed 
        //! Flag_state is set to captured 
        //! Player is decorated to indicate that a flag is captured         
        notice_collisions_with("flag1", [&](Event &e) {
            decorate("<circle x='-5' y='5' r='5' style='fill: green'></circle>");
            int flag_id = e.value()["id"];
            remove_agent(flag_id);
            flag_state = CAPTURED; 
        }); 

        //! When Player collides with the goal, 
        //! and the player has a flag 
        //! then a point is scored.
        notice_collisions_with("goal", [&](Event &e) {
            decorate(""); 
            int flag_id = e.value()["id"];
            if (flag_state == CAPTURED){
                score++; 
                flag_state = MISSING; 
            }
        }); 
           
    }

    void start() {}

    void update() {
        //! If the flag is not held by the player or set in the intial position 
        //! Create a new flag at the origin. 
        if (flag_state == MISSING){
            Agent& a = add_agent("flag1", 300, 0, 0, {{"fill","skyblue"},{"stroke","black"}});
            flag_state = SET; 
        }

        //! Adds three water blobs and provides a force to get them moving
        if (firing){
            Agent& water = add_agent("water", 
                            x() + 25*cos(angle()), 
                            y() + 25*sin(angle()), 
                            angle(), 
                            WATER_STYLE);    
                            water.omni_apply_force(1200*cos(angle()),1200*sin(angle()));
            
            Agent& water2 = add_agent("water", 
                            x() + 18*cos(angle()-0.3), 
                            y() + 18*sin(angle()-0.3), 
                            angle(), 
                            WATER_STYLE);    
                            water2.omni_apply_force(1200*cos(angle()),1200*sin(angle()));

            Agent& water3 = add_agent("water", 
                            x() + 18*cos(angle()+0.3), 
                            y() + 18*sin(angle()+0.3), 
                            angle(), 
                            WATER_STYLE);    
                            water3.omni_apply_force(1200*cos(angle()),1200*sin(angle()));
        }
        
        //! Controls the velocity based on keystroke positions. 
        track_velocity(v,omega, 10, 10);

        label(std::to_string((int)score), 20, 20);

    }
    void stop() {}

    std::deque<Agent> walls; 
    int score; 
    int max_wall =4; 
    double v, omega;
    double const vel_magnitude = 50;
    double const rot_magnitude = 50;
    double const PI_DEF = 3.141592653589793238463;
    bool firing, walling_left, walling_right;
    typedef enum {
        SET, 
        CAPTURED,
        MISSING
    } flag_states ;
    flag_states flag_state;
    const json WATER_STYLE = { 
                   {"fill", "blue"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "0px"},
                   {"strokeOpacity", "0.25"}
               };

};

class Player1 : public Agent {
    public:
    Player1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    Player1Controller c;
    
};

DECLARE_INTERFACE(Player1)

#endif