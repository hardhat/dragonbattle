#include <SDL.h>
#include "main.h"
#include "game.h"
#include "player.h"
#include "font.h"
#include "sound.h"

Game game;

Game::Game() {
	background=NULL;
	gameOver=false;
	victory=false;
}

void Game::resetGame() {
	gameOver=false;
	victory=false;
	dragon.resetGame();
	while(player.size()<6) {
		Player *pl=new Player();
		player.push_back(pl);
	}
	while(player.size()>6) {
		Player *pl=player.front();
		player.pop_front();
		delete pl;
	}
	for(PlayerList::iterator p=player.begin();p!=player.end();p++) {
		Player *pl=*p;
		pl->resetGame();
	}
	currentPlayer=player.begin();
}

void Game::update(int elapsed) {
	// Update level
	if(gameOver==true) return;
	
	// update dragon
	dragon.update(elapsed);
	if(!dragon.isAlive()) {
		gameOver=true;
		victory=true;	
		sound.playOnce(SFX_WIN);
		return;
	}
	
	// update players
	int living=0;
	for(PlayerList::iterator p=player.begin();p!=player.end();p++) {
		Player *pl=*p;
		pl->update(elapsed);
		if(pl->isAlive()) {
			living++;
		}
	}
	if(living==0) {
		gameOver=true;
		victory=false;
		sound.playOnce(SFX_LOSE);
	}
}

void Game::draw() {
	// Draw background
	if(!background)	background=new Sprite("fossil_cave320.jpg");
	if(background) {
		background->x=screenw/2;
		background->y=screenh/2;
		background->draw();
	}
	
	// draw dragon
	dragon.draw();
	
	
	int x=screenw/2-16*player.size();
	// draw players
	for(PlayerList::iterator p=player.begin();p!=player.end();p++) {
		Player *pl=*p;
		
		if(pl->avatar) pl->avatar->x=x;
		if(pl->avatarDead) pl->avatarDead->x=x;
		if(pl->shield) pl->shield->x=x;
		x+=32;
		pl->draw();
	}
	
	if(gameOver) {
		const char *message;
		if(victory) {
			message="Players Win!";
		} else {
			message="Players Lose.";
		}
		drawMessage(FONT_HEADLINE,message,10,80);
	}
}

void Game::handleAction(int id,bool down) {
	if(id==13 || id==10 || id==SDLK_KP_ENTER) {
		resetGame();
	}
	if(down) {
		switch (id) {
		case 'a':
			player[0]->attack(&game.dragon,false);
			break;
		case 'b':
			player[1]->attack(&game.dragon,false);
			break;
		case 'c':
			player[2]->attack(&game.dragon,false);
			break;
		case 'd':
			player[3]->attack(&game.dragon,false);
			break;
		case 'e':
			player[4]->attack(&game.dragon,false);
			break;
		case 'f':
			player[5]->attack(&game.dragon,false);
			break;
		case 'A':
			player[0]->attack(&game.dragon,true);
			break;
		case 'B':
			player[1]->attack(&game.dragon,true);
			break;
		case 'C':
			player[2]->attack(&game.dragon,true);
			break;
		case 'D':
			player[3]->attack(&game.dragon,true);
			break;
		case 'E':
			player[4]->attack(&game.dragon,true);
			break;
		case 'F':
			player[5]->attack(&game.dragon,true);
			break;
		case '1':
			player[0]->block(AT_FIRE);
			break;
		case '2':
			player[1]->block(AT_FIRE);
			break;
		case '3':
			player[2]->block(AT_FIRE);
			break;
		case '4':
			player[3]->block(AT_FIRE);
			break;
		case '5':
			player[4]->block(AT_FIRE);
			break;
		case '6':
			player[5]->block(AT_FIRE);
			break;
		default:
			break;
		}
	}
}

Actor *Game::getNextPlayer()
{
	if(player.size()==0) return NULL;	// everyone is dead.
	if(currentPlayer==player.end()) {
		currentPlayer=player.begin();
	}
	Player *pl=*currentPlayer;
	currentPlayer++;
	return pl;
}

int Game::getPlayerCount()
{
	int count=0;
	for(PlayerList::iterator p=player.begin();p!=player.end();p++) {
		Player *pl=*p;
		if(pl->isAlive()) count++;
	}
	return count;
}
