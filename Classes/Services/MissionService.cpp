#include "MissionService.h"
#include <yhge/yhge.h>
#include "Datas/DataFactory.h"

USING_NS_CC;

USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MissionService::MissionService()
:m_currentZone(0)
,m_currentMap(0)
,m_lastMapStepIndex(0)
{
    
}

MissionService::~MissionService()
{

}

int MissionService::getPlayedZone()
{
    return m_currentZone;
}

int MissionService::getPlayedMap()
{
    return m_currentMap;
}

void MissionService::completeMap(int mapId)
{
    Json::Value mapData=DataFactory::getInstance()->getMapData()->getDataById(mapId);
    
    int nextMapId=mapData["next_map"].asInt();
    
    if (nextMapId) {
        //如果有，则继续
        m_currentMap=nextMapId;
        m_lastMapStepIndex=0;
    }else{
        //此区域已经完成，进行下一个区域
        Json::Value zoneData=DataFactory::getInstance()->getZoneData()->getDataById(m_currentZone);
        int nextZoneId=mapData["next_zone"].asInt();
        if (nextZoneId) {
            m_currentZone=nextZoneId;
            m_lastMapStepIndex=0;
        }else{
            //已经通关。
            CCLOG("complete zone");
        }
    }
}

NS_CC_GE_END
