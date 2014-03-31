#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ChoiceScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	//1.…Ë÷√Android∑µªÿ∫Õ≤Àµ•∞¥º¸
	setKeypadEnabled(true);
    
	//2.¥¥Ω®πÿ±’≤Àµ•œÓ
	CCMenuItemImage	*pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    
	//3.ªÒ»°ø… ”«¯”Úµƒ¥Û–°∫Õ‘≠µ„
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	//4.…Ë÷√≤Àµ•Œª÷√µΩ”“œ¬Ω«
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
                                origin.y + visibleSize.height - pCloseItem->getContentSize().height/2));
	CCMenu *pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
	//5.¥¥Ω®“ª∏ˆ°∞play game°±∞¥≈•¿¥ø™ º”Œœ∑,…Ë÷√Œª÷√£¨»ª∫Û…Ë÷√Àı∑≈±»¿˝¿¥  ”¶∆¡ƒª,
	//»ª∫ÛÃÌº”≤Àµ•œÓµΩ≤Àµ•÷–£¨º”»Î≤„÷–
	CCMenuItemImage *pItemPlay = CCMenuItemImage::create(
                                                         "playgameNormal.png", "playgameClose.png", this, menu_selector(HelloWorld::menuPlayGameCallback));
	pItemPlay->setPosition(ccp(visibleSize.width / 2, visibleSize.height*1.0f / 4.0f));
	pItemPlay->setScaleX(visibleSize.width / 600);
	pItemPlay->setScaleY(visibleSize.height / 400);
	
	CCMenu *pMenuPlay = CCMenu::create(pItemPlay, NULL);
	pMenuPlay->setPosition(CCPointZero);
	this->addChild(pMenuPlay, 1);
    
	//6.¥¥Ω®“ª∏ˆ∆Ù∂Øµƒ±≥æ∞ΩÁ√Ê
	CCSprite *pSprite = CCSprite::create("ScenceStart.png");
	pSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	CCSize sz = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / sz.width);
	pSprite->setScaleY(visibleSize.height / sz.height);
	this->addChild(pSprite, 0);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuPlayGameCallback(CCObject* pSender)
{
    CCScene* pScene = ChoiceScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
    return;
}

void HelloWorld::keyBackClicked()
{
    CCLayer::keyBackClicked();
    CCDirector::sharedDirector()->end();
}

void HelloWorld::keyMenuClicked()
{
    CCLayer::keyMenuClicked();
}
