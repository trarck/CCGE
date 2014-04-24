#ifndef CCGE_CONSTS_GAMEDEFINE_H_
#define CCGE_CONSTS_GAMEDEFINE_H_

#include "CCGEMacros.h"

NS_CC_GE_BEGIN

#define GAME_CONTENT_PATH "content"

const int kBattleCellCol=3;
const int kBattleCellRow=3;

const int kBattleCellSize=9;

const float kBattleCellOffsetX=0;
const float kBattleCellOffsetY=20;

const float kBattleSelfOffsetX=60;
const float kBattleSelfOffsetY=0;

const float kBattleOppOffsetX=-40;
const float kBattleOppOffsetY=0;

const int kBattleOppOffsetCell=4;

enum BattleSide
{
    kSelfSide=1,
    kOppSide=2
};


enum StepEventType
{
    kNopEvent=0,//没有事件
    kBattleEvent,
    kGetMoneyEvent,
    kGetExpEvent,
    kGetItemEvent,
    kPvpEvent,
    
    kStartEvent,//开始结点
    kEndEvent//结束结点
};

enum BattleStateEvent
{
    //近身普通攻击
    kBSENearAttack,
    //远程普通攻击
    kBSEFarAttack,
    
};

NS_CC_GE_END

#endif // CCGE_CONSTS_GAMEDEFINE_H_
