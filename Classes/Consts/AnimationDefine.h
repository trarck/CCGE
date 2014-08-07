#ifndef CCGE_CONSTS_ANIMATIONDEFINE_H_
#define CCGE_CONSTS_ANIMATIONDEFINE_H_


/**
 * 动画相关定义
 */

#define CCGE_ANIMATION_TYPE_MOVE "move"
#define CCGE_ANIMATION_TYPE_BATTLE "battle"

#define CCGE_ANIMATION_NAME "name"
#define CCGE_ANIMATION_DIRECTION "direction"
#define CCGE_ANIMATION_SHOWFIRSTFRAME "showFirstFrame"

#define CCGE_ANIMATION_ATTACK "attack"
#define CCGE_ANIMATION_IDLE "idle"
#define CCGE_ANIMATION_DIE "die"
#define CCGE_ANIMATION_BEATTACK "beAttack"
#define CCGE_ANIMATION_USE_SKILL "useSkill"
#define CCGE_ANIMATION_MOVE "move"

/*
 
         左上          上         右上
 
 
         左            中          右
 
 
         左下          下          右下
 
 
 */
enum EightDirction
{
    kEightDirctionRightBottom=0,
    kEightDirctionLeftBottom=1,
    kEightDirctionLeftTop=2,
    kEightDirctionRightTop=3,
    kEightDirctionBottom=4,
    kEightDirctionLeft=5,
    kEightDirctionTop=6,
    kEightDirctionRight=7
};


#endif /* defined(CCGE_CONSTS_ANIMATIONDEFINE_H_) */
