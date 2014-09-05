#ifndef CCGE_CONSTS_GAMEDMESSAGE_H_
#define CCGE_CONSTS_GAMEDMESSAGE_H_

#include "CCGEMacros.h"

NS_CC_GE_BEGIN

enum GameMessage
{
    //用户的message最好从一个大号开始，防止和系统冲突。
    kMSGEntityAttackComplete=100000,
    
    //某个entity可以攻击
    kMSGTrunEntityAttack,
    //开始攻击
    kMSGAttackStart,
    //结束攻击
    kMSGAttackStop,
    
    //用户血量改变
    kMSGEntityHealthChange,
    kMSGAttackDamage,
    kMSGBattlePositionUpdate,
    //
    kMSGBattleMoveComplete,
    kMSGBattleMoveToTargetComplete,
    kMSGBattleMoveBackOriginComplete,
    
    //战斗提示
    kMSGBattlePopup,
    
    kMSGHitMiss,

};

NS_CC_GE_END

#endif // CCGE_CONSTS_GAMEDMESSAGE_H_
