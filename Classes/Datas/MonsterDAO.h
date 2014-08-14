#ifndef CCGE_DATAS_MONSTERDAO_H_
#define CCGE_DATAS_MONSTERDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>
#include "BaseSqlDAO.h"

NS_CC_GE_BEGIN

/**
 * 怪物数据
 */
class MonsterDAO:public BaseSqlDAO
{
public:
    
	MonsterDAO();
    
	~MonsterDAO();
    
    inline yhge::Json::Value getDataById(int monsterId)
    {
        return loadData(monsterId);
    }
    
    /**
     * @brief 根据monster id 取得unit id
     */
    int getUnitId(int monsterId);
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_MONSTERDAO_H_
