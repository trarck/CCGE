#include "SkillManager.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


SkillManager::SkillManager()
{
    YHDEBUG("UpdateManager create");
}

SkillManager::~SkillManager()
{
    YHDEBUG("UpdateManager destroy");
}

void SkillManager::addSkillComponent(int entityId,SkillComponent* skillComponent)
{    
    m_skills[entityId].push_back(skillComponent);
}

void SkillManager::addEntityPassiveSkillInfo(int entityId,const yhge::Json::Value& skillInfo)
{
    m_passiveSkillsMap[entityId].append(skillInfo);
}

yhge::Json::Value& SkillManager::getEntityPassiveSkillInfos(int entityId)
{
    return m_passiveSkillsMap[entityId];
}

void SkillManager::addEntityAuraSkillInfo(int entityId,const yhge::Json::Value& skillInfo)
{
    m_auraSkillsMap[entityId].append(skillInfo);
}

yhge::Json::Value& SkillManager::getEntityAuraSkillInfos(int entityId)
{
    return m_auraSkillsMap[entityId];
}

void SkillManager::addEntityNegativeAuraSkillInfo(int entityId,const yhge::Json::Value& skillInfo)
{
    m_negativeAuraSkillsMap[entityId].append(skillInfo);
}

yhge::Json::Value& SkillManager::getEntityNegativeAuraSkillInfos(int entityId)
{
    return m_negativeAuraSkillsMap[entityId];
}

NS_CC_GE_END
