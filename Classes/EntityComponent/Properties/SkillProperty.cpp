#include "SkillProperty.h"
#include "EntityComponent/GameEntity.h"

NS_CC_GE_BEGIN

void SkillProperty::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target = target;
}

NS_CC_GE_END
