#ifndef CCGE_SERVICES_BATTLESERVICE_H_
#define CCGE_SERVICES_BATTLESERVICE_H_

#include "BaseService.h"

NS_CC_GE_BEGIN

/**
 * @brief 战斗逻辑
 */
class BattleService:public BaseService
{
public:
    
	BattleService();
    
	~BattleService();
    
    /**
     * @brief 战斗开始前的准备
     * 从远程或本地取得战斗双方的队伍数据，战斗用到的随机数等。
     * @param oppId 在pvp中为玩家角色id，pve中为ai的id
     */
    virtual void prepareBattle(int oppId);
//    
//    /**
//     * @brief pvp战斗开始前的准备
//     * 从远程或本地取得战斗双方的队伍数据，战斗用到的随机数等。
//     * @param oppId 对手的id
//     */
//    virtual void preparePvpBattle(int oppId);
//    
//    /**
//     * @brief pve战斗开始前的准备
//     * 从远程或本地取得战斗双方的队伍数据，战斗用到的随机数等。
//     * @param mapId 地图id
//     * @param stepId 步骤id
//     */
//    virtual void preparePveBattle(int mapId,int stepId);
//    
//    /**
//     * @brief pve战斗开始前的准备
//     * 从远程或本地取得战斗双方的队伍数据，战斗用到的随机数等。
//     * @param oppId 怪物id
//     */
//    virtual void preparePveBattle(int oppId);
    
    /**
     * @brief 取得自己的战斗数据
     * 队员(troops)已经包含排列信息,阵法(formation formula)
     */
    virtual CCDictionary* getSelfBattleData();
    
    /**
     * @brief 取得对方的战斗数据
     * 队员(troops)已经包含排列信息,阵法(formation formula)
     */
    virtual CCDictionary* getOppBattleData();
    
    /**
     * @brief 取得对方的战斗数据
     * 队员(troops)已经包含排列信息,阵法(formation formula)
     * @param oppId 对手的id
     */
    virtual CCDictionary* getOppBattleData(int oppId);
    
    /**
     * @brief 取得自己队伍
     */
    virtual std::vector<int> getSelfTroops();
    
    /**
     * @brief 取得对方队伍
     */
    virtual std::vector<int> getOppTroops();
    
    /**
     * @brief 取得自己的战斗阵法
     */
    virtual int getSelfFormationFormula();

    /**
     * @brief 取得对方的战斗阵法
     */
    virtual int getOppFormationFormula();
    
protected:
    
    
};

NS_CC_GE_END
#endif //CCGE_SERVICES_BATTLESERVICE_H_
