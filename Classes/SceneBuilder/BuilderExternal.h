#ifndef CCMVC_SCENEBUILDER_BUILDEREXTERNAL_H_
#define CCMVC_SCENEBUILDER_BUILDEREXTERNAL_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhgui/yhgui.h>
#include <yhmvc/yhmvc.h>
#include "../Scenes/BaseScene.h"
#include "../Controllers/BaseController.h"

NS_CC_GE_BEGIN

//==============BaseScene==============//
/**
 * @brief BaseScene 结点创建
 */
class BaseSceneCreator:public yhgui::ElementCreator
{
public:
    
    YHGUI_VIRTUAL_NEW_AUTORELEASE_CREATE_ELEMENT_METHOD(BaseScene);
    YHGUI_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BaseSceneCreator,creator);
};

/**
 * @brief BaseScene的子控制器属性处理
 */
class BaseSceneControllerPropertyParser:public yhgui::PropertyParser
{
public:
    
    void parse(CCNode* node,const yhge::Json::Value& properties,CCNode* parent,yhgui::UIBuilder* builder);
    
    YHGUI_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BaseSceneControllerPropertyParser,create);
};

/**
 * @brief BaseScene的处理器
 */
class BaseSceneParser:public yhgui::NodeParser
{
public:
    
    virtual void setupPropertyParser();
    
    YHGUI_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BaseSceneParser,create);
};

//==============Controller==============//

/**
 * @brief BaseController创建器，不直接使用。是父类
 */
class BaseControllerCreator:public yhmvc::ControllerCreator
{
public:
    
    //virtual CCNode * createElement(const yhge::Json::Value& defineData,yhgui::UIBuilder* builder,CCNode* parent);
    
    YHMVC_BUILDER_CREATE_CONTROLLER(BaseController);
    
    YHGUI_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BaseControllerCreator,creator);
    
protected:
    
    //virtual yhmvc::View* loadView(BaseController* controller,const yhge::Json::Value& defineData,CCNode* parent,yhgui::UIBuilder* builder);
    //由于ControllerCreator使用的是Controller这里不能使用BaseController,否则虚数就没有效果
    virtual yhmvc::View* loadView(yhmvc::Controller* controller,const yhge::Json::Value& defineData,CCNode* parent,yhgui::UIBuilder* builder);
};


NS_CC_GE_END



#endif // CCMVC_SCENEBUILDER_BUILDEREXTERNAL_H_
