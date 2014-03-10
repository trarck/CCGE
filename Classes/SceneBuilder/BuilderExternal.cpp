
#include "BuilderExternal.h"

USING_NS_CC;
USING_NS_CC_YHMVC;

NS_CC_GE_BEGIN

void BaseSceneControllerPropertyParser::parse(CCNode* node,const yhge::Json::Value& properties,CCNode* parent,yhgui::UIBuilder* builder)
{
    yhge::Json::Value controllersValue=properties[yhmvc::kElementPropertyController];
    if (!controllersValue.isNull()) {
        BaseScene* scene=static_cast<BaseScene*>(node);
        yhmvc::View* view=NULL;
        
        yhge::Json::Value::UInt count=controllersValue.size();
        for (int i=0;i<count;i++) {
            view=static_cast<yhmvc::View*>(builder->buildElement(controllersValue[i],node,false));
            scene->addController(view->getController());
            scene->getDocument()->addChild(view);
        }
    }
}

void BaseSceneParser::setupPropertyParser()
{
    yhgui::NodeParser::setupPropertyParser();
    
    registerPropertyParser(kElementPropertyController, BaseSceneControllerPropertyParser::create());
}

yhmvc::View*
BaseControllerCreator::loadView(
                            yhmvc::Controller* controller,
                            const yhge::Json::Value& defineData,
                            CCNode* parent,yhgui::UIBuilder* builder)
{
    BaseController* baseController=static_cast<BaseController*>(controller);

    //替换事件处理
    yhgui::ElementEventParser* elementEventParser=builder->getElementEventParser();
    elementEventParser->retain();
    
    builder->setElementEventParser(baseController->createEventParser());
    
    yhmvc::View* view=ControllerCreator::loadView(baseController, defineData, parent, builder);
    
    builder->setElementEventParser(elementEventParser);
    elementEventParser->release();
    
    return view;
}

NS_CC_GE_END
