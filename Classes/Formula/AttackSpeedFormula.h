//
//  DamageFormula.h
//
#ifndef CCGE_FORMULA_DAMAGEFORMULA_H_
#define CCGE_FORMULA_DAMAGEFORMULA_H_

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class DamageFormula : public CCObject 
{

public:

    /**
     * 计算伤害值
     DR:伤害减免，AC:护甲,PAM1:系数1,DAM:伤害值,ATK:攻击力
     DR=AC/(AC+PAM1)
     
     DAM=ATK*(1-DR)=ATK*(1-AC/(AC+PAM1))=ATK*PAM1/(AC+PAM1)
     
     */
    inline static int calcDamage(float attack,float defence,float param1)
    {
        return (int)(attack*param1/(defence+param1));
    }
    
    /**
     * 计算攻击速度
     
     初始攻击速度=1/初始攻击间隔
     
     攻击速度=初始攻击速度*(1+加成)   
     
     攻击频率=1/攻击速度
            =1/(初始攻击速度*(1+加成))=(1/初始攻击速度)*(1/(1+加成))=初始攻击间隔/(1+加成)
     
     加成=用户的速度属性*0.02

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
        return baseAttackSpeed*(1+othersAttackSpeed+agility*param1);
    }
    
    /**
     * @brief 计算攻击速度
     * @param baseAttackSpeed 初始攻击速度
     * @param othersAttackSpeed 其它攻击速度，包含敏捷属性的影响在内的一切对攻击速度的影响.
     */
    inline static float calcAttackSpeed(float baseAttackSpeed,float othersAttackSpeed)
    {
        return baseAttackSpeed*(1+othersAttackSpeed);
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

#endif //CCGE_FORMULA_DAMAGEFORMULA_H_
