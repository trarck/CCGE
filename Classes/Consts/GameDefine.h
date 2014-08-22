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

const float kBattleUpdateInterval=0.125f;//1.0f/60.0f;

const int kCampPlayer=1;
const int kCampEnemy=-1;
const int kCampBoth=0;

const CCRect kStageRect=CCRect(0, -120, 800, 240);

const float kStageSideDistanceX=50.0f;

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

enum GroupUpdatePriority
{
    kUnitUpdate,
    kProjectileUpdate,
    kNpcUpdate,
    
    kRendererMoveUpdate,
};

enum ComponentUpdatePriority
{
    kMoveUpdate,
    kSkillUpdate,
    kAIUpdate,
    kBuffUpdate,
    kVisibleMoveUpdate,
};

enum BattleAttributeType
{
    kBattleAttributeNone,
    kBattleAttributeHP,
    kBattleAttributeMP,
    kBattleAttributeSTR,
    kBattleAttributeAGI,
    kBattleAttributeINT,
    kBattleAttributeARM,
    kBattleAttributeMR,
    kBattleAttributeAD,
    kBattleAttributeAP,
    kBattleAttributeHAST,
    kBattleAttributeCRIT,
    kBattleAttributeMCRIT,
    kBattleAttributeARMP,
    kBattleAttributeMRI,
    kBattleAttributeHIT,
    kBattleAttributeDODG,
    kBattleAttributeHPS,
    kBattleAttributeMPS,
    kBattleAttributeHPR,
    kBattleAttributeMPR,
    kBattleAttributeHEAL,
    kBattleAttributeLFS,
    kBattleAttributeCDR,
    kBattleAttributePIMU,
    kBattleAttributeMIMU,
    kBattleAttributeSKL,
    kBattleAttributeSILR,
    kBattleAttributeMSPD,
    kBattleAttributePDM,
};

enum SkillPhaseEventType
{
    kSkillPhaseEventNone,
    kSkillPhaseEventAttack,
};

enum SkillDamageType
{
    kSkillDamageTypePhysical,
    kSkillDamageTypeMagic,
    kSkillDamageTypeHoly,
    kSkillDamageTypeHeal,
};

enum SkillTargetType
{
    kSkillTargetTypeTarget,
    kSkillTargetTypeSelf,
    kSkillTargetTypeNearest,
    kSkillTargetTypeFarthest,
    kSkillTargetTypeRandom,
    kSkillTargetTypeWeakest,
    kSkillTargetTypeStrongest,
    kSkillTargetTypeMaxMP,
    kSkillTargetTypeMinMP,
    kSkillTargetTypeMaxInt,
    kSkillTargetTypeMinHP,
    
};

enum SkillTrackType
{
    kSkillTrackTypeNone,
    kSkillTrackTypeProjectile,
    kSkillTrackTypeChain,
};

enum SkillAOEOrigin
{
    kSkillAOEOriginNone,
    kSkillAOEOriginSelf,
    kSkillAOEOriginTarget,
};

enum SkillAOEShape
{
    kSkillAOEShapeNone,
    kSkillAOEShapeRectangle,
    kSkillAOEShapeCircle,
    kSkillAOEShapeHalfCircle,
    kSkillAOEShapeQuarterCircle,
};

enum BattlePopupType
{
    kBattlePopupTypeDamage,
    kBattlePopupTypeHeal,
    kBattlePopupTypeGold,
    kBattlePopupTypeText,
};

NS_CC_GE_END

#endif // CCGE_CONSTS_GAMEDEFINE_H_
