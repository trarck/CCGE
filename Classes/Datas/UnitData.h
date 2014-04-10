#ifndef CCGE_DATAS_UNITDATA_H_
#define CCGE_DATAS_UNITDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 单位数据
 */
class UnitData:public yhge::SqliteDBData
{
public:
    
	UnitData();
    
	~UnitData();
    
    inline yhge::Json::Value getDataById(int entityId)
    {
        return loadData(entityId);
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_UNITDATA_H_
