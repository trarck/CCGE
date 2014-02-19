#include "BattlePrepareController.h"
#include "Game.h"
#include "EntityComponent/EntityFactory.h"
#include "Scenes/GameSceneDirector.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

BattlePrepareController::BattlePrepareController(void)
{
    m_sName="BattlePrepareController";
}

BattlePrepareController::~BattlePrepareController(void)
{
    CCLOG("BattlePrepareController destroy");
}

void BattlePrepareController::layerDidLoad()
{

}

void BattlePrepareController::onLayerExit()
{
    LayerController::onLayerExit();
}

void BattlePrepareController::getBattleData()
{
    
}

void BattlePrepareController::loadResource()
{
    
}

NS_CC_GE_END