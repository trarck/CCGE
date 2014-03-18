#include "StepGameWorldController.h"
#include "SceneDirector/GameSceneDirector.h"
#include "EntityComponent/EntityFactory.h"
#include "Layers/GameActiveSortLayer.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_GE_BEGIN

static const int kGameMapZOrder=1;
static const int kFullSceneEffectZOrder=2;

static const float MoveSmallDistance=3;

static int stepNears[][2]={
	{0 ,-1},{0 , 1},
	{-1 , 0},{1, 0},
};

static const int kStepNearsCount=4;

StepGameWorldController::StepGameWorldController()
:m_walkPaths(NULL)
{
	CCLOG("StepGameWorldController create");
    m_sName="StepGameWorldController";
}

StepGameWorldController::~StepGameWorldController()
{
	CCLOG("StepGameWorldController destroy begin");

    
    CC_SAFE_RELEASE_NULL(m_walkPaths);
    

}

//// on "init" you need to initialize your instance
//bool StepGameWorldController::init()
//{
//    if ( !GameWorldController::init() )
//    {
//        return false;
//    }
//
//	return true;
//}
//
//bool StepGameWorldController::init(int zoneId,int mapId)
//{
//    if ( !GameWorldController::init(zoneId,mapId))
//    {
//        return false;
//    }
//    
//	return true;
//}

void StepGameWorldController::setup()
{
    GameWorldController::setup();

    CCPointValue* firstPointValue=static_cast<CCPointValue*>(m_walkPaths->objectAtIndex(0));
    CCPoint firstPos=firstPointValue->getPoint();
    
    addPlayerAtCoord(firstPos);
    
    CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(firstPos));
    
    CCLOG("first: cell:%f,%f,view:%f,%f",firstPos.x,firstPos.y,viewPos.x,viewPos.y);
    
    m_pGameCamera->moveTo(viewPos.x,-viewPos.y);
}

/**
 * 设置游戏地图
 */
ISOMapInfo* StepGameWorldController::createGameMap()
{
    ISOMapInfo* mapInfo=GameWorldController::createGameMap();
    
    //创建地图上的行走路径
    m_walkPaths=this->buildWalkPaths(mapInfo);
    m_walkPaths->retain();
    
//    //debug show walk path
//    CCObject* pObj=NULL;
//    CCPointValue* pointValue=NULL;
//    std::string pathLog="";
//    
//    CCARRAY_FOREACH(m_walkPaths, pObj){
//        pointValue=static_cast<CCPointValue*>(pObj);
//        pathLog+=CCString::createWithFormat("(%d,%d)",(int)pointValue->getPoint().x,(int)pointValue->getPoint().y)->getCString();
//    }
//    CCLOG("walk path:%s",pathLog.c_str());
 
    return mapInfo;
}

/*
 * 取得路径tile的id
 */
int StepGameWorldController::getStepTileId(ISOMapInfo* mapInfo)
{
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        
        ISOTilesetInfo* tilesetInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(tilesets, pObj)
        {
            tilesetInfo = static_cast<ISOTilesetInfo*>(pObj);
            if (tilesetInfo)
            {
                
                CCArray* tileInfos=tilesetInfo->getTiles();
                
                CCARRAY_FOREACH(tileInfos, pObj){
                    ISOTileInfo* tileInfo= static_cast<ISOTileInfo*>(pObj);
                    
                    CCString* type=static_cast<CCString*>(tileInfo->getProperties()->objectForKey("type"));
                    if (type && type->intValue()==1) {
                        return tileInfo->getId()+tilesetInfo->getFirstGid();
                    }
                }
            }
        }
    }
    
    return 0;
}


/*
 * 构建行走路径所在的层
 */
ISOLayerInfo* StepGameWorldController::getStepLayer(ISOMapInfo* mapInfo)
{
    CCArray* layers=mapInfo->getLayers();
    ISOLayerInfo* layerInfo=NULL;
    CCObject* pObj=NULL;
    
    CCARRAY_FOREACH(layers, pObj){
        layerInfo=static_cast<ISOLayerInfo*>(pObj);
        if (layerInfo->getName()=="ground") {
            return layerInfo;
        }
    }
    
    return NULL;
}

/*
 * 创建行走路径
 */
CCArray* StepGameWorldController::buildWalkPaths(ISOMapInfo* mapInfo,int startX,int startY)
{

    int stepTileId=this->getStepTileId(mapInfo);
    
    if (!stepTileId)  return NULL;
    
    //取得行走路径所在的层
    ISOLayerInfo* layerInfo=this->getStepLayer(mapInfo);
    return this->createWalkPaths(layerInfo,stepTileId,startX,startY);
}

/*
 * 创建行走路径
 */
CCArray* StepGameWorldController::createWalkPaths(ISOLayerInfo* layerInfo,int stepTileId,int startX,int startY)
{
    unsigned int* tiles=layerInfo->getTiles();
    
    int col=(int)layerInfo->getLayerSize().width;
    int row=(int)layerInfo->getLayerSize().height;
    
    CCArray* paths=CCArray::create();
    
    int nextX=0,nextY=0;
    
    int stepX=0,stepY=0;
    
    int newStepX=0,newStepY=0;
    
    int x=startX,y=startY;
    
    while (getNextStepPoint(&nextX,&nextY,&newStepX,&newStepY,tiles,col,row,x,y,stepX,stepY,stepTileId)){
        paths->addObject(CCPointValue::create(nextX, nextY));
        x=nextX;
        y=nextY;
        stepX=newStepX;
        stepY=newStepY;
    }
    
    return paths;
}

/*
 * 创建行走路径
 */
