#ifndef CCGE_SCENES_SCENEREGISTERDATA_H_
#define CCGE_SCENES_SCENEREGISTERDATA_H_

#include <yhmvc/Core/SceneDirector.h>
#include "CCGEMacros.h"

typedef struct SceneRegisterItem
{
    std::string name;
    cocos2d::yhmvc::SceneCreate createFun;
} SceneRegisterItem;

//TODO use generate tool to create this file
#include "SceneDefine.h"
#include "Scenes/MainScene.h"
#include "Scenes/TestISOScene.h"
#include "Scenes/MissionScene.h"
#include "Scenes/BattleScene.h"
#include "Scenes/TestSqliteScene.h"

NS_CC_GE_BEGIN

static SceneRegisterItem kSceneRegisterData[]=
{
    {kMainScene,SCENE_CREATE_SELECTOR(MainScene::create)},
	{kTestISOScene,SCENE_CREATE_SELECTOR(TestISOScene::create)},
    {kMissioncene,SCENE_CREATE_SELECTOR(MissionScene::create)},
    {kBattlecene,SCENE_CREATE_SELECTOR(BattleScene::create)},
    {kTestSqlite,SCENE_CREATE_SELECTOR(TestSqliteScene::create)},
};

NS_CC_GE_END

#endif //CCGE_SCENES_SCENEREGISTERDATA_H_
