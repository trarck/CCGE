#include "TestISOController.h"
#include <yhge/isometric.h>
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
    isoXmlParser->initWithTMXFile("map/iso-test.tmx");
    
    ISOMapInfo* mapInfo=isoXmlParser->getMapInfo();
    
    CCLOG("tileset count:%d",mapInfo->getTilesets()->count());
    ISOTilesetInfo* tilesetInfo=(ISOTilesetInfo*)mapInfo->getTilesets()->objectAtIndex(0);
    CCLOG("tiles count:%d,%s\n%f,%f",tilesetInfo->getTiles()->count(),tilesetInfo->getImageSource(),tilesetInfo->getImageSize().width,tilesetInfo->getImageSize().height);
    
    ISOTileMap* isoMap=new ISOTileMap();
    isoMap->init();
    m_layer->addChild(isoMap,0,kLayerTagTestIsoLayer);
    
    struct timeval now;
    gettimeofday(&now,NULL);
    ISOTileMapBuilder* mapBuilder=new ISOTileMapBuilder();
    mapBuilder->init(isoMap);
	mapBuilder->setMapLayerType(ISOTileMapBuilder::BatchDynamicLayerType);
    mapBuilder->buildWithMapInfo(mapInfo);
    
    struct timeval end;
    gettimeofday(&end,NULL);
    
    CCLOG("use:%ld,%d", end.tv_sec-now.tv_sec,end.tv_usec-now.tv_usec);
	

}


NS_CC_GE_END