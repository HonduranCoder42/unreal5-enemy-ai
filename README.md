# unreal5-enemy-ai
**Senior College Project for Game Development Capstone.**\
\
This is the code written for AI of the main enemy (Charlie) and the director for the game Dread Not.\
\
The Charlie folder contains the Code for the Charlie AI, the Patrol Path that Charlie follows, and a couple 
Behavior Tree tasks which are used in the behavior tree made for Charlie in Blueprint.\
\
The Director folder contains the code for the Director AI (still in development), which is a simple AI that intermitenly checks on the current state of 
the game and adjusts some of Charlie's values accordingly. This is to help balance Charlie's difficulty mid-game. At this moment only the
number of damaged rooms are taken into account for difficulty adjustment, but the amount of time left and the current health of the submarine
will be taken into account in the future.
