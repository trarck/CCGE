
#ifndef CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
#define CCGE_ENTITYCOMPONENT_GAMEENTITY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "Properties/UnitProperty.h"

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
    
    inline void setUnitProperty(UnitProperty* unitProperty)
    {
        m_unitProperty = unitProperty;
    }
    
    inline UnitProperty* getUnitProperty()
    {
        return m_unitProperty;
    }

private:

    yhge::RendererComponent* m_rendererComponent;

    yhge::ISOPositionComponent* m_isoPositionComponent;
    
    UnitProperty* m_unitProperty;
    
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
