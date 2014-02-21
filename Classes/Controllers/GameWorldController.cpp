#include "GameWorldController.h"
#include "Scenes/GameSceneDirector.h"
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

GameWorldController::GameWorldController()
:m_zoneId(0)
,m_mapId(0)
,m_iMapColumn(0)
,m_iMapRow(0)
,m_bIsTouchMoved(true)
,m_pUnits(NULL)
,m_pGameCamera(NULL)
,m_isoMap(NULL)
,m_astar(NULL)
,m_occlusion(NULL)
,m_player(NULL)
,m_activeLayer(NULL)
,m_walkPaths(NULL)
{
	CCLOG("GameWorldController create");
    m_sName="GameWorldController";
}

GameWorldController::~GameWorldController()
{
	CCLOG("GameWorldController destroy begin");
	//CCLOG("player retain:%d",m_pPlayer->retainCount());
	CC_SAFE_RELEASE_NULL(m_pGameCamera);
	//在创建的时候已经添加到自动释放池里了。
	//CC_SAFE_RELEASE(m_pBackground);
	//CC_SAFE_RELEASE(m_pIntermediate);
	//CC_SAFE_RELEASE(m_pForeground);
	//CCLOG("player retain:%d",m_pPlayer->retainCount());
    m_player->cleanupComponents();
	CC_SAFE_RELEASE_NULL(m_player);
	CC_SAFE_RELEASE_NULL(m_pUnits);

    CC_SAFE_RELEASE_NULL(m_isoMap);
    CC_SAFE_RELEASE_NULL(m_astar);
    CC_SAFE_RELEASE_NULL(m_occlusion);
    
    CC_SAFE_RELEASE_NULL(m_walkPaths);
    
	CCLOG("GameWorldController destroy end");
}

// on "init" you need to initialize your instance
bool GameWorldController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Controller::init() )
    {
        return false;
    }

	m_iMapColumn=20;
	m_iMapRow=20;
	return true;
}

bool GameWorldController::init(int zoneId,int mapId)
{
	init();
	m_zoneId=zoneId;
    m_mapId=mapId;
	return true;
}

void GameWorldController::viewDidLoad()
{
    Controller::viewDidLoad();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);
    this->setup();
}

void GameWorldController::onViewExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Controller::onViewExit();
}

void GameWorldController::setup()
{
    CCSize contentSize= this->getPreferredContentSize();
	//m_pUnits=new CCArray(10);

	m_pGameCamera=new ISOCamera();
	m_pGameCamera->init();
	m_pGameCamera->setMoveDelegate(this);
    
    //base
	this->createGameMap();
    
    setupUtil();
    
	//objects
//	loadBackground();
//	loadInterMediate();
	
    m_pGameCamera->scaleTo(2);
	//setupNetWork();
    m_pGameCamera->moveTo(-contentSize.width/2, 0);

    this->setCameraMoveRange();
    
    createTestMenu();
    
    addPlayerAtCoord(ccp(10,10));
}

/**
 * 初始化一些工具方法
 * 寻路，坐标转换
 */
void GameWorldController::setupUtil()
{
	//astar search
//	CC_SAFE_RELEASE(m_astar);
	m_astar=new CallbackAstar();
	m_astar->init();
	m_astar->setBounding(0,0,m_iMapColumn,m_iMapRow);
	m_astar->setCheckBarrierHandle(check_workable_selector(GameWorldController::isWorkable),this);
	
//    //深度排序
//    m_occlusion=new SortZIndex();
//    m_occlusion->init();
//
//    
//    //test zindex
//    
//    
//    SortZIndexNode* node1=new SortZIndexNode();
//    node1->setRect(CCRectMake(10,10, 3, 1));
//    m_occlusion->insert(node1);
//    node1->release();
//
//    SortZIndexNode* node2=new SortZIndexNode();
//    node2->setRect(CCRectMake(8,12, 1, 1));
//    m_occlusion->insert(node2);
//    node2->release();
//    
//    SortZIndexNode* node3=new SortZIndexNode();
//    node3->setRect(CCRectMake(11,9, 1, 1));
//    m_occlusion->insert(node3);
//    node3->release();
//    
//    m_occlusion->updateZOrder();
    
}


/**
 * 设置游戏地图
 */
