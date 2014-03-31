//
//  TileMapInfo.h
//  Tank
//
//  Created by zyf on 14-2-16.
//
//


//获取地图信息
#ifndef __Tank__TileMapInfo__
#define __Tank__TileMapInfo__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

//tile类型，草地，钢铁，河流等
enum enumTileType
{
    tileNone,tileGrass,
    tileSteel,tileWall,
    tileRiver,tileKing,
    tileDiedKing
};

//根据地图中gid获取对应tile的leixing
static enumTileType gidToTileType[]=
{
    tileNone,
    
    tileNone,tileNone,tileGrass,tileGrass,tileSteel,tileSteel,
    tileNone,tileNone,tileGrass,tileGrass,tileSteel,tileSteel,
    
    tileWall,tileWall,tileRiver,tileRiver,tileKing,tileKing,
    tileWall,tileWall,tileRiver,tileRiver,tileKing,tileKing,

    //死亡的king，把原来的tileKing改成了tileDiedKing
    tileDiedKing,tileDiedKing,tileNone,tileNone,tileNone,tileNone,
    tileDiedKing,tileDiedKing,tileNone,tileNone,tileNone,tileNone
};

class TileMapInfo {
    
public:
    bool collisionTest(CCRect rect);
    
    static TileMapInfo* createMapInfoWithFile(const char* tmxFile);
    void initMapInfoWithFile(const char* tmxFile);
    CC_SYNTHESIZE(CCTMXTiledMap*, mTMAXTileMap, TileMap);
private:
    CCTMXLayer* mTMXLayers[2];
};


#endif /* defined(__Tank__TileMapInfo__) */
