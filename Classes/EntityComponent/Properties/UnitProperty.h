#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class UnitProperty : public yhge::Property
{
public:
    
    UnitProperty()
    :m_unitId(0)
    ,m_level(0)
    ,m_health(0.0f)
    ,m_maxHealth(0.0f)
    ,m_mana(0.0f)
    ,m_maxMana(0.0f)
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
    ,m_mainAttribute(0)
    ,m_walkSpeed(0.0f)
    ,m_dodg(0.0f)
    ,m_healthRecovery(0.0f)
    ,m_manaRecovery(0.0f)
    ,m_heal(0.0f)
    ,m_lifeDrain(0.0f)
    ,m_manaCostReduced(0.0f)
    ,m_basicSkill(0)
    ,m_maxStars(0)
    ,m_stars(0)
    ,m_flyable(false)
    ,m_puppetId(0)
    {
        
    }
    
    
    inline void setUnitId(int unitId)
    {
        m_unitId = unitId;
    }
    
    inline int getUnitId()
    {
        return m_unitId;
    }
    
    inline void setLevel(int level)
    {
        m_level = level;
    }
    
    inline int getLevel()
    {
        return m_level;
    }
    
    inline void setHealth(float health)
    {
        m_health = health;
    }
    
    inline float getHealth()
    {
        return m_health;
    }
    
    inline void setMaxHealth(float maxHealth)
    {
        m_maxHealth = maxHealth;
    }
    
    inline float getMaxHealth()
    {
        return m_maxHealth;
    }
    
    inline void setMana(float mana)
    {
        m_mana = mana;
    }
    
    inline float getMana()
    {
        return m_mana;
    }
    
    inline void setMaxMana(float maxMana)
    {
        m_maxMana = maxMana;
    }
    
    inline float getMaxMana()
    {
        return m_maxMana;
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
    
    inline void setMainAttribute(int mainAttribute)
    {
        m_mainAttribute = mainAttribute;
    }
    
    inline int getMainAttribute()
    {
        return m_mainAttribute;
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
    
    inline void setWalkSpeed(float walkSpeed)
    {
        m_walkSpeed = walkSpeed;
    }
    
    inline float getWalkSpeed()
    {
        return m_walkSpeed;
    }
    
    inline void setBasicSkill(int basicSkill)
    {
        m_basicSkill = basicSkill;
    }
    
    inline int getBasicSkill()
    {
        return m_basicSkill;
    }
    
    inline void setMaxStars(int maxStars)
    {
        m_maxStars = maxStars;
    }
    
    inline int getMaxStars()
    {
        return m_maxStars;
    }
    
    inline void setStars(int stars)
    {
        m_stars = stars;
    }
    
    inline int getStars()
    {
        return m_stars;
    }
    
    inline void setFlyable(bool flyable)
    {
        m_flyable = flyable;
    }
    
    inline bool isFlyable()
    {
        return m_flyable;
    }
    
    inline void setDescription(const std::string& description)
    {
        m_description = description;
    }
    
    inline const std::string& getDescription()
    {
        return m_description;
    }

    inline void setIcon(const std::string& icon)
    {
        m_icon = icon;
    }
    
    inline const std::string& getIcon()
    {
        return m_icon;
    }
    
    inline void setPuppetId(int puppetId)
    {
        m_puppetId = puppetId;
    }
    
    inline int getPuppetId()
    {
        return m_puppetId;
    }
    
    inline void setProto(const yhge::Json::Value& proto)
    {
        m_proto = proto;
    }
    
    inline const yhge::Json::Value& getProto()
    {
        return m_proto;
    }
    
protected:
    //配置表里的unitId
    int m_unitId;
    //等级
    int m_level;
    //当前生命值 HP
    float m_health;
    //最大生命值
    float m_maxHealth;
    //当前魔法值 MP
    float m_mana;
    //最大魔法值
    float m_maxMana;
    //力量 STR
    float m_strength;
    //敏捷 AGI
    float m_agility;
    //智力 INT
    float m_intellect;
    //主属性 0--力量,1--敏捷,2--智力
    int m_mainAttribute;
    
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
    
    //物理免疫
    int m_physicalImmune;
    //魔法免疫
    int m_magicImmune;
    
    //技能等级加成 SKL
    int m_skillLevelAddition;
    //抵抗沉默几率 SILR
    float m_silenceResistance;
    
    //行走速度
    float m_walkSpeed;
    
    //模型速度。MSPD.主要影响移动速度和模型动画的更新速度，对技能的更新cd无影响。比如中了小黑的冰箭。
    float m_modelSpeeder;
    
    //普通攻击技能
    int m_basicSkill;
    //最大星级
    int m_maxStars;
    //当前星级
    int m_stars;
    //可飞行
    bool m_flyable;
    //描述
    std::string m_description;
    //图标
    std::string m_icon;
    //动画id
    int m_puppetId;
    
    yhge::Json::Value m_proto;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
