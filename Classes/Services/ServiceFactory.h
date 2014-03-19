#ifndef CCGE_SERVICES_SERVICEFACTORY_H_
#define CCGE_SERVICES_SERVICEFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "PveBattleService.h"
#include "MissionService.h"

NS_CC_GE_BEGIN

/**
 * @brief 逻辑工场
 */
class ServiceFactory:public CCObject
{
public:
    
	ServiceFactory();
    
	~ServiceFactory();

    bool init();

    static ServiceFactory* getInstance();
    
    void setup();
    
    PveBattleService* getPveBattleService()
    {
        return m_pveBattleService;
    }
    
    inline MissionService* getMissionService()
    {
        return m_missionService;
    }
    
protected:
    
    PveBattleService* m_pveBattleService;
    
    MissionService* m_missionService;
    
};

NS_CC_GE_END
#endif //CCGE_SERVICES_SERVICEFACTORY_H_
