//
//  BaseScene.h
//  CCGE
//
//  Created by duanhouhai on 13-8-6.
//
//

#ifndef CCGE_SCENES_BASESCENE_H_
#define CCGE_SCENES_BASESCENE_H_

#include "cocos2d.h"
#include <yhgui/yhgui.h>
#include <yhmvc/Core/Scene.h>
#include "CCGEMacros.h"

NS_CC_GE_BEGIN
class BaseScene:public cocos2d::yhmvc::Scene
{
public:
    
    BaseScene();
    ~BaseScene();
    
    bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
protected:
    
    yhgui::Component* m_document;
};

NS_CC_GE_END

#endif /* defined(CCGE_SCENES_BASESCENE_H_) */
