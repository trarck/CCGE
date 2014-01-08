//
//  Game.h
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#ifndef __CCMVC__Game__
#define __CCMVC__Game__

#include "cocos2d.h"
#include "CCGEMacros.h"

NS_CC_GE_BEGIN

class Game:public CCObject
{
public:
    
    
    static Game* getInstance();

    /**
	 * 设置场景管理
	 */
    void setupSceneDirector();
};

NS_CC_GE_END



#endif /* defined(__CCMVC__Game__) */
