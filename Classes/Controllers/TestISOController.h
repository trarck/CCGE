#ifndef CCGE_CONTROLLERS_TestISOController_H_
#define CCGE_CONTROLLERS_TestISOController_H_

#include <yhge/yhge.h>
#include <yhmvc/yhmvc.h>
#include <yhge/isometric.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

/**
 * 单独的。
 * 由Scene来组合controller。
 * 可以添加其它controller来作为显示内容
 * 由于结构简单不容易出错。
 */
class TestISOController:public yhmvc::LayerController,public CCTouchDelegate
{
public:
	
    TestISOController(void);
    
	~TestISOController(void);

	void layerDidLoad();
    
    void onLayerExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    void menuBigCallback(CCObject* pSender);
    void menuSmallCallback(CCObject* pSender);
    
private:

	CCPoint m_touchStartPosition;
	yhge::ISOTileMap* m_isoMap;
	CCPoint m_isoMapStartPosition;
};
NS_CC_GE_END

#endif //CCGE_CONTROLLERS_TestISOController_H_
