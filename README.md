# ECE520 Final Project

ENVIRO BASED CAPTURE THE FLAG
===

Goal: For my final project for ECE520, I will be building a 2D capture the flag game with novel game play dynamics. This repo is a prototype of the game that demonstrates the key aspects of the game play.

This game is very much like a traditonal capture the flag game with some novel game play dynamics. 

Like a traditional capture the flag game there are: 
- Individual flags that need to be captured by colliding the player into them. The flags are placed such that the players will need to cross paths to collect the flags, to increase conflict. 
- A goal to bring the flag to score points. 

Some novel game play dynamics in this game are: 
- Players do not have a life bar but instead are eliminated by getting pushed off the edge similar to a platformer type game. 
- Players make use of water streams to push the opponent off the edge and deter their progress. 
- Players can also bring up walls as protection from the water streams

Challenges 
=== 
One of the primary challenges of making the game was just making sure that movement was controllable and predictable. I tried using apply_force() initially but it proved to be hard to control. The track_velocity() function worked better in controlling linear velocity, but turning was still a bit tough to control. It turns out the trick was just to dampen the turning by adding more rotational friction to the agent defition. 

It also took some time tuning the water balls to make a powerful enough stream to make the game a little more entertaining. It turns out game balancing is very time consuming and difficult! 

Another challenge was to get the multi player working. I first tried using multiple agents with a coordinator much like in the provided example, but this proved difficult to test with just one environment. Instead I created two separate agents that used the same keyboard. This kind of set up is very similar to the old school 2d scroller blaster games. 

Installation and Running the Code
=== 
```bash 
git clone https://github.com/basikthings/ENVIRO_CPTR_THE_FLAG_BLSTR.git
cd ENVIRO_CPTR_THE_FLAG_BLSTR
```

Navigate to the folder on a command line and enter 

```bash 
docker run -p80:80 -p8765:8765 -v $PWD/:/source -it klavins/enviro:v1.6 bash
```

This will start a container environment using Docker provided by Professor Klavins

```bash 
make
esm start
enviro
```
Open a web browser and navigate to: 
```html 
localhost
```
Enjoy! 

Gamplay
===
Capture the Flag Agents
---
- ***player***: Is the character that the user controls using a D pad spanned by {w,a,s,d} or {i,j,k,l}. The players can also shoot a stream of water by holding down {f} or {;} respectively for the two players. The players can also put up high mass walls on either side to block the opponents stream of water {c,t} or [.,[} respectively.  

- ***flag***: The player needs to run into the flag to capture it. 

- ***goal***: The player needs to run into the goal to earn a point. A point is only earned when the player runs into the goal while having a flag captured. 

- ***water***: Water is shot from each of the players. There's a bit of bending the laws of physics here, but the water is made to weigh nearly the same as the mass of the player. This gives each player the ability to use their own water stream to push the opposing players. 

- ***wall***: Walls can be dropped by the players as a way to protect against opposing player  water streams or to use a way to deflect your own water stream. 

- ***map_end***: The four walls of the map are elimination zones that brings the players back to their respective bases. Players compete to push each other into the map_ends to impede the opponents progress. 


<img src = "https://github.com/basikthings/ENVIRO_CPTR_THE_FLAG_BLSTR/tree/master/images/gameplay.png">