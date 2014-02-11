#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class UnitProperty : public yhge::Property
{
public:
    
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

protected:
    
    int m_level;
    float m_health;
    float m_maxHealth;
    float m_mana;
    float m_maxMana;
    float m_defence;
    float m_damage;

};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
