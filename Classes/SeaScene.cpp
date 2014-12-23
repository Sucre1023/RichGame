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
    _map =TMXTiledMap::create("sea.tmx");
    _map->setPosition(0,0);
    addChild(_map);
}