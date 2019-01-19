#include <stdio.h>

#include "main.h"
#include "actor.h"
#include "sound.h"

Actor::Actor()
{
	//printf("Actor::Actor()\n");

	attackType=AT_FORCE;
	fullHealth=100;
	attackRegenerateTime=2000;

	for(int i=0;i<6;i++) {
		resistance[i]=0;	// percent of how resistent they are to various attacks
	}
	
	blockType=AT_NONE;
	blockRegenerateTime=2000;
	enemy=false;
	avatar=NULL;
	avatarDead=NULL;
	shield=NULL;
}

void Actor::resetGame()
{
	blockTimer=0;
	attackTimer=0;
	health=fullHealth;
	
	for(BulletList::iterator p=bulletList.begin();p!=bulletList.end();p++) {
		Bullet *b=*p;
		delete b;
	}
	bulletList.clear();
	
	for(NoticeList::iterator p=noticeList.begin();p!=noticeList.end();p++) {
		Notice *n=*p;
		delete n;
	}
	noticeList.clear();
	
}

Actor::~Actor()
{
}

void Actor::update(int elapsed)
{
	if(attackTimer>=elapsed) attackTimer-=elapsed; else attackTimer=0;
	if(blockTimer>=elapsed) blockTimer-=elapsed; else blockTimer=0;

	bool deadBullet=false;
	for(BulletList::iterator p=bulletList.begin();p!=bulletList.end();p++) {
		Bullet *b=*p;
		b->update(elapsed);
		if(!b->isActive()) deadBullet=true;
	}
	if(deadBullet) {
		BulletList list=bulletList;
		bulletList.clear();
		for(BulletList::iterator p=list.begin();p!=list.end();p++) {
			Bullet *b=*p;
			if(b->isActive()) {
				bulletList.push_back(b);
			} else {
                b->target->receiveAttack(b->damage,b->attackType);
				delete b;	// all done.
			}
		}
	}
	
	bool deadNotice=false;
	for(NoticeList::iterator p=noticeList.begin();p!=noticeList.end();p++) {
		Notice *n=*p;
		n->update(elapsed);
		if(!n->isActive()) deadNotice=true;
	}
	if(deadNotice) {
		NoticeList list=noticeList;
		noticeList.clear();
		for(NoticeList::iterator p=list.begin();p!=list.end();p++) {
			Notice *n=*p;
			if(n->isActive()) {
				noticeList.push_back(n);
			} else {
				delete n;	// all done.
			}
		}
	}
}

void Actor::draw()
{
	//printf("%s: %d HP, %d ATK, %d BLK\n",enemy?"Dragon":"Player",health,attackTimer,blockTimer);
	//printf("blockRegenerateTime=%d, attackRegenerateTime=%d\n",blockRegenerateTime, attackRegenerateTime);

	if(blockTimer>0 && shield) {
		shield->draw();
	}
	if(health>0 && avatar) {
		avatar->draw();
	} else if(health==0 && avatarDead) {
		avatarDead->draw();
	}
	for(BulletList::iterator p=bulletList.begin();p!=bulletList.end();p++) {
		Bullet *b=*p;
		b->draw();
	}
	for(NoticeList::iterator p=noticeList.begin();p!=noticeList.end();p++) {
		Notice *n=*p;
		n->draw();
	}
}

bool Actor::isAlive() {
	return health>0;
}

bool Actor::isAttackReady() {
	if(health==0) return false;
	return attackTimer<=0;
}

void Actor::attack(Actor *target, bool heavy) {
	if(health==0) return;
	if(attackTimer==0 && blockTimer==0) {
		//printf("%s: is attacking with a %s attack of type %d\n",enemy?"Dragon":"Player",heavy?"heavy":"light",(int)attackType);

		//target->receiveAttack(heavy?10:5,attackType);
		attackTimer=attackRegenerateTime*(heavy?2:1);
		//printf("Attack active for %d ms.\n",attackTimer);
		float sx=0,sy=0,tx=0,ty=0;
		if(avatar) {
			sx=avatar->x;
			sy=avatar->y;
		}
		if(target->avatar) {
			tx=target->avatar->x;
			ty=target->avatar->y;
		}
		bulletList.push_back(new Bullet(attackType,sx+16,sy,tx,ty,attackRegenerateTime*(heavy?2:1),target,heavy?10:5));
	}
}

void Actor::receiveAttack(int amount, AttackType type) {
	float sx=0,sy=0;
	if(avatar) {
		sx=avatar->x;
		sy=avatar->y;
	}

	if(health==0) return;	// already dead.

	if(blockTimer==0) {
		health-=amount;
		if(health<0) health=0;
		//printf("%s: Received attack of %d and type %d.  %d HP remaining.\n",enemy?"Dragon":"Player",amount,(int)type,health);
		if(health==0) {
			if(!enemy) sound.playOnce(SFX_DIE);
			noticeList.push_back(new Notice(sx,sy,"Dead"));
		} else {
			static int ugh=0;
			std::string message=std::to_string(-amount);
			noticeList.push_back(new Notice(sx,sy,message.c_str()));
			if(enemy) {
				sound.playOnce(SFX_ZAP);
			} else {
				sound.playOnce(ugh!=0?ugh==2?SFX_UGH1:SFX_UGH2:SFX_UGH3);
				ugh=(ugh+1)%3;
			}
		}
	} else {
		//printf("%s: Blocked attack.\n",enemy?"Dragon":"Player");
		sound.playOnce(SFX_HAH);
		noticeList.push_back(new Notice(sx,sy,"Blocked"));		
	}
}

void Actor::block(AttackType type) {
	if(health==0) return;

	//printf("Block requested.\n");
	if(blockTimer==0 && attackTimer==0) {
		blockType=type;
		blockTimer=blockRegenerateTime;
		//printf("Block active for %d ms.\n",blockTimer);
	}
}
