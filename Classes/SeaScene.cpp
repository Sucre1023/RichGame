    //
//  SeaScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#include "SeaScene.h"
Scene *SeaScene::createScene()
{
    auto scene =Scene::create();
    auto layer =SeaScene::create();
    scene->addChild(layer);
    return scene;

}
bool SeaScene::init()
{
    if (!GameBaseScene::init()) {
        return false;
    }
    return true;
}

void GameBaseScene::addMap()
{
    _map =TMXTiledMap::create("finalsea.tmx");
    _map->setPosition(0,0);
    addChild(_map);
}

void GameBaseScene::initShuzu()
{

    Hang =20;
    Lie =29;
    //根据行列数创建数组Shuzu
    Shuzu =new bool*[Hang];
    for (int i =0; i<Hang; i++) {
        Shuzu[i] =new bool [Lie];
    }
    //Shuzu默认为false；
    for (int i =0; i<Hang; i++) {
        for (int j =0; j<Lie; j++) {
            Shuzu[i][j] =false;
        }
    }


}