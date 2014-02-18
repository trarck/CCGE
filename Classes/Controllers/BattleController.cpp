#include "BattleController.h"
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

void BattleController::layerDidLoad()
{
    this->loadBattleGround();
    
    this->loadEntities();
}

void BattleController::onLayerExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    LayerController::onLayerExit();
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
        
        renderer->setPosition(ccp(offset.x+(i/row)*kGameTileWidth,offset.y+(i%row)*kGameTileHeight));
        
        renderer->setZOrder(row-i%row);
        
        m_layer->addChild(renderer);
    }
}

void BattleController::loadOppEntities()
{
    CCSize contentSize =  this->getPreferredContentSize();
    
    int teamSize=9;
    int col=3;
    int row=3;
    
    CCPoint offset=ccp(contentSize.width-row*kGameTileWidth+60,20);
    
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
        
        renderer->setPosition(ccp(offset.x+(i/row)*kGameTileWidth,offset.y+(i%row)*kGameTileHeight));
        
        renderer->setZOrder(row-i%row);
        
        m_layer->addChild(renderer);
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