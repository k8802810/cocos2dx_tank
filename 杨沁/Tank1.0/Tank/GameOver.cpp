//
//  GameOver.cpp
//  Tank
//
//  Created by zyf on 14-3-5.
//
//

#include "GameOver.h"

CCScene *GameOver::scene()
{
    CCScene *scene=CCScene::create();
    GameOver *layer=GameOver::create();
    if (scene&&layer) {
        scene->addChild(layer);
    }
    return scene;
}

bool GameOver::init()
{
    if (!CCLayer::init())
        return false;
    CCSize szWin=CCDirector::sharedDirector()->getWinSize();
    CCSprite *pSprite=CCSprite::create("over.png");
    pSprite->setPosition(ccp(szWin.width/2, szWin.height/2));
    CCSize szSprite=pSprite->getContentSize();
    pSprite->setScaleX(0.8*szWin.width/szSprite.width);
    pSprite->setScaleY(0.8*szWin.height/szSprite.height);
    this->addChild(pSprite,0);
    
    //创建返回菜单
    CCMenuItemFont *reStartItem = CCMenuItemFont::create("RESTART",this,menu_selector(GameOver::reStartGame));
    reStartItem->setPosition(ccp(szWin.width/2, szWin.height/2));
    reStartItem->setFontSizeObj(55);
    //reStartItem->setFontNameObj("Georgia-Bold");
    reStartItem->setColor(ccc3(0, 0, 0));
    CCMenu *pMenu = CCMenu::create(reStartItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu,1);
    
    return true;
}

void GameOver::reStartGame()
{
    //场景转换到HelloWorldScene
    CCScene *pScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(5.0f,pScene));
}