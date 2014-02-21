#ifndef CCGE_CONTROLLERS_BATTLECONTROLLER_H_
#define CCGE_CONTROLLERS_BATTLECONTROLLER_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"
#include "Consts/GameDefine.h"
#include "Services/BattleService.h"

NS_CC_GE_BEGIN

/**
 * 战斗直接使用直角坐标系
 * 显示可以使用斜视角
 */
class BattlePrepareController:public yhmvc::Controller
{
public:
	
    BattlePrepareController(void);
    
	~BattlePrepareController(void);

	void viewDidLoad();
    
    void onViewExit();
    
    /**
     * @brief 取得战斗数据
     */
    void getBattleData(CCDictionary* battleParam);
    
    /**
     * @brief 加载战斗资源
     */
    void loadResource();
    
    void gotoBattleScene();
    
    void onBattle(CCObject* sender);
    
private:
    
    BattleService* m_battleService;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_BATTLECONTROLLER_H_
