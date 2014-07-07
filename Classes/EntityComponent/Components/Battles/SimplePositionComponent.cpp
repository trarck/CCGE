#include "SimplePositionComponent.h"
#include "Consts/GameDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"


USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

SimplePositionComponent::SimplePositionComponent()
:m_rendererComponent(NULL)
,Component("PositionComponent")
,m_battleProperty(NULL)
{
    
}

SimplePositionComponent::~SimplePositionComponent()
{
}

void SimplePositionComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
    
    GameEntity* entity=static_cast<GameEntity*>(m_owner);
    
    m_battleProperty=entity->getBattleProperty();
}

void SimplePositionComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool SimplePositionComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGBattlePositionUpdate, NULL, message_selector(SimplePositionComponent::onUpdatePosition), this);
        
        return true;
    }
    return false;
}

void SimplePositionComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    messageManager->removeReceiver(m_owner, kMSGBattlePositionUpdate);
    
    Component::cleanupMessages();
}

CCPoint SimplePositionComponent::getPositionFromProperty()
{
    //通过战斗属性取得，物体所在的坐标
    
    float x=m_battleProperty->getX();
    float y=m_battleProperty->getY();
    CCLOG("pos:%f,%f",x,y);
    return ccp(x,y);
}

void SimplePositionComponent::setPosition(const CCPoint & pos)
{
   
    m_battleProperty->setX(pos.x);
    m_battleProperty->setY(pos.y);

    m_rendererComponent->getRenderer()->setPosition(pos);
}

void SimplePositionComponent::setPosition(float x,float y)
{

    m_battleProperty->setX(x);
    m_battleProperty->setY(y);
    
    m_rendererComponent->getRenderer()->setPosition(ccp(x, y));

}

CCPoint SimplePositionComponent::getPosition()
{
    return ccp(m_battleProperty->getX(), m_battleProperty->getY());
}

void SimplePositionComponent::updateRendererPosition()
{
    m_rendererComponent->getRenderer()->setPosition(getPositionFromProperty());
}

void SimplePositionComponent::onUpdatePosition(yhge::Message* message)
{
    updateRendererPosition();
}

NS_CC_GE_END

