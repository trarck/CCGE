#include "GameEngine.h"
#include "Consts/GameDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameEngine::GameEngine()
:m_entityFactory(NULL)
,m_battleUpdateManager(NULL)
,m_battleManager(NULL)
{
    
}

GameEngine::~GameEngine()
{
    CCLOG("GameEngine destroy");
    CC_SAFE_RELEASE_NULL(m_entityFactory);
    CC_SAFE_RELEASE_NULL(m_battleUpdateManager);
    CC_SAFE_RELEASE_NULL(m_battleManager);
}

bool GameEngine::init()
{
    if (Engine::init()) {
        
        setupManagers();
        
        m_entityFactory=new EntityFactory();
        m_entityFactory->init();
        m_entityFactory->setEngine(this);
        
        return true;
    }
    
    return false;
}

void GameEngine::setupManagers()
{
    //set battle updater
    m_battleUpdateManager=new BattleUpdateManager();
    m_battleUpdateManager->init();
    m_battleUpdateManager->setEngine(this);
    m_battleUpdateManager->setInterval(kBattleUpdateInterval);
    
    m_scheduler->registerUpdate(m_battleUpdateManager, schedule_selector(BattleUpdateManager::update), 0);
    
    m_battleManager=new BattleManager();
    m_battleManager->init();
    m_battleManager->setEngine(this);
    
}

NS_CC_GE_END
