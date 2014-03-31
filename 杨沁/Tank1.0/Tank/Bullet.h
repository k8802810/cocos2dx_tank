//
//  Bullet.h
//  Tank
//
//  Created by zyf on 14-2-20.
//
//

#ifndef __Tank__Bullet__
#define __Tank__Bullet__

#include <iostream>
#include "cocos2d.h"
#include "Tank.h"
using namespace cocos2d;

class Bullet : public CCSprite
{
public:
	Bullet();
	~Bullet();
    
	static Bullet* createBulletWithTank(Tank* tank);
	void initBulletWithTank(Tank* tank);
	bool fire();
    bool stopFire();
	virtual void update(float delta);
	void bulletBoom();
    
private:
	//bool isFlying;
	Tank* mTank;
	TileMapInfo* mTileMapInfo;
	float stepX, stepY;
    /////
    void gameover();
    /////

    CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
    CC_SYNTHESIZE(bool, IsBlock, BLock);
    CC_SYNTHESIZE(bool, mFlyState, FlyState);
};

#endif /* defined(__Tank__Bullet__) */
