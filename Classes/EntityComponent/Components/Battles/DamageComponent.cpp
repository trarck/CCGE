#include "DamageComponent.h"
#include "Game.h"
#include "Consts/GameMessage.h"
#include "Consts/PropertyDefine.h"
#include "Consts/DataDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/AnimationDefine.h"
#include "EntityComponent/GameEntity.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

DamageComponent::DamageComponent()
:GameComponent("DamageComponent")
,m_unitProperty(NULL)
,m_battleProperty(NULL)
,m_popupComponent(NULL)
{
    
}

DamageComponent::~DamageComponent()
{

}

void DamageComponent::setup()
{
    GameComponent::setup();
    
    m_unitProperty=static_cast<UnitProperty*>(m_owner->getProperty(CCGE_PROPERTY_UNIT));
    m_battleProperty=static_cast<BattleProperty*>(m_owner->getProperty(CCGE_PROPERTY_BATTLE));
    
    m_popupComponent=static_cast<PopupComponent*>(m_owner->getComponent("PopupComponent"));
}

void DamageComponent::cleanup()
{
    GameComponent::cleanup();
}

void DamageComponent::takeHeal(float amount,int type,GameEntity* source)
{
    if (!m_unitProperty->isAlive()) {
        return;
    }
    
    type=type==kBattleAttributeNone?kBattleAttributeHP:type;
    
    if (source) {
        BattleProperty* sourceBattleProperty=static_cast<BattleProperty*>(source->getProperty(CCGE_PROPERTY_BATTLE));
        
        amount*=sourceBattleProperty->getPerDamageMod();
    }
    
    bool isAddPoint=true;
    
    if (type==kBattleAttributeMP) {
        setMP(m_unitProperty->getMana()+amount);
    }else if (true){//TODO check buff healable
        setHP(m_unitProperty->getHealth()+amount);
    }else{
        isAddPoint=false;
    }
    
    //TODO unfreeActor
    if (isAddPoint && amount>1 && true/*show able*/) {
        //TODO show tip
    }
}

float DamageComponent::getLostHPAfterImmunity(float damage,int immunity)
{
    return MAX(1, damage*(100-immunity)/100.0f);
}

float DamageComponent::takeDamage(float amount,int damageType,int field,GameEntity* source,float coefficient,float critMod)
{
    if (!m_unitProperty->isAlive()) {
        return 0;
    }
    
    CCAssert(source!=NULL, "DamageComponent::takeDamage source can't be null");
    
    field=field==kBattleAttributeNone?kBattleAttributeHP:field;
    coefficient=coefficient==0?1:coefficient;
    critMod=critMod==0?1:coefficient;
    
    if (m_unitProperty->isManuallyCasting()) {
        CCAssert(false, "DamageComponent::takeDamage when cast manually skill no damage");
    }
    
    float defence=0,dd=0,dc=0,crit=0;
    
    int immunity=0;
    
    BattleProperty* sourceBattleProperty=static_cast<BattleProperty*>(source->getProperty(CCGE_PROPERTY_BATTLE));
    
    switch (damageType) {
        case kSkillDamageTypePhysical:
            defence=MAX(0, m_battleProperty->getArmor()-sourceBattleProperty->getArmorPenetrate());
            crit=sourceBattleProperty->getCrit();
            immunity=m_battleProperty->getPhysicalImmune();
            dd=defence*8;
            dc=dd;
            break;
        case kSkillDamageTypeMagic:
            defence=MAX(0, m_battleProperty->getMagicResistance()-sourceBattleProperty->getMagicResistanceIgnore());
            crit=sourceBattleProperty->getMagicCrit();
            immunity=m_battleProperty->getMagicImmune();
            dd=defence*12;
            dc=defence*2.5;
            break;
        case kSkillDamageTypeHoly:
            defence=0;
            crit=0;
            dd=0;
            dc=0;
            break;
            
        default:
            CCAssert(false, "DamageComponent::takeDamage unknown damage type");
            break;
    }
    
    float critProb=crit /(100+dc)*critMod;
    
    bool isCrit=critProb > Game::getInstance()->getEngine()->rand();
    
    float critMultiplier=isCrit?2:1;
    
    amount=MAX(0, amount);
    
    float damage=amount* amount/(amount+dd*coefficient);
    
    damage *=critMultiplier*sourceBattleProperty->getPerDamageMod();
    
    if (immunity>100) {
        //TODO show immunity
        m_popupComponent->showPopup("immunity", "blue", kBattlePopupTypeText);
        return 0;
    }
    
    //TODO parse damage in buff
    
    if (damage<=0) {
        return 0;
    }
    
    float lost=getLostHPAfterImmunity(damage, immunity);
    
    damage=MIN(m_unitProperty->getHealth(), lost);
    
    //TODO damage statistics
    
    if (field==kBattleAttributeHP) {
        m_unitProperty->addHealth(-lost);
        if (m_unitProperty->getHealth()<=0) {
            //TODO change to die state
        }else{
            //TODO other condition
            if (lost>m_battleProperty->getHealth()*0.08) {
                //TODO change to hurt state
                
            }
        }
        
        float manaGain=lost* m_unitProperty->getManaGainRateFromInfo() / m_battleProperty->getHealth();
        
        float mp=m_unitProperty->getMana()+manaGain*Game::getInstance()->getEngine()->getBattleManager()->getManaBonus();
        
        setMP(mp);
        
    }else if (field==kBattleAttributeMP){
        m_unitProperty->addMana(-lost);
    }
    
    //show lost tip
    
    return lost;
}

void DamageComponent::setMP(float mp)
{
    if (mp>m_battleProperty->getMana()) {
        mp=m_battleProperty->getMana();
    }
    m_unitProperty->setMana(mp);
}

void DamageComponent::setHP(float hp)
{
    if (hp>m_battleProperty->getHealth()) {
        hp=m_battleProperty->getHealth();
    }
    m_unitProperty->setHealth(hp);
}

NS_CC_GE_END

