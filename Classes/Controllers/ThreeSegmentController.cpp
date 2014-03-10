#include "ThreeSegmentController.h"
#include "yhmvc/Core/View.h"
#include "SceneDirector/GameSceneDirector.h"

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
    CCLOG("ThreeSegmentController destroy");
}

void ThreeSegmentController::viewDidLoad()
{
    CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
    
    float headerHeight=60.0f,footerHeight=64.0f;
    
    float bodyHeight=screenSize.height;//-headerHeight-footerHeight;
    
	m_bodyLayer=yhmvc::View::create();
    m_bodyLayer->setContentSize(CCSizeMake(screenSize.width, bodyHeight));
    m_bodyLayer->setPosition(ccp(0.0f, 0));
    m_view->addChild(m_bodyLayer);

    //create three layer
    m_headerLayer=yhmvc::View::create();
    m_headerLayer->setContentSize(CCSizeMake(screenSize.width, headerHeight));
    m_headerLayer->setPosition(ccp(0.0f, screenSize.height-headerHeight));
    m_view->addChild(m_headerLayer);
    
    m_footerLayer=yhmvc::View::create();
    m_footerLayer->setContentSize(CCSizeMake(screenSize.width,footerHeight));
    m_view->addChild(m_footerLayer);
    

}

NS_CC_GE_END