#ifndef CCGE_SERVICES_USERSERVICE_H_
#define CCGE_SERVICES_USERSERVICE_H_

#include "BaseService.h"

NS_CC_GE_BEGIN

/**
 * @brief 用户逻辑
 */
class UserService:public BaseService
{
public:
    
	UserService();
    
	~UserService();

    /**
     * @brief 取得当前登录的用户数据
     */
    CCDictionary* getCurrentUser();
    
    /**
     * @brief 取得当前玩家的角色
     */
    CCDictionary* getPlayRole();
    
    
};

NS_CC_GE_END
#endif //CCGE_SERVICES_USERSERVICE_H_
