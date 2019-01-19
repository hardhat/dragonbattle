#include <stdio.h>

#include "main.h"
#include "dragon.h"
#include "sound.h"

Dragon::Dragon() {
	//printf("Dragon::Dragon()\n");
	fullHealth=600;	
	enemy=true;
	attackRegenerateTime=500;
	mode=0;
	//resetGame();
}
	
void Dragon::resetGame() {
	Actor::resetGame();
	attackType=AT_FIRE;
	static bool skipOnce=false;
	if(skipOnce)
		sound.playOnce(SFX_WELCOME);
	skipOnce=true;
#if 1
	avatar=new Sprite("reddragon.png");
	avatar->x=screenw/2;
	avatar->y=24;
	avatarDead=new Sprite("reddragondead.png");
	avatarDead->x=screenw/2;
	avatarDead->y=24;
#endif
	mode=0;
}

void Dragon::update(int elapsed) {
	Actor::update(elapsed);
	
	if(health<fullHealth && isAttackReady()) {
		// if it is time attack, then we attack.
		Actor *player=game.getNextPlayer();
		int count=game.getPlayerCount();

		attack(player,mode<6);
		mode++;
		if(mode>=count*2) mode=0;
		if(count<6 && mode>=6) mode=0;
	}
}

void Dragon::draw() {
	Actor::draw();
}
