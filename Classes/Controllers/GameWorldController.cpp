#include "GameWorldController.h"
#include "Game.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const int kGameMapZOrder=1;
static const int kFullSceneEffectZOrder=2;

static const float MoveSmallDistance=3;

GameWorldController::GameWorldController()
:m_zoneId(0)
,m_mapId(0)
,m_iMapColumn(0)
,m_iMapRow(0)
,m_bIsTouchMoved(true)
,m_pUnits(NULL)
,m_pGameCamera(NULL)
,m_isoMap(NULL)
{
	CCLOG("GameWorldController create");
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
//	CC_SAFE_RELEASE(m_pPlayer);
	CC_SAFE_RELEASE(m_pUnits);

    CC_SAFE_RELEASE_NULL(m_isoMap);
    
	CCLOG("GameWorldController destroy end");
}

// on "init" you need to initialize your instance
bool GameWorldController::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerController::init() )
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

void GameWorldController::layerDidLoad()
{
    LayerController::layerDidLoad();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);
    this->setup();
}

void GameWorldController::onLayerExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    LayerController::onLayerExit();
}

void GameWorldController::setup()
{
    CCSize contentSize= this->getPreferredContentSize();
	//m_pUnits=new CCArray(10);

	m_pGameCamera=new ISOCamera();
	m_pGameCamera->init();
	m_pGameCamera->setMoveDelegate(this);

    setupUtil();
    
    
    
    //base
	this->createGameMap();
	//objects
//	loadBackground();
//	loadInterMediate();
	
    m_pGameCamera->scaleTo(2);
	//setupNetWork();
    m_pGameCamera->moveTo(-contentSize.width/2, 0);
    
    createTestMenu();
}

/**
 * 初始化一些工具方法
 * 寻路，坐标转换
 */
void GameWorldController::setupUtil()
{
	//astar search
//	CC_SAFE_RELEASE(m_pAstar);
//	m_pAstar=new CCAstar();
//	m_pAstar->init();
//	m_pAstar->setBounding(0,0,m_iMapColumn,m_iMapRow);
//	m_pAstar->setCheckBarrierHandle(check_barrier_selector(GameWorldController::isWorkable),this);
	
	//CC_SAFE_RELEASE(m_pZIndex);
	//m_pZIndex=new CCZIndex();
	//m_pZIndex->init(m_pIntermediate);
	//m_pZIndex->start();
	//m_pZIndex->release();
}


/**
 * 设置游戏地图
 */
void GameWorldController::createGameMap()
{
    //移除去之前的地图文件
    if (m_isoMap) {
        m_layer->removeChild(m_isoMap);
    }
    
    CCSize visibleSize =this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    //取得要使用的layer渲染类型
    int mapLyaerType=ISOTileMapBuilder::BatchLayerType;
    
    CCInteger* mapLyaerTypeValue=static_cast<CCInteger*>(Game::getInstance()->getSceneContext());
    
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
    mapBuilder->buildWithMapInfo(mapInfo);
    
    struct timeval end;
    gettimeofday(&end,NULL);
    
    CCLOG("use:%ld", (end.tv_sec-now.tv_sec)*1000000+end.tv_usec-now.tv_usec);
    
    //构建dynamic group
    //    m_isoMap->setupDynamicGroup();
    m_isoMap->showCoordLine();
    
    m_layer->addChild(m_isoMap,kGameMapZOrder);
    
    //m_isoMap->release();
    
}

