#ifndef CCGE_DATAS_BATTLEMODEL_H_
#define CCGE_DATAS_BATTLEMODEL_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * @brief 战斗模型
 */
class BattleModel:public CCObject
{
public:
    
	BattleModel();
    
	~BattleModel();
    
    /**
     * @brief 取得自己队伍
     */
    std::vector<int> getSelfTroops();
    
    /**
     * @brief 取得对方的队伍
     */
    std::vector<int> getOppTroops();
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_DATAS_BATTLEMODEL_H_
