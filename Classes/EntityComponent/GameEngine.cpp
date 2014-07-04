#include "GameEngine.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameEngine::GameEngine()
:m_entityFactory(NULL)
{
    
}

GameEngine::~GameEngine()
{
    CCLOG("GameEngine destroy");
    CC_SAFE_RELEASE_NULL(m_entityFactory);
}

bool GameEngine::init()
{
    if (Engine::init()) {
        
        m_entityFactory=new EntityFactory();
        m_entityFactory->init();
        m_entityFactory->setEngine(this);
        
        return true;
    }
    
    return false;
}

NS_CC_GE_END
