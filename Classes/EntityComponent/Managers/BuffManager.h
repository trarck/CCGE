#ifndef CCGE_ENTITYCOMPONENT_MANAGERS_BuffManager_H_
#define CCGE_ENTITYCOMPONENT_MANAGERS_BuffManager_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

#include "EntityComponent/Components/Battles/BuffComponent.h"

NS_CC_GE_BEGIN

/**
 * buff管理器
 */
class BuffManager : public yhge::ECManager
{
public:
    
    typedef yhge::List<BuffComponent*> BuffList;
    typedef std::map<int, BuffList> EntityBuffMap;
    typedef std::map<int, BuffComponent*> WeakBuffMap;
    
    BuffManager();
    
    virtual ~BuffManager();
    
    inline BuffList& getEntityBuffs(int entityId)
    {        
        return m_buffs[entityId];
    }
    
    void addBuffComponent(int entityId,BuffComponent* buffComponent);
    
protected:
    
    //active buff
    EntityBuffMap m_buffs;
    
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_BuffManager_H_
