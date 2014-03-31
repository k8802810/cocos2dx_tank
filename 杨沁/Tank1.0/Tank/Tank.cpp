//
//  Tank.cpp
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#include "Tank.h"
#include "Bullet.h"

Tank::Tank():mBulletDelta(0.0),mIsBlock(false)
{}

Tank::~Tank()
{}

//
//Tank* Tank::createTankWithTankType(const char* tankTypeName)
//{
//    CCSpriteFrameCache* pCache=CCSpriteFrameCache::sharedSpriteFrameCache();
//    pCache->addSpriteFramesWithFile("tank.plist");
//    
//    Tank* tank=new Tank();
//    tank->initWithSpriteFrameName(tankTypeName);
//    tank->autorelease();
//    return tank;
//}

void Tank::remove()
{
    mTileMapInfo->getTileMap()->removeChild(this);
}

//通过控制手柄产生的命令控制坦克移动
bool Tank::command(enumOrder order)
{
    float stepX=0.0f;
    float stepY=0.0f;
    float fRotation=getRotation();
    //static float fRotation=0.0f;
    
    switch (order) {
        case cmdNothing:
            break;
        case cmdGoUP:
            stepY=1.0f;
            fRotation=0.0f;
            break;
        case cmdGoDown:
            stepY=-1.0f;
            fRotation=180.0f;
            break;
        case cmdGoLeft:
            stepX=-1.0f;
            fRotation=270.0f;
            break;
        case cmdGoRight:
            stepX=1.0f;
            fRotation=90.0f;
            break;
        case cmdFire:
            //调用子弹开火
            return mBullet->fire();
            
            
        default:
            break;
    }
    
    //setPositionX(getPositionX()+stepX);
    //setPositionY(getPositionY()+stepY);
    setRotation(fRotation);
    
    //检测地图上的碰撞
    CCRect rect=this->boundingBox();
    mMovedRect.setRect(rect.getMinX()+stepX,rect.getMinY()+stepY, rect.size.width,rect.size.height);
    if (!mTileMapInfo->collisionTest(mMovedRect)) {
        setBlock(false);
        return true;
    }
    setBlock(true);
    
//    if (!mTileMapInfo->collisionTest(CCRectMake(rect.getMinX()+stepX, rect.getMinY()+stepY, rect.size.width, rect.size.height))) {
//        setPositionX(getPositionX()+stepX);
//        setPositionY(getPositionY()+stepY);
//        return true;
//    }
    return false;
}

//在坦克中使用这个指针来检测是否碰撞。
void Tank::initTankWithTankType(const char* tankTypeName,TileMapInfo* tileMapInfo)
{
    initWithSpriteFrameName(tankTypeName);
    mTileMapInfo=tileMapInfo;
    
    //将坦克放入地图层中
    mTileMapInfo->getTileMap()->addChild(this);
    
    //缩放到合适的大小
    CCTMXTiledMap* tmxTileMap=mTileMapInfo->getTileMap();
    CCSize tileSize=tmxTileMap->getTileSize();
    CCSize tankSize=getContentSize();
    //比地图上砖块小一点
    setScale((tileSize.height*2-4)/(tankSize.height));
    
    //初始化坦克的子弹
    mBullet = Bullet::createBulletWithTank(this);
}

//来返回一个Tank实例
//可以看到我们添加了plist文件，然后从中加载了tankTypeName类型的Tank精灵，然后初始化，最后加入自动释放列表。
Tank* Tank::createTankWithTankType(const char* tankTypeName,TileMapInfo* tileMapInfo)
{
    CCSpriteFrameCache* pCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile("tank.plist");
    
    Tank* tank=new Tank();
    tank->initTankWithTankType(tankTypeName, tileMapInfo);
    tank->autorelease();
    return tank;
}

void Tank::move()
{
    setPosition(ccp(mMovedRect.getMidX(), mMovedRect.getMidY()));
}

void Tank::setBlock(bool isBlock)
{
    mIsBlock=isBlock;
    if (mIsBlock==true) {
        mMovedRect=boundingBox();
    }
}

bool Tank::getBlock()
{
    return mIsBlock;
}
