#ifndef CCGE_DATAS_ZoneData_H_
#define CCGE_DATAS_ZoneData_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Jsoncpp/json.h>
#include <yhge/Datas/CocosData.h>
#include <yhge/Datas/JSONData.h>

NS_CC_GE_BEGIN

/**
 * 区域数据
 * id.key
 */
class ZoneData:public yhge::JSONData
{
public:
    
	ZoneData();
    
	~ZoneData();
    
    inline const yhge::Json::Value& getDataById(int zoneId)
    {
        char idKey[10];
        sprintf(idKey, "%u",zoneId);
        return m_data[idKey];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_ZoneData_H_
