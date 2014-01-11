#include "ThreeSegmentController.h"
#include "yhmvc/Core/Layer.h"
#include "Scenes/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

ThreeSegmentController::ThreeSegmentController(void)
:m_headerLayer(NULL)
,m_footerLayer(NULL)
,m_bodyLayer(NULL)
{
    m_sName="ThreeSegmentController";
}


ThreeSegmentController::~ThreeSegmentController(void)
{
    
}

void ThreeSegmentController::layerDidLoad()
{
    CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
    
    float headerHeight=60.0f,footerHeight=64.0f;
    
    float bodyHeight=screenSize.height;//-headerHeight-footerHeight;
    
	m_bodyLayer=yhmvc::Layer::create();
    m_bodyLayer->setContentSize(CCSizeMake(screenSize.width, bodyHeight));
    m_bodyLayer->setPosition(ccp(0.0f, 0));
    m_layer->addChild(m_bodyLayer);

    //create three layer
    m_headerLayer=yhmvc::Layer::create();
    m_headerLayer->setContentSize(CCSizeMake(screenSize.width, headerHeight));
    m_headerLayer->setPosition(ccp(0.0f, screenSize.height-headerHeight));
    m_layer->addChild(m_headerLayer);
    
    m_footerLayer=yhmvc::Layer::create();
    m_footerLayer->setContentSize(CCSizeMake(screenSize.width,footerHeight));
    m_layer->addChild(m_footerLayer);
    

}

NS_CC_GE_END