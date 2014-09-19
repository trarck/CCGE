#include "BuffEffects.h"

NS_CC_GE_BEGIN

void BuffEffects::applyStun()
{
    setStun(true);
    applyImmoblilize();
    applySilence();
    applyDisarm();
    applyDisableAI();
}

void BuffEffects::applyImprisonment()
{
    setImprisonment(true);
    applyStun();
    applyUntargetable();
    applyInvulnerable();
}

void BuffEffects::reset()
{
    m_untargetable=0;
    m_uncontrollable=0;
    m_immoblilize=0;
    m_silence=0;
    m_disarm=0;
    m_enchanted=0;
    m_stun=0;
    m_invulnerable=0;
    m_disableAI=0;
    m_noHPR=0;
    m_unheal=0;
    m_stable=0;
    m_frozen=0;
    m_building=0;
    m_fix=0;
    m_imprisonment=0;
}

NS_CC_GE_END
