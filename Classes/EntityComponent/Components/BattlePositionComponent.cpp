#include "BattlePositionComponent.h"
#include "Consts/GameDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/Properties/BattleProperty.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

BattlePositionComponent::BattlePositionComponent()
:m_rendererComponent(NULL)
,Component("BattlePositionComponent")
,m_rendererPosition(CCPointZero)
,m_lastCol(-1)
,m_lastRow(-1)
{
    
}

BattlePositionComponent::~BattlePositionComponent()
{
}

void BattlePositionComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<SpriteRendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void BattlePositionComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool BattlePositionComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, kMSGBattlePositionUpdate, NULL, message_selector(BattlePositionComponent::onUpdatePosition), this);
        
        return true;
    }
    return false;
}

void BattlePositionComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    messageManager->removeReceiver(m_owner, kMSGBattlePositionUpdate);
    
    Component::cleanupMessages();
}

CCPoint BattlePositionComponent::getPositionFromCell()
{
    
//    GameEntity* entity=static_cast<GameEntity*>(m_owner);
//    
//    BattleProperty* battleProperty=entity->getBattleProperty();
//    
//    if(battleProperty){
//        
//        //通过战斗属性取得，物体所在的坐标
//        
//        int col=0;//battleProperty->getCol();
//        int row=0;//battleProperty->getRow();
//        
//        if (m_lastCol==col && m_lastRow==row){
//            return m_rendererPosition;
//        }
//        
//        m_lastCol=col;
//        m_lastRow=row;
//        
//        int x=0,y=0;
//        
//        CCPoint offset;
//        
//        int offsetCell=0;
//        
//        switch (battleProperty->getCamp()) {
//            case kSelfSide:{
//                x=kBattleCellRow-row-1;
//                y=kBattleCellCol-col-1;
//                offset.x=kBattleSelfOffsetX;
//                offset.y=kBattleSelfOffsetY;
//                break;
//            }
//            case kOppSide:{
//                x=row;
//                y=kBattleCellCol-col-1;
//                offset.x=kBattleOppOffsetX;
//                offset.y=kBattleOppOffsetY;
//                offsetCell=kBattleOppOffsetCell;
//                break;
//            }
//            default:
//                break;
//        }
//        
//        //y方向居中对齐，坐标要加0.5
//        CCPoint pos=dimetric::StaticTopViewCoordinateFormulae::gameToView2F(x+offsetCell,y);
//        pos.x+=offset.x+x*kBattleCellOffsetX;
//        pos.y+=offset.y+y*kBattleCellOffsetY;
//        
//        m_rendererPosition=pos;
//        
//        return pos;
//    }
    
    return m_rendererPosition;
}

void BattlePositionComponent::updateRendererPosition()
{
    m_rendererComponent->getRenderer()->setPosition(getPositionFromCell());
}

void BattlePositionComponent::onUpdatePosition(yhge::Message* message)
{
    updateRendererPosition();
}

NS_CC_GE_END

