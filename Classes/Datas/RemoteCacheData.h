#ifndef CCGE_DATAS_ANIMATIONDATA_H_
#define CCGE_DATAS_ANIMATIONDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>
#include <yhge/Datas/JSONData.h>
#include "Consts/DataDefine.h"

NS_CC_GE_BEGIN

/**
 * 远程数据缓存
 */
class RemoteCacheData:public yhge::JSONData
{
public:
    
	RemoteCacheData();
    
	~RemoteCacheData();
    
    
    /**
     * @brief 取得用户缓存数据
     */
    inline const yhge::Json::Value& getUserData()
    {
        return m_data[CCGE_DATA_PLAYROLE];
    }
    
    /**
     * @brief 取得用户角色缓存数据
     */
    inline const yhge::Json::Value& getPlayRoleData()
    {
        return m_data[CCGE_DATA_PLAYROLE];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_ANIMATIONDATA_H_
