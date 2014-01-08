//
//  GameMacros.h
//  CCMVC
//
//  Created by duanhouhai on 13-11-1.
//
//

#ifndef CCGE_CCGEMACROS_H_
#define CCGE_CCGEMACROS_H_

#ifdef __cplusplus
#define NS_CC_GE_BEGIN                     namespace cocos2d { namespace ccge {
#define NS_CC_GE_END                       }}
#define USING_NS_CC_GE					using namespace cocos2d::ccge
#else
#define NS_CC_GE_BEGIN
#define NS_CC_GE_END
#define USING_NS_CC_GE
#endif //__cplusplus

#endif //CCGE_CCGEMACROS_H_
