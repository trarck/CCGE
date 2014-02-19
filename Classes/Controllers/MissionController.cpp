#include "MissionController.h"
#include <yhge/isometric.h>
#include "Game.h"
#include "Scenes/GameSceneDirector.h"


USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHGE_ISOMETRIC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

MissionController::MissionController(void)
:m_gameWorld(NULL)
{
    
}


MissionController::~MissionController(void)
{
    CCLOG("MissionController destroy");
    CC_SAFE_RELEASE_NULL(m_gameWorld);
}

void MissionController::layerDidLoad()
{
    CCSize visibleSize =  this->getPreferredContentSize();//CCSizeMake(480,240);//
    
    m_gameWorld=new GameWorldController();
    m_gameWorld->init(1000, 1);
    m_gameWorld->setPreferredContentSize(visibleSize);
    
    m_layer->addChild(m_gameWorld->getLayer());
    
}

void MissionController::onLayerExit()
{
    LayerController::onLayerExit();
}

void MissionController::doStepEvent()
{
    
}

NS_CC_GE_END