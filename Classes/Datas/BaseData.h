#ifndef CCGE_DATAS_BaseData_H_
#define CCGE_DATAS_BaseData_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>
#include <yhge/Datas/CocosData.h>
#include <yhge/Datas/JSONData.h>

NS_CC_GE_BEGIN

/**
 * 基础数据
 * id.key
 */
class BaseData:public yhge::JSONData
{
public:
    
	BaseData();
    
	~BaseData();
    
    inline const yhge::Json::Value& getDataById(int aId)
    {
        char idKey[10];
        sprintf(idKey, "%u",aId);
        return m_data[idKey];
    }
    
    inline const yhge::Json::Value& getDataById(int aId,const std::string& key)
    {
        char idKey[10];
        sprintf(idKey, "%u",aId);
        return m_data[idKey][key];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_BaseData_H_
