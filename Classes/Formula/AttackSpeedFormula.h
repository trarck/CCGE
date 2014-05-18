#ifndef CCGE_FORMULA_ATTACKSPEEDFORMULA_H_
#define CCGE_FORMULA_ATTACKSPEEDFORMULA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

static const float kMinAttackSpeed=0.2f;
static const float kMaxAttackSpeed=5.0f;
static const float kAgilityToAttackSpeedParam=0.02f;

/**
 * 攻击速度的值越大，攻击的越快
 */
class AttackSpeedFormula : public CCObject 
{

public:
    
    /**
     * 计算攻击速度
     
     初始攻击速度=1/初始攻击间隔
     
     攻击速度=初始攻击速度*(1+加成)   
     
     攻击频率=1/攻击速度
            =1/(初始攻击速度*(1+加成))=(1/初始攻击速度)*(1/(1+加成))=初始攻击间隔/(1+加成)
     
     加成=用户的速度属性*转换率

     范围:
     0.2<=攻击速度<=5
     0.2<=攻击间隔<=5;
     
     攻击速度和攻击间隔互导。
     
     攻击间隔有二种计算方式，一种由攻击速度求导，一种是通过初始间隔通过公式计算。
     
     @param baseAttackSpeed 初始攻击速度
     @param othersAttackSpeed 其它攻击速度，除了敏捷属性的影响外的其它一切(技能,buffer,debuffer).
     @param agility 敏捷，对攻击速度有影响的属性
     @param param1 属性到攻击速度的转化率
     */
    
    inline static float calcAttackSpeed(float baseAttackSpeed,float othersAttackSpeed,float agility,float param1)
    {
        float attackSpeed=baseAttackSpeed*(1+othersAttackSpeed+agility*param1);
        
        attackSpeed=MAX(kMinAttackSpeed,MIN(kMaxAttackSpeed, attackSpeed));
        
        return attackSpeed;
    }
    
    /**
     * @brief 计算攻击速度
     * @param baseAttackSpeed 初始攻击速度
     * @param othersAttackSpeed 其它攻击速度，包含敏捷属性的影响在内的一切对攻击速度的影响.
     */
    inline static float calcAttackSpeed(float baseAttackSpeed,float othersAttackSpeed)
    {
        float attackSpeed=baseAttackSpeed*(1+othersAttackSpeed);
        
        attackSpeed=MAX(kMinAttackSpeed,MIN(kMaxAttackSpeed, attackSpeed));
        
        return attackSpeed;
    }
    
    /**
     * @brief 计算敏捷对攻击速度的影响
     * @param agility 敏捷，对攻击速度有影响的属性
     * @param param1 属性到攻击速度的转化率
     */
    inline static float calcAtrributeAttackSpeed(float agility,float param1)
    {
        return agility* param1;
    }
};

NS_CC_GE_END

#endif //CCGE_FORMULA_ATTACKSPEEDFORMULA_H_
