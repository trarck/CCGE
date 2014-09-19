#include "BuffComponent.h"
#include "Consts/GameMessage.h"
#include "Consts/DataDefine.h"
#include "Consts/PropertyDefine.h"
#include "Consts/GameDefine.h"
#include "Consts/PropertyDefine.h"
#include "EntityComponent/GameEntity.h"
#include "EntityComponent/Properties/BuffEffects.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

BuffComponent::BuffComponent()
:Component("BuffComponent")
{
    
}

BuffComponent::~BuffComponent()
{

}

void BuffComponent::setup()
{
    Component::setup();

}

void BuffComponent::cleanup()
{
    Component::cleanup();
}

bool BuffComponent::registerMessages()
{
    if(Component::registerMessages()){
    
        yhge::MessageManager* messageManager=this->getMessageManager();
        
//        messageManager->registerReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner, message_selector(BuffComponent::onEntityDie),this);
        
        return true;
    }
    return false;
}

void BuffComponent::cleanupMessages()
{
    yhge::MessageManager* messageManager=this->getMessageManager();
    
//    messageManager->removeReceiver(messageManager->getGlobalObject(), MSG_ENTITY_DIE, m_owner);
    
    Component::cleanupMessages();
}

void BuffComponent::update(float delta)
{
    
}

void BuffComponent::apply()
{
    
    BattleProperty* property=static_cast<BattleProperty*>(m_owner->getProperty(CCGE_PROPERTY_BATTLE));
    
    BattleProperty* casterProperty=static_cast<BattleProperty*>(m_owner->getProperty(CCGE_PROPERTY_BATTLE));
    
    Json::Value buffExts=m_info["exts"];
    
    float baseValue=0.0f;
    float extValue=0.0f;
    
#define SET_BATTLE_ATTRIBUTE_MACRO(NAME,ATTR)\
    do{if (!m_info[NAME].isNull() || !buffExts[NAME].isNull()) {\
        baseValue=m_info[NAME].asDouble();\
        extValue=buffExts[NAME].asDouble()+ casterProperty->get##ATTR()*buffExts[NAME "_mult"].asDouble();\
        property->set##ATTR(property->get##ATTR()+baseValue+extValue);\
    }}while(0)

    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_HEALTH,Heal);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MANA,Mana);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_ARMOR,Armor);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MAGIC_RESISTANCE,MagicResistance);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_ATTACK_DAMAGE,AttackDamage);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_ABILITY_POWER,AbilityPower);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_ATTACK_SPEED,AttackSpeed);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_CRIT,Crit);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MAGIC_CRIT,MagicCrit);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_ARMOR_PENETRATE,ArmorPenetrate);
    
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MAGIC_RESISTANCE_IGNORE,MagicResistanceIgnore);

    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_HIT,Hit);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_DODG,Dodg);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_HEALTH_REGENERATE,HealthRegenerate);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MANA_REGENERATE,ManaRegenerate);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_HEAL,Heal);


    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_HEAL,Heal);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_LIFE_DRAIN,LifeDrain);
    SET_BATTLE_ATTRIBUTE_MACRO(CCGE_UNIT_MANA_COST_REDUCED,ManaCostReduced);

    //use as type
    Json::Value controllerEffects=m_info[CCGE_BUFF_CONTROL_EFFECT];
    
    for (int i=0; i<controllerEffects.size(); ++i) {
        applyEffect(controllerEffects[i].asInt());
    }
}

void BuffComponent::applyEffect(const std::string& effect)
{
    
}

void BuffComponent::applyEffect(int effectType)
{
    BuffEffects* buffEffects=static_cast<BuffEffects*>(m_owner->getProperty(CCGE_PROPERTY_BUFF_EFFECTS));
    
    switch (effectType) {
        case kBuffEffectUntargetable:
            buffEffects->applyUntargetable();
            break;
        case kBuffEffectUncontrollable:
            buffEffects->applyUncontrollable();
            break;
        case kBuffEffectImmoblilize:
            buffEffects->applyImmoblilize();
            break;
        case kBuffEffectSilence:
            buffEffects->applySilence();
            break;
        case kBuffEffectDisarm:
            buffEffects->applyDisarm();
            break;
        case kBuffEffectEnchanted:
            buffEffects->applyEnchanted();
            break;
        case kBuffEffectStun:
            buffEffects->applyStun();
            break;
        case kBuffEffectInvulnerable:
            buffEffects->applyInvulnerable();
            break;
        case kBuffEffectDisableAI:
            buffEffects->applyDisableAI();
            break;
        case kBuffEffectNoHPR:
            buffEffects->applyNoHPR();
            break;
        case kBuffEffectUnheal:
            buffEffects->applyUnheal();
            break;
        case kBuffEffectStable:
            buffEffects->applyStable();
            break;
        case kBuffEffectFrozen:
            buffEffects->applyFrozen();
            break;
        case kBuffEffectBuilding:
            buffEffects->applyBuilding();
            break;
        case kBuffEffectFix:
            buffEffects->applyFix();
            break;
        case kBuffEffectImprisonment:
            buffEffects->applyImprisonment();
            break;

        default:
            break;
    }
}

NS_CC_GE_END

