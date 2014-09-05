#include "StateComponent.h"
#include "Game.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/States/UnitState.h"

#include "MoveComponent.h"
#include "SkillComponent.h"
#include "AIComponent.h"

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
    
    m_unitProperty->setState(kUnitStateIdle);
    
    m_moveProperty->setWalkVelocity(CCPointZero);
    
    //set action
    setAction(CCGE_ANIMATION_IDLE);
    
    this->getMessageManager()->dispatchMessage(MSG_MOVE_STOP, this, m_owner);
    
}

void StateComponent::walk(const CCPoint& dest)
{
    if(!m_unitProperty->isAlive()) return;
    
    if (m_unitProperty->getState()!=kUnitStateWalk) {
        m_unitProperty->setState(kUnitStateWalk);
        
        //set action
        setAction(CCGE_ANIMATION_MOVE);
    }
    
    MoveComponent* moveComponent=static_cast<MoveComponent*>(m_owner->getComponent("MoveComponent"));
    moveComponent->moveTo(dest);
    
    this->getMessageManager()->dispatchMessage(MSG_MOVE_TO, this, m_owner,CCPointValue::create(dest));
    
}

void StateComponent::castSkill(SkillComponent* skill,GameEntity* target)
{
    if(!m_unitProperty->isAlive()) return;
    
    m_unitProperty->setState(kUnitStateAttack);
    
    m_moveProperty->setWalkVelocity(CCPointZero);
    
    skill->start(target);
    
    Game::getInstance()->getEngine()->getSkillManager()->setEntityCurrentSkill(m_owner->m_uID, skill);
}

void StateComponent::castManualSkill()
{
    if(!m_unitProperty->isAlive()) return;
    
    SkillComponent* manualSkill=Game::getInstance()->getEngine()->getSkillManager()->getEntityManualSkill(m_owner->m_uID);
    
    CCAssert(manualSkill!=NULL, "StateComponent::castManualSkill skill is null");
    
    if (manualSkill->canTrigger()) {
        manualSkill->trigger();
        return;
    }
    
    AIComponent* aiComponent=static_cast<AIComponent*>(m_owner->getComponent("AIComponent"));
    
    if (!manualSkill->canCastWithTarget(aiComponent->getTarget())) {
        return;
    }
    
    SkillComponent* currentSkill=Game::getInstance()->getEngine()->getSkillManager()->getEntityCurrentSkill(m_owner->m_uID);
    if (currentSkill) {
        currentSkill->interrupt();
    }
    
    castSkill(manualSkill, aiComponent->getTarget());
    
    m_unitProperty->setManuallyCasting(true);
    
    //TODO engine freeze
    
    //self unfreeze
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
    setAction(CCGE_ANIMATION_DIE);
    
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
    setAction(CCGE_ANIMATION_BEATTACK);
    
    m_unitProperty->setState(kUnitStateHurt);
    
    m_moveProperty->setWalkVelocity(CCPointZero);
}

void StateComponent::setAction(const std::string& name)
{
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(name), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    MessageManager::defaultManager()->dispatchMessage(MSG_CHANGE_ANIMATION, NULL, m_owner,data);
}

NS_CC_GE_END

