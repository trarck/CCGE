#include "TestISOController.h"
#include <yhge/isometric.h>
#include "Game.h"
#include "SceneDirector/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

enum{
	kLayerTagTestIsoLayer=1,
    kLayerTagTestIsoLayerDynamic
};

TestISOController::TestISOController(void)
{
    
}


TestISOController::~TestISOController(void)
{
    CCLOG("TestISOController destroy");
}

void TestISOController::viewDidLoad()
{
    
    ISOStaticCoordinate::initTileSize(64, 32);

    
    CCSize visibleSize =  this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    //取得要使用的layer渲染类型
    int mapLyaerType=ISOTileMapBuilder::NormalLayerType;
    
    CCInteger* mapLyaerTypeValue=static_cast<CCInteger*>(GameSceneDirector::getInstance()->getSceneContext());
    
    if (mapLyaerTypeValue) {
        mapLyaerType=mapLyaerTypeValue->getValue();
    }

    //解析地图数据
    ISOXMLParser* isoXmlParser=new ISOXMLParser();
    isoXmlParser->setTranslateLayerData(true);
    isoXmlParser->setTranslateObjectCoord(true);
    isoXmlParser->initWithTMXFile("map/iso-test.tmx");
    
    ISOMapInfo* mapInfo=isoXmlParser->getMapInfo();
    
    CCLOG("tileset count:%d",mapInfo->getTilesets()->count());
    ISOTilesetInfo* tilesetInfo=(ISOTilesetInfo*)mapInfo->getTilesets()->objectAtIndex(0);
    CCLOG("tiles count:%d,%s\n%f,%f",tilesetInfo->getTiles()->count(),tilesetInfo->getImageSource(),tilesetInfo->getImageSize().width,tilesetInfo->getImageSize().height);
    
    //构建地图
    m_isoMap=new ISOTileMap();
    m_isoMap->init();
    m_isoMap->setScale(1);
	m_isoMap->setVisibleSize(visibleSize);
    m_isoMap->setUseDynamicGroup(true);
      
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
    m_isoMap->setupDynamicGroup();
    
    m_view->addChild(m_isoMap,0,kLayerTagTestIsoLayer);
    m_isoMap->release();

	m_isoMap->showCoordLine();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);
    
    CCPoint offset=ccp(32,0);
    m_isoMap->setPosition(offset);
    m_isoMap->scrollLayer(ccpNeg(offset));
    
    CCMenuItemLabel *pItem=CCMenuItemLabel::create(CCLabelTTF::create("big", "Arial", 26),
                                                   this,
                                                   menu_selector(TestISOController::menuBigCallback));
    
    CCMenuItemLabel *pItem2=CCMenuItemLabel::create(CCLabelTTF::create("small", "Arial", 26),
                                                   this,
                                                   menu_selector(TestISOController::menuSmallCallback));
    
    CCMenu* pMenu = CCMenu::create(pItem,pItem2, NULL);
	pMenu->setPosition( ccp(visibleSize.width/2,30) );
	pMenu->alignItemsHorizontallyWithPadding(20);
    m_view->addChild(pMenu, 1);
}

void TestISOController::onViewExit()
{
    ISOStaticCoordinate::initTileSize(120, 60);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Controller::onViewExit();
}

bool TestISOController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_touchStartPosition=pTouch->getLocation();
	m_isoMapStartPosition=m_isoMap->getPosition();
	return true;
}

void TestISOController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos=pTouch->getLocation();
	pos=ccpSub(pos,m_touchStartPosition);

    CCPoint mapPos=ccpAdd(m_isoMapStartPosition,pos);
    
//    CCLOG("diff:%f,%f b:%f,%f",pos.x,pos.y,mapPos.x,mapPos.y);
    
	m_isoMap->setPosition(mapPos);
	m_isoMap->scrollLayer(ccpNeg(mapPos));
}

void TestISOController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pos=pTouch->getLocation();
    pos=ccpSub(m_touchStartPosition,pos);
    
}

void TestISOController::menuBigCallback(CCObject* pSender)
{
    float scale=m_isoMap->getScale();
    
    CCPoint offset=m_isoMap->getPosition();
    
    offset.x/=scale;
    offset.y/=scale;
    
    scale+=0.5;
    
    m_isoMap->setScale(scale);
    
    offset.x*=scale;
    offset.y*=scale;
  
    CCLOG("%f,%f",offset.x,offset.y);
    
    m_isoMap->setPosition(offset);
    m_isoMap->scrollLayer(ccpNeg(offset));
}

void TestISOController::menuSmallCallback(CCObject* pSender)
{
    float scale=m_isoMap->getScale();
    
    CCPoint offset=m_isoMap->getPosition();
    
    offset.x/=scale;
    offset.y/=scale;
    
    scale-=0.5;
    
    m_isoMap->setScale(scale);
    
    offset.x*=scale;
    offset.y*=scale;
    
    CCLOG("%f,%f",offset.x,offset.y);
    
    m_isoMap->setPosition(offset);
    m_isoMap->scrollLayer(ccpNeg(offset));
}

NS_CC_GE_END