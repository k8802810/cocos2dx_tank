//
//  EnemyAI.cpp
//  Tank
//
//  Created by zyf on 14-2-21.
//
//

#include "EnemyAI.h"
#include "Bullet.h"
#include "GameOver.h"

EnemyAI::EnemyAI()
{}

EnemyAI::~EnemyAI()
{}

//初始化了敌方坦克出身的三个地点，然后创建了一个容量为4的数组mEnemyTanks来存放敌方坦克对象。
void EnemyAI::initEnemyAIWithTank(Tank* tank)
{
    mTank=tank;
    mTileMapInfo=tank->getTileMapInfo();
    mEnemyTanks=CCArray::createWithCapacity(4);
    mEnemyTanks->retain();
    
    //初始化出现地点
    CCSize mapSize=mTileMapInfo->getTileMap()->getContentSize();
    CCSize tileSize=mTileMapInfo->getTileMap()->layerNamed("layer_0")->getMapTileSize();
    bornPoint[0]=ccp(tileSize.width, mapSize.height-tileSize.height);
    bornPoint[1]=ccp(mapSize.width/2, mapSize.height-tileSize.height);
    bornPoint[2]=ccp(mapSize.width-tileSize.width, mapSize.height-tileSize.height);
    
    score = 0;
    life = 3;
    
    endlessLife = false;
}

//静态方法返回EnmeyAI类指针：
EnemyAI* EnemyAI::createEnemyAIWithTank(Tank* tank)
{
    EnemyAI* enemyTank=new EnemyAI();
    enemyTank->initEnemyAIWithTank(tank);
    return enemyTank;
}

/*可以看到deltaTimes累加时间，超过2秒就开始添加坦克，初始三个坦克从固定位置添加，
然后第四个坦克随机位置添加。*/
void EnemyAI::addTank(float delta)//delta是每一帧调用之间的事件间隔
{
    static float deltaTimes=0.0f;
    deltaTimes+=delta;
    if (deltaTimes>=2.0f) {
        deltaTimes=0.0f;
        int count=mEnemyTanks->count();
        if (count<3)//先从固定位置添加三个坦克
        {
            Tank* enemyTank=Tank::createTankWithTankType(enemyTankType[count], mTileMapInfo);
            enemyTank->setPosition(bornPoint[count]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }
        else if(count==3)//第四个坦克随机添加
        {
            int tankTypeIndex=(int)(CCRANDOM_0_1()*4)%3;
            Tank* enemyTank=Tank::createTankWithTankType(enemyTankType[tankTypeIndex], mTileMapInfo);
            enemyTank->setPosition(bornPoint[tankTypeIndex]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }
    }
}

void EnemyAI::move()
{
    mTank->move();
    CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* tank=(Tank*)pObj;
        //如果坦克阻塞，换个方向
        if (tank->getBlock())
            tank->setRotation((int)(CCRANDOM_0_1()*3.8)*90);
        //如果上面的判断完成后，坦克根据自己的阻塞状态移动
        tank->move();
    }
}

//从mEnemyTanks中遍历坦克对象，然后向固定方向移动，遇到墙壁则随机换方向移动。
//在下面，子弹消失后，隔0.5秒再次发射子弹。
void EnemyAI::tankAction(float delta)
{
    CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* tank=(Tank*)pObj;
        
        //坦克自动移动，碰到墙壁自动换方向
        //CCRect rect =tank->boundingBox();//自己加的
        //if (mTileMapInfo->collisionTest(rect))//自己加的
        
        int Rotation=tank->getRotation();
        tank->command((enumOrder)(Rotation/90+1));
    
//        
//        if (!tank->command((enumOrder)(Rotation/90+1)))
//        {
//
//                int n=(int)(CCRANDOM_0_1()*5)%5;
//                if (n!=0)
//                    tank->command((enumOrder)n);
//        }
    
        
        //每隔一秒开一次火
        tank->setBulletDelta(tank->getBulletDelta()+delta);
        if (tank->getBulletDelta()>1) {
            //开火后，如果子弹在飞行中，归零记时
            if (tank->command(cmdFire)) {
                tank->setBulletDelta(0.0);
            }
        }
        
        //检测坦克之间的碰撞
        //collisionTest();
        
        //如果坦克阻塞，换个方向
        //if (tank->getBlock())
        //   tank->setRotation((int)(CCRANDOM_0_1()*3.2)*90);
        //如果上面的判断完成后，坦克根据自己的阻塞状态移动
        //tank->move();
    }
    //mTank->move();
    
    //检测坦克之间的碰撞
    collisionTest();
    move();
}

//在每一帧切换的时候被调用
void EnemyAI::update(float delta)
{
    //坦克不足4个，补充坦克
    addTank(delta);
    //坦克行为控制
    tankAction(delta);
}

//碰撞函数先是检测两个矩形区域是否相交
bool EnemyAI::IsRectIntersect(CCRect rectA,CCRect rectB)
{
    float left=MAX(rectA.getMinX(), rectB.getMinX());
    float right=MIN(rectA.getMaxX(), rectB.getMaxX());
    if (left>right)
        return false;
    float top=MIN(rectA.getMaxY(), rectB.getMaxY());
    float bottom=MAX(rectA.getMinY(), rectB.getMinY());
    if (top<bottom)
        return false;
    return true;
}

