#include "BattleUpdateManager.h"

USING_NS_CC;
USING_NS_CC_YHGE;

NS_CC_GE_BEGIN


BattleUpdateManager::BattleUpdateManager()
:m_elapsed(0)
,m_interval(0)
,m_ticks(0)
{
    YHDEBUG("UpdateManager create");
}

BattleUpdateManager::~BattleUpdateManager()
{
    YHDEBUG("UpdateManager destroy");
}

void BattleUpdateManager::update(float delta)
{
    if (m_paused) {
        return;
    }
    
    m_elapsed+=delta;
    if (m_elapsed>=m_interval) {
        
        UpdateManager::update(m_interval);
        ++m_ticks;
        while (m_elapsed>=m_interval) {
            m_elapsed-=m_interval;
        }
    }
}


NS_CC_GE_END
