#ifndef CCGE_SCENES_TESTSQLITESCENE_H_
#define CCGE_SCENES_TESTSQLITESCENE_H_

#include "ThreeSegmentScene.h"

NS_CC_GE_BEGIN

class TestSqliteScene : public ThreeSegmentScene
{
public:

    void loadContents();

    CREATE_FUNC(TestSqliteScene);
    
private:
    
};
NS_CC_GE_END

#endif // CCGE_SCENES_TESTSQLITESCENE_H_
