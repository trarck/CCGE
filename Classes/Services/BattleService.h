#ifndef CCGE_SERVICES_BATTLESERVICE_H_
#define CCGE_SERVICES_BATTLESERVICE_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * @brief 战斗逻辑
 */
class BattleService:public CCObject
{
public:
    
	BattleService();
    
	~BattleService();
    
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
#endif //CCGE_SERVICES_BATTLESERVICE_H_
