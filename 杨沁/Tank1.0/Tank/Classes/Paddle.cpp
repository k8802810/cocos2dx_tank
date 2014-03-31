//
//  Paddle.cpp
//  Tank
//
//  Created by zyf on 14-2-8.
//
//

#include "Paddle.h"

Paddle::Paddle()
{}

Paddle::~Paddle()
{}

//我们在Paddle中重载CCSprite的initWithTexture，默认设置状态为kPaddleStateUngrabbed，不再捕获状态中。
bool Paddle::initWithTexture(CCTexture2D* pTexture)
{
    if (CCSprite::initWithTexture(pTexture)) {
        m_state=kPaddleStateUngrabbed;
    }
    return true;
}

//添加一个static Paddle* paddleWithTexture(CCTexture2D* pTexture);来加载纹理，并返回Paddle实例
Paddle* Paddle::paddleWithTexture(CCTexture2D* pTexture)
{
	Paddle *pPaddle = new Paddle();
	pPaddle->initWithTexture(pTexture);
	pPaddle->autorelease();
    
	return pPaddle;
}

//如果在捕获状态中，那么就不用继续捕获输入，
//如果不正在捕获状态中，触摸点也不在精灵中，则不继续捕获输入，
//如果不在捕获状态中，但是触摸点在精灵上，就设置捕获状态为正在捕获，并继续捕获后面的输入。
bool Paddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (m_state!=kPaddleStateUngrabbed) return false;
    if (!containsTouchLocation(touch)) return false;
    m_state=kPaddleStateGrabbed;
    return true;
}

void Paddle::ccTouchMoved(CCTouch* touch,CCEvent* event)
{}

//其中判断触摸点是否在精灵上的相关函数
CCRect Paddle::rect()
{
    CCSize size=getTexture()->getContentSize();
    return CCRectMake(-size.width/2, -size.height/2, size.width, size.height);
}
bool Paddle::containsTouchLocation(CCTouch *touch)
{
    CCPoint ccp=convertTouchToNodeSpaceAR(touch);
    return rect().containsPoint(ccp);
}

//输入结束后，设置为未捕获状态
void Paddle::ccTouchEnded(CCTouch* touch, CCEvent *event)
{
    m_state=kPaddleStateUngrabbed;
}

//在onEnter()中把精灵层注册到触摸事件的分发器中，
void Paddle::onEnter()
{
    CCDirector *pDirector=CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    CCSprite::onEnter();
}

//在onExit()中把注册的精灵层移除
void Paddle::onExit()
{
    CCDirector *pDirector=CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}