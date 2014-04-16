#ifndef CCMVC_SCENEBUILDER_GAMESCENEBUILDER_H_
#define CCMVC_SCENEBUILDER_GAMESCENEBUILDER_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhmvc/yhmvc.h>
#include "../Scenes/BaseScene.h"

NS_CC_GE_BEGIN

class GameSceneBuilder:public yhmvc::MvcBuilder
{
public:
    
    GameSceneBuilder();
    
    ~GameSceneBuilder();
    
    static GameSceneBuilder* getInstance();
    
    /**
     * @brief 加入扩展
     * 把Scene的创建方式改为创建BaseScene
     */
    void setupExtend();
    
    void addController(const std::string& constroller,yhgui::ElementCreator* creator);
    
    static BaseScene* buildScene();
    
    static std::string getSceneDefineFile(const std::string& sceneName);
};

NS_CC_GE_END



#endif // CCMVC_SCENEBUILDER_GAMESCENEBUILDER_H_
