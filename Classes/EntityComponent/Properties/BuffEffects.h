#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class BuffEffects : public yhge::Property
{
public:
    
    BuffEffects()
    :m_untargetable(0)
    ,m_uncontrollable(0)
    ,m_immoblilize(0)
    ,m_silence(0)
    ,m_disarm(0)
    ,m_enchanted(0)
    ,m_stun(0)
    ,m_invulnerable(0)
    ,m_disableAI(0)
    ,m_noHPR(0)
    ,m_unheal(0)
    ,m_stable(0)
    ,m_frozen(0)
    ,m_building(0)
    ,m_fix(0)
    ,m_imprisonment(0)
    {
        
    }
    
    void reset();
    
    inline void applyUntargetable()
    {
        m_untargetable=true;
    }
    
    inline  void applyUncontrollable()
    {
        m_uncontrollable=true;
    }
    
    
    inline  void applyImmoblilize()
    {
        m_immoblilize=true;
    }
    
    inline  void applySilence()
    {
        m_silence=true;
    }
    
    
    inline  void applyDisarm()
    {
        m_disarm=true;
    }
    
    
    inline  void applyEnchanted()
    {
        m_enchanted=true;
    }
    
    void applyStun();
    
    inline  void applyInvulnerable()
    {
        m_invulnerable=true;
    }
    
    inline  void applyDisableAI()
    {
        m_disableAI=true;
    }
    
    
    inline  void applyNoHPR()
    {
        m_noHPR=true;
    }
    
    
    inline  void applyUnheal()
    {
        m_unheal=true;
    }
    
    inline  void applyStable()
    {
        m_stable=true;
    }
    
    inline void applyFrozen()
    {
        setFrozen(true);
        applyStun();
    }
    
    inline void applyBuilding()
    {
        setBuilding(true);
        applyStable();
        applyFix();
    }
    
    
    inline  void applyFix()
    {
        m_fix=true;
    }
    
    void applyImprisonment();
    
public:
    
    inline void setUntargetable( bool untargetable)
    {
        m_untargetable = untargetable;
    }
    
    inline  bool isUntargetable()
    {
        return m_untargetable;
    }
    
    inline void setUncontrollable( bool uncontrollable)
    {
        m_uncontrollable = uncontrollable;
    }
    
    inline  bool isUncontrollable()
    {
        return m_uncontrollable;
    }
    
    inline void setImmoblilize( bool immoblilize)
    {
        m_immoblilize = immoblilize;
    }
    
    inline  bool isImmoblilize()
    {
        return m_immoblilize;
    }
    
    inline void setSilence( bool silence)
    {
        m_silence = silence;
    }
    
    inline  bool isSilence()
    {
        return m_silence;
    }
    
    inline void setDisarm( bool disarm)
    {
        m_disarm = disarm;
    }
    
    inline  bool isDisarm()
    {
        return m_disarm;
    }
    
    inline void setEnchanted( bool enchanted)
    {
        m_enchanted = enchanted;
    }
    
    inline  bool isEnchanted()
    {
        return m_enchanted;
    }
    
    inline void setStun( bool stun)
    {
        m_stun = stun;
    }
    
    inline  bool isStun()
    {
        return m_stun;
    }
    
    inline void setInvulnerable( bool invulnerable)
    {
        m_invulnerable = invulnerable;
    }
    
    inline  bool isInvulnerable()
    {
        return m_invulnerable;
    }
    
    inline void setDisableAI( bool disableAI)
    {
        m_disableAI = disableAI;
    }
    
    inline  bool isDisableAI()
    {
        return m_disableAI;
    }
    
    inline void setNoHPR( bool noHPR)
    {
        m_noHPR = noHPR;
    }
    
    inline  bool isNoHPR()
    {
        return m_noHPR;
    }
    
    inline void setUnheal( bool unheal)
    {
        m_unheal = unheal;
    }
    
    inline  bool isUnheal()
    {
        return m_unheal;
    }
    
    inline void setStable( bool stable)
    {
        m_stable = stable;
    }
    
    inline  bool isStable()
    {
        return m_stable;
    }
    
    inline void setFrozen( bool frozen)
    {
        m_frozen = frozen;
    }
    
    inline  bool isFrozen()
    {
        return m_frozen;
    }
    
    inline void setBuilding( bool building)
    {
        m_building = building;
    }
    
    inline  bool isBuilding()
    {
        return m_building;
    }
    
    inline void setFix( bool fix)
    {
        m_fix = fix;
    }
    
    inline  bool isFix()
    {
        return m_fix;
    }
    
    inline void setImprisonment(bool imprisonment)
    {
        m_imprisonment = imprisonment;
    }
    
    inline bool isImprisonment()
    {
        return m_imprisonment;
    }
    
protected:

    //不可成为目标//
    bool m_untargetable;
    
    //不可控制//
    bool m_uncontrollable;
    
    //不能活动//
    bool m_immoblilize;
    
    //沉默//
    bool m_silence;
    
    //缴械//
    bool m_disarm;
    
    //魅惑//
    bool m_enchanted;
    
    //石化//
    bool m_stun;
    
    //无敌//
    bool m_invulnerable;
    
    //无AI
    bool m_disableAI;
    
    //无生命值恢复//
    bool m_noHPR;
    
    //不能被治疗//
    bool m_unheal;
    
    //稳固，不能被击退或击飞//
    bool m_stable;
    
    //冻结//
    bool m_frozen;
    
    //建筑//
    bool m_building;
    
    bool m_fix;
    
    //监禁
    bool m_imprisonment;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_BUFFPROPERTY_H_