void GameWorldController::createGameMap()
{
    //移除去之前的地图文件
    if (m_isoMap) {
        m_view->removeChild(m_isoMap);
    }
    
    CCSize visibleSize =this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    //取得要使用的layer渲染类型
    int mapLyaerType=ISOTileMapBuilder::BatchLayerType;
    
    CCInteger* mapLyaerTypeValue=static_cast<CCInteger*>(GameSceneDirector::getInstance()->getSceneContext());
    
    if (mapLyaerTypeValue) {
        mapLyaerType=mapLyaerTypeValue->getValue();
    }
    
    //加载数据
    ISOMapInfo* mapInfo=loadMapData();
    
    //构建地图
    m_isoMap=new ISOTileMap();
    m_isoMap->init();
//    m_isoMap->setScale(4);
	m_isoMap->setVisibleSize(visibleSize);
    //    m_isoMap->setUseDynamicGroup(true);
    
    struct timeval now;
    gettimeofday(&now,NULL);
    
    ISOTileMapBuilder* mapBuilder=new ISOTileMapBuilder();
    mapBuilder->init(m_isoMap);
	mapBuilder->setMapLayerType(mapLyaerType);
    mapBuilder->setActiveLayerName("top");
    
    //不要创建活动层，由游戏自己创建
    mapBuilder->setBuildActiveLayer(true);
    
    mapBuilder->buildWithMapInfo(mapInfo);
    
    struct timeval end;
    gettimeofday(&end,NULL);
    
    CCLOG("use:%ld", (end.tv_sec-now.tv_sec)*1000000+end.tv_usec-now.tv_usec);
    
    //构建dynamic group
    //    m_isoMap->setupDynamicGroup();
    m_isoMap->showCoordLine();
    

    m_activeLayer=static_cast<ISOActiveLayer*>(m_isoMap->getActiveLayer());
    
//    ISOActiveLayerInfo* activeLayerInfo=mapBuilder->getActiveLayerInfo(mapInfo);
//    this->createActiveLayer(activeLayerInfo);
    
    //加入渲染树中
    m_view->addChild(m_isoMap,kGameMapZOrder);
    
    //设置地图的格子行列
    CCSize mapSize=m_isoMap->getMapSize();
    m_iMapColumn=(int)mapSize.width;
    m_iMapRow=(int)mapSize.height;
    
    
    //创建地图上的行走路径
    m_walkPaths=this->buildWalkPaths(mapInfo);
    m_walkPaths->retain();
    
    //debug show walk path
    CCObject* pObj=NULL;
    CCPointValue* pointValue=NULL;
    std::string pathLog="";
    
    CCARRAY_FOREACH(m_walkPaths, pObj){
        pointValue=static_cast<CCPointValue*>(pObj);
        pathLog+=CCString::createWithFormat("(%d,%d)",(int)pointValue->getPoint().x,(int)pointValue->getPoint().y)->getCString();
    }
    CCLOG("walk path:%s",pathLog.c_str());
    
    //m_isoMap->release();
}

/*
 * 创建活动层
 */
void GameWorldController::createActiveLayer(ISOActiveLayerInfo* activeLayerInfo)
{
    m_activeLayer=new GameActiveSortLayer();
    m_activeLayer->init();
    m_activeLayer->setMap(m_isoMap);
    m_activeLayer->setLayerName(activeLayerInfo->getName());
    m_activeLayer->setLayerOrientation(m_isoMap->getMapOrientation());
    if (activeLayerInfo->getProperties()) {
        m_activeLayer->setProperties(activeLayerInfo->getProperties());
    }
    m_activeLayer->setObjects(activeLayerInfo->getObjects());
    m_activeLayer->setupLayer();
    
    m_isoMap->addChild(m_activeLayer,activeLayerInfo->getRenderIndex());
    m_isoMap->setActiveLayer(m_activeLayer);
    
    m_activeLayer->release();
}

