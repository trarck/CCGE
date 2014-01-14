#include "GameWorld.h"
#include "Game.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

enum{
	kLayerTagTestIsoLayer=1,
    kLayerTagTestIsoLayerDynamic
};
int mapItemGid=0;

static const int kGameMapZOrder=1;
static const int kFullSceneEffectZOrder=2;

static const float MoveSmallDistance=3;

GameWorld::GameWorld()
:m_zoneId(0)
,m_mapId(0)
,m_iMapColumn(0)
,m_iMapRow(0)
,m_bIsTouchMoved(true)
,m_pUnits(NULL)
{
	CCLOG("GameWorld create");
}

GameWorld::~GameWorld()
{
	CCLOG("GameWorld destroy begin");
	//CCLOG("player retain:%d",m_pPlayer->retainCount());
	CC_SAFE_RELEASE_NULL(m_pGameCamera);
	//在创建的时候已经添加到自动释放池里了。
	//CC_SAFE_RELEASE(m_pBackground);
	//CC_SAFE_RELEASE(m_pIntermediate);
	//CC_SAFE_RELEASE(m_pForeground);
	//CCLOG("player retain:%d",m_pPlayer->retainCount());
//	CC_SAFE_RELEASE(m_pPlayer);
	CC_SAFE_RELEASE(m_pUnits);
    
	CCLOG("GameWorld destroy end");
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
//    this->setScale(8);

	m_iMapColumn=20;
	m_iMapRow=20;

    ccDrawColor4B(0,255, 0, 255);
	//add coord line
//	ISOCoordinateLayer* coordLayer=ISOCoordinateLayer::create();
//	coordLayer->setMapWidth(m_iMapColumn);
//	coordLayer->setMapHeight(m_iMapRow);
//	this->addChild(coordLayer,100);
    
//    CCLayerColor* tempLayer=CCLayerColor::create(ccc4(0,0,255,255), 1000.0f, 1000.0f);
//    this->addChild(tempLayer);
    
    
//    CCSpriteBatchNode* bn=CCSpriteBatchNode::create("map/iso.png");
//    
//    CCTexture2D* texture=bn->getTexture();
//    
//    texture->setAliasTexParameters();
//    
//    CCRect rect;
//    rect.origin=ccp(0,0);
//    rect.size=CCSizeMake(64, 32);
//    
//    CCSprite* cellTile=CCSprite::createWithTexture(texture,rect);
//    cellTile->setAnchorPoint(ccp(0,0));
//
//    CCPoint pos=positionForIsoAt(1, 1);
//    pos.y=-pos.y;
//    CCLOG("init:%f,%f",pos.x,pos.y);
//    cellTile->setPosition(pos);
//
//    cellTile->setBatchNode(bn);
//    bn->addChild(cellTile);
//
//
//    cellTile=CCSprite::createWithTexture(texture,rect);
//    cellTile->setAnchorPoint(ccp(0,0));
//    
//    pos=positionForIsoAt(1, 0);
//    pos.y=-pos.y;
//    CCLOG("init:%f,%f",pos.x,pos.y);
//    cellTile->setPosition(pos);
//    
//    cellTile->setBatchNode(bn);
//    bn->addChild(cellTile);
//    
//    cellTile=CCSprite::createWithTexture(texture,rect);
//    cellTile->setAnchorPoint(ccp(0,0));
//    
//    pos=positionForIsoAt(0, 1);
//    pos.y=-pos.y;
//    CCLOG("init:%f,%f",pos.x,pos.y);
//    cellTile->setPosition(pos);
//
//    cellTile->setBatchNode(bn);
//    bn->addChild(cellTile);
//    
//    cellTile=CCSprite::createWithTexture(texture,rect);
//    cellTile->setAnchorPoint(ccp(0,0));
//    
//    pos=positionForIsoAt(0, 0);
//    pos.y=-pos.y;
//    CCLOG("init:%f,%f",pos.x,pos.y);
//    cellTile->setPosition(pos);
//
//    cellTile->setBatchNode(bn);
//    bn->addChild(cellTile);
//    
//    bn->setPosition(ccp(0,100));
//    
//    this->addChild(bn);
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
 //   float scaleX=screenSize.width/480;
	//float scaleY=screenSize.height/320;
	//this->setScale(scaleX>scaleY?scaleY:scaleX);

	//screenSize=CCSizeMake(480,320);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(GameWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );
//    
//    CCMenuItemLabel *pRunItem=CCMenuItemLabel::create(CCLabelTTF::create("run", "Arial", 12),
//                                                      this, 
//                                                      menu_selector(GameWorld::menuRunCallback));
//    pRunItem->setPosition(ccp(screenSize.width-60,20));
//    
//    CCMenuItemLabel *pStopItem=CCMenuItemLabel::create(CCLabelTTF::create("stop", "Arial", 12),
//                                                      this, 
//                                                      menu_selector(GameWorld::menuStopCallback));
//    pStopItem->setPosition(ccp(screenSize.width-90,20));
//    
//    CCMenuItemLabel *pMoveToItem=CCMenuItemLabel::create(CCLabelTTF::create("moveTo", "Arial", 12),
//                                                       this, 
//                                                       menu_selector(GameWorld::menuMoveToCallback));
//    pMoveToItem->setPosition(ccp(screenSize.width-120,20));
//    
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem,pRunItem,pStopItem,pMoveToItem, NULL);
//    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu, 1);

    
	return true;
}

