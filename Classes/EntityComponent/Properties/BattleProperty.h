#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_BATTLEPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_BATTLEPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BattleProperty : public yhge::Property
{
public:
    
    BattleProperty()
    :m_health(0.0f)
    ,m_mana(0.0f)
    ,m_strength(0.0f)
    ,m_agility(0.0f)
    ,m_intellect(0.0f)
    ,m_armor(0.0f)
    ,m_magicResistance(0.0f)
    ,m_attackDamage(0.0f)
    ,m_abilityPower(0.0f)
    ,m_attackSpeed(0.0f)
    ,m_crit(0.0f)
    ,m_magicCrit(0.0f)
    ,m_armorPenetrate(0.0f)
    ,m_magicResistanceIgnore(0.0f)
    ,m_hit(0)
    ,m_dodg(0.0f)
    ,m_healthRegenerate(0.0f)
    ,m_manaRegenerate(0.0f)
    ,m_healthRecovery(0.0f)
    ,m_manaRecovery(0.0f)
    ,m_heal(0.0f)
    ,m_lifeDrain(0.0f)
    ,m_manaCostReduced(0.0f)
    ,m_physicalImmune(0)
    ,m_magicImmune(0)
    ,m_skillLevelAddition(0)
    ,m_silenceResistance(0)
    ,m_modelSpeeder(1.0f)
    ,m_perDamageMod(1.0f)
    {
        
    }
    
    inline void setHealth(float health)
    {
        m_health = health;
    }
    
    inline float getHealth()
    {
        return m_health;
    }
    
    inline void setMana(float mana)
    {
        m_mana = mana;
    }
    
    inline float getMana()
    {
        return m_mana;
    }
    
    inline void setArmor(float armor)
    {
        m_armor = armor;
    }
    
    inline float getArmor()
    {
        return m_armor;
    }
    
    inline void setMagicResistance(float magicResistance)
    {
        m_magicResistance = magicResistance;
    }
    
    inline float getMagicResistance()
    {
        return m_magicResistance;
    }
    
    inline void setAttackDamage(float attackDamage)
    {
        m_attackDamage = attackDamage;
    }
    
    inline float getAttackDamage()
    {
        return m_attackDamage;
    }
    
    inline void setAbilityPower(float abilityPower)
    {
        m_abilityPower = abilityPower;
    }
    
    inline float getAbilityPower()
    {
        return m_abilityPower;
    }
    
    inline void setAttackSpeed(float attackSpeed)
    {
        m_attackSpeed = attackSpeed;
    }
    
    inline float getAttackSpeed()
    {
        return m_attackSpeed;
    }
    
    inline void setCrit(float crit)
    {
        m_crit = crit;
    }
    
    inline float getCrit()
    {
        return m_crit;
    }
    
    inline void setMagicCrit(float magicCrit)
    {
        m_magicCrit = magicCrit;
    }
    
    inline float getMagicCrit()
    {
        return m_magicCrit;
    }
    
    inline void setArmorPenetrate(float armorPenetrate)
    {
        m_armorPenetrate = armorPenetrate;
    }
    
    inline float getArmorPenetrate()
    {
        return m_armorPenetrate;
    }
    
    inline void setMagicResistanceIgnore(float magicResistanceIgnore)
    {
        m_magicResistanceIgnore = magicResistanceIgnore;
    }
    
    inline float getMagicResistanceIgnore()
    {
        return m_magicResistanceIgnore;
    }
    
    inline void setStrength(float strength)
    {
        m_strength = strength;
    }
    
    inline float getStrength()
    {
        return m_strength;
    }
    
    inline void setAgility(float agility)
    {
        m_agility = agility;
    }
    
    inline float getAgility()
    {
        return m_agility;
    }
    
    inline void setIntellect(float intellect)
    {
        m_intellect = intellect;
    }
    
    inline float getIntellect()
    {
        return m_intellect;
    }
    
    inline void setHit(float hit)
    {
        m_hit = hit;
    }
    
    inline float getHit()
    {
        return m_hit;
    }
    
    inline void setDodg(float dodg)
    {
        m_dodg = dodg;
    }
    
    inline float getDodg()
    {
        return m_dodg;
    }
    
    inline void setHealthRecovery(float healthRecovery)
    {
        m_healthRecovery = healthRecovery;
    }
    
    inline float getHealthRecovery()
    {
        return m_healthRecovery;
    }
    
    inline void setManaRecovery(float manaRecovery)
    {
        m_manaRecovery = manaRecovery;
    }
    
    inline float getManaRecovery()
    {
        return m_manaRecovery;
    }
    
    inline void setHealthRegenerate(float healthRegenerate)
    {
        m_healthRegenerate = healthRegenerate;
    }
    
    inline float getHealthRegenerate()
    {
        return m_healthRegenerate;
    }
    
    inline void setManaRegenerate(float manaRegenerate)
    {
        m_manaRegenerate = manaRegenerate;
    }
    
    inline float getManaRegenerate()
    {
        return m_manaRegenerate;
    }
    
    inline void setHeal(float heal)
    {
        m_heal = heal;
    }
    
    inline float getHeal()
    {
        return m_heal;
    }
    
    inline void setLifeDrain(float lifeDrain)
    {
        m_lifeDrain = lifeDrain;
    }
    
    inline float getLifeDrain()
    {
        return m_lifeDrain;
    }
    
    inline void setManaCostReduced(float manaCostReduced)
    {
        m_manaCostReduced = manaCostReduced;
    }
    
    inline float getManaCostReduced()
    {
        return m_manaCostReduced;
    }
    
    inline void setPhysicalImmune(int physicalImmune)
    {
        m_physicalImmune = physicalImmune;
    }
    
    inline int getPhysicalImmune()
    {
        return m_physicalImmune;
    }
    
    inline void setMagicImmune(int magicImmune)
    {
        m_magicImmune = magicImmune;
    }
    
    inline int getMagicImmune()
    {
        return m_magicImmune;
    }
    
    inline void setSkillLevelAddition(int skillLevelAddition)
    {
        m_skillLevelAddition = skillLevelAddition;
    }
    
    inline int getSkillLevelAddition()
    {
        return m_skillLevelAddition;
    }
    
    inline void setSilenceResistance(float silenceResistance)
    {
        m_silenceResistance = silenceResistance;
    }
    
    inline float getSilenceResistance()
    {
        return m_silenceResistance;
    }
    
    inline void setModelSpeeder(float modelSpeeder)
    {
        m_modelSpeeder = modelSpeeder;
    }
    
    inline float getModelSpeeder()
    {
        return m_modelSpeeder;
    }
    
    inline void setPerDamageMod(float perDamageMod)
    {
        m_perDamageMod = perDamageMod;
    }
    
    inline float getPerDamageMod()
    {
        return m_perDamageMod;
    }
protected:
    
    //当前生命值 HP
    float m_health;
    //当前魔法值 MP
    float m_mana;
    //力量 STR
    float m_strength;
    //敏捷 AGI
    float m_agility;
    //智力 INT
    float m_intellect;
    //物理护甲 ARM
    float m_armor;
    //魔法抗性 MR
    float m_magicResistance;
    //物理攻击 AD
    float m_attackDamage;
    //魔法强度 AP
    float m_abilityPower;
    //攻击速度 HAST。攻击频率不受减速效果影响。
    float m_attackSpeed;
    //物理暴击 CRIT
    float m_crit;
    //魔法暴击 MCRIT
    float m_magicCrit;
    //护甲穿透 ARMP
    float m_armorPenetrate;
    //忽视魔法抗性 MRI
    float m_magicResistanceIgnore;
    //命中 HIT
    float m_hit;
    //闪避 DODG
    float m_dodg;
    //实时生命回复。HPS 每秒回多少。
    float m_healthRegenerate;
    //实时魔法回复。MPS 每秒回多少。
    float m_manaRegenerate;
    //战斗结束生命回复 HPR 每场 回合制特有
    float m_healthRecovery;
    //战斗结束能量回复 MPR 每场 回合制特有
    float m_manaRecovery;
    //治疗效果 HEAL
    float m_heal;
    //吸血 LFS
    float m_lifeDrain;
    //魔法消耗减少 CDR
    float m_manaCostReduced;
    //物理免疫 PIMU
    int m_physicalImmune;
    //魔法免疫 MIMU
    int m_magicImmune;
    //技能等级加成 SKL
    int m_skillLevelAddition;
    //抵抗沉默几率 SILR
    float m_silenceResistance;
    //模型速度。MSPD.主要影响移动速度和模型动画的更新速度，对技能的更新cd无影响。比如中了小黑的冰箭。
    float m_modelSpeeder;
    //单次技能结果效果调整参数。包括伤害和治疗。
    float m_perDamageMod;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BATTLEPROPERTY_H_
