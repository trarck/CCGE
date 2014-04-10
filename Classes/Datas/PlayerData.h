#ifndef CCGE_DATAS_PLAYERDATA_H_
#define CCGE_DATAS_PLAYERDATA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/yhge.h>

NS_CC_GE_BEGIN

/**
 * 玩家实体数据
 */
class PlayerData:public yhge::SqliteDBData
{
public:
    
	PlayerData();
    
	~PlayerData();
    
    inline yhge::Json::Value getDataById(int playerId)
    {
        return loadData(playerId);
    }
    
    /**
     * @brief 根据player id 取得unit id
     */
    int getUnitId(int playerId);
    
protected:
    
    
};

NS_CC_GE_END

#endif //CCGE_DATAS_PLAYERDATA_H_
