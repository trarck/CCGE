#include "StateMachineComponent.h"
#include "Consts/GameMessage.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/States/UnitState.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kBarWidth=40;
static const float kBarHeight=4;

StateMachineComponent::StateMachineComponent()
:Component("StateMachineComponent")
,m_fSMMachine(NULL)
{
    
}

StateMachineComponent::~StateMachineComponent()
{
    CC_SAFE_RELEASE_NULL(m_fSMMachine);
}

bool StateMachineComponent::init()
{
    if (Component::init()) {
        
        m_fSMMachine=new FSMMachine();
        m_fSMMachine->init();
        
        return true;
    }
    
    return false;
}

void StateMachineComponent::setup()
{
    Component::setup();
    
    m_fSMMachine->setOwner(m_owner);
    setupStates();
}

void StateMachineComponent::cleanup()
{
    //解决传递NULL引起的函数二义性
    FSMState* state=NULL;
    m_fSMMachine->changeState(state);
    
    Component::cleanup();
}

void StateMachineComponent::setupStates()
{
    GameEntity* entity=static_cast<GameEntity*>(m_owner);
    
    //idle
    UnitIdleState* idleState=new UnitIdleState();
    idleState->init(m_fSMMachine);
    idleState->setGameEntity(entity);
    m_fSMMachine->addState(idleState, UnitIdleState::kIdleState);
    
    //walk
    UnitWalkState* walkState=new UnitWalkState();
    walkState->init(m_fSMMachine);
    walkState->setGameEntity(entity);
    m_fSMMachine->addState(walkState, UnitWalkState::kWalkState);
    
    //attack
    UnitAttackState* attackState=new UnitAttackState();
    attackState->init(m_fSMMachine);
    attackState->setGameEntity(entity);
    m_fSMMachine->addState(attackState, UnitAttackState::kAttackState);
    
    //hurt
    UnitHurtState* hurtState=new UnitHurtState();
    hurtState->init(m_fSMMachine);
    hurtState->setGameEntity(entity);
    m_fSMMachine->addState(hurtState, UnitHurtState::kHurtState);
    
    //dead
    UnitDeadState* deadState=new UnitDeadState();
    deadState->init(m_fSMMachine);
    deadState->setGameEntity(entity);
    m_fSMMachine->addState(deadState, UnitDeadState::kDeadState);
    
    //birth
    UnitBirthState* birthState=new UnitBirthState();
    birthState->init(m_fSMMachine);
    birthState->setGameEntity(entity);
    m_fSMMachine->addState(birthState, UnitBirthState::kBirthState);
    
    //dying
    UnitDyingState* dyingState=new UnitDyingState();
    dyingState->init(m_fSMMachine);
    dyingState->setGameEntity(entity);
    m_fSMMachine->addState(dyingState, UnitDyingState::kDyingState);
    
    //开始设置为空闲状态
    m_fSMMachine->changeState(idleState);
}

NS_CC_GE_END

