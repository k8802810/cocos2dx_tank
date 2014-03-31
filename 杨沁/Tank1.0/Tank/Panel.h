//
//  Panel.h
//  Tank
//
//  Created by zyf on 14-2-12.
//
//

#ifndef __Tank__Panel__
#define __Tank__Panel__

#define RES_PADDLE_LEFT "left.png"
#define RES_PADDLE_LEFT_PRESS "left_press.png"
#define RES_PADDLE_RIGHT "right.png"
#define RES_PADDLE_RIGHT_PRESS "right_press.png"
#define RES_PADDLE_UP "top.png"
#define RES_PADDLE_UP_PRESS "top_press.png"
#define RES_PADDLE_DOWN "buttom.png"
#define RES_PADDLE_DOWN_PRESS "buttom_press.png"
#define RES_PADDLE_FIRE "fire.png"
#define RES_PADDLE_FIRE_PRESS "fire_press.png"

#include <iostream>
#include "cocos2d.h"
#include "Paddle.h"

using namespace cocos2d;

enum enumOrder
{
    cmdNothing ,
    cmdGoUP,
    cmdGoRight,
    cmdGoDown,
    cmdGoLeft,
    cmdFire
};

class Panel:public CCLayer {
    
public:
    virtual bool init();
    CREATE_FUNC(Panel);
    enumOrder getOrder();
protected:
    Paddle* m_pPaddleUP;
    Paddle* m_pPaddleDown;
    Paddle* m_pPaddleLeft;
    Paddle* m_pPaddleRight;
    Paddle* m_pPaddleFire;
};

#endif /* defined(__Tank__Panel__) */
