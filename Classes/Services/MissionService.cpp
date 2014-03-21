#include "MissionService.h"

USING_NS_CC;

NS_CC_GE_BEGIN

MissionService::MissionService()
:m_lastMapStepIndex(0)
{

}

MissionService::~MissionService()
{

}

int MissionService::getPlayedZone()
{
    return 1;
}

int MissionService::getPlayedMap()
{
    return 1;
}

void MissionService::completeMap(int mapId)
{
    
}

NS_CC_GE_END
