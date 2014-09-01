#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_DAMAGECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_DAMAGECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "../GameComponent.h"
#include "EntityComponent/Properties/UnitProperty.h"
#include "EntityComponent/Properties/BattleProperty.h"

#include "PopupComponent.h"

NS_CC_GE_BEGIN

/**
 * 处理伤害结果，包括治疗
 */
class DamageComponent : public GameComponent
{
public:
    
    DamageComponent();
    
    ~DamageComponent();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
    
    /**
     * 恢复hp|mp
     */
    void takeHeal(float amount,int type,GameEntity* source);
    
    float getLostHPAfterImmunity(float damage,int immunity);
    
    float takeDamage(float amount,int damageType,int field,GameEntity* source,float coefficient=0,float critMod=0);
    
protected:
    void setMP(float mp);
    void setHP(float hp);
protected:
    
    UnitProperty* m_unitProperty;
    BattleProperty* m_battleProperty;
    
    PopupComponent* m_popupComponent;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_BATTLES_DAMAGECOMPONENT_H_
