//
//  GameBaseScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#include "GameBaseScene.h"
Scene *GameBaseScene::createScene()
{
    auto scene =Scene::create();
    auto layer =GameBaseScene::create();
    scene->addChild(layer);
    return scene;

}
bool GameBaseScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //加入右边信息栏
    visibleSie =Director::getInstance()->getVisibleSize();
    rightbanner =Sprite::create("right_banner.png");
    rightbanner->setAnchorPoint(Point(0,0));
    rightbanner->setPosition(visibleSie.width-150,0);
    addChild(rightbanner);
    addMap();
    addPlayer();
    return true;
}
//void GameBaseScene::drawTable(int playnumber)
//{
//    auto s = Director::getInstance()->getWinSize();
//    
//    auto draw = DrawNode::create();
//    this->addChild(draw);
//    
//    for(int i=0;i<playnumber;i++)
//    {
//        draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y-2*i*tableHeight),
//                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y-2*i*tableHeight), 1,
//                          Color4F(0, 1, 0, 1));
//        
//        draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y - 2*(i+1)*tableHeight),
//                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - 2*(i+1)*tableHeight), 1,
//                          Color4F(0, 1, 0, 1));
//        
//        draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight),
//                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 1,
//                          Color4F(0, 1, 0, 1));
//        
//        draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2*i*tableHeight),
//                          Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2* tableHeight-2*i*tableHeight), 1,
//                          Color4F(0, 1, 0, 1));
//    }
//
//    
//    
//}
void GameBaseScene::addPlayer()
{
    //人物1
    Sprite *player_1 =Sprite::create("player1.png");
    player_1->cocos2d::Node::setPosition(visibleSie.width-120,visibleSie.height-70);
    addChild(player_1);
    
    Label *player_1_money =Label::create();
    player_1_money->setString("$");
    player_1_money->setSystemFontSize(25);
    player_1_money->setPosition(visibleSie.width-90,visibleSie.height-50);
    addChild(player_1_money);
    Label *player_1_strength =Label::create();
    player_1_strength->setString("+");
    player_1_strength->setSystemFontSize(25);
    player_1_strength->setPosition(visibleSie.width-90,visibleSie.height-90);
    addChild(player_1_strength);
   //
    Sprite *player_2 =Sprite::create("player2.png");
    player_2->cocos2d::Node::setPosition(visibleSie.width-120,visibleSie.height-300);
    addChild(player_2);
    
    Label *player_2_money =Label::create();
    player_2_money->setString("$");
    player_2_money->setSystemFontSize(25);
    player_2_money->setPosition(visibleSie.width-90,visibleSie.height-270);
    addChild(player_2_money);
    Label *player_2_strength =Label::create();
    player_2_strength->setString("+");
    player_2_strength->setSystemFontSize(25);
    player_2_strength->setPosition(visibleSie.width-90,visibleSie.height-330);
    addChild(player_2_strength);

}