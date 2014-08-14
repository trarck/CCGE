#ifndef CCGE_DATAS_CHARACTERDAO_H_
#define CCGE_DATAS_CHARACTERDAO_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include "BaseSqlDAO.h"

NS_CC_GE_BEGIN

/**
 * 玩家实体数据
 */
class CharacterDAO:public BaseSqlDAO
{
public:
    
	CharacterDAO();
    
	~CharacterDAO();
    
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

#endif //CCGE_DATAS_CHARACTERDAO_H_
