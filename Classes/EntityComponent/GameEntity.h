
#ifndef CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
#define CCGE_ENTITYCOMPONENT_GAMEENTITY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "Properties/UnitProperty.h"
#include "Properties/BattleProperty.h"
#include "Components/GameAttackComponent.h"
#include "Components/HealthBarComponent.h"

NS_CC_GE_BEGIN

class GameEntity:public yhge::Entity
{
public:
    
	GameEntity();
    
	~GameEntity();
    
    CREATE_FUNC(GameEntity);

    inline void setRendererComponent(yhge::RendererComponent* rendererComponent)
    {
        m_rendererComponent = rendererComponent;
    }

    inline yhge::RendererComponent* getRendererComponent()
    {
        return m_rendererComponent;
    }

    void setISOPositionComponent(yhge::ISOPositionComponent* isoPositionComponent)
    {
        m_isoPositionComponent = isoPositionComponent;
    }

    yhge::ISOPositionComponent* getISOPositionComponent()
    {
        return m_isoPositionComponent;
    }
    
    inline void setAttackComponent(GameAttackComponent* attackComponent)
    {
        m_attackComponent = attackComponent;
    }
    
    inline GameAttackComponent* getAttackComponent()
    {
        return m_attackComponent;
    }
    
    inline void setUnitProperty(UnitProperty* unitProperty)
    {
        m_unitProperty = unitProperty;
    }
    
    inline UnitProperty* getUnitProperty()
    {
        return m_unitProperty;
    }

    inline void setBattleProperty(BattleProperty* battleProperty)
    {
        m_battleProperty = battleProperty;
    }
    
    inline BattleProperty* getBattleProperty()
    {
        return m_battleProperty;
    }
    
    inline void setHealthBarComponent(HealthBarComponent* healthBarComponent)
    {
        m_healthBarComponent = healthBarComponent;
    }
    
    inline HealthBarComponent* getHealthBarComponent()
    {
        return m_healthBarComponent;
    }
    
private:

    yhge::RendererComponent* m_rendererComponent;

    yhge::ISOPositionComponent* m_isoPositionComponent;
    
    GameAttackComponent* m_attackComponent;
    
    UnitProperty* m_unitProperty;
    
    BattleProperty* m_battleProperty;
    
    HealthBarComponent* m_healthBarComponent;
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