bool GameWorld::init(int zoneId,int mapId)
{
	init();
	m_zoneId=zoneId;
    m_mapId=mapId;
	return true;
}
void GameWorld::setup()
{
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//m_pUnits=new CCArray(10);

	m_pGameCamera=new ISOCamera();
	m_pGameCamera->init();
	m_pGameCamera->setMoveDelegate(this);
    
	//base
	createGameMap();

    setupUtil();
    
	//objects
//	loadBackground();
//	loadInterMediate();
	
	//setupNetWork();
    m_pGameCamera->moveTo(-screenSize.width/2, 0);
}

/**
 * 初始化一些工具方法
 * 寻路，坐标转换
 */
void GameWorld::setupUtil()
{
	//astar search
//	CC_SAFE_RELEASE(m_pAstar);
//	m_pAstar=new CCAstar();
//	m_pAstar->init();
//	m_pAstar->setBounding(0,0,m_iMapColumn,m_iMapRow);
//	m_pAstar->setCheckBarrierHandle(check_barrier_selector(GameWorld::isWorkable),this);
	
	//CC_SAFE_RELEASE(m_pZIndex);
	//m_pZIndex=new CCZIndex();
	//m_pZIndex->init(m_pIntermediate);
	//m_pZIndex->start();
	//m_pZIndex->release();
}


/**
 * 设置游戏地图
 */
void GameWorld::createGameMap()
{
    //移除去之前的地图文件
    if (m_isoMap) {
        this->removeChild(m_isoMap);
    }
    
    CCSize visibleSize =this->getContentSize();//CCSizeMake(480,240);//
    
    //取得要使用的layer渲染类型
    int mapLyaerType=ISOTileMapBuilder::NormalLayerType;
    
    CCInteger* mapLyaerTypeValue=static_cast<CCInteger*>(Game::getInstance()->getSceneContext());
    
    if (mapLyaerTypeValue) {
        mapLyaerType=mapLyaerTypeValue->getValue();
    }
    
    //加载数据
    ISOMapInfo* mapInfo=loadMapData();
    
    //构建地图
    m_isoMap=new ISOTileMap();
    m_isoMap->init();
    m_isoMap->setScale(4);
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
    
    this->addChild(m_isoMap,kGameMapZOrder);
    
    m_isoMap->release();
    
}

ISOMapInfo* GameWorld::loadMapData()
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


//void GameWorld::setupNetWork()
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->connectServer("10.10.49.217",8124);
//	//gameClient->login();
//	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameWorld::say),this,10,false);
//}
//
//void GameWorld::say(float delta)
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->say("hello every one");
//}


/**
 * 增加一个主角
 * @param {CCPoint} coord 地图坐标
 */
void GameWorld::addPlayerAtCoord(CCPoint coord)
{
//	m_pPlayer=new Player();
//	m_pPlayer->init(2);
//	m_pPlayer->setCoordinateAndTranslate(coord);
//	m_pPlayer->setGameWorld(this);
//	m_pPlayer->setupComponents();
//	addInterMediateDynamicEntity(m_pPlayer);
//	CCLOG("m_pPlayer count:%d",m_pPlayer->retainCount());
}


void GameWorld::addTeammateAtCoord(CCPoint coord)
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
void GameWorld::movePlayerToViewLocation(CCPoint location)
{
//	moveViewEntity(m_pPlayer,location);
}

//void GameWorld::moveViewEntity(Unit* entity,CCPoint location)
//{
//	CCPoint coord=isoViewToGamePoint(location);
//	moveEntity(entity,coord);
//}

//void GameWorld::moveEntity(Unit* entity,CCPoint coord)
//{
//    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, entity,&coord);
//}

/**
 * 对寻路算法的封装
 */
CCArray* GameWorld::searchPathsFrom(int fromX ,int fromY ,int toX ,int toY)
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
CCArray* GameWorld::searchPathsFrom(CCPoint from ,CCPoint to )
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
CCArray* GameWorld::mapPathsToViewPaths(CCArray* paths)
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

void GameWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameWorld::menuRunCallback(CCObject* pSender)
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

void GameWorld::menuStopCallback(CCObject* pSender)
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

void GameWorld::menuMoveToCallback(CCObject* pSender)
{
   
    
//    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
//    CCPoint to=isoViewToGame2F(screenSize.width/2+50,screenSize.height/2+50);
//	CCPoint from=m_pPlayer->getCoordinate();
//    
//	CCArray* paths=searchPathsFrom(from,to);
//    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
//	paths->release();
}

bool  GameWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //GL coordinates
    CCPoint touchPoint = pTouch->getLocation(); 
	
	m_bIsTouchMoved=false;
	m_startTouchLocation=touchPoint;
	m_startPoint=this->getPosition();
	m_lastTouchLocation=touchPoint;

	CCPoint mapCoord=isoViewToGamePoint(m_pGameCamera->getLocationInWorld(touchPoint));
	CCLOG("touch began view cood:%f,%f,map:%f,%f",touchPoint.x,touchPoint.y,mapCoord.x,mapCoord.y);
	return true;
}

void  GameWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

void  GameWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
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
void GameWorld::onCameraMove(const CCPoint& worldPosition)
{
    m_isoMap->setPosition(ccpNeg(worldPosition));
    m_isoMap->scrollLayer(worldPosition);
}

void GameWorld::updateMapPosition(const CCPoint& position)
{
    m_isoMap->scrollLayer(position);
}

void GameWorld::updateMapPosition(float x,float y)
{
    updateMapPosition(ccp(x,y));
}

CCPoint GameWorld::toGameCoordinate(const CCPoint& position)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(position));
}

CCPoint GameWorld::toGameCoordinate(float x,float y)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(ccp(x,y)));
}


bool GameWorld::isWorkable(int x ,int y)
{
    return true;
}

NS_CC_GE_END