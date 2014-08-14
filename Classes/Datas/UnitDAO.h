#ifndef CCGE_DATAS_UNITDAO_H_
#define CCGE_DATAS_UNITDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "BaseSqlDAO.h"

NS_CC_GE_BEGIN

/**
 * 单位数据
 */
class UnitDAO:public BaseSqlDAO
{
public:
    
	UnitDAO();
    
	~UnitDAO();
    
    inline yhge::Json::Value getDataById(int entityId)
    {
        return loadData(entityId);
    }
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_UNITDAO_H_
