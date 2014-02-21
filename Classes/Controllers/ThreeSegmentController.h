#ifndef CCGE_CONTROLLERS_THREESEGMENTCONTROLLER_H_
#define CCGE_CONTROLLERS_THREESEGMENTCONTROLLER_H_

#include "yhmvc/Core/Controller.h"
#include "yhmvc/Core/View.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN
class ThreeSegmentController:public cocos2d::yhmvc::Controller
{
public:
	
    ThreeSegmentController(void);
    
	~ThreeSegmentController(void);

	void viewDidLoad();    
    
    //get setter
    
    inline yhmvc::View* getHeaderLayer()
    {
        return m_headerLayer;
    }
    
    inline yhmvc::View* getFooterLayer()
    {
        return m_footerLayer;
    }
    
    inline yhmvc::View* getBodyLayer()
    {
        return m_bodyLayer;
    }
    
protected:
    
    yhmvc::View* m_headerLayer;
    yhmvc::View* m_footerLayer;
    yhmvc::View* m_bodyLayer;
};

NS_CC_GE_END

#endif //CCGE_CONTROLLERS_THREESEGMENTCONTROLLER_H_
