#include "GameAttackComponent.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/GameEntity.h"
#include "Formula/DamageFormula.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

GameAttackComponent::GameAttackComponent()
:m_damageFormulaParameterOne(400)
,m_animationComponent(NULL)
{
    
}

GameAttackComponent::~GameAttackComponent()
{
    CC_SAFE_RELEASE_NULL(m_target);
}

void GameAttackComponent::setup()
{
    AttackComponent::setup();
    m_animationComponent=static_cast<AnimationComponent*>(m_owner->getComponent("AnimationComponent"));
}

void GameAttackComponent::cleanup()
{
    m_animationComponent=NULL;
    AttackComponent::cleanup();
}

bool GameAttackComponent::registerMessages()
{
    if(AttackComponent::registerMessages()){
    
        return true;
    }
    return false;
}

void GameAttackComponent::cleanupMessages()
{
    AttackComponent::cleanupMessages();
}

void GameAttackComponent::attack()
{
    if(m_target){
        CCLOG("GameAttackComponent::startAttack");
        
        //执行攻击动画
        m_animationComponent->runAnimation(CCGE_ANIMATION_ATTACK);
        
        //处理目标伤害
        this->parseTargetDamage();
    }else {
        CCLOG("GameAttackComponent::startAttack no target");
    }
}

/**
 * 处理目标伤害
 */
void GameAttackComponent::parseTargetDamage()
{
    GameEntity* entity=static_cast<GameEntity*>(m_target);
    UnitProperty* unitProperty=entity->getUnitProperty();
    
    int targetHp=unitProperty->getHealth();
    
    int damage=this->calcDamage(unitProperty);
    
    CCLOG("current target hp %d ",targetHp);
    
    targetHp=targetHp-damage;
    
    CCLOG("afeter target hp %d ",targetHp);
    
    if (targetHp<=0) {
        unitProperty->setHealth(0);
        
        //send target die message
        this->getMessageManager()->dispatchMessage(MSG_ENTITY_DIE, m_target, this->getMessageManager()->getGlobalObject());
        
    }else{
        unitProperty->setHealth(targetHp);
    }
}

/**
 * 使用技能攻击
 */
void GameAttackComponent::attackWithSkillId(int skillId)
{
    
}

/**
 * 计算伤害值
 * 直接使用公式
 */
int GameAttackComponent::calcDamage(UnitProperty* targetUnitProperty)
{
    GameEntity* ownerEntity=static_cast<GameEntity*>(m_owner);
    UnitProperty* ownerUnitProperty=ownerEntity->getUnitProperty();
    
    //TODO:攻击相克
    return DamageFormula::calcDamage(ownerUnitProperty->getDamage(), targetUnitProperty->getDefence(), m_damageFormulaParameterOne);
}


NS_CC_GE_END

