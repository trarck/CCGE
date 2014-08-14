#ifndef CCGE_DATAS_ZONEDAO_H_
#define CCGE_DATAS_ZONEDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 区域数据
 * id.key
 */
class ZoneDAO:public yhge::data::JSONDataDAO
{
public:
    
	ZoneDAO();
    
	~ZoneDAO();
    
    inline const yhge::Json::Value& getDataById(int zoneId)
    {
        char idKey[10];
        sprintf(idKey, "%u",zoneId);
        return m_data[idKey];
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_ZONEDAO_H_
