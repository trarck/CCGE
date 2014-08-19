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

NS_CC_GE_END
