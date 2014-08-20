#include "BattleProperty.h"
#include "Consts/GameDefine.h"

NS_CC_GE_BEGIN


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

NS_CC_GE_END
