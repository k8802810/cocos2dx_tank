//
//  EnemyAI.h
//  Tank
//
//  Created by zyf on 14-2-21.
//
//

#ifndef __Tank__EnemyAI__
#define __Tank__EnemyAI__

#include <iostream>
#include "Tank.h"
#include "Props.h"

static const char* enemyTankType[]=
{
    "normalU.png","speedU.png","armor1U.png"
};

/*在成员变量中，mEnemyTanks存放了所有的坦克，
mTank存放了玩家坦克，最后mTileMapInfo存放了地图信息。
bornPoint存放了敌方坦克出身的三个位置。*/
class EnemyAI {
    
public:
    EnemyAI();
    ~EnemyAI();
    
    static EnemyAI* createEnemyAIWithTank(Tank* tank);
    void initEnemyAIWithTank(Tank* tank);
    void update(float delta);
    bool IsRectIntersect(CCRect rectA,CCRect rectB);
    void collisionTest();
    void move();
    int score;
    int getScore();
    void setScore(int newScore);
    int life;
    int getLife();
    void setLife(int newLife);
    bool endlessLife;
private:
    void addTank(float delta);
    void tankAction(float delta);
private:
    CCArray* mEnemyTanks;
    Tank* mTank;
    Props* mProps;
    TileMapInfo* mTileMapInfo;
    //出发地点
    CCPoint bornPoint[3];
};

#endif /* defined(__Tank__EnemyAI__) */
