#include "BattleController.h"
#include <yhgui/yhgui.h>
#include <yhge/yhge.h>
#include "Game.h"
#include "Consts/GameDefine.h"
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

/*
 格子分布
 
      row
 
 col  7   4   1         1   4   7
 
      8   5   2         2   5   8
     
      9   6   3         3   6   9
 */

void BattleController::convertCoord(int index,int* col,int* row,int* x,int* y)
{
    *col=index%kBattleCellCol;
    *row=index/kBattleCellCol;
    
    //x=kBattleCellCol-row-1
    //y=kBattleCellRow-col-1;
    *x=kBattleCellRow-*row-1;
    *y=kBattleCellCol-*col-1;
}

void BattleController::loadSelfEntities()
{
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    int teamSize=9;
    for (int i=0; i<teamSize; ++i) {
        
        convertCoord(i, &col, &row, &x, &y);
        
        GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(2);
        
        //set animation
        CCDictionary* data=new CCDictionary();
        data->setObject(CCString::create("idle"), "name");
        data->setObject(CCInteger::create(0), "direction");
        MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
        
        RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
        CCNode* renderer=rendererComponent->getRenderer();
        
        renderer->setScale(1.5f);
        
        //y方向居中对齐，坐标要加0.5
        CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(x,y+0.5);
        
        pos.x+=kBattleSelfOffsetX+x*kBattleCellOffsetX;
        pos.y+=kBattleSelfOffsetY+y*kBattleCellOffsetY;
        
        renderer->setPosition(pos);
        
        renderer->setZOrder(kBattleCellRow-i%kBattleCellRow);
        
        m_view->addChild(renderer);
    }
}

void BattleController::loadOppEntities()
{
    
    int col=0;
    int row=0;
    int x=0;
    int y=0;
    
    int teamSize=9;
    
    for (int i=0; i<teamSize; ++i) {
        
        convertCoord(i, &col, &row, &x, &y);
        
        GameEntity* entity=EntityFactory::getInstance()->createBattlePlayer(3);
        
        //set animation
        CCDictionary* data=new CCDictionary();
        data->setObject(CCString::create("idle"), "name");
        data->setObject(CCInteger::create(1), "direction");
        MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, entity,data);
        
        RendererComponent* rendererComponent=static_cast<RendererComponent*>(entity->getComponent("RendererComponent"));
        CCNode* renderer=rendererComponent->getRenderer();
        
        renderer->setScale(1.5f);
        
        //y方向居中对齐，坐标要加0.5
        CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(x+kBattleOppOffsetCell,y+0.5);
        
        pos.x+=kBattleOppOffsetX+x*kBattleCellOffsetX;
        pos.y+=kBattleOppOffsetY+y*kBattleCellOffsetY;
        
        renderer->setPosition(pos);
        
        renderer->setZOrder(kBattleCellRow-i%kBattleCellRow);
        
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