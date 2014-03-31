//
//  GameOver.h
//  Tank
//
//  Created by zyf on 14-3-5.
//
//

#ifndef __Tank__GameOver__
#define __Tank__GameOver__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class GameOver:public CCLayer {
    
public:
    virtual bool init();
    CREATE_FUNC(GameOver);
    static CCScene *scene();
    void reStartGame();
};


#endif /* defined(__Tank__GameOver__) */
