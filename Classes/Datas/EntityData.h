#ifndef CCGE_DATAS_ENTITYDATA_H_
#define CCGE_DATAS_ENTITYDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 单位数据
 */
class EntityData:public yhge::SqliteDBData
{
public:
    
	EntityData();
    
	~EntityData();
    
    inline yhge::Json::Value getDataById(int unitId)
    {
        return loadData(unitId);
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_ENTITYDATA_H_
