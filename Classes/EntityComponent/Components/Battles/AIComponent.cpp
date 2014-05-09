#include "AIComponent.h"
#include "GameDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/Properties/BattleProperty.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

AIComponent::AIComponent()
{
    
}

AIComponent::~AIComponent()
{
}

void AIComponent::setup()
{
    Component::setup();
}

void AIComponent::cleanup()
{
    Component::cleanup();
}

bool AIComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(m_owner, kMSGBattlePositionUpdate, NULL, message_selector(AIComponent::onUpdatePosition), this);
        
        return true;
    }
    return false;
}

void AIComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
//    messageManager->removeReceiver(m_owner, kMSGBattlePositionUpdate);
    
    Component::cleanupMessages();
}

NS_CC_GE_END