ISOMapInfo* GameWorldController::loadMapData()
{
    //解析地图数据
    ISOXMLParser* isoXmlParser=new ISOXMLParser();
    isoXmlParser->setTranslateLayerData(true);
    isoXmlParser->setTranslateObjectCoord(true);
//    isoXmlParser->initWithTMXFile(CCString::createWithFormat("map/zone/%d_%d.tmx",m_zoneId,m_mapId)->getCString());
    isoXmlParser->initWithTMXFile("map/zone/m1xin/cj0101.tmx");
    
    ISOMapInfo* mapInfo=isoXmlParser->getMapInfo();
    
    CCLOG("tileset count:%d",mapInfo->getTilesets()->count());
    ISOTilesetInfo* tilesetInfo=(ISOTilesetInfo*)mapInfo->getTilesets()->objectAtIndex(0);
    CCLOG("tiles count:%d,%s\n%f,%f",tilesetInfo->getTiles()->count(),tilesetInfo->getImageSource(),tilesetInfo->getImageSize().width,tilesetInfo->getImageSize().height);
    
    //自动释放
//    mapInfo->retain();
//    mapInfo->autorelease();
    
    isoXmlParser->autorelease();
    
    return mapInfo;
    
}


/*
 * 取得路径tile的id
 */
int GameWorldController::getStepTileId(ISOMapInfo* mapInfo)
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
ISOLayerInfo* GameWorldController::getStepLayer(ISOMapInfo* mapInfo)
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
CCArray* GameWorldController::buildWalkPaths(ISOMapInfo* mapInfo,int startX,int startY)
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
CCArray* GameWorldController::createWalkPaths(ISOLayerInfo* layerInfo,int stepTileId,int startX,int startY)
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
CCArray* GameWorldController::createWalkPathsFromCell(unsigned int* tiles,int col,int row,int stepTileId,int startX,int startY,int stepX,int stepY)
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
bool GameWorldController::getNextStepPoint(int* nextX,int* nextY,int* outStepX,int* outStepY,unsigned int* tiles,int col,int row,int cellX,int cellY,int stepX,int stepY,int stepTileId)
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
CCArray* GameWorldController::buildWalkPaths(ISOMapInfo* mapInfo)
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
CCArray* GameWorldController::createWalkPaths(ISOLayerInfo* layerInfo,int stepTileId)
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

/**
 * 设置相机的可视
 */
void GameWorldController::setCameraMoveRange()
{
    //计算相机可移动范围
    CCSize mapSize=m_isoMap->getMapSize();
    CCSize visibleSize=m_isoMap->getOrignalVisibleSize();
    
    float scale=m_pGameCamera->getScale();

    float minX=-mapSize.height*ISOStaticCoordinate::sTileWidth*0.5*scale;
    float minY=0;
    float maxX=mapSize.width*ISOStaticCoordinate::sTileWidth*0.5*scale;
    float maxY=(mapSize.height+mapSize.height)*ISOStaticCoordinate::sTileHeight*0.5*scale;
    //由于坐标原点在屏幕左下角，所以要对maxX,maxY进行修正，它们的大小要减去可视区域大小
    maxX-=visibleSize.width;
    maxY-=visibleSize.height;
 
    m_pGameCamera->setNeedCheckPositionRane(true);
    m_pGameCamera->setMoveRange(minX,minY,maxX,maxY);
}

/**
 * 创建测试按钮
 */
void GameWorldController::createTestMenu()
{
    CCSize visibleSize =this->getPreferredContentSize();
    
    CCMenuItemLabel *pItem=CCMenuItemLabel::create(CCLabelTTF::create("big", "Arial", 26),
                                                   this,
                                                   menu_selector(GameWorldController::menuBigCallback));
    
    CCMenuItemLabel *pItem2=CCMenuItemLabel::create(CCLabelTTF::create("small", "Arial", 26),
                                                    this,
                                                    menu_selector(GameWorldController::menuSmallCallback));
    
    CCMenu* pMenu = CCMenu::create(pItem,pItem2, NULL);
	pMenu->setPosition( ccp(visibleSize.width/2,30) );
	pMenu->alignItemsHorizontallyWithPadding(20);
    m_view->addChild(pMenu, 1);
}

//void GameWorldController::setupNetWork()
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->connectServer("10.10.49.217",8124);
//	//gameClient->login();
//	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameWorldController::say),this,10,false);
//}
//
//void GameWorldController::say(float delta)
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->say("hello every one");
//}


/**
 * 增加一个主角
 * @param {CCPoint} coord 地图坐标
 */
