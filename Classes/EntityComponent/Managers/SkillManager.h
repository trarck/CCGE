
#ifndef CCGE_ENTITYCOMPONENT_MANAGERS_SKILLMANAGER_H_
#define CCGE_ENTITYCOMPONENT_MANAGERS_SKILLMANAGER_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

#include "EntityComponent/Components/Battles/SkillComponent.h"

NS_CC_GE_BEGIN

/**
 * 技能管理器
 */
class SkillManager : public yhge::ECManager
{
public:
    
    typedef yhge::List<SkillComponent*> SkillList;
    typedef std::map<int, SkillList> EntitySkillMap;
    
    SkillManager();
    
    virtual ~SkillManager();
    
    inline SkillList& getEntitySkills(int entityId)
    {
        return m_skills.at(entityId);
    }
    
    void addSkillComponent(int entityId,SkillComponent* skillComponent);
    
protected:
    
    EntitySkillMap m_skills;
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_SKILLMANAGER_H_