ISOMapInfo* GameWorldController::loadMapData()
{
    //解析地图数据
    ISOXMLParser* isoXmlParser=new ISOXMLParser();
    isoXmlParser->setTranslateLayerData(true);
    isoXmlParser->setTranslateObjectCoord(true);
    isoXmlParser->initWithTMXFile(CCString::createWithFormat("map/zone/%d_%d.tmx",m_zoneId,m_mapId)->getCString());
    
    ISOMapInfo* mapInfo=isoXmlParser->getMapInfo();
    
    CCLOG("tileset count:%d",mapInfo->getTilesets()->count());
    ISOTilesetInfo* tilesetInfo=(ISOTilesetInfo*)mapInfo->getTilesets()->objectAtIndex(0);
    CCLOG("tiles count:%d,%s\n%f,%f",tilesetInfo->getTiles()->count(),tilesetInfo->getImageSource(),tilesetInfo->getImageSize().width,tilesetInfo->getImageSize().height);
    
    //自动释放
    mapInfo->retain();
    mapInfo->autorelease();
    
    isoXmlParser->release();
    
    return mapInfo;
    
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
    m_layer->addChild(pMenu, 1);
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
//	m_pPlayer=new Player();
//	m_pPlayer->init(2);
//	m_pPlayer->setCoordinateAndTranslate(coord);
//	m_pPlayer->setGameWorld(this);
//	m_pPlayer->setupComponents();
//	addInterMediateDynamicEntity(m_pPlayer);
//	CCLOG("m_pPlayer count:%d",m_pPlayer->retainCount());
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
//	CCPoint coord=isoViewToGamePoint(location);
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
//	m_pAstar->reset();
//	m_pAstar->setStart(fromX ,fromY);
//	m_pAstar->setEnd(toX ,toY);
//	
//	return m_pAstar->search()?m_pAstar->getPathWithEnd():NULL;
    return NULL;
}

/**
 * 对寻路算法的封装
 * 返回的数组要手动释放
 */
CCArray* GameWorldController::searchPathsFrom(CCPoint from ,CCPoint to )
{
//	m_pAstar->reset();
//	m_pAstar->setStart((int)from.x ,(int) from.y);
//	m_pAstar->setEnd((int)to.x ,(int) to.y);
//	bool result=m_pAstar->search();
//	return result?m_pAstar->getPathWithEnd():NULL;
    return NULL;
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
            toPos=isoGameToViewPoint(it->getPoint());
			newPaths->addObject(CCPointValue::create(toPos));
		}
		return newPaths;
	}else {
		return NULL;
	}
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
//    CCPoint to=isoViewToGame2F(screenSize.width/2+50,screenSize.height/2+50);
//	CCPoint from=m_pPlayer->getCoordinate();
//    
//	CCArray* paths=searchPathsFrom(from,to);
//    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
//	paths->release();
}

bool  GameWorldController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //GL coordinates
    CCPoint touchPoint = pTouch->getLocation(); 
	
	m_bIsTouchMoved=false;
	m_startTouchLocation=touchPoint;
    m_startPoint=m_layer->getPosition();
	m_lastTouchLocation=touchPoint;

	CCPoint mapCoord=isoViewToGamePoint(m_pGameCamera->getLocationInWorld(touchPoint));
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
		 CCPoint to=isoViewToGamePoint(touchPoint);
		 //如果player正在移动，则此时取到的坐标和最终停下来的不一致。
//		 CCPoint from=m_pPlayer->getCoordinate();
//    
//		 CCArray* paths=searchPathsFrom(from,to);
//		 if(paths){
//			 CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
//			 paths->release();
//		 }
	}
}


/**
 * 相机移动
 * 参数为相机所在的地图位置
 */
void GameWorldController::onCameraMove(const CCPoint& worldPosition)
{
    m_isoMap->setPosition(ccpNeg(worldPosition));
    m_isoMap->scrollLayer(worldPosition);
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

void GameWorldController::updateMapPosition(const CCPoint& position)
{
    m_isoMap->scrollLayer(position);
}

void GameWorldController::updateMapPosition(float x,float y)
{
    updateMapPosition(ccp(x,y));
}

void GameWorldController::menuBigCallback(CCObject* pSender)
{
    m_pGameCamera->scaleBy(0.5f);
}

void GameWorldController::menuSmallCallback(CCObject* pSender)
{
    m_pGameCamera->scaleBy(-0.5f);
}

CCPoint GameWorldController::toGameCoordinate(const CCPoint& position)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(position));
}

CCPoint GameWorldController::toGameCoordinate(float x,float y)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(ccp(x,y)));
}


bool GameWorldController::isWorkable(int x ,int y)
{
    return true;
}

NS_CC_GE_END