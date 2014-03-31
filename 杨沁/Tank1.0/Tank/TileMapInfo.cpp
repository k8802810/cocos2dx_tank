//
//  TileMapInfo.cpp
//  Tank
//
//  Created by zyf on 14-2-16.
//
//

#include "TileMapInfo.h"

//从一个tmx地图文件初始化地图信息
void TileMapInfo::initMapInfoWithFile(const char* tmxFile)
{
    mTMAXTileMap=CCTMXTiledMap::create(tmxFile);
    mTMXLayers[0]=mTMAXTileMap->layerNamed("layer_0");
    mTMXLayers[1]=mTMAXTileMap->layerNamed("layer_1");
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCSize mapSize=mTMAXTileMap->getContentSize();
    
    //缩放地图到合适的屏幕大小
    mTMAXTileMap->setScale(winSize.height/mTMAXTileMap->getContentSize().height);
    
    //将地图放到屏幕中间
    mTMAXTileMap->setPosition(ccp((winSize.width-mapSize.width*mTMAXTileMap->getScale())/2, (winSize.height-mapSize.height*mTMAXTileMap->getScale())/2));
}

//实现一个静态方法，返回一个TileMapInfo的实例
TileMapInfo*  TileMapInfo::createMapInfoWithFile(const char* tmxFile)
{
    TileMapInfo* tileMapInfo=new TileMapInfo();
    tileMapInfo->initMapInfoWithFile(tmxFile);
    return tileMapInfo;
}

//实现碰撞检测的函数
/*可以看到碰撞检测函数比较麻烦，首先判断了传进来的矩形是否在地图中，
然后依次对矩形四个顶点进行碰撞检测，如果矩形进入了除 tileNone和tileGrass之外的区域
说明无法行走了，则返回true来表示碰撞了。
其中我们用到了tileGIDAt函数，他可以从一个tmx中表示的地图坐标获取gid。*/
bool TileMapInfo::collisionTest(CCRect rect)
{
    int gid=0;
    CCSize mapSize=mTMAXTileMap->getContentSize();
    CCSize tileSize=mTMAXTileMap->getTileSize();
    
    if (rect.getMidX()<0||rect.getMaxX()>=mapSize.width||
        rect.getMidY()<0||rect.getMaxY()>=mapSize.height) {
        return true;
    }
    
//    printf("*********************");
//    for (int i=0; i<12; i++)
//    {
//        for(int j=0;j<26;j++)
//    {
//        if (j==0) printf("%d:\n",i);
//        printf(" %d",gid=mTMXLayers[0]->tileGIDAt(ccp(i, j)));
//    }
//        printf("\n");
//    }
    
    //将坦克Y坐标转换为地图上的Y坐标
    float MinY=mapSize.height-rect.getMinY();
    float MaxY=mapSize.height-rect.getMaxY();
    //对坦克四个顶点进行碰撞检测
    /***zyf****修复底线的bug****/
    float yy=(int)(MinY / tileSize.height);
    if(yy==26)return true;
    /*************************/
    gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),
                                       (int)(MinY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
		return true;

	gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),
                                       (int)(MaxY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
		return true;
    
	gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),
                                       (int)(MaxY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
		return true;
    
    /***zyf****修复底线的bug****/
    yy=(int)(MinY / tileSize.height);
    if(yy==26)return true;
    /*************************/
	gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),
                                       (int)(MinY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
		return true;
    
    
    return false;
}