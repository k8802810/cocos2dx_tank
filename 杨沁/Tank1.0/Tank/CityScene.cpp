//
//  CityScene.cpp
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#include "CityScene.h"

CityScene::CityScene()
{
    
}

CityScene::~CityScene()
{
    
}

CCScene *CityScene::scene()
{
	CCScene* scene = CCScene::create();
	CityScene* layer = CityScene::create();
    
	scene->addChild(layer);
    
	return scene;
}

CCScene *CityScene::scene(int round)
{
	CCScene* scene = CCScene::create();
	CityScene* layer = CityScene::create(round);
    
	scene->addChild(layer);
    
	return scene;
}

CityScene *CityScene::create(int round)
{
	CityScene* pRet = new CityScene();
	if (pRet)
	{
		pRet->setRound(round);
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
	}
    
	return NULL;
}

bool  CityScene::init()
{
	CCLayer::init();
    
    flag = false;
    
    //初始化地图信息
    char szRound[260];
    sprintf(szRound, "Round%d.tmx",m_nRound);
    tileMapInfo=TileMapInfo::createMapInfoWithFile(szRound);
    CCTMXTiledMap* tmxTileMap=tileMapInfo->getTileMap();
    this->addChild(tmxTileMap);
    
    //创建金币label
    CCString* strMoneyScore = CCString::createWithFormat("金币：0");//格式化为字符串
    moneyLabel = CCLabelTTF::create(strMoneyScore->m_sString.c_str(),"Arial",20);//从CCString中获得char*,更新金币
    moneyLabel->setAnchorPoint(ccp(0, 0));
    moneyLabel->setColor(ccc3(255, 255, 255));
    moneyLabel->setPosition(ccp(0,580));
    addChild(moneyLabel);
    
    //创建生命label
    CCString* strLifeScore = CCString::createWithFormat("生命：3");//格式化为字符串
    lifeLabel = CCLabelTTF::create(strLifeScore->m_sString.c_str(),"Arial",20);//从CCString中获得char*,更新生命
    lifeLabel->setAnchorPoint(ccp(0, 0));
    lifeLabel->setColor(ccc3(255, 255, 255));
    lifeLabel->setPosition(ccp(0,560));
    addChild(lifeLabel);
    
    //在已有的地图上，创建玩家坦克
    mPlayerTank[0]=Tank::createTankWithTankType("player2U.png", tileMapInfo);
    
    //放到地图中初始化位置
    CCSize tileSize=tmxTileMap->getTileSize();
    CCSize mapSize=tmxTileMap->getContentSize();
    mPlayerTank[0]->setPosition(ccp(mapSize.width/2-tileSize.width*3, tileSize.height));
    CCPoint xx=mPlayerTank[0]->getPosition();
    //显示虚拟手柄
    mLayerPanel=Panel::create();
    addChild(mLayerPanel,3);
    
    //创建坦克的AI
    mEnemyAI=EnemyAI::createEnemyAIWithTank(mPlayerTank[0]);
    
    //创建无敌模式坦克
    endlessLifeMode = CCSprite::create("shield2.png");
    endlessLifeMode->setVisible(false);
    endlessLifeMode->setPosition(ccp(0, 0));
    tileMapInfo->getTileMap()->addChild(endlessLifeMode);
    
	return true;
}

//在onEnter中设置一个定时器，
void CityScene::onEnter()
{
    CCLayer::onEnter();
    this->scheduleUpdate();
    this->schedule(schedule_selector(CityScene::propsUpdate),5.0f);
}

void CityScene::update(float delta)
{
    CCLayer::update(delta);
    //简单的向前运动。测试使用
    //mLayerTank[0]->setPositionY(mLayerTank[0]->getPositionY()+1);
    //将控制面板中的mLayerPanel获取的命令传给坦克
    mPlayerTank[0]->command(mLayerPanel->getOrder());
    
    //调用敌人AI的update
    mEnemyAI->update(delta);
    
    int score = mEnemyAI->getScore();
    CCString* strScore = CCString::createWithFormat("金币：%d",score);
    moneyLabel->setString(strScore->m_sString.c_str());
    
    int life = mEnemyAI->getLife();
    CCString* strLife = CCString::createWithFormat("生命：%d",life);
    lifeLabel->setString(strLife->m_sString.c_str());
    
    if (mEnemyAI->endlessLife) {
        this->schedule(schedule_selector(CityScene::setEndlessLife),10.0f);
        endlessLifeMode->setVisible(true);
        endlessLifeMode->setPosition(mPlayerTank[0]->getPosition());
    }
    
    if (mprops != NULL) {
        if (flag == true&&mprops->flag == true) {
            if (mEnemyAI->IsRectIntersect(mprops->boundingBox(), mPlayerTank[0]->getMovedRect())) {
                if (mprops->propsType == 0) {
                    mEnemyAI->setScore(mEnemyAI->getScore()+100);
                } else if (mprops->propsType == 1) {
                    if(mEnemyAI->getLife()<3){
                        mEnemyAI->setLife(mEnemyAI->getLife()+1);
                    }
                } else if (mprops->propsType == 2) {
                    mEnemyAI->endlessLife = true;
                }
                mprops->removeProps();
                flag = false;
            }
        }
    }
}

void CityScene::propsUpdate(float dalta)
{
    //创建道具金币
    mprops = Props::createPropsWithPropsType(tileMapInfo);
    flag = true;
}

void CityScene::setEndlessLife(CCTime dt)
{
    this->unschedule(schedule_selector(CityScene::setEndlessLife));
    mEnemyAI->endlessLife = false;
    endlessLifeMode->setVisible(false);
}