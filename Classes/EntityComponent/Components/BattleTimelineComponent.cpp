#include "BattleTimelineComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

BattleTimelineComponent::BattleTimelineComponent()
:m_rendererComponent(NULL)
,Component("BattleTimelineComponent")
,m_attackSpeed(1.0f)
,m_attackDuration(1.0f)
,m_attackScheduleStarted(false)
{
    
}

BattleTimelineComponent::~BattleTimelineComponent()
{
}

void BattleTimelineComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
    
}

void BattleTimelineComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool BattleTimelineComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGAttackStart, NULL,
                                         message_selector(BattleTimelineComponent::onAttackStart),this);
        
        messageManager->registerReceiver(m_owner, kMSGAttackStop, NULL,
                                         message_selector(BattleTimelineComponent::onAttackStop),this);
        
        return true;
    }
    return false;
}

void BattleTimelineComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, kMSGAttackStart, message_selector(BattleTimelineComponent::onAttackStart));
    messageManager->removeReceiver(m_owner, kMSGAttackStop, message_selector(BattleTimelineComponent::onAttackStop));
    
    Component::cleanupMessages();
}

void BattleTimelineComponent::startAttackSchedule()
{
    if (!m_attackScheduleStarted) {
        m_attackScheduleStarted=true;
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(BattleTimelineComponent::attackUpdate), this, m_attackDuration, false);
    }
    
}

void BattleTimelineComponent::stopAttackSchedule()
{
    if (m_attackScheduleStarted) {
        m_attackScheduleStarted=false;
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(BattleTimelineComponent::attackUpdate), this);
    }
}

void BattleTimelineComponent::attackUpdate(float delta)
{
    //开始一轮攻击
    getMessageManager()->dispatchMessage(kMSGTrunEntityAttack, this, m_owner);
}

void BattleTimelineComponent::onAttackStart(yhge::Message* message)
{
    startAttackSchedule();
}

void BattleTimelineComponent::onAttackStop(yhge::Message* message)
{
    stopAttackSchedule();
}

NS_CC_GE_END

