#ifndef CCGE_SERVICES_MISSIONSERVICE_H_
#define CCGE_SERVICES_MISSIONSERVICE_H_

#include "BaseService.h"

NS_CC_GE_BEGIN

/**
 * @brief 探索逻辑
 */
class MissionService:public BaseService
{
public:
    
	MissionService();
    
	~MissionService();
    
    CCDictionary* getMapStepEvents(int mapId);
    
    /**
     * @brief 取得完家所在的区
     */
    int getPlayedZone();
    
    /**
     * @brief 取得完家所在的地图
     */
    int getPlayedMap();
    
    /**
     * @brief 玩家完成一个地图
     * 计算一个区，下一个地图
     *
     * @param mapId 完成的地图id
     */
    void completeMap(int mapId);
    
public:
    
    inline void setCurrentZone(int currentZone)
    {
        m_currentZone = currentZone;
    }
    
    inline int getCurrentZone()
    {
        return m_currentZone;
    }
    
    inline void setCurrentMap(int currentMap)
    {
        m_currentMap = currentMap;
    }
    
    inline int getCurrentMap()
    {
        return m_currentMap;
    }
    
    inline void setLastMapStepIndex(int lastMapStepIndex)
    {
        m_lastMapStepIndex = lastMapStepIndex;
    }
    
    inline int getLastMapStepIndex()
    {
        return m_lastMapStepIndex;
    }
    
protected:
    //当前探索的区域
    int m_currentZone;
    
    //当前探索的地图
    int m_currentMap;
    
    //探索的地图所有的位置.支持多个地图一起探索。
    std::map<int, int> m_exploreMapStep;
    
    //当前探索地图的位置。
    int m_lastMapStepIndex;
    
};

NS_CC_GE_END
#endif //CCGE_SERVICES_MISSIONSERVICE_H_
