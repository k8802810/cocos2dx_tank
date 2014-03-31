//
//  Tank.h
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#ifndef __Tank__Tank__
#define __Tank__Tank__

#include <iostream>
#include "Panel.h"
#include "TileMapInfo.h"
#include "cocos2d.h"

using namespace cocos2d;

class Bullet;

class Tank:public CCSprite {
    
public:
    Tank();
    ~Tank();
    
    static Tank* createTankWithTankType(const char* tankTypeName,TileMapInfo* tileMapInfo);
    void initTankWithTankType(const char* tankTypeName,TileMapInfo* tileMapInfo);
    void remove();
    bool command(enumOrder order);
    void move();//根据是否阻塞来控制坦克移动
    void setBlock(bool isBlock);
    bool getBlock();
private:
    bool mIsBlock;
	//Bullet* mBullet;
	CC_SYNTHESIZE(Bullet*, mBullet, Bullet);
    CC_SYNTHESIZE(TileMapInfo*, mTileMapInfo, TileMapInfo);
    CC_SYNTHESIZE(float, mBulletDelta, BulletDelta);
    //mMovedRect是移动后的位置，目的是保存移动后的位置来检测碰撞，
    //如果发现与其他坦克碰撞了，则不执行移动动作；
    CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
    //IsBlock是用来标记坦克是否被碰撞的
    //CC_SYNTHESIZE(bool, IsBlock, Block);
};


#endif /* defined(__Tank__Tank__) */
