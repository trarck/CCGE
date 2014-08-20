
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
    typedef std::map<int, SkillComponent*> CurrentSkillMap;
    
    SkillManager();
    
    virtual ~SkillManager();
    
    inline SkillList& getEntitySkills(int entityId)
    {        
        return m_skills[entityId];
    }
    
    void addSkillComponent(int entityId,SkillComponent* skillComponent);
    
    inline void setEntityCurrentSkill(int entityId,SkillComponent* skillComponent)
    {
        m_currentSkillMap[entityId]=skillComponent;
    }
    
    inline SkillComponent* getEntityCurrentSkill(int entityId,SkillComponent* skillComponent)
    {
        return m_currentSkillMap[entityId];
    }
    
protected:
    
    EntitySkillMap m_skills;
    
    //weak ref
    CurrentSkillMap m_currentSkillMap;
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_SKILLMANAGER_H_
