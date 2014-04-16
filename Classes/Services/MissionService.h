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
    
    bool init();
    
    /**
     * @brief 取得玩家所在的区
     */
    int getPlayedZone();
    
    /**
     * @brief 取得玩家所在的地图
     */
    int getPlayedMap();
    
    /**
     * @brief 取得地图的事件信息
     * 这些信息是保存在服务器端。根据具体需求来确定刷新时间。
     * 一种是：定时间刷新，再数据中加一个过期时间，如果时间超过则刷新。
     * 一种是：完成地图就消除数据，下次取数据的时候再生成。
     *
     * @param mapId 地图id
     *
     * @return 事件信息
     */
    CCDictionary* getMapStepEvents(int mapId);
    
    /**
     * @brief 生成地图的事件信息
     * 根据路径生成事件信息
     *
     * @param mapId 地图id
     * @param paths 事件点
     *
     * @return 事件信息
     */
    CCDictionary* generateMapStepEvents(int mapId,CCArray* paths,int mapColumn);
    
    /**
     * @brief 消除地图事件数据
     *
     * @param mapId 地图id
     */
    void cleanupMapStepEvents(int mapId);
    
    /**
     * @brief 完成地图上的某一步
     * 向服务端发送完成事件，获取物品
     *
     * @param stepKey 每一步的key
     */
    void completeCurrentMapStep(int stepKey)
    {
        completeCurrentMapStep(m_currentMap,stepKey);
    }
    
    /**
     * @brief 完成地图上的某一步
     * 向服务端发送完成事件，获取物品
     *
     * @param mapId 的地图id
     * @param stepKey 每一步的key
     */
    void completeCurrentMapStep(int mapId,int stepKey);
    
    /**
     * @brief 玩家完成一个地图
     * 计算一个区，下一个地图
     *
     * @param mapId 完成的地图id
     */
    void completeCurrentMap()
    {
        completeMap(m_currentMap);
    }
    
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
        CCLOG("setCurrentMap:%d",currentMap);
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
    
    inline void setMoveLeftStep(int moveLeftStep)
    {
        m_moveLeftStep = moveLeftStep;
    }
    
    inline int getMoveLeftStep()
    {
        return m_moveLeftStep;
    }
    
protected:
    
    int positionToStepKey(const CCPoint& pos,int mapColumn);
    
protected:
    //当前探索的区域
    int m_currentZone;
    
    //当前探索的地图
    int m_currentMap;
    
    //探索的地图所有的位置.支持多个地图一起探索。
    std::map<int, int> m_exploreMapStep;
    
    //当前探索地图的位置。
    int m_lastMapStepIndex;
    
    //移动的剩余步骤
    int m_moveLeftStep;
    
    CCDictionary* m_mapStepEventsCache;
};

NS_CC_GE_END
#endif //CCGE_SERVICES_MISSIONSERVICE_H_
