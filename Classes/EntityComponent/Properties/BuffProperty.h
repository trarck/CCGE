#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BuffProperty : public yhge::Property
{
public:
    
    BuffProperty()
    {
        
    }
    
    
    inline void setId(int id)
    {
        m_id = id;
    }
    
    inline int getId()
    {
        return m_id;
    }
    
    inline void setName(const std::string& name)
    {
        m_name = name;
    }
    
    inline const std::string& getName()
    {
        return m_name;
    }
    
    inline void setTime(float time)
    {
        m_time = time;
    }
    
    inline float getTime()
    {
        return m_time;
    }
    
    inline void setClearOnDeath(bool clearOnDeath)
    {
        m_clearOnDeath = clearOnDeath;
    }
    
    inline bool isClearOnDeath()
    {
        return m_clearOnDeath;
    }
    
    inline void setShieldType(int shieldType)
    {
        m_shieldType = shieldType;
    }
    
    inline int getShieldType()
    {
        return m_shieldType;
    }
    
    inline void setShieldValue(float shieldValue)
    {
        m_shieldValue = shieldValue;
    }
    
    inline float getShieldValue()
    {
        return m_shieldValue;
    }
    
    inline void setLevelCheckDice(int levelCheckDice)
    {
        m_levelCheckDice = levelCheckDice;
    }
    
    inline int getLevelCheckDice()
    {
        return m_levelCheckDice;
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
    
    inline void setPhysicalImmune(float physicalImmune)
    {
        m_physicalImmune = physicalImmune;
    }
    
    inline float getPhysicalImmune()
    {
        return m_physicalImmune;
    }
    
    inline void setMagicImmune(float magicImmune)
    {
        m_magicImmune = magicImmune;
    }
    
    inline float getMagicImmune()
    {
        return m_magicImmune;
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
    
    inline void setModelSpeeder(float modelSpeeder)
    {
        m_modelSpeeder = modelSpeeder;
    }
    
    inline float getModelSpeeder()
    {
        return m_modelSpeeder;
    }
    
    inline void setControlEffects(const std::vector<std::string>& controlEffects)
    {
        m_controlEffects = controlEffects;
    }
    
    inline const std::vector<std::string>& getControlEffects()
    {
        return m_controlEffects;
    }
    
    inline void setShader(const std::string& shader)
    {
        m_shader = shader;
    }
    
    inline const std::string& getShader()
    {
        return m_shader;
    }
    
protected:
    int m_id;
    std::string m_name;
    //持续时间
    float m_time;
    //死亡清除
    bool m_clearOnDeath;
    //护盾类型 0-无护盾,1-防物理(AD),2-防魔法(AP),3-暗影盾(shallow grave)[死亡后任然可以存活一段时间],255-all
    int m_shieldType;
    //护盾的值
    float m_shieldValue;
    //命中等级.主要是负面buff作用于目标的时候
    int m_levelCheckDice;
    //力量
    float m_strength;
    //敏捷
    float m_agility;
    //智力
    float m_intellect;
    //护甲
    float m_armor;
    //魔法抗性
    float m_magicResistance;
    //物理攻击力
    float m_attackDamage;
    //法术强度
    float m_abilityPower;
    //攻击速度
    float m_attackSpeed;
    //物理暴击
    float m_crit;
    //魔法暴击
    float m_magicCrit;
    //穿透物理护甲
    float m_armorPenetrate;
    //忽视魔法抗性
    float m_magicResistanceIgnore;
    //物理免疫
    float m_physicalImmune;
    //魔法免疫
    float m_magicImmune;
    //命中
    float m_hit;
    //闪避
    float m_dodg;
    //生命回复
    float m_healthRegenerate;
    //魔法值回复
    float m_manaRegenerate;
    //治疗效果
    float m_heal;
    //吸血等级
    float m_lifeDrain;
    //魔法消耗降低
    float m_manaCostReduced;
    //模型速度
    float m_modelSpeeder;
    //控制效果
    std::vector<std::string> m_controlEffects;
    //效果用到的Shader
    std::string m_shader;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_
