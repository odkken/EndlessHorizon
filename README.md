EndlessHorizon
==============

Platformer based on c++ game from scratch PANG tutorial (sfml)

Need to redo this with an improved object manager, to handle all game object types
correctly (need to circumvent the current casts to subclasses of VisibleGameObject).
Could improve collision and rendering performance by partitioning world into a grid,
and look into multithreading the different loops (update/events/draw).

World initialization should take place somewhere other than game.cpp, but the entire
thing should probably be restructured using a State design pattern.
