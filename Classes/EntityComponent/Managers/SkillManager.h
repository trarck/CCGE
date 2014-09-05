
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
    typedef std::map<int, SkillComponent*> WeakSkillMap;
    
    //the value is array
    typedef std::map<int, yhge::Json::Value> SkillInfosMap;
    
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
    
    inline SkillComponent* getEntityCurrentSkill(int entityId)
    {
        return m_currentSkillMap[entityId];
    }
    
    inline void setEntityManualSkill(int entityId,SkillComponent* skillComponent)
    {
        m_manualSkillMap[entityId]=skillComponent;
    }
    
    inline SkillComponent* getEntityManualSkill(int entityId)
    {
        return m_manualSkillMap[entityId];
    }
    
    void addEntityPassiveSkillInfo(int entityId,const yhge::Json::Value& skillInfo);
    
    yhge::Json::Value& getEntityPassiveSkillInfos(int entityId);
    
    void addEntityAuraSkillInfo(int entityId,const yhge::Json::Value& skillInfo);
    
    yhge::Json::Value& getEntityAuraSkillInfos(int entityId);
    
    void addEntityNegativeAuraSkillInfo(int entityId,const yhge::Json::Value& skillInfo);
    
    yhge::Json::Value& getEntityNegativeAuraSkillInfos(int entityId);
    
protected:
    
    //active skill
    EntitySkillMap m_skills;
    //manual skill is active skill
    WeakSkillMap m_manualSkillMap;
    //current active skill
    WeakSkillMap m_currentSkillMap;
    
    //passive skill
    SkillInfosMap m_passiveSkillsMap;
    
    //aura skill
    SkillInfosMap m_auraSkillsMap;
    
    //negative aura
    SkillInfosMap m_negativeAuraSkillsMap;
    
};


NS_CC_GE_END



#endif // CCGE_ENTITYCOMPONENT_MANAGERS_SKILLMANAGER_H_
