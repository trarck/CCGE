#ifndef CCGE_CONTROLLERS_BATTLECONTROLLER_H_
#define CCGE_CONTROLLERS_BATTLECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "Consts/GameDefine.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class BattlePrepareController:public yhmvc::LayerController
{
public:
	
    BattlePrepareController(void);
    
	~BattlePrepareController(void);

	void layerDidLoad();
    
    void onLayerExit();
    
    /**
     * @brief 取得战斗数据
     */
    void getBattleData();
    
    /**
     * @brief 加载战斗资源
     */
    void loadResource();
    
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_BATTLECONTROLLER_H_
