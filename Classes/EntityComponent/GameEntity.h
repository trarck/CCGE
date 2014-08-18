
#ifndef CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
#define CCGE_ENTITYCOMPONENT_GAMEENTITY_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"
#include "Components/Battles/SkillComponent.h"

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
    
    inline void setSkillComponents(std::vector<SkillComponent*>& skillComponents)
    {
        m_skillComponents = skillComponents;
    }
    
    inline std::vector<SkillComponent*>& getSkillComponents()
    {
        return m_skillComponents;
    }
    
    inline void addSkillComponent(SkillComponent* skillComponent,int index)
    {
        m_skillComponents.insert(m_skillComponents.begin()+index, skillComponent);
    }
    
private:
    
    yhge::RendererComponent* m_rendererComponent;

    std::vector<SkillComponent*> m_skillComponents;
};

NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_GAMEENTITY_H_
