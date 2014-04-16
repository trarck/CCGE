#include "BattlePrepareController.h"
#include "Game.h"
#include "Consts/DataDefine.h"
#include "EntityComponent/EntityFactory.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Services/ServiceFactory.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

BattlePrepareController::BattlePrepareController(void)
:m_battleService(NULL)
{
    m_sName="BattlePrepareController";
}

BattlePrepareController::~BattlePrepareController(void)
{
    CCLOG("BattlePrepareController destroy");
}

void BattlePrepareController::viewDidLoad()
{
    CCDictionary* battleParam=static_cast<CCDictionary*>(GameSceneDirector::getInstance()->getSceneContext());
    getBattleData(battleParam);
//    loadResource();
    
    //create test button
    
    CCMenuItemLabel *battleBtn=CCMenuItemLabel::create(CCLabelTTF::create("battle", "Arial", 20),
                                                     this,
                                                     menu_selector(BattlePrepareController::onBattle));
    
    CCMenu* menu=CCMenu::create(battleBtn,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
}

void BattlePrepareController::onViewExit()
{
    Controller::onViewExit();
}

void BattlePrepareController::getBattleData(CCDictionary* battleParam)
{
    CCInteger* battleTypeValue=static_cast<CCInteger*>(battleParam->objectForKey(CCGE_DATA_BATTLE_TYPE));
    int battleType=battleTypeValue->getValue();
    
    CCInteger* oppIdValue=static_cast<CCInteger*>(battleParam->objectForKey(CCGE_DATA_BATTLE_OPPID));
    int oppId=oppIdValue?oppIdValue->getValue():0;
    
    m_battleService=ServiceFactory::getInstance()->getPveBattleService();
    m_battleService->prepareBattle(oppId);
    
    
}

void BattlePrepareController::loadResource()
{
    
}

void BattlePrepareController::gotoBattleScene()
{
    GameSceneDirector::getInstance()->replaceScene(kBattleScene);
}


void BattlePrepareController::onBattle(CCObject* sender)
{
    gotoBattleScene();
}

NS_CC_GE_END