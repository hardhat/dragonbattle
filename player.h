#ifndef PLAYER_H
#define PLAYER_H
#include "actor.h"

class Player : public Actor {
	
public:
	Player();
	virtual void resetGame();
	virtual void update(int elapsed);
	virtual void draw();
};

#endif
