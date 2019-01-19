#ifndef GAME_H
#define GAME_H

#include <deque>

#include "sprite.h"
#include "player.h"
#include "dragon.h"

typedef std::deque<Player *> PlayerList;

class Game 
{
public:
	Dragon dragon;
	PlayerList player;
	bool gameOver;
	bool victory;
	Sprite *background;

	PlayerList::iterator currentPlayer;
	
	Game();
	void resetGame();
	void update(int elapsed);
	void draw();
	void handleAction(int id,bool down);
	Actor *getNextPlayer();
	int getPlayerCount();
};

#endif
