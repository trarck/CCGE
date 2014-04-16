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
    
    virtual void createDocument();
    
//    void loadContents();
    
    CREATE_FUNC(BaseScene);
    
public:
    
    inline void setDocument(yhgui::Component* document)
    {
        //        CC_SAFE_RETAIN(document);
        //        CC_SAFE_RELEASE(m_document);
        m_document = document;
    }
    
    inline yhgui::Component* getDocument()
    {
        return m_document;
    }
    
protected:
    
    yhgui::Component* m_document;
    
    yhgui::NormalDocumentTreeOrganizer* m_internalOrgnaizer;
};

NS_CC_GE_END

#endif /* defined(CCGE_SCENES_BASESCENE_H_) */
