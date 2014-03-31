//
//  Props.cpp
//  Tank
//
//  Created by cstlab on 14-3-10.
//
//

#include "Props.h"

Props::Props()
{
}

Props::~Props()
{
}

void Props::initPropsWithPropsType(TileMapInfo* tileMapInfo)
{
    flag = true;
    propsType = (int)(CCRANDOM_0_1()*4)%3;
    if (propsType == 0)
        initWithFile("money.png");
    else if (propsType == 1)
        initWithFile("love.png");
    else if (propsType == 2)
        initWithFile("born1.png");
    
    mTileMapInfo = tileMapInfo;
    
    //初始化出现地点
    CCSize mapSize = mTileMapInfo->getTileMap()->getContentSize();
    CCSize tileSize = mTileMapInfo->getTileMap()->layerNamed("layer_0")->getMapTileSize();
    bornPoint[0] = ccp(tileSize.width+50, mapSize.height-tileSize.height);
    bornPoint[1] = ccp(mapSize.width/2,mapSize.height/2);
    bornPoint[2] = ccp(mapSize.width/2+tileSize.width*3, tileSize.height);
    bornPoint[3] = ccp(mapSize.width-tileSize.width-100, mapSize.height-tileSize.height);
    bornPoint[4] = ccp(tileSize.width+10, tileSize.height);
    int bornPointIndex=(int)(CCRANDOM_0_1()*6)%5;
    setPosition(bornPoint[bornPointIndex]);
    mTileMapInfo->getTileMap()->addChild(this);    
    
    //动作结束监听
    CCMoveTo* moveAction = CCMoveTo::create(3.0f, bornPoint[bornPointIndex]);
    //回调对象，CCCallFunc也是一个动作，只不过这个动作是个回调函数
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Props::removeProps));
    CCSequence* action = CCSequence::create(moveAction,callFunc,NULL);
    this->runAction(action);
}

Props* Props::createPropsWithPropsType(TileMapInfo* tileMapInfo)
{
    Props* money = new Props();
    money->initPropsWithPropsType(tileMapInfo);
    money->autorelease();
    
    return money;
}

//移除道具
void Props::removeProps()
{
    mTileMapInfo->getTileMap()->removeChild(this);
    flag = false;
    printf("remove money\n");
}