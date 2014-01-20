#ifndef CCGE_ENTITYCOMPONENT_COMPONENTS_PLAYERGRIDMOVECOMPONENT_H_
#define CCGE_ENTITYCOMPONENT_COMPONENTS_PLAYERGRIDMOVECOMPONENT_H_

#include "cocos2d.h"
#include <yhge/yhge.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 按地图的格子移动
 */
class PlayerGridMoveComponent : public yhge::GridMoveComponent{

public:

    PlayerGridMoveComponent();
    ~PlayerGridMoveComponent();

    /**
     * 移动动画步骤
     * 现在直接使用地图坐标
     * 以后优化使用view视图的坐标，减少坐标转换
     */
    void updateDirection( float delta);

    /**
     * 移动动画步骤
     * 通过路径移动的动画步骤
     */
    void updatePath2(float delta);

    void setCamera(yhge::ISOCamera* camera)
    {
        m_camera = camera;
    }

    yhge::ISOCamera* getCamera()
    {
        return m_camera;
    }

protected:

    virtual void prepareMove();

    virtual void startMoveUpdateSchedule();
    //virtual void stopMoveUpdateSchedule();

    virtual SEL_SCHEDULE getUpdateDirectionHandle();
    virtual SEL_SCHEDULE getUpdatePathHandle();

    bool checkNeedMoveCamera();
    
protected:
    
    yhge::ISOCamera* m_camera;

    CCPoint m_lastCameraPosition;

    CCRect m_innerRect;
    CCSize m_innerOffsetSize;
    
    bool m_needMoveCamera;
};

NS_CC_GE_END

#endif //CCGE_ENTITYCOMPONENT_COMPONENTS_PLAYERGRIDMOVECOMPONENT_H_
