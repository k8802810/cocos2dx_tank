//
//  MyPaddle.h
//  Tank
//
//  Created by zyf on 14-2-9.
//
//

#ifndef __Tank__MyPaddle__
#define __Tank__MyPaddle__

#include <iostream>
#include "Paddle.h"
#include "ChoiceScene.h"
#define ROUNDS 20

enum enum_evt {
    evt_start ,
    evt_pressA,
    evt_pressB,
    evt_text
};

class MyPaddle:public Paddle {
    CC_SYNTHESIZE(enum_evt, m_evttyp, evttyp);
    CC_SYNTHESIZE(ChoiceScene*, m_pSence, pSence);
    
public:
    MyPaddle();
    ~MyPaddle();
    
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    
    static MyPaddle* paddleWithTexture(CCTexture2D* pTexture);
    
private:
    bool bFlag;
};

#endif /* defined(__Tank__MyPaddle__) */