void GameWorldController::addPlayerAtCoord(CCPoint coord)
{
    CCSize visibleSize=this->getPreferredContentSize();
    CCPoint pos=ccp(visibleSize.width/2,visibleSize.height/2);
    pos=m_view->convertToWorldSpace(pos);
    
    GameEntity* player=EntityFactory::getInstance()->createPlayer(2);
    setPlayer(player);
    
    ISOPositionComponent* iosPositionComponent=static_cast<ISOPositionComponent*>(m_player->getComponent("ISOPositionComponent"));
    iosPositionComponent->setCoordinate(coord);
    iosPositionComponent->updateRendererPosition();
    
    //set animation
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_player,data);

    CameraFlowGridMoveComponent* gridMoveComponent=static_cast<CameraFlowGridMoveComponent*>(m_player->getComponent("GridMoveComponent"));
    gridMoveComponent->setCamera(m_pGameCamera);
    gridMoveComponent->setInnerOrigin(pos);

    RendererComponent* rendererComponent=static_cast<RendererComponent*>(m_player->getComponent("RendererComponent"));
    m_activeLayer->addChild(rendererComponent->getRenderer());
    
//    m_activeLayer->addDynamicObject(player);
    
}


void GameWorldController::addTeammateAtCoord(CCPoint coord)
{
//	Player* player=new Player();
//	player->init(3);
//	player->setCoordinateAndTranslate(coord);
//	player->setGameWorld(this);
//	player->setupComponents();
//	addInterMediateDynamicEntity(player);
//	player->release();
}

/**
 * 移动主角
 * @param {CCPoint} location 视图坐标
 */
void GameWorldController::movePlayerToViewLocation(CCPoint location)
{
//	moveViewEntity(m_pPlayer,location);
}

//void GameWorldController::moveViewEntity(Unit* entity,CCPoint location)
//{
//	CCPoint coord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(location));
//	moveEntity(entity,coord);
//}

//void GameWorldController::moveEntity(Unit* entity,CCPoint coord)
//{
//    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, entity,&coord);
//}

/**
 * 对寻路算法的封装
 */
CCArray* GameWorldController::searchPathsFrom(int fromX ,int fromY ,int toX ,int toY)
{
	m_astar->reset();
	m_astar->setStart(fromX ,fromY);
	m_astar->setEnd(toX ,toY);
	
	return m_astar->search()?m_astar->getPathWithEnd():NULL;
}

/**
 * 对寻路算法的封装
 * 返回的数组要手动释放
 */
CCArray* GameWorldController::searchPathsFrom(CCPoint from ,CCPoint to )
{
	m_astar->reset();
	m_astar->setStart((int)from.x ,(int) from.y);
	m_astar->setEnd((int)to.x ,(int) to.y);
    
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
	bool result=m_astar->search();
    gettimeofday(&end,NULL);
    CCLOG("use:%d",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    
	return result?m_astar->getPathWithEnd():NULL;
}

/**
 * 地图格子转成视图坐标(视图坐标不同于屏幕坐标)
 * 返回的数组要手动释放
 */
CCArray* GameWorldController::mapPathsToViewPaths(CCArray* paths)
{
	if (paths) {
        
		CCArray *newPaths=CCArray::createWithCapacity(paths->count());
        
		CCPointValue* it=NULL;
		CCObject* pObj=NULL;

        CCPoint toPos;
        
		CCARRAY_FOREACH(paths,pObj){
			it=(CCPointValue*)pObj;
            toPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(it->getPoint()));
			newPaths->addObject(CCPointValue::create(toPos));
		}
		return newPaths;
	}else {
		return NULL;
	}
}


bool GameWorldController::isWorkable(int x ,int y)
{
    return true;
}

CCPoint GameWorldController::toGameCoordinate(const CCPoint& position)
{
    return YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(m_pGameCamera->getLocationInWorld(position)));
}

CCPoint GameWorldController::toGameCoordinate(float x,float y)
{
    return YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(m_pGameCamera->getLocationInWorld(ccp(x,y))));
}

void GameWorldController::updateMapPosition(const CCPoint& position)
{
    m_isoMap->setPosition(ccpNeg(position));
    m_isoMap->scrollLayer(position);
}

void GameWorldController::updateMapPosition(float x,float y)
{
    updateMapPosition(ccp(x,y));
}

