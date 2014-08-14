#include "SkillComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "Consts/DataDefine.h"
#include "EntityComponent/GameEntity.h"


USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

SkillComponent::SkillComponent()
:GameComponent("SkillComponent")
,m_cdRemaining(0)
,m_casting(false)
,m_target(NULL)
,m_currentPhaseIdx(0)
,m_currentPhase(NULL)
,m_currentPhaseElapsed(0)
,m_nextEventIdx(NULL)
,m_nextEvent(NULL)
,m_attackCounter(NULL)
,m_maxRangeSq(0)
,m_minRangeSq(0)
,m_update(true)
,m_canCast(false)
,m_canCastTick(-1)
,m_battleUpdateManager(NULL)
{
    
}

SkillComponent::~SkillComponent()
{

}

void SkillComponent::setup()
{
    GameComponent::setup();

    if (m_maxRangeSq==0) {
        m_maxRangeSq=MAXFLOAT;
    }
    
    m_battleUpdateManager=Game::getInstance()->getEngine()->getBattleUpdateManager();
}

void SkillComponent::cleanup()
{
    GameComponent::cleanup();
}

bool SkillComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(SkillComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void SkillComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void SkillComponent::update(float delta)
{
    if (m_casting){
        //TODO attck phase
        
        
    }else{
        m_cdRemaining-=delta;
    }
}

bool SkillComponent::canCastWithTarget(GameEntity* target)
{
    if (m_canCastTick==m_battleUpdateManager->getTicks()) {
        return m_canCast;
    }
    
    m_canCastTick=m_battleUpdateManager->getTicks();
    
    m_canCast=false;
    
    if (m_proto[CCGE_SKILL_COST_MP].asDouble()>m_entityOwner->getUnitProperty()->getMana()) {
        return false;
    }
    
    if (m_cdRemaining>0) {
        return false;
    }
    
    //TODO check buff
    
    //check distance
    float distanceSQ=(target->getBattleProperty()->getPosition()-m_entityOwner->getBattleProperty()->getPosition()).getLengthSq();
    if (distanceSQ>m_maxRangeSq) {
        return false;
    }
    if (distanceSQ<m_minRangeSq) {
        return false;
    }
    
    m_canCast=true;
    
    return true;
}

bool SkillComponent::willCast()
{
    return true;
}


bool SkillComponent::isManual()
{
    return m_proto[CCGE_SKILL_MANUAL].asBool();
}

void SkillComponent::cast(GameEntity* target)
{
    //TODO check alive
    
    //TODO change state
    CCLOG("skill cast:%d",m_proto[CCGE_SKILL_ID].asInt());
    start(target);
}

void SkillComponent::start(GameEntity* target)
{
    setTarget(target);
    
    m_cdRemaining=m_proto[CCGE_SKILL_CD].asDouble();
    m_casting=true;
    m_attackCounter=0;
    m_update=true;
    m_entityOwner->getBattleProperty()->setGlobalCd(m_proto[CCGE_SKILL_GLOBAL_CD].asDouble());
    
    float mp=m_entityOwner->getUnitProperty()->getMana();
    
    //TODO use reduce cost mp
    m_entityOwner->getUnitProperty()->setMana(mp-m_proto[CCGE_SKILL_COST_MP].asDouble());
    
    //TODO run launch effect
    
}

void SkillComponent::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

NS_CC_GE_END

