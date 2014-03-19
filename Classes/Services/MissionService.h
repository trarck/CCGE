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
    
public:
    
    inline void setLastMapStepIndex(int lastMapStepIndex)
    {
        m_lastMapStepIndex = lastMapStepIndex;
    }
    
    inline int getLastMapStepIndex()
    {
        return m_lastMapStepIndex;
    }
    
protected:
    
    int m_lastMapStepIndex;
};

NS_CC_GE_END
#endif //CCGE_SERVICES_MISSIONSERVICE_H_
