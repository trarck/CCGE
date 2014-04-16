#ifndef CCGE_SERVICES_SERVICEFACTORY_H_
#define CCGE_SERVICES_SERVICEFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "PveBattleService.h"
#include "MissionService.h"
#include "UserService.h"
#include "UnitService.h"

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
    
    static void destroyInstance();
    
    void setup();
    
    PveBattleService* getPveBattleService()
    {
        return m_pveBattleService;
    }
    
    inline MissionService* getMissionService()
    {
        return m_missionService;
    }
    
    inline UserService* getUserService()
    {
        return m_userService;
    }
    
    inline UnitService* getUnitService()
    {
        return m_unitService;
    }
    
protected:
    
    PveBattleService* m_pveBattleService;
    
    MissionService* m_missionService;
    
    UserService* m_userService;
    
    UnitService* m_unitService;
};

NS_CC_GE_END
#endif //CCGE_SERVICES_SERVICEFACTORY_H_
