#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "Consts/DataDefine.h"
#include "Consts/GameDefine.h"

NS_CC_GE_BEGIN

class UnitProperty : public yhge::Property
{
public:
    
    UnitProperty()
    :m_unitId(0)
    ,m_state(0)
    ,m_level(0)
    ,m_health(0.0f)
    ,m_mana(0.0f)
    ,m_stars(0)
    ,m_rank(0)
    ,m_rankRatio(0.0f)
    ,m_camp(0)
    ,m_foecamp(0)
    ,m_radius(0.0f)
    ,m_sizeMod(1.0f)
    ,m_attackRange(0)
    ,m_alive(true)
    ,m_canCastManual(false)
    ,m_globalCd(0.0)
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
    
    inline void setState(int state)
    {
        m_state = state;
    }
    
    inline int getState()
    {
        return m_state;
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
        if (health<0) {
            m_health=0;
        }else{
            m_health = health;
        }
    }
    
    inline float getHealth()
    {
        return m_health;
    }
    
    inline void addHealth(float health)
    {
        setHealth(m_health += health);
    }
    
    inline void setMana(float mana)
    {
        if(mana<0){
            m_mana=0;
        }else{
            m_mana = mana;
        }
    }
    
    inline float getMana()
    {
        return m_mana;
    }
    
    inline void addMana(float mana)
    {
        setMana(m_mana+mana);
    }

    inline void setStars(int stars)
    {
        m_stars = stars;
    }
    
    inline int getStars()
    {
        return m_stars;
    }
    inline void setRank(int rank)
    {
        m_rank = rank;
    }
    
    inline int getRank()
    {
        return m_rank;
    }
    
    inline void setRankRatio(float rankRatio)
    {
        m_rankRatio = rankRatio;
    }
    
    inline float getRankRatio()
    {
        return m_rankRatio;
    }
    
    inline void setCamp(int camp)
    {
        m_camp = camp;
    }
    
    inline int getCamp()
    {
        return m_camp;
    }
    
    inline void setFoecamp(int foecamp)
    {
        m_foecamp = foecamp;
    }
    
    inline int getFoecamp()
    {
        return m_foecamp;
    }
    
    inline void setRadius(float radius)
    {
        m_radius = radius;
    }
    
    inline float getRadius()
    {
        return m_radius;
    }
    
    inline void setSizeMod(float sizeMod)
    {
        m_sizeMod = sizeMod;
    }
    
    inline float getSizeMod()
    {
        return m_sizeMod;
    }
    
    inline void setAttackRange(float attackRange)
    {
        m_attackRange = attackRange;
    }
    
    inline float getAttackRange()
    {
        return m_attackRange;
    }
    
    inline void setAlive(bool alive)
    {
        m_alive = alive;
    }
    
    inline bool isAlive()
    {
        return m_state!=kUnitStateDead && m_state!=kUnitStateDying;
    }
    
    inline void setCanCastManual(bool canCastManual)
    {
        m_canCastManual = canCastManual;
    }
    
    inline bool isCanCastManual()
    {
        return m_canCastManual;
    }
    
    inline void setManuallyCasting(bool manuallyCasting)
    {
        m_manuallyCasting = manuallyCasting;
    }
    
    inline bool isManuallyCasting()
    {
        return m_manuallyCasting;
    }
    
    inline void setGlobalCd(float globalCd)
    {
        m_globalCd = globalCd;
    }
    
    inline float getGlobalCd()
    {
        return m_globalCd;
    }
    
    inline void addGlobalCd(float delta)
    {
        m_globalCd+=delta;
    }
    
    
    inline void setInfo(const yhge::Json::Value& info)
    {
        m_info = info;
    }
    
    inline const yhge::Json::Value& getInfo()
    {
        return m_info;
    }
    
    inline float getWalkSpeedFromInfo()
    {
        return m_info[CCGE_UNIT_WALK_SPEED].asDouble();
    }
    
    inline int getPuppetIdFromInfo()
    {
        return m_info[CCGE_UNIT_PUPPET_ID].asInt();
    }
    
    inline std::string getPuppetFromInfo()
    {
        return m_info[CCGE_UNIT_PUPPET].asString();
    }

    inline float getManaGainRateFromInfo()
    {
        return m_info[CCGE_UNIT_MANA_GAIN_RATE].asDouble();
    }
    
protected:
    //unitId
    int m_unitId;
    //状态
    int m_state;
    //等级
    int m_level;
    //当前生命值 HP
    float m_health;
    //当前魔法值 MP
    float m_mana;    
    //当前星级
    int m_stars;
    //当前阶级
    int m_rank;
    //阶级
    float m_rankRatio;
    //阵营
    int m_camp;
    //对方阵营
    int m_foecamp;
    //半径
    float m_radius;
    
    //缩放大小
    float m_sizeMod;
    //攻击范围
    float m_attackRange;
    //是否活着
    bool m_alive;
    
    //能否施放大招
    bool m_canCastManual;
    //正在施放大招
    bool m_manuallyCasting;
    
    //技能公用cd
    float m_globalCd;
    
    //表里的信息
    yhge::Json::Value m_info;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_UNITPROPERTY_H_
