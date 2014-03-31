//
//  Bullet.cpp
//  Tank
//
//  Created by zyf on 14-2-20.
//
//

#include "Bullet.h"
#include "TileMapInfo.h"
#include "GameOver.h"
#include "cocos2d.h"
using namespace cocos2d;

//isFlying指示子弹是否在飞行中，初始为false表示没有飞行。
Bullet::Bullet() :mFlyState(false)
{
}

Bullet::~Bullet()
{
}

/*在Bullet类中我们用mTank成员变量存储了他所属的坦克，
用mTIleMapInfo存储了他所属的地图。
用bullet.png精灵帧初始化了精灵。
然后把子弹加入了地图层中
然后把子弹设置为不可见。*/
void Bullet::initBulletWithTank(Tank* tank)
{
	mTank = tank;
	mTileMapInfo = mTank->getTileMapInfo();
	initWithSpriteFrameName("bullet.png");
    setScale(1.5/3.0);
    setVisible(false);
	mTileMapInfo->getTileMap()->addChild(this);
	
}

//创建一个Bullet类实例，然后用tank参数初始化，
Bullet* Bullet::createBulletWithTank(Tank* tank)
{
	Bullet* bullet = new Bullet();
	bullet->initBulletWithTank(tank);
	bullet->autorelease();
    
	return bullet;
}


/*可以看到，先判断子弹是否在飞行中，如果不在飞行中被调用了，
则先设置飞行状态isFlying为飞行中。
然后设置子弹初始位置为坦克所在的位置，
然后根据坦克旋转的方向，来设置子弹的运行方向分量——stepX和stepY。
最后调用scheduleUpdate()启动update定时器。这样显示每一帧动画的时候，
就会调用我们的update()函数。*/
bool Bullet::fire()
{
	if (!mFlyState)
	{
		mFlyState = true;
		setVisible(true);
		setPosition(mTank->getPosition());
		//设置子弹运行方向
		int Rotation = mTank->getRotation();
		switch (Rotation)
        {
            case 0:
                stepX = 0.0f, stepY = 2.0f;
                break;
            case 90:
                stepX = 2.0f, stepY = 0.0f;
                break;
            case 180:
                stepX = 0.0f, stepY = -2.0f;
                break;
            case 270:
                stepX = -2.0f, stepY = 0.0f;
                break;
            default:
                break;
		}
		scheduleUpdate();
        return true;
	}
    
	return false;
}

bool Bullet::stopFire()
{
    if (mFlyState==true) {
        mFlyState=false;
        setVisible(false);
        unscheduleUpdate();
        return true;
    }
    return false;
}

/*上面先设置了子弹根据分量stepX和stepY移动后的位置。
然后获取自己在地图上的CCRect，然后传入地图信息类中的碰撞检测函数。
如果碰撞了，就调用unscheduleUpdate()来取消update()定时器，
然后设置子弹为不可见，飞行状态设置为false，调用bulletBoom()来引爆子弹。*/
void Bullet::update(float delta)
{
	CCSprite::update(delta);
	
    mMovedRect=boundingBox();
    mMovedRect.origin.x+=stepX;
    mMovedRect.origin.y+=stepY;
    
    //设置移动后的位置
	setPosition(ccp(getPositionX() + stepX, getPositionY() + stepY));
    
	//检测是否有碰撞
	CCRect rect = boundingBox();
	if (mTileMapInfo->collisionTest(rect))
	{
        stopFire();
//		unscheduleUpdate();
//		setVisible(false);
//		mFlyState = false;
		//引爆子弹
		bulletBoom();
	}
}

/*先获取了自己的位置rect和地图的尺寸mapSIze。
首先判断了自己是否跑到了地图外边。如果在地图外边就直接返回。
然后获取了layer_0层的地图信息，将屏幕中的Y轴转换成tmx地图中的Y轴，
然后判断子弹四个角所接触的图块，如果图块是墙壁，那么获取墙壁的GID都设置成tileNone，这样就相当于炸毁墙壁图块。*/
void Bullet::bulletBoom()
{
	CCRect rect = boundingBox();
	CCSize mapSize = mTileMapInfo->getTileMap()->getContentSize();
    
	if (rect.getMinX() < 0 || rect.getMaxX() >= mapSize.width ||
		rect.getMinY() < 0 || rect.getMaxY() >= mapSize.height)
		return ;
    
	CCTMXLayer* tmxLayer = mTileMapInfo->getTileMap()->layerNamed("layer_0");
	CCSize tileSize = tmxLayer->getMapTileSize();
    
	//调整Y轴位tmx地图中的Y轴
	float MinY = mapSize.height - rect.getMinY();
	float MaxY = mapSize.height - rect.getMaxY();
    
	//将与子弹碰撞的墙壁tileWall图块删除
	CCPoint pt = ccp((int)(rect.getMinX() / tileSize.width),(int)(MinY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    /*****************************************///击中司令部
    if (gidToTileType[tmxLayer->tileGIDAt(pt)]==tileKing)
        gameover();
        //tmxLayer->setTileGID(gidToTileType[tileDiedKing], pt);
    /*****************************************/
    
	pt = ccp((int)(rect.getMinX() / tileSize.width),(int)(MaxY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    /*****************************************///击中司令部
    if (gidToTileType[tmxLayer->tileGIDAt(pt)]==tileKing)
        gameover();
        //tmxLayer->setTileGID(gidToTileType[tileDiedKing], pt);
    /*****************************************/
    
	pt = ccp((int)(rect.getMaxX() / tileSize.width),(int)(MinY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    /*****************************************///击中司令部
    if (gidToTileType[tmxLayer->tileGIDAt(pt)]==tileKing)
        gameover();
        //tmxLayer->setTileGID(gidToTileType[tileDiedKing], pt);
    /*****************************************/
    
	pt = ccp((int)(rect.getMaxX() / tileSize.width),(int)(MaxY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    /*****************************************///击中司令部
    if (gidToTileType[tmxLayer->tileGIDAt(pt)]==tileKing)
        gameover();
        //tmxLayer->setTileGID(gidToTileType[tileDiedKing], pt);
    /*****************************************/
}

void Bullet::gameover()
{
    CCScene* scene=GameOver::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}