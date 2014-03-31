//
//  Props.h
//  Tank
//
//  Created by cstlab on 14-3-10.
//
//

#ifndef __Tank__Props__
#define __Tank__Props__

#include <iostream>
#include "cocos2d.h"
#include "TileMapInfo.h"
using namespace cocos2d;

class Props:public CCSprite
{
public:
    Props();
    ~Props();
    static Props* createPropsWithPropsType(TileMapInfo* tileMapInfo);
    void initPropsWithPropsType(TileMapInfo* tileMapInfo);
    void removeProps();
    CREATE_FUNC(Props);
    bool flag;
    int propsType;
private:
    TileMapInfo* mTileMapInfo;
    CCPoint bornPoint[5];
};

#endif /* defined(__Tank__Props__) */
