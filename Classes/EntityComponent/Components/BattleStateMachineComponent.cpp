#include "BattleStateMachineComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/States/BattleState.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

BattleStateMachineComponent::BattleStateMachineComponent()
:m_rendererComponent(NULL)
,Component("BattleStateMachineComponent")
,m_fSMMachine(NULL)
{
    
}

BattleStateMachineComponent::~BattleStateMachineComponent()
{
    CC_SAFE_RELEASE_NULL(m_fSMMachine);
}

bool BattleStateMachineComponent::init()
{
    if (Component::init()) {
        
        m_fSMMachine=new FSMMachine();
        m_fSMMachine->init();
        
        return true;
    }
    
    return false;
}

void BattleStateMachineComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
    
    m_fSMMachine->setOwner(m_owner);
    setupStates();
}

void BattleStateMachineComponent::cleanup()
{
    m_rendererComponent=NULL;
    //解决传递NULL引起的函数二义性
    FSMState* state=NULL;
    m_fSMMachine->changeState(state);
    
    Component::cleanup();
}

bool BattleStateMachineComponent::registerMessages()
{
    if(Component::registerMessages()){
    
//        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(m_owner, MSG_ATTACK, NULL,
//                                         message_selector(FSMMachine::handleMessage),m_fSMMachine);
        
        return true;
    }
    return false;
}

void BattleStateMachineComponent::cleanupMessages()
{
//    yhge::MessageManager* messageManager=this->getMessageManager();
//    
//    messageManager->removeReceiver(m_owner, MSG_ATTACK,message_selector(FSMMachine::handleMessage));
    
    Component::cleanupMessages();
}


void BattleStateMachineComponent::setupStates()
{
    GameEntity* entity=static_cast<GameEntity*>(m_owner);
    
    //idle
    BattleIdleState* idleState=new BattleIdleState();
    idleState->init(m_fSMMachine);
    idleState->setGameEntity(entity);
    m_fSMMachine->addState(idleState, BattleState::kIdleState);
    
    //move
    BattleMoveState* moveState=new BattleMoveState();
    moveState->init(m_fSMMachine);
    moveState->setGameEntity(entity);
    m_fSMMachine->addState(moveState, BattleState::kMoveState);
    
    //attack
    BattleAttackState* attackState=new BattleAttackState();
    attackState->init(m_fSMMachine);
    attackState->setGameEntity(entity);
    m_fSMMachine->addState(attackState, BattleState::kAttackState);
    
    //be attack
    BattleBeAttackState* beAttackState=new BattleBeAttackState();
    beAttackState->init(m_fSMMachine);
    beAttackState->setGameEntity(entity);
    m_fSMMachine->addState(beAttackState, BattleState::kBeAttackState);
    
    //prepare skill
    BattlePrepareSkillkState* prepareSkillState=new BattlePrepareSkillkState();
    prepareSkillState->init(m_fSMMachine);
    prepareSkillState->setGameEntity(entity);
    m_fSMMachine->addState(prepareSkillState, BattleState::kPrepareSkillState);
    
    //fire skill
    BattleFireSkillkState* fireSkillState=new BattleFireSkillkState();
    fireSkillState->init(m_fSMMachine);
    fireSkillState->setGameEntity(entity);
    m_fSMMachine->addState(fireSkillState, BattleState::kFireSkillState);
    
    //开始设置为空闲状态
    m_fSMMachine->changeState(idleState);
    
}

void BattleStateMachineComponent::onAttackDamage(yhge::Message* message)
{
    
    CCInteger* damageValue=static_cast<CCInteger*>(message->getData());
    if (damageValue) {
        
        CCString* damageString=CCString::createWithFormat("-%d",damageValue->getValue());
        
        //show damage tip
        CCLabelBMFont* label=CCLabelBMFont::create(damageString->getCString(), "fonts/Red_36.fnt");
        
        CCSize size=m_rendererComponent->getRenderer()->getContentSize();
        CCPoint pos=CCPointZero;//m_rendererComponent->getRenderer()->getPosition();
        
//        label->setPosition(ccp(pos.x,pos.y+size.height+50));
        
        float scale=m_rendererComponent->getRenderer()->getScale();
        
        label->setPosition(ccp(size.width/(2*scale),pos.y+(size.height/scale)+40));
        
        label->setScale(1/scale);
        
        //action
        CCAction* effect=CCSequence::createWithTwoActions(CCMoveBy::create(0.4f, ccp(0,40.0f)), CCRemoveSelf::create());
        
        //和renderer在一个结点。如果renderer移动，则显示会跟着移动，看起来真些。
//        m_rendererComponent->getRenderer()->getParent()->addChild(label,1000);
        m_rendererComponent->getRenderer()->addChild(label,1000);
        
        label->runAction(effect);
    }
}


NS_CC_GE_END

