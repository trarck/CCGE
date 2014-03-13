#ifndef CCGE_CONSTS_GAMEDMESSAGE_H_
#define CCGE_CONSTS_GAMEDMESSAGE_H_

#include "CCGEMacros.h"

NS_CC_GE_BEGIN

enum GameMessage
{
    //用户的message最好从一个大号开始，防止和系统冲突。
    kMSGEntityAttackComplete=100000,
    //用户血量改变
    kMSGEntityHealthChange

};

NS_CC_GE_END

#endif // CCGE_CONSTS_GAMEDMESSAGE_H_