CCArray* StepGameWorldController::createWalkPathsFromCell(unsigned int* tiles,int col,int row,int stepTileId,int startX,int startY,int stepX,int stepY)
{
    CCArray* paths=CCArray::create();
    
    int nextX=0,nextY=0;
    
    int newStepX=0,newStepY=0;
    
    int x=startX,y=startY;
    
    while (getNextStepPoint(&nextX,&nextY,&newStepX,&newStepY,tiles,col,row,x,y,stepX,stepY,stepTileId)){
        paths->addObject(CCPointValue::create(nextX, nextY));
        x=nextX;
        y=nextY;
        stepX=newStepX;
        stepY=newStepY;
    }
    
    return paths;
}

/**
 * @brief 取得当前格子的下一个格子
 *
 * @param nextX 下一个格子横坐标
 * @param nextY 下一个格子纵坐标
 * @param outStepX 找到下个格子的步进x
 * @param outStepY 找到下个格子的步进y
 * @param tiles 层包含的格子信息
 * @param col 层的行数
 * @param row 层的列数
 * @param cellX 当前搜索格子X
 * @param cellY 当前搜索格子Y
 * @param stepX 进入当前格子的步进X
 * @param stepY 进入当前格子的步进Y
 * @param stepTileId 需要检查的tile的id
 *
 * @return 是否查找成功
 */
bool StepGameWorldController::getNextStepPoint(int* nextX,int* nextY,int* outStepX,int* outStepY,unsigned int* tiles,int col,int row,int cellX,int cellY,int stepX,int stepY,int stepTileId)
{
    int dx=0,dy=0;
    int x=-1,y=-1;
    
    for (int i=0; i<kStepNearsCount; ++i) {
        dx=stepNears[i][0];
        dy=stepNears[i][1];
        
        if (dx!=-stepX || dy!=-stepY) {
            
            x=cellX+dx;
            y=cellY+dy;
            
            //在地图的范围内
            if (x>=0 && x<col && y>=0 && y<row) {
                
                if (*(tiles+y*col+x)==stepTileId) {
                    
                    *nextX=x;
                    *nextY=y;
                    *outStepX=dx;
                    *outStepY=dy;
                    
                    return true;
                }
            }
        }
    }
    
    return false;
}


/*
 * 构建行走路径
 * 从任意点开始创建
 */
CCArray* StepGameWorldController::buildWalkPaths(ISOMapInfo* mapInfo)
{
    int stepTileId=this->getStepTileId(mapInfo);
    
    if (!stepTileId)  return NULL;
    
    //取得行走路径所在的层
    ISOLayerInfo* layerInfo=this->getStepLayer(mapInfo);
    return this->createWalkPaths(layerInfo,stepTileId);
}

/*
 * 创建行走路径
 *  从任意点开始创建
 */
CCArray* StepGameWorldController::createWalkPaths(ISOLayerInfo* layerInfo,int stepTileId)
{
    unsigned int* tiles=layerInfo->getTiles();
    
    int col=(int)layerInfo->getLayerSize().width;
    int row=(int)layerInfo->getLayerSize().height;
    
    int cellX=-1,cellY=-1;
    
    //查找一个路径上的点
    for (int y=0; y<row; ++y) {
        for (int x=0; x<col; ++x) {
            if (*(tiles+y*col+x)==stepTileId) {
                cellX=x;
                cellY=y;
                break;
            }
        }
    }
    
    //没有路径点，直接返回
    if (cellX==-1 && cellY==-1) return NULL;
    
    int stepX=0,stepY=0;
    int x=-1,y=-1;
    int newStepX=0,newStepY=0;
    int nextX=0,nextY=0;
    
    int haveNext=false;
    
    CCArray* nextPaths=CCArray::create();
    CCArray* prevPaths=CCArray::create();
    
    for (int i=0; i<kStepNearsCount; ++i) {
        
        stepX=stepNears[i][0];
        stepY=stepNears[i][1];
        
        x=cellX+stepX;
        y=cellY+stepY;
        
        //在地图的范围内
        if (x>=0 && x<col && y>=0 && y<row) {
            
            if (*(tiles+y*col+x)==stepTileId) {
                
                
                if (haveNext){
                    //已经有next的路径点，搜索prev路径点
                    
                    //添加找到的第一个结点
                    nextPaths->addObject(CCPointValue::create(x, y));
                    
                    //继续搜索第一个结点后面的结点
                    while (getNextStepPoint(&nextX,&nextY,&newStepX,&newStepY,tiles,col,row,x,y,stepX,stepY,stepTileId)){
                        
                        prevPaths->addObject(CCPointValue::create(nextX, nextY));
                        
                        x=nextX;
                        y=nextY;
                        stepX=newStepX;
                        stepY=newStepY;
                    }
                    
                }else{
                    //第一次找到的点为next点。如果只有一个next则当前点是起点或终点。
                    
                    //添加找到的第一个结点
                    nextPaths->addObject(CCPointValue::create(x, y));
                    
                    //继续搜索第一个结点后面的结点
                    while (getNextStepPoint(&nextX,&nextY,&newStepX,&newStepY,tiles,col,row,x,y,stepX,stepY,stepTileId)){
                        
                        nextPaths->addObject(CCPointValue::create(nextX, nextY));
                        
                        x=nextX;
                        y=nextY;
                        stepX=newStepX;
                        stepY=newStepY;
                    }
                    
                    haveNext=true;
                }

            }
        }
    }
    
    //把next和prev合并到一起
    
    //注意prev是反向的
    prevPaths->reverseObjects();
    //添加当前结点
    prevPaths->addObject(CCPointValue::create(cellX,cellY));
    //添加next结点
    prevPaths->addObjectsFromArray(nextPaths);
    
    return prevPaths;
}

NS_CC_GE_END