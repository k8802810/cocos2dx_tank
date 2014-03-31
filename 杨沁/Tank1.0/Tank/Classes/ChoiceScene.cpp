//
//  ChoiceScene.cpp
//  Tank
//
//  Created by zyf on 14-2-2.
//
//

#include "ChoiceScene.h"
#include "MyPaddle.h"
using namespace cocos2d;

CCScene *ChoiceScene::scene()
{
    CCScene *scene=CCScene::create();
    ChoiceScene *layer=ChoiceScene::create();
    if (scene&&layer) {
        scene->addChild(layer);
    }
    return scene;
}

bool ChoiceScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    setKeypadEnabled(true);
    //添加一个黑色背景,并进行比例缩放
    CCSize szWin=CCDirector::sharedDirector()->getWinSize();
    CCSprite *pSprite=CCSprite::create("Black.png");
    pSprite->cocos2d::CCNode::setPosition(ccp(szWin.width/2, szWin  .height/2));
    CCSize szSprite=pSprite->getContentSize();
    pSprite->setScaleX(szWin.width/szSprite.width);
    pSprite->setScaleY(szWin.height/szSprite.height);
    this->addChild(pSprite,0);
    
    const char *szImgs[4] = { "btn_play.png", "btn_rewind.png",
		"btn_fast_forward.png", "fps_images.png" };
	float fSettings[4][4] = {
		{ 20.0f / 480, 16.0f / 320, 280.0f / 480, 160.0f / 320 },
		{ 20.0f / 480, 16.0f / 320, 200.0f / 480, 160.0f / 320 },
		{ 20.0f / 480, 16.0f / 320, 240.0f / 480, 160.0f / 320 },
		{ 20.0f / 480, 22.0f / 320, 280.0f / 480, 172.0f / 320 }
	};
    
    //分别对开始游戏，上一关，下一关按钮的图片加载上来显示到合适位置
    enum_evt evts[4]={evt_start,evt_pressA,evt_pressB,evt_text};
    for (int i = 0; i < 3; ++i)
	{
		float* fSetting = fSettings[i];
		CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage(szImgs[i]);
		//CCSprite* pPaddle = CCSprite::createWithTexture(paddleTexture);
		MyPaddle* pPaddle=MyPaddle::paddleWithTexture(paddleTexture);
        CCSize szBtn = pPaddle->getContentSize();
		pPaddle->setScaleX(szWin.width / szBtn.width * fSetting[0]);
		pPaddle->setScaleY(szWin.height / szBtn.height * fSetting[1]);
		pPaddle->setPosition(ccp(szWin.width * fSetting[2], szWin.height * fSetting[3]));
		addChild(pPaddle);
        
        //设置当前场景到MyPaddle中,然后设置事件类型到MyPaddle中
        pPaddle->setpSence(this);
        pPaddle->setevttyp(evts[i]);
	}
    
    //对现实关卡的数字进行操作，设置显示数字为1，
    int i = 3;
	ccColor3B color = { 0, 0, 0 };
	float* fSetting = fSettings[i];
	CCLabelAtlas* label1 = CCLabelAtlas::create("1", szImgs[i], 16, 32, '.');
    
	CCSize sz = label1->getContentSize();
	label1->setAnchorPoint(ccp(0.5f, 0.5f));
	label1->setScaleX(szWin.width / sz.width * fSetting[0]);
	label1->setScaleY(szWin.height / sz.height * fSetting[1]);
	label1->setPosition(ccp(szWin.width * fSetting[2], szWin.height * fSetting[3]));
	label1->setColor(color);
    addChild(label1, 0, evt_text);
	//addChild(label1, 0);
    
    return true;
}

void ChoiceScene::touchDownAction(CCObject* sender, unsigned int controlEvent)
{
    if (controlEvent==evt_pressA) {
        m_nRound=1+(m_nRound-1+ROUNDS-1)%ROUNDS;
        update();
    }
    else if(controlEvent==evt_pressB)
    {
        m_nRound=1+(m_nRound+1+ROUNDS-1)%ROUNDS;
        update();
    }
    else if(controlEvent==evt_start)
    {
        //开始对应关卡的场景，稍后添加
    }
}

void ChoiceScene::update()
{
    char szTemp[260];
    CCLabelAtlas* label1=(CCLabelAtlas*)getChildByTag(evt_text);//getChildByTag来根据Tag来获取子节点的指针，
    sprintf(szTemp, "%d",m_nRound);
    label1->setString(szTemp);
}

