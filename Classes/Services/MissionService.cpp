#include "MissionService.h"
#include <yhge/yhge.h>
#include "Game.h"
#include "Datas/DataFactory.h"
#include "Consts/GameDefine.h"

USING_NS_CC;

USING_NS_CC_YHGE;

NS_CC_GE_BEGIN

MissionService::MissionService()
:m_currentZone(0)
,m_currentMap(0)
,m_lastMapStepIndex(0)
,m_moveLeftStep(0)
,m_mapStepEventsCache(NULL)
{
    
}

MissionService::~MissionService()
{
    CC_SAFE_RELEASE_NULL(m_mapStepEventsCache);
}

bool MissionService::init()
{
    if (!BaseService::init()) {
        return false;
    }
    
    m_mapStepEventsCache=new CCDictionary();
    return true;
}

CCDictionary* MissionService::getMapStepEvents(int mapId)
{
    CCDictionary* stepEvents=static_cast<CCDictionary*>(m_mapStepEventsCache->objectForKey(mapId));
    
    if (!stepEvents) {
        //TODO 取得或生成数据
        return NULL;
    }
    
    return stepEvents;
}

CCDictionary* MissionService::generateMapStepEvents(int mapId,CCArray* paths,int mapColumn)
{
    CCDictionary* stepEvents=new CCDictionary();
    
    CCPointValue* posValue=NULL;
    CCPoint pos;
    int key=0;
    
    //start
    posValue= static_cast<CCPointValue*>(paths->objectAtIndex(0));
    pos=posValue->getPoint();
    key=positionToStepKey(pos,mapColumn);
    stepEvents->setObject(CCInteger::create(kStartEvent), key);
    
    //end
    posValue= static_cast<CCPointValue*>(paths->objectAtIndex(paths->count()-1));
    pos=posValue->getPoint();
    key=positionToStepKey(pos,mapColumn);
    stepEvents->setObject(CCInteger::create(kEndEvent), key);
    
    //其它点，随机生成
    for (int i=1; i<paths->count()-2; ++i) {
        posValue= static_cast<CCPointValue*>(paths->objectAtIndex(i));
        pos=posValue->getPoint();
        key=positionToStepKey(pos,mapColumn);
        stepEvents->setObject(CCInteger::create(Game::getInstance()->getRandom()->Next(kStartEvent)), key);
    }

    m_mapStepEventsCache->setObject(stepEvents, mapId);
    
    stepEvents->release();
    
    return stepEvents;
}

void MissionService::cleanupMapStepEvents(int mapId)
{
    m_mapStepEventsCache->removeObjectForKey(mapId);
}

void MissionService::completeCurrentMapStep(int mapId,int stepKey)
{
    //TODO 发送服务器数据
    CCDictionary* stepEvents=getMapStepEvents(mapId);
    stepEvents->removeObjectForKey(stepKey);
}

int MissionService::positionToStepKey(const CCPoint& pos,int mapColumn)
{
    return mapColumn * (int)pos.y+(int)pos.x;
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
    //消除地图数据
    cleanupMapStepEvents(mapId);
    
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
