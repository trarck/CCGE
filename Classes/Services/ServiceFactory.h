#ifndef CCGE_SERVICES_SERVICEFACTORY_H_
#define CCGE_SERVICES_SERVICEFACTORY_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

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

};

NS_CC_GE_END
#endif //CCGE_SERVICES_SERVICEFACTORY_H_
