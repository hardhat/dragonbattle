#ifndef ACTOR_H
#define ACTOR_H

#include <deque>

#include "sprite.h"
#include "bullet.h"
#include "notice.h"

typedef std::deque<Bullet *> BulletList;
typedef std::deque<Notice *> NoticeList;

class Actor {
public:
	int health;
	int fullHealth;
	AttackType attackType;
	int attackTimer;
	int attackRegenerateTime;

	int resistance[6];	// percent of how resistent they are to various attacks

	AttackType blockType;
	int blockTimer;
	int blockRegenerateTime;
	bool enemy;
	Sprite *avatar;	
	Sprite *avatarDead;
	Sprite *shield;
	
	BulletList bulletList;
	NoticeList noticeList;
	
	Actor();
	virtual ~Actor();
	virtual void resetGame();
	virtual void update(int elapse);
	virtual void draw();

	bool isAlive();
	bool isAttackReady();
	void attack(Actor *target,bool heavy);
	void receiveAttack(int amount, AttackType type);
	void block(AttackType type);
};

#endif
