#include "BattleProperty.h"
#include "Consts/GameDefine.h"

NS_CC_GE_BEGIN

float BattleProperty::StrengthToHealth=18;
float BattleProperty::StrengthToArmor=0.15;

float BattleProperty::AgilityToAttackDamage=0.4;
float BattleProperty::AgilityToCrit=0.4;
float BattleProperty::AgilityToArmor=0.08;

float BattleProperty::IntellectToAbilityPower=2.4;
float BattleProperty::IntellectToMagicResistance=0.1;

float BattleProperty::getAttributeByType(int type)
{
    switch (type) {
        case kBattleAttributeHP:
            return m_health;
        case kBattleAttributeMP:
            return m_mana;
        case kBattleAttributeSTR:
            return m_strength;
        case kBattleAttributeAGI:
            return m_agility;
        case kBattleAttributeINT:
            return m_intellect;
        case kBattleAttributeARM:
            return m_armor;
        case kBattleAttributeMR:
            return m_magicResistance;
        case kBattleAttributeAD:
            return m_attackDamage;
        case kBattleAttributeAP:
            return m_abilityPower;
        case kBattleAttributeHAST:
            return m_attackSpeed;
        case kBattleAttributeCRIT:
            return m_crit;
        case kBattleAttributeMCRIT:
            return m_magicCrit;
        case kBattleAttributeARMP:
            return m_armorPenetrate;
        case kBattleAttributeMRI:
            return m_magicResistanceIgnore;
        case kBattleAttributeHIT:
            return m_hit;
        case kBattleAttributeDODG:
            return m_dodg;
        case kBattleAttributeHPS:
            return m_healthRegenerate;
        case kBattleAttributeMPS:
            return m_manaRegenerate;
        case kBattleAttributeHPR:
            return m_healthRecovery;
        case kBattleAttributeMPR:
            return m_manaRecovery;
        case kBattleAttributeHEAL:
            return m_heal;
        case kBattleAttributeLFS:
            return m_lifeDrain;
        case kBattleAttributeCDR:
            return m_manaCostReduced;
        case kBattleAttributePIMU:
            return m_physicalImmune;
        case kBattleAttributeMIMU:
            return m_magicImmune;
        case kBattleAttributeSKL:
            return m_skillLevelAddition;
        case kBattleAttributeSILR:
            return m_silenceResistance;
        case kBattleAttributeMSPD:
            return m_modelSpeeder;
        case kBattleAttributePDM:
            return m_perDamageMod;
        default:
            break;
    }
    
    return 0;
}

void BattleProperty::setAttributeByType(int type,float value)
{
    switch (type) {
        case kBattleAttributeHP:
            m_health=value;
        case kBattleAttributeMP:
            m_mana=value;
        case kBattleAttributeSTR:
            m_strength=value;
        case kBattleAttributeAGI:
            m_agility=value;
        case kBattleAttributeINT:
            m_intellect=value;
        case kBattleAttributeARM:
            m_armor=value;
        case kBattleAttributeMR:
            m_magicResistance=value;
        case kBattleAttributeAD:
            m_attackDamage=value;
        case kBattleAttributeAP:
            m_abilityPower=value;
        case kBattleAttributeHAST:
            m_attackSpeed=value;
        case kBattleAttributeCRIT:
            m_crit=value;
        case kBattleAttributeMCRIT:
            m_magicCrit=value;
        case kBattleAttributeARMP:
            m_armorPenetrate=value;
        case kBattleAttributeMRI:
            m_magicResistanceIgnore=value;
        case kBattleAttributeHIT:
            m_hit=value;
        case kBattleAttributeDODG:
            m_dodg=value;
        case kBattleAttributeHPS:
            m_healthRegenerate=value;
        case kBattleAttributeMPS:
            m_manaRegenerate=value;
        case kBattleAttributeHPR:
            m_healthRecovery=value;
        case kBattleAttributeMPR:
            m_manaRecovery=value;
        case kBattleAttributeHEAL:
            m_heal=value;
        case kBattleAttributeLFS:
            m_lifeDrain=value;
        case kBattleAttributeCDR:
            m_manaCostReduced=value;
        case kBattleAttributePIMU:
            m_physicalImmune=value;
        case kBattleAttributeMIMU:
            m_magicImmune=value;
        case kBattleAttributeSKL:
            m_skillLevelAddition=value;
        case kBattleAttributeSILR:
            m_silenceResistance=value;
        case kBattleAttributeMSPD:
            m_modelSpeeder=value;
        case kBattleAttributePDM:
            m_perDamageMod=value;
        default:
            break;
    }
}

void BattleProperty::setAttributeByType(int type,int value)
{
    switch (type) {
        case kBattleAttributeHP:
            m_health=value;
        case kBattleAttributeMP:
            m_mana=value;
        case kBattleAttributeSTR:
            m_strength=value;
        case kBattleAttributeAGI:
            m_agility=value;
        case kBattleAttributeINT:
            m_intellect=value;
        case kBattleAttributeARM:
            m_armor=value;
        case kBattleAttributeMR:
            m_magicResistance=value;
        case kBattleAttributeAD:
            m_attackDamage=value;
        case kBattleAttributeAP:
            m_abilityPower=value;
        case kBattleAttributeHAST:
            m_attackSpeed=value;
        case kBattleAttributeCRIT:
            m_crit=value;
        case kBattleAttributeMCRIT:
            m_magicCrit=value;
        case kBattleAttributeARMP:
            m_armorPenetrate=value;
        case kBattleAttributeMRI:
            m_magicResistanceIgnore=value;
        case kBattleAttributeHIT:
            m_hit=value;
        case kBattleAttributeDODG:
            m_dodg=value;
        case kBattleAttributeHPS:
            m_healthRegenerate=value;
        case kBattleAttributeMPS:
            m_manaRegenerate=value;
        case kBattleAttributeHPR:
            m_healthRecovery=value;
        case kBattleAttributeMPR:
            m_manaRecovery=value;
        case kBattleAttributeHEAL:
            m_heal=value;
        case kBattleAttributeLFS:
            m_lifeDrain=value;
        case kBattleAttributeCDR:
            m_manaCostReduced=value;
        case kBattleAttributePIMU:
            m_physicalImmune=value;
        case kBattleAttributeMIMU:
            m_magicImmune=value;
        case kBattleAttributeSKL:
            m_skillLevelAddition=value;
        case kBattleAttributeSILR:
            m_silenceResistance=value;
        case kBattleAttributeMSPD:
            m_modelSpeeder=value;
        case kBattleAttributePDM:
            m_perDamageMod=value;
        default:
            break;
    }
}

NS_CC_GE_END
