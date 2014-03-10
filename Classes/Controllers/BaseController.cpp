#include "BaseController.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

BaseController::BaseController(void)
{
    
}


BaseController::~BaseController(void)
{
    CCLOG("BaseController destroy");
}

yhgui::ElementEventParser* BaseController::createEventParser()
{
    return yhgui::ElementEventParser::create();
}

NS_CC_GE_END