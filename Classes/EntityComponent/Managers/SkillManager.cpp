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
    EntitySkillMap::iterator iter=m_skills.find(entityId);
    if (iter==m_skills.end()) {
        SkillList emptyList;
        m_skills.insert(std::make_pair(entityId,emptyList));
    }
    
    m_skills.at(entityId).push_back(skillComponent);
}

NS_CC_GE_END
