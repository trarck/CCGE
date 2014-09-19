#include "BuffManager.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


BuffManager::BuffManager()
{
    YHDEBUG("BuffManager create");
}

BuffManager::~BuffManager()
{
    YHDEBUG("BuffManager destroy");
}

void BuffManager::addBuffComponent(int entityId,BuffComponent* buffComponent)
{    
    m_buffs[entityId].push_back(buffComponent);
}

NS_CC_GE_END