bool  GameWorldController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //GL coordinates
    CCPoint touchPoint = pTouch->getLocation(); 
	
	m_bIsTouchMoved=false;
	m_startTouchLocation=touchPoint;
    m_startPoint=m_view->getPosition();
	m_lastTouchLocation=touchPoint;

	CCPoint mapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(m_pGameCamera->getLocationInWorld(touchPoint)));
	CCLOG("touch began view cood:%f,%f,map:%f,%f",touchPoint.x,touchPoint.y,mapCoord.x,mapCoord.y);
	return true;
}

void  GameWorldController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	float dx=touchPoint.x-m_startTouchLocation.x;
	float dy=touchPoint.y-m_startTouchLocation.y;
	if(abs(dx)>MoveSmallDistance || abs(dy)>MoveSmallDistance){
		m_bIsTouchMoved=true;
		m_pGameCamera->moveOpposite(touchPoint.x-m_lastTouchLocation.x,touchPoint.y-m_lastTouchLocation.y);
       
		m_lastTouchLocation=touchPoint;
        
	}
}

void  GameWorldController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!m_bIsTouchMoved){
		 CCPoint touchPoint = pTouch->getLocation();
		 touchPoint=m_pGameCamera->getLocationInWorld(touchPoint);
		 CCPoint to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(touchPoint));
		 //如果player正在移动，则此时取到的坐标和最终停下来的不一致。
//		 CCPoint from=m_pPlayer->getCoordinate();
//    
         ISOPositionComponent* isoPosition=m_player->getISOPositionComponent();

		 CCArray* paths=searchPathsFrom(ccp(isoPosition->getX(),isoPosition->getY()),to);
		 if(paths){
             CCObject* pObj=NULL;
             CCPoint pos;
             std::string pathStr="";
             CCARRAY_FOREACH(paths, pObj){
                 pos=static_cast<CCPointValue*>(pObj)->getPoint();
                 pathStr+=CCString::createWithFormat("%d,%d:",(int)pos.x,(int)pos.y)->getCString();
             }
             CCLOG("path:%s",pathStr.c_str());
			 MessageManager::defaultManager()->dispatchMessage(MSG_MOVE_PATH, NULL, m_player,paths);
//			 paths->release();
		 }
	}
}


/**
 * 相机移动
 * 参数为相机所在的地图位置
 */
void GameWorldController::onCameraMove(const CCPoint& worldPosition)
{
    updateMapPosition(worldPosition);
}

/**
 * 相机缩放
 */
void GameWorldController::onCameraScale(float scaleX,float scaleY)
{
    if (scaleX==scaleY) {
        m_isoMap->setScale(scaleX);
    }
}

void GameWorldController::menuBigCallback(CCObject* pSender)
{
    m_pGameCamera->scaleBy(0.5f);
}

void GameWorldController::menuSmallCallback(CCObject* pSender)
{
    m_pGameCamera->scaleBy(-0.5f);
}



void GameWorldController::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void GameWorldController::menuRunCallback(CCObject* pSender)
{
    //    CCDictionary* data=new CCDictionary();
    //    data->setObject(CCString::create("move"), "name");
    //    data->setObject(CCInteger::create(3), "direction");
    //
    //    CCLOG("set begin action");
    //    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_pPlayer,data);
    //    CCLOG("set begin action after");
    CCPoint p=ccp(1,1);
    
    //    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION, NULL, m_pPlayer,&p);
    
}

void GameWorldController::menuStopCallback(CCObject* pSender)
{
    //    CCDictionary* data=new CCDictionary();
    //    data->setObject(CCString::create("idle"), "name");
    //    data->setObject(CCInteger::create(0), "direction");
    //
    //    CCLOG("set begin action");
    //    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_pPlayer,data);
    //    CCLOG("set begin action after");
    
    
    //    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION_STOP, NULL, m_pPlayer);
}

void GameWorldController::menuMoveToCallback(CCObject* pSender)
{
    
    
    //    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    //    CCPoint to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGame2F(screenSize.width/2+50,screenSize.height/2+50));
    //	CCPoint from=m_pPlayer->getCoordinate();
    //
    //	CCArray* paths=searchPathsFrom(from,to);
    //    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
    //	paths->release();
}


NS_CC_GE_END