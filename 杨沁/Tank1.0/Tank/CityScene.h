//
//  CityScene.h
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#ifndef __Tank__CityScene__
#define __Tank__CityScene__

#include <iostream>
#include "Panel.h"
#include "Tank.h"
#include "cocos2d.h"
#include "EnemyAI.h"
#include "Props.h"

using namespace cocos2d;

class CityScene : public cocos2d::CCLayer
{
public:
	CityScene();
	~CityScene();
	virtual bool  init();
    virtual void onEnter();
    virtual void update(float delta);
    virtual void propsUpdate(float dalta);
    virtual void setEndlessLife(CCTime dt);
    
	static cocos2d::CCScene *scene();
	static cocos2d::CCScene *scene(int round);
	CREATE_FUNC(CityScene);
	static CityScene *create(int round);
    CCLabelTTF* moneyLabel;
    CCLabelTTF* lifeLabel;
	CC_SYNTHESIZE(int, m_nRound, Round);
    
private:
    //显示虚拟手柄
    Panel* mLayerPanel;
    Tank* mPlayerTank[2];
    EnemyAI* mEnemyAI;
    Props* mprops;
    TileMapInfo* tileMapInfo;
    CCSprite* endlessLifeMode;
    bool flag;
};
#endif /* defined(__Tank__CityScene__) */
