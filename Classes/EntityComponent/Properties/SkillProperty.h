#ifndef CCGE_ENTITYCOMPONENT_PROPERTIES_SkillProperty_H_
#define CCGE_ENTITYCOMPONENT_PROPERTIES_SkillProperty_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class SkillProperty : public yhge::Property
{
public:
    
    SkillProperty()
    
    {
        
    }
    
    
    
    inline void setId(int id)
    {
        m_id = id;
    }
    
    inline int getId()
    {
        return m_id;
    }
    
    inline void setName(const std::string& name)
    {
        m_name = name;
    }
    
    inline const std::string& getName()
    {
        return m_name;
    }
    
    inline void setAttackType(int attackType)
    {
        m_attackType = attackType;
    }
    
    inline int getAttackType()
    {
        return m_attackType;
    }
    
    inline void setDamageType(int damageType)
    {
        m_damageType = damageType;
    }
    
    inline int getDamageType()
    {
        return m_damageType;
    }
    
    inline void setTargetType(int targetType)
    {
        m_targetType = targetType;
    }
    
    inline int getTargetType()
    {
        return m_targetType;
    }
    
    inline void setTargetCamp(int targetCamp)
    {
        m_targetCamp = targetCamp;
    }
    
    inline int getTargetCamp()
    {
        return m_targetCamp;
    }
    
    inline void setMaxRange(float maxRange)
    {
        m_maxRange = maxRange;
    }
    
    inline float getMaxRange()
    {
        return m_maxRange;
    }
    
    inline void setMinRange(float minRange)
    {
        m_minRange = minRange;
    }
    
    inline float getMinRange()
    {
        return m_minRange;
    }
    
    inline void setInitCD(float initCD)
    {
        m_initCD = initCD;
    }
    
    inline float getInitCD()
    {
        return m_initCD;
    }
    
    inline void setGlobalCD(float globalCD)
    {
        m_globalCD = globalCD;
    }
    
    inline float getGlobalCD()
    {
        return m_globalCD;
    }
    
    inline void setCD(float cd)
    {
        m_cd = cd;
    }
    
    inline float getCD()
    {
        return m_cd;
    }
    
    inline void setManual(int manual)
    {
        m_manual = manual;
    }
    
    inline int getManual()
    {
        return m_manual;
    }
    
    inline void setCostMp(float costMp)
    {
        m_costMp = costMp;
    }
    
    inline float getCostMp()
    {
        return m_costMp;
    }
    
    inline void setActiveType(int activeType)
    {
        m_activeType = activeType;
    }
    
    inline int getActiveType()
    {
        return m_activeType;
    }
    
    inline void setKnockUp(float knockUp)
    {
        m_knockUp = knockUp;
    }
    
    inline float getKnockUp()
    {
        return m_knockUp;
    }
    
    inline void setKnockBack(float knockBack)
    {
        m_knockBack = knockBack;
    }
    
    inline float getKnockBack()
    {
        return m_knockBack;
    }
    
    inline void setMoveForward(float moveForward)
    {
        m_moveForward = moveForward;
    }
    
    inline float getMoveForward()
    {
        return m_moveForward;
    }
    
    inline void setAffectedCamp(int affectedCamp)
    {
        m_affectedCamp = affectedCamp;
    }
    
    inline int getAffectedCamp()
    {
        return m_affectedCamp;
    }
    
    inline void setAffectField(int affectField)
    {
        m_affectField = affectField;
    }
    
    inline int getAffectField()
    {
        return m_affectField;
    }
    
    inline void setGainMp(float gainMp)
    {
        m_gainMp = gainMp;
    }
    
    inline float getGainMp()
    {
        return m_gainMp;
    }
    
    inline void setLevel(int level)
    {
        m_level = level;
    }
    
    inline int getLevel()
    {
        return m_level;
    }
    
    inline void setBuffId(int buffId)
    {
        m_buffId = buffId;
    }
    
    inline int getBuffId()
    {
        return m_buffId;
    }
    
    inline void setLifeDrainRatio(float lifeDrainRatio)
    {
        m_lifeDrainRatio = lifeDrainRatio;
    }
    
    inline float getLifeDrainRatio()
    {
        return m_lifeDrainRatio;
    }
    
    inline void setCritRatio(float critRatio)
    {
        m_critRatio = critRatio;
    }
    
    inline float getCritRatio()
    {
        return m_critRatio;
    }
    
    inline void setOutsideScreen(float outsideScreen)
    {
        m_outsideScreen = outsideScreen;
    }
    
    inline float getOutsideScreen()
    {
        return m_outsideScreen;
    }
    
    inline void setBasicNum(float basicNum)
    {
        m_basicNum = basicNum;
    }
    
    inline float getBasicNum()
    {
        return m_basicNum;
    }
    
    inline void setPassiveAttr(float passiveAttr)
    {
        m_passiveAttr = passiveAttr;
    }
    
    inline float getPassiveAttr()
    {
        return m_passiveAttr;
    }
    
    inline void setPlusAttr(float plusAttr)
    {
        m_plusAttr = plusAttr;
    }
    
    inline float getPlusAttr()
    {
        return m_plusAttr;
    }
    
    inline void setPlusRatio(float plusRatio)
    {
        m_plusRatio = plusRatio;
    }
    
    inline float getPlusRatio()
    {
        return m_plusRatio;
    }
    
    inline void setChainGap(float chainGap)
    {
        m_chainGap = chainGap;
    }
    
    inline float getChainGap()
    {
        return m_chainGap;
    }
    
    inline void setChainJumps(int chainJumps)
    {
        m_chainJumps = chainJumps;
    }
    
    inline int getChainJumps()
    {
        return m_chainJumps;
    }
    
    inline void setTileGravity(float tileGravity)
    {
        m_tileGravity = tileGravity;
    }
    
    inline float getTileGravity()
    {
        return m_tileGravity;
    }
    
    inline void setTileXySpeed(float tileXySpeed)
    {
        m_tileXySpeed = tileXySpeed;
    }
    
    inline float getTileXySpeed()
    {
        return m_tileXySpeed;
    }
    
    inline void setTileZSpeed(float tileZSpeed)
    {
        m_tileZSpeed = tileZSpeed;
    }
    
    inline float getTileZSpeed()
    {
        return m_tileZSpeed;
    }
    
    inline void setTileOttHeight(float tileOttHeight)
    {
        m_tileOttHeight = tileOttHeight;
    }
    
    inline float getTileOttHeight()
    {
        return m_tileOttHeight;
    }
    
    inline void setTilePiercing(int tilePiercing)
    {
        m_tilePiercing = tilePiercing;
    }
    
    inline int getTilePiercing()
    {
        return m_tilePiercing;
    }
    
    inline void setTileDistance(float tileDistance)
    {
        m_tileDistance = tileDistance;
    }
    
    inline float getTileDistance()
    {
        return m_tileDistance;
    }
    
    inline void setAimTarget(int aimTarget)
    {
        m_aimTarget = aimTarget;
    }
    
    inline int getAimTarget()
    {
        return m_aimTarget;
    }
    
    inline void setPuppetAction(const std::string& puppetAction)
    {
        m_puppetAction = puppetAction;
    }
    
    inline const std::string& getPuppetAction()
    {
        return m_puppetAction;
    }
    
    inline void setXShift(float xShift)
    {
        m_xShift = xShift;
    }
    
    inline float getXShift()
    {
        return m_xShift;
    }
    
    inline void setLaunchEffect(const std::string& launchEffect)
    {
        m_launchEffect = launchEffect;
    }
    
    inline const std::string& getLaunchEffect()
    {
        return m_launchEffect;
    }
    
    inline void setImpactEffect(const std::string& impactEffect)
    {
        m_impactEffect = impactEffect;
    }
    
    inline const std::string& getImpactEffect()
    {
        return m_impactEffect;
    }
    
    inline void setImpactZorder(float impactZorder)
    {
        m_impactZorder = impactZorder;
    }
    
    inline float getImpactZorder()
    {
        return m_impactZorder;
    }
    
    inline void setPointEffect(const std::string& pointEffect)
    {
        m_pointEffect = pointEffect;
    }
    
    inline const std::string& getPointEffect()
    {
        return m_pointEffect;
    }
    
    inline void setPointZorder(float pointZorder)
    {
        m_pointZorder = pointZorder;
    }
    
    inline float getPointZorder()
    {
        return m_pointZorder;
    }
    
    inline void setAoeShape(int aoeShape)
    {
        m_aoeShape = aoeShape;
    }
    
    inline int getAoeShape()
    {
        return m_aoeShape;
    }
    
    inline void setShapeArg1(float shapeArg1)
    {
        m_shapeArg1 = shapeArg1;
    }
    
    inline float getShapeArg1()
    {
        return m_shapeArg1;
    }
    
    inline void setShapeArg2(float shapeArg2)
    {
        m_shapeArg2 = shapeArg2;
    }
    
    inline float getShapeArg2()
    {
        return m_shapeArg2;
    }
    
    inline void setScriptArg1(float scriptArg1)
    {
        m_scriptArg1 = scriptArg1;
    }
    
    inline float getScriptArg1()
    {
        return m_scriptArg1;
    }
    
    inline void setScriptArg2(float scriptArg2)
    {
        m_scriptArg2 = scriptArg2;
    }
    
    inline float getScriptArg2()
    {
        return m_scriptArg2;
    }
    
    inline void setScriptArg3(float scriptArg3)
    {
        m_scriptArg3 = scriptArg3;
    }
    
    inline float getScriptArg3()
    {
        return m_scriptArg3;
    }
    
    inline void setScriptArg4(float scriptArg4)
    {
        m_scriptArg4 = scriptArg4;
    }
    
    inline float getScriptArg4()
    {
        return m_scriptArg4;
    }
    
    inline void setScriptArg5(float scriptArg5)
    {
        m_scriptArg5 = scriptArg5;
    }
    
    inline float getScriptArg5()
    {
        return m_scriptArg5;
    }
    
    inline void setScriptArg6(float scriptArg6)
    {
        m_scriptArg6 = scriptArg6;
    }
    
    inline float getScriptArg6()
    {
        return m_scriptArg6;
    }

    inline void setActions(const std::vector<std::string>& actions)
    {
        m_actions = actions;
    }
    
    inline const std::vector<std::string>& getActions()
    {
        return m_actions;
    }
    
protected:
    
    int m_id;
    std::string m_name;
    //攻击类型 普通攻击,法术攻击,其它攻击
    int m_attackType;
    //伤害类型 物理伤害,魔法伤害,忽视护甲抗性伤害
    int m_damageType;
    //目标类型 默认,自己,最近,最远,随机,最弱,最强,最多魔法,最少魔法,最大智力,最少血量
    int m_targetType;
    //目标阵营
    int m_targetCamp;
    //--攻击最大范围
    float m_maxRange;
    //攻击最小范围
    float m_minRange;
    //技能cd
    float m_initCD;
    //公用cd
    float m_globalCD;
    //打断后继续的cd
    float m_cd;
    //是手动技能还是自动释放。大招是手动，其它小技能都自动释放
    int m_manual;
    //消耗的魔法值
    float m_costMp;
    //技能作用方式 0-主动(active)需要施放(手动或自动),1-被动(passive)加属性类,2-光环(aura),3-负光环(negative_aura)
    int m_activeType;
    //击飞，z方向偏移
    float m_knockUp;
    //击退，x方向
    float m_knockBack;
    //攻击的时候是移动距离。0-不移动
    float m_moveForward;
    //作用的阵营 -1-对方,0-所有,1-己方
    int m_affectedCamp;
    //影响的属性 0-hp,1-mp
    int m_affectField;
    //回复mp的参数
    float m_gainMp;
    //
    int m_level;
    //技能附带的Buff
    int m_buffId;
    //吸血比。0-不吸血。使用百分比,50表示50%即0.5，也可以是小数，根据公式实际调整
    float m_lifeDrainRatio;
    //暴击伤害比。
    float m_critRatio;
    //攻击屏幕外的单位
    float m_outsideScreen;
    //被动属性类型
    float m_basicNum;
    //被动属性类型
    float m_passiveAttr;
    //附加属性类型
    float m_plusAttr;
    //附加属性比例
    float m_plusRatio;
    //攻击链的持续时间
    float m_chainGap;
    //攻击链跳跃次数
    int m_chainJumps;
    //
    float m_tileGravity;
    float m_tileXySpeed;
    float m_tileZSpeed;
    float m_tileOttHeight;
    //子弹是否穿透
    int m_tilePiercing;
    //子弹的攻击距离 0-无限大
    float m_tileDistance;
    //是否瞄准目标
    int m_aimTarget;
    //一群子弹动画名
    std::string m_puppetAction;
    //技能效果播放的x轴偏移
    float m_xShift;
    //起手动画
    std::string m_launchEffect;
    //
    std::string m_impactEffect;
    float m_impactZorder;
    
    std::string m_pointEffect;
    float m_pointZorder;
    //范围攻击类型 0-不是范围攻击 1-rectangle,2-circle,3-halfcircle,4-quartercircle
    int m_aoeShape;
    float m_shapeArg1;
    float m_shapeArg2;
    //功能参数
    float m_scriptArg1;
    float m_scriptArg2;
    float m_scriptArg3;
    float m_scriptArg4;
    float m_scriptArg5;
    float m_scriptArg6;
    
    //子弹动画名
    std::vector<std::string> m_actions;
};

NS_CC_GE_END

#endif // CCGE_ENTITYCOMPONENT_PROPERTIES_SkillProperty_H_
