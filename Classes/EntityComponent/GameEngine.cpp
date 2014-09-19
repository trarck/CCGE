#include "GameEngine.h"
#include "Consts/GameDefine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const unsigned int kRandomMultiplier=3125;
static const unsigned long long kRandomModer=34359738337;

GameEngine::GameEngine()
:m_entityFactory(NULL)
,m_battleUpdateManager(NULL)
,m_battleManager(NULL)
,m_skillManager(NULL)
,m_randomSeed(1)
,m_buffManager(NULL)
{
    
}

GameEngine::~GameEngine()
{
    CCLOG("GameEngine destroy");
    CC_SAFE_RELEASE_NULL(m_entityFactory);
    CC_SAFE_RELEASE_NULL(m_battleUpdateManager);
    CC_SAFE_RELEASE_NULL(m_battleManager);
    CC_SAFE_RELEASE_NULL(m_skillManager);
    CC_SAFE_RELEASE_NULL(m_buffManager);
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
    
    m_skillManager=new SkillManager();
    m_skillManager->init();
    m_skillManager->setEngine(this);
    
    m_buffManager=new BuffManager();
    m_buffManager->init();
    m_buffManager->setEngine(this);
    
}

float GameEngine::rand()
{
    int nextSeed=m_randomSeed * kRandomMultiplier % kRandomModer;
    float ret= nextSeed /kRandomModer;
    m_randomSeed=nextSeed;
    return ret;
}

void GameEngine::srand(int seed)
{
    CCAssert(seed!=0, "GameEngine::srand seed is zero");
    m_randomSeed=seed;
}

NS_CC_GE_END
