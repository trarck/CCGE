#ifndef CCGE_GAME_H_
#define CCGE_GAME_H_

#include "cocos2d.h"
#include "CCGEMacros.h"
#include <yhge/Message/MessageManager.h>

NS_CC_GE_BEGIN

class Game:public CCObject
{
public:
    
	Game();
	~Game();
    
    static Game* getInstance();

    /**
     * 执行初始化的工作
     */
    void setup();
    
    /**
	 * 设置场景管理
	 */
    void setupSceneDirector();
    
    inline static yhge::MessageManager* getMessageManager()
    {
        return yhge::MessageManager::defaultManager();
    }
        
private:
};

NS_CC_GE_END



#endif //CCGE_GAME_H_
