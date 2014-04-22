#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class UnitProperty : public yhge::Property
{
public:
    
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
    
    inline void setDefence(float defence)
    {
        m_defence = defence;
    }
    
    inline float getDefence()
    {
        return m_defence;
    }
    
    inline void setDamage(float damage)
    {
        m_damage = damage;
    }
    
    inline float getDamage()
    {
        return m_damage;
    }
    
    inline void setAgility(float agility)
    {
        m_agility = agility;
    }
    
    inline float getAgility()
    {
        return m_agility;
    }
    
    inline void setAttackSpeed(float attackSpeed)
    {
        m_attackSpeed = attackSpeed;
    }
    
    inline float getAttackSpeed()
    {
        return m_attackSpeed;
    }
    
    inline void setBaseAttackSpeed(float baseAttackSpeed)
    {
        m_baseAttackSpeed = baseAttackSpeed;
    }
    
    inline float getBaseAttackSpeed()
    {
        return m_baseAttackSpeed;
    }

    inline void setIcon(const std::string& icon)
    {
        m_icon = icon;
    }
    
    inline const std::string& getIcon()
    {
        return m_icon;
    }
protected:
    int m_unitId;
    int m_level;
    float m_health;
    float m_maxHealth;
    float m_mana;
    float m_maxMana;
    float m_defence;
    float m_damage;
    float m_agility;
    //整个攻击速度包含加成
    float m_attackSpeed;
    //基础攻击速度，固有的
    float m_baseAttackSpeed;
    //图标
    std::string m_icon;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
