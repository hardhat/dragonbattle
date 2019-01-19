#include <stdio.h>

#include "main.h"
#include "player.h"

Player::Player()
{
	//printf("Player::Player()\n");
	//resetGame();
}

void Player::resetGame()
{
	Actor::resetGame();
	avatar=new Sprite("player.png");
	avatar->x=screenw/2;
	avatar->y=screenh-24;

	shield=new Sprite("playershield.png");
	shield->x=screenw/2;
	shield->y=screenh-24;

	avatarDead=new Sprite("playerdead.png");
	avatarDead->x=screenw/2;
	avatarDead->y=screenh-24;
}

void Player::update(int elapsed)
{
	Actor::update(elapsed);
}

void Player::draw()
{
	Actor::draw();
}