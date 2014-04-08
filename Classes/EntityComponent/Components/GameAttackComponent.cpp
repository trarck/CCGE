#include "GameAttackComponent.h"
#include "Consts/AnimationDefine.h"
#include "Consts/GameMessage.h"
#include "Consts/GameDefine.h"
#include "EntityComponent/GameEntity.h"
#include "Formula/DamageFormula.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

static const float kAttackKeepDisance=80.0f;

GameAttackComponent::GameAttackComponent()
:m_damageFormulaParameterOne(400)
,m_animationComponent(NULL)
,m_rendererComponent(NULL)
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
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void GameAttackComponent::cleanup()
{
    m_animationComponent=NULL;
    m_rendererComponent=NULL;
    AttackComponent::cleanup();
}

bool GameAttackComponent::registerMessages()
{
    if(AttackComponent::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
        messageManager->registerReceiver(m_owner, MSG_ANIMATION_COMPLETE, NULL, message_selector(GameAttackComponent::onAttackAnimationComplete),this);
        
        return true;
    }
    return false;
}

void GameAttackComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
    messageManager->removeReceiver(m_owner, MSG_ANIMATION_COMPLETE);
    
    AttackComponent::cleanupMessages();
}

void GameAttackComponent::attack()
{
    if(m_target){
        CCLOG("GameAttackComponent[%d]::startAttack",m_uID);
        //移动攻击者到被攻击都的前面
        moveToTargetFront();
        
        //显示攻击动画.移动的同时显示动画
        showAttackAnimation();
    }else {
        CCLOG("GameAttackComponent::startAttack no target");
    }
}


// 使用技能攻击
void GameAttackComponent::attackWithSkillId(int skillId)
{
    
}

void GameAttackComponent::moveToTargetFront()
{
    m_originalPosition=m_rendererComponent->getRenderer()->getPosition();
    
    GameEntity* target=static_cast<GameEntity*>(m_target);
    
    CCPoint targetPosition=target->getRendererComponent()->getRenderer()->getPosition();

    //根据目标对象，修正攻击方的位置
    BattleProperty* battleProperty=target->getBattleProperty();
    if (battleProperty->getSide()==kSelfSide) {
        targetPosition.x+=kAttackKeepDisance;
    }else{
        targetPosition.x-=kAttackKeepDisance;
    }
    
    
    CCLOG("GameAttackComponent::moveTo:%f,%f from:%f,%f",targetPosition.x,targetPosition.y,m_originalPosition.x,m_originalPosition.y);
    
    CCMoveTo* moveToAction=CCMoveTo::create(0.04f, targetPosition);
    
    CCFiniteTimeAction*  action = CCSequence::create(moveToAction,
                                                     CCCallFunc::create(this, callfunc_selector(GameAttackComponent::onMoveToTargetFrontComplete)),
                                                     NULL);
    
    m_rendererComponent->getRenderer()->runAction(action);
}

void GameAttackComponent::moveBackOrigin()
{
    CCMoveTo* moveToAction=CCMoveTo::create(0.04f, m_originalPosition);
    
    CCLOG("GameAttackComponent::moveBack:%f,%f",m_originalPosition.x,m_originalPosition.y);
    
    CCFiniteTimeAction*  action = CCSequence::create(moveToAction,
                                                     CCCallFunc::create(this, callfunc_selector(GameAttackComponent::onMoveBackOriginComplete)),
                                                     NULL);
    
    m_rendererComponent->getRenderer()->runAction(action);
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
    
    CCLOG("GameAttackComponent::current target hp %d ",targetHp);
    
    targetHp=targetHp-damage;
    
    CCLOG("GameAttackComponent::afeter target hp %d ",targetHp);
    
    MessageManager* messageManager=this->getMessageManager();
    
    messageManager->dispatchMessage(kMSGAttackDamage,this,m_target,CCInteger::create(damage));
    
    if (targetHp<=0) {
        targetHp=0;
        unitProperty->setHealth(targetHp);
        messageManager->dispatchMessage(kMSGEntityHealthChange, m_target, messageManager->getGlobalObject(),CCFloat::create(targetHp));
        
        //send target die message
        messageManager->dispatchMessage(MSG_ENTITY_DIE, m_target, messageManager->getGlobalObject());
        
    }else{
        unitProperty->setHealth(targetHp);
        messageManager->dispatchMessage(kMSGEntityHealthChange, m_target, messageManager->getGlobalObject(),CCFloat::create(targetHp));
    }
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

void GameAttackComponent::onMoveToTargetFrontComplete()
{
    CCLOG("GameAttackComponent::onMoveToTargetFrontComplete");

    //由位置决定人物朝向
//    BattleProperty* battleProperty=static_cast<GameEntity*>(m_target)->getBattleProperty();
//    int direction=battleProperty->getSide()-1;
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_BEATTACK), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    
    //目标做被攻击动画
    this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, m_target, data);
    
    data->release();
    
}

void GameAttackComponent::onMoveBackOriginComplete()
{
    CCLOG("GameAttackComponent::onMoveBackOriginComplete");
    
    //恢复空闲动画
    showIdleAnimation();
    
    //恢复目标动画
    //由位置决定人物朝向
//    BattleProperty* battleProperty=static_cast<GameEntity*>(m_target)->getBattleProperty();
//    int direction=battleProperty->getSide()-1;
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create(CCGE_ANIMATION_IDLE), CCGE_ANIMATION_NAME);
    data->setObject(CCInteger::create(kEightDirctionRightBottom), CCGE_ANIMATION_DIRECTION);
    this->getMessageManager()->dispatchMessage(MSG_CHANGE_ANIMATION, this, m_target, data);
    
    data->release();
    
    //发送消息，本次攻击结束
    getMessageManager()->dispatchMessage(kMSGEntityAttackComplete, this, m_owner);
    
    //消除目标
    setTarget(NULL);
}

void GameAttackComponent::onAttackAnimationComplete(yhge::Message* message)
{
    CCLOG("GameAttackComponent[%d]::onAttackAnimationComplete",m_uID);
    
    //处理目标伤害
    parseTargetDamage();
    
    moveBackOrigin();
}

void GameAttackComponent::showAttackAnimation()
{
    //由位置决定人物朝向
//    BattleProperty* battleProperty=static_cast<GameEntity*>(m_owner)->getBattleProperty();
//    int direction=battleProperty->getSide()-1;
    
    //执行攻击动画
    m_animationComponent->runAnimation(CCGE_ANIMATION_ATTACK,kEightDirctionRightBottom,true);
}

void GameAttackComponent::showIdleAnimation()
{
    //由位置决定人物朝向
//    BattleProperty* battleProperty=static_cast<GameEntity*>(m_owner)->getBattleProperty();
//    int direction=battleProperty->getSide()-1;
    
    //执行攻击动画
    m_animationComponent->runAnimation(CCGE_ANIMATION_IDLE,kEightDirctionRightBottom,true);
}

NS_CC_GE_END

