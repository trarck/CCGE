#ifndef CCGE_SERVICES_PVEBATTLESERVICE_H_
#define CCGE_SERVICES_PVEBATTLESERVICE_H_

#include "cocos2d.h"
#include "BattleService.h"

NS_CC_GE_BEGIN

/**
 * @brief pve战斗逻辑
 */
class PveBattleService:public BattleService
{
public:
    
	PveBattleService();
    
	~PveBattleService();
    
    /**
     * @brief 战斗开始前的准备
     * 从远程或本地取得战斗双方的队伍数据，战斗用到的随机数等。
     * @param oppId 在pvp中为玩家角色id，pve中为ai的id
     */
    virtual void prepareBattle(int oppId);
    
    /**
     * @brief 取得对方的队伍
     */
    virtual std::vector<int> getOppTroops(int oppId);
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_SERVICES_PVEBATTLESERVICE_H_
