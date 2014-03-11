#include "BattleController.h"
#include <yhgui/yhgui.h>
#include <yhge/yhge.h>
#include "Game.h"
#include "EntityComponent/EntityFactory.h"
#include "SceneDirector/GameSceneDirector.h"
#include "Layers/DimetricCoordinateLayer.h"

USING_NS_CC;
USING_NS_CC_YHGE;
USING_NS_CC_YHMVC;
USING_NS_CC_YHGE_ISOMETRIC;

NS_CC_GE_BEGIN

static const float kGameTileWidth=100;
static const float kGameTileHeight=90;

//static const float kGameTileWidth=120;
//static const float kGameTileHeight=60;

//static const float kGameTileWidth=120;
//static const float kGameTileHeight=48;

BattleController::BattleController(void)
:m_mapId(0)
,m_zoneId(0)
,m_step(0)
{
    m_sName="BattleController";
}

BattleController::~BattleController(void)
{
    CCLOG("BattleController destroy");
}

void BattleController::viewDidLoad()
{
    this->loadBattleGround();
    
    this->loadEntities();
    
    //create test button
    
    CCMenuItemLabel *skipBtn=CCMenuItemLabel::create(CCLabelTTF::create("skip", "Arial", 20),
                                                   this,
                                                   menu_selector(BattleController::onSkip));

    CCMenu* menu=CCMenu::create(skipBtn,NULL);
    menu->alignItemsHorizontally();
    
    m_view->addChild(menu);
    
}

void BattleController::onViewExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Controller::onViewExit();
}

void BattleController::loadBattleGround()
{
    //TODO load by zoneId
    
}

void BattleController::loadEntities()
{
    //加载自己
    this->loadSelfEntities();
    
    //加载对方
    this->loadOppEntities();
    
    //show coordinate line
    DimetricCoordinateLayer* coordLayer=new DimetricCoordinateLayer();
    coordLayer->setMapWidth(20);
    coordLayer->setMapHeight(20);
    coordLayer->setAnchorPoint(ccp(0,0));
    coordLayer->setPosition(ccp(0,1));
    
    m_view->addChild(coordLayer);
    
    coordLayer->release();
}

void BattleController::loadSelfEntities()
{
    CCSize contentSize =  this->getPreferredContentSize();
    
    int teamSize=9;
    int col=3;
    int row=3;
    
    CCPoint offset=ccp(40,20);
    
    for (int i=0; i<teamSize; ++i) {
        
        GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(2);
        
        //set animation
        CCDictionary* data=new CCDictionary();
        data->setObject(CCString::create("idle"), "name");
        data->setObject(CCInteger::create(0), "direction");
        MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
        
        RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
        CCNode* renderer=rendererComponent->getRenderer();
        
        renderer->setScale(1.5f);
        
        //放在格子中，坐标要加0.5
        CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(i/row,i%row+0.5);
        
//        CCPoint pos=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(i/row,i%row+0.5);
        
        pos.x+=offset.x;
        pos.y+=(i%row)*20;
        
        renderer->setPosition(pos);
        
        renderer->setZOrder(row-i%row);
        
        m_view->addChild(renderer);
    }
}

void BattleController::loadOppEntities()
{
    CCSize contentSize =  this->getPreferredContentSize();
    
    int teamSize=9;
    int col=3;
    int row=3;
    
    CCPoint offset=ccp(contentSize.width/2-200,220);
    
//    dimetric::StaticSideViewCoordinateFormulae::initTileSize(120, 20);
    
    int offsetCol=5;
    
    for (int i=0; i<teamSize; ++i) {
        
        GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(3);
        
        //set animation
        CCDictionary* data=new CCDictionary();
        data->setObject(CCString::create("idle"), "name");
        data->setObject(CCInteger::create(1), "direction");
        MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
        
        RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
        CCNode* renderer=rendererComponent->getRenderer();
        
        renderer->setScale(1.5f);
//        CCPoint pos=dimetric::StaticSideViewCoordinateFormulae::gameToView2F(i/row,i%row);
        CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(offsetCol+i/row,i%row+0.5);
        
//        CCLOG("aa:%d,%d,to:%d,%d",i,i%row,(int)pos.x,(int)pos.y);
        
//        pos.x+=offset.x;
//        pos.y+=offset.y;
        pos.y+=(i%row)*20;
        
        renderer->setPosition(pos);
        
        renderer->setZOrder(row-i%row);
        
        m_view->addChild(renderer);
    }
}

void BattleController::start()
{
    parseStep();
}

void BattleController::pause()
{
    
}

void BattleController::stop()
{
    
}

void BattleController::parseStep()
{
    //myself
    for (int i=0; i<kBattleCellCol*kBattleCellRow; ++i) {
        if (m_selfTroops[i]) {
            
            //get entity from model
            
            
        }
    }
    
    //opp
}

/**
 * @brief 战斗结束操作
 */
void BattleController::doBattleEnd()
{
    
}

void BattleController::onSkip(CCObject* pSender)
{
    //goto before battle scene
    GameSceneDirector::getInstance()->setSceneContext(CCInteger::create(ISOTileMapBuilder::BatchLayerType));
    GameSceneDirector::getInstance()->popScene();
}

bool BattleController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BattleController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void BattleController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
NS_CC_GE_END