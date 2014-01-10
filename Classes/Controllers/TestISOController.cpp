#include "TestISOController.h"
#include <yhge/isometric.h>
#include "Game.h"
#include "Scenes/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHGE;
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

void TestISOController::layerDidLoad()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    ISOXMLParser* isoXmlParser=new ISOXMLParser();
    isoXmlParser->setTranslateLayerData(true);
    isoXmlParser->setTranslateObjectCoord(true);
    isoXmlParser->initWithTMXFile("map/iso-test.tmx");
    
    ISOMapInfo* mapInfo=isoXmlParser->getMapInfo();
    
    CCLOG("tileset count:%d",mapInfo->getTilesets()->count());
    ISOTilesetInfo* tilesetInfo=(ISOTilesetInfo*)mapInfo->getTilesets()->objectAtIndex(0);
    CCLOG("tiles count:%d,%s\n%f,%f",tilesetInfo->getTiles()->count(),tilesetInfo->getImageSource(),tilesetInfo->getImageSize().width,tilesetInfo->getImageSize().height);
    
    m_isoMap=new ISOTileMap();
    m_isoMap->init();
    m_isoMap->setScale(2);
    
    m_layer->addChild(m_isoMap,0,kLayerTagTestIsoLayer);
    m_isoMap->release();

    int mapLyaerType=ISOTileMapBuilder::NormalLayerType;
    
    CCInteger* mapLyaerTypeValue=static_cast<CCInteger*>(Game::getInstance()->getSceneContext());
    
    if (mapLyaerTypeValue) {
        mapLyaerType=mapLyaerTypeValue->getValue();
    }
    
    struct timeval now;
    gettimeofday(&now,NULL);
    ISOTileMapBuilder* mapBuilder=new ISOTileMapBuilder();
    mapBuilder->init(m_isoMap);
	mapBuilder->setMapLayerType(mapLyaerType);
    mapBuilder->buildWithMapInfo(mapInfo);
    

    struct timeval end;
    gettimeofday(&end,NULL);
    
    CCLOG("use:%ld,%d", end.tv_sec-now.tv_sec,end.tv_usec-now.tv_usec);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);
}

void TestISOController::onLayerExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    LayerController::onLayerExit();
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
    m_isoMapStartPosition=ccpAdd(m_isoMapStartPosition, pos);
}


NS_CC_GE_END