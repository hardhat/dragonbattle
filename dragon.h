#ifndef DRAGON_H
#define DRAGON_H

#include "actor.h"

class Dragon : public Actor
{
private:
	int mode;
public:
	Dragon();
	virtual void resetGame();
	void resetGame(int playerCount);
	virtual void update(int elapsed);
	virtual void draw();
};

#endif