void EnemyAI::collisionTest()//来检测所有坦克之间的碰撞
{
    Bullet* playerBullet=mTank->getBullet();
    //坦克之间的碰撞
    CCArray* ccTmpArray=CCArray::create();
    ccTmpArray->addObjectsFromArray(mEnemyTanks);
    ccTmpArray->addObject(mTank);
    CCObject* pObjSrc;
    CCARRAY_FOREACH(ccTmpArray, pObjSrc)
    {
        Tank* tankSrc=(Tank*)pObjSrc;
        CCObject* pObjdst;
        CCARRAY_FOREACH(ccTmpArray, pObjdst)
        {
            Tank* tankDst=(Tank*)pObjdst;
            if (tankSrc!=tankDst)
            {
                CCRect rectDst;
                if (ccTmpArray->indexOfObject(pObjSrc)>ccTmpArray->indexOfObject(pObjdst))
                {
                    //之前的坦克已经确定了要移动的位置
                    rectDst=tankDst->getMovedRect();
                }
                else
                {
                    //还没有确定要移动的坦克
                    rectDst=tankDst->boundingBox();
                }
                if (IsRectIntersect(tankSrc->getMovedRect(), rectDst))
                {
                    //确保再移动之前没有重合
                    if (!IsRectIntersect(tankSrc->boundingBox(), rectDst))
                    {
                        tankSrc->setBlock(true);
                    }
                }
            }
        }
    }
    
    //玩家子弹和敌方子弹之间的碰撞
    CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Bullet* enemyBullet=((Tank*)pObj)->getBullet();
        if (playerBullet->getFlyState()&&enemyBullet->getFlyState())
        {
            if (IsRectIntersect(playerBullet->getMovedRect(), enemyBullet->getMovedRect()))
            {
                enemyBullet->stopFire();
                playerBullet->stopFire();
                break;
            }
        }
    }
    
    //玩家子弹和敌方坦克之间的碰撞
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        if (playerBullet->getFlyState())
        {
            Tank* enemyTank=(Tank*)pObj;
            if (IsRectIntersect(playerBullet->getMovedRect(), enemyTank->getMovedRect())) {
                mEnemyTanks->removeObject(pObj);
                enemyTank->remove();
                playerBullet->stopFire();
                score += 50;
                printf("%d",score);
                break;
            }
        }
    }
    
    //敌方子弹和玩家的碰撞
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Bullet* enemyBullet=((Tank*)pObj)->getBullet();
        if (enemyBullet->getFlyState())
        {
            if (IsRectIntersect(enemyBullet->getMovedRect(), mTank->getMovedRect())) {
                if (endlessLife == false) {
                    enemyBullet->stopFire();
                    mTank->setVisible(false);
                    life -= 1;
                    printf("%d",life);
                    /*****zyf******/
                    if (life <= 0) {
                        CCScene* scene=GameOver::scene();
                        CCDirector::sharedDirector()->replaceScene(scene);
                    } else {
                        //放到地图中初始化位置
                        CCTMXTiledMap* tmxTileMap=mTileMapInfo->getTileMap();
                        CCSize tileSize=tmxTileMap->getTileSize();
                        CCSize mapSize=tmxTileMap->getContentSize();
                        mTank->setPosition(ccp(mapSize.width/2-tileSize.width*3, tileSize.height));
                        mTank->setMovedRect(mTank->boundingBox());
                        mTank->setVisible(true);
                    }
                    /**************/
                    break;
                }
            }
        }
    }
    
    
    //道具与玩家的碰撞
//    if (IsRectIntersect(mProps->getMovedRect(), mTank->getMovedRect())) {
//        mProps->removeProps();
//        score += 50;
//        printf("%d",score);
//    }
    
    /*CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* enemyTank=(Tank*)pObj;
        if (IsRectIntersect(mTank->getMovedRect(), enemyTank->getMovedRect())){
            enemyTank->setBlock(true);
            mTank->setBlock(true);
        }
    }
    //敌方坦克之间的碰撞
    CCArray* ccTmpArray=CCArray::create();
    ccTmpArray->addObjectsFromArray(mEnemyTanks);
    while (ccTmpArray->count()) {
        CCObject* pObj;
        Tank* tmpTank=(Tank*)ccTmpArray->lastObject();
        ccTmpArray->removeLastObject();
        CCARRAY_FOREACH(ccTmpArray, pObj)
        {
            if (IsRectIntersect(tmpTank->getMovedRect(), ((Tank*)pObj)->getMovedRect())) {
                tmpTank->setBlock(true);
                ((Tank*)pObj)->setBlock(true);
                ccTmpArray->removeObject(pObj);
            }
        }
    }*/
}

int EnemyAI::getScore()
{
    return score;
}

int EnemyAI::getLife()
{
    return life;
}

void EnemyAI::setScore(int newScore)
{
    score = newScore;
}

void EnemyAI::setLife(int newLife)
{
    life = newLife;
}