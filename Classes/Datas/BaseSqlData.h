#ifndef CCGE_DATAS_BaseSqlData_H_
#define CCGE_DATAS_BaseSqlData_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 数据库数据
 */
class BaseSqlData:public yhge::SqliteDBData
{
public:
    
	BaseSqlData();
    
	~BaseSqlData();
    
    inline yhge::Json::Value getDataById(int aId)
    {
        return loadData(aId);
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_BaseSqlData_H_
