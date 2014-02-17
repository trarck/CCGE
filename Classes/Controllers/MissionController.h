#ifndef CCGE_CONTROLLERS_MissionController_H_
#define CCGE_CONTROLLERS_MissionController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "GameWorldController.h"
#include "Layers/GameWorld.h"

NS_CC_GE_BEGIN

/**
 * 单独的。
 * 由Scene来组合controller。
 * 可以添加其它controller来作为显示内容
 * 由于结构简单不容易出错。
 */
class MissionController:public yhmvc::LayerController,public CCTouchDelegate
{
public:
	
    MissionController(void);
    
	~MissionController(void);

	void layerDidLoad();
    
    void onLayerExit();

private:

	CCPoint m_touchStartPosition;
	yhge::isometric::ISOTileMap* m_isoMap;
	CCPoint m_isoMapStartPosition;
    
    GameWorldController* m_gameWorld;
//    GameWorld* m_gameWorld;
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_MissionController_H_
