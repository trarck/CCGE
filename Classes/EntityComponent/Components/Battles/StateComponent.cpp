#include "StateComponent.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/States/UnitState.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

StateComponent::StateComponent()
:GameComponent("StateComponent")
,m_unitProperty(NULL)
,m_moveProperty(NULL)
{
    
}

StateComponent::~StateComponent()
{

}

bool StateComponent::init()
{
    if (Component::init()) {
        
        return true;
    }
    
    return false;
}

void StateComponent::setup()
{
    Component::setup();
    
    m_unitProperty=static_cast<UnitProperty*>(m_owner->getProperty(CCGE_PROPERTY_UNIT));
    m_moveProperty=static_cast<MoveProperty*>(m_owner->getProperty(CCGE_PROPERTY_MOVE));
    
    
}

void StateComponent::cleanup()
{
    
    Component::cleanup();
}

void StateComponent::idle()
{
    if(!m_unitProperty->isAlive()) return;
    
    if (m_unitProperty->getState()==kUnitStateIdle) {
        return;
    }
    
    m_moveProperty->setWalkVelocity(CCPointZero);
    
    //set action
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
    
    m_unitProperty->setState(kUnitStateIdle);
}

void StateComponent::die(GameEntity* killer)
{
    if(!m_unitProperty->isAlive()) return;

    //TODO remove buffer
    SkillComponent* currentSkill= Game::getInstance()->getEngine()->getSkillManager()->getEntityCurrentSkill(m_owner->m_uID);
    if (currentSkill) {
        currentSkill->interrupt();
    }
    
    m_unitProperty->setState(kUnitStateDying);
    
    m_unitProperty->setCanCastManual(false);
    m_unitProperty->setHealth(0);
    m_unitProperty->setMana(0);
    
    m_moveProperty->setWalkVelocity(CCPointZero);
    
    //TODO use die effect
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_DIE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
    
    Game::getInstance()->getEngine()->getBattleManager()->onUnitDie(static_cast<GameEntity*>(m_owner), killer);

}

void StateComponent::hurt()
{
    if(!m_unitProperty->isAlive()) return;
    
    SkillComponent* currentSkill= Game::getInstance()->getEngine()->getSkillManager()->getEntityCurrentSkill(m_owner->m_uID);
    if (currentSkill) {
        currentSkill->interrupt();
    }
    
    //TODO interruptSound
    
    //set action
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_BEATTACK), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
    
    m_unitProperty->setState(kUnitStateHurt);
    
    m_moveProperty->setWalkVelocity(CCPointZero);
    
}

NS_CC_GE_END

