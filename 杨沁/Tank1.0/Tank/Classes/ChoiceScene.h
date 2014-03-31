//
//  ChoiceScene.h
//  Tank
//
//  Created by zyf on 14-2-2.
//
//

#ifndef __Tank__ChoiceScene__
#define __Tank__ChoiceScene__

#include <iostream>
#include "cocos2d.h"

class ChoiceScene:public cocos2d::CCLayer {
    
public:
    virtual bool init();
    CREATE_FUNC(ChoiceScene);
    static cocos2d::CCScene *scene();
    void touchDownAction(CCObject* sender,unsigned int controlEvent);
private:
    void update();
    int m_nRound;
    
};

#endif /* defined(__Tank__ChoiceScene__) */
