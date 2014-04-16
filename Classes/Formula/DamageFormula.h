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
};

NS_CC_GE_END

#endif //CCGE_FORMULA_DAMAGEFORMULA_H_
