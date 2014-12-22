//
//  SplashScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/21.
//
//

#include "SplashScene.h"
#define FIRST_IMAGE   "first.png"
#define SEC_IMAGE     "second.png"
#define THI_IMAGE      "third.png"
#define FOUR_IMAGE      "four.png"
Scene *SplashScene::createScene()
{
    auto scene =Scene::create();
    auto layer =SplashScene::create();
    scene->addChild(layer);
    return scene;

}
bool SplashScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize =Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    initMoveSprite();
    scheduleOnce(schedule_selector(SplashScene::startMoveSprite), 1.0f);//
    return true;
    
}

void SplashScene::initMoveSprite()
{
    //创建4张图片
    fir_Sprite =Sprite::create(FIRST_IMAGE);
    sec_Sprite =Sprite::create(SEC_IMAGE);
    thir_Sprite =Sprite::create(THI_IMAGE);
    four_Sprite =Sprite::create(FOUR_IMAGE);
    //设置精灵锚点
    fir_Sprite->setAnchorPoint(Point(0,0.5));
    sec_Sprite->setAnchorPoint(Point(0,0.5));
    thir_Sprite->setAnchorPoint(Point(0,0.5));
    four_Sprite->setAnchorPoint(Point(0,0.5));

    spriteSize =fir_Sprite->getContentSize();//
    //设置位置
    sec_Sprite->setPosition(visibleSize.width/2 -(2*spriteSize.width),visibleSize.height/2);
    thir_Sprite->setPosition(visibleSize.width/2-spriteSize.width,visibleSize.height/2);
    four_Sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    fir_Sprite->setPosition(visibleSize.width/2 +spriteSize.width,visibleSize.height/2);
    
    addChild(fir_Sprite);
    addChild(sec_Sprite);
    addChild(thir_Sprite);
    addChild(four_Sprite);
    
}

//动画效果：E S T <-T，TEST的第一个T起初在最右边，需要移动到最左边
void SplashScene::startMoveSprite(float dt)
{
//TEST的第一个“T”从右往左移
    MoveBy *movefirstT = MoveBy::create(MOVE_SPEED, Point(-spriteSize.width,0));
    fir_Sprite->runAction(movefirstT);
    
    //TEST的另一个T从左往右移，相当于两个T交换位置
    MoveBy *movefourT =MoveBy::create(MOVE_SPEED, Point(spriteSize.width,0));
//调用movethirdtoLeft()函数，移动“S”；
    CallFunc *callFunc3 =CallFunc::create(CC_CALLBACK_0(SplashScene::movethirdtoLeft, this));


    four_Sprite->runAction(Sequence::create(movefourT,callFunc3, NULL));
}
void SplashScene::movethirdtoLeft()
{
    //TEST的第一个“T”继续从右往左移
    MoveBy *movefirstT2 = MoveBy::create(MOVE_SPEED, Point(-spriteSize.width,0));
    fir_Sprite->runAction(movefirstT2);
    
    //TEST的S从左往右移，相当于交换位置
    MoveBy *movethird =MoveBy::create(MOVE_SPEED, Point(spriteSize.width,0));
    
    //调用movesecondtoLeft()函数，移动“E”；
    CallFunc *callFunc2 =CallFunc::create(CC_CALLBACK_0(SplashScene::movesecondtoLeft, this));
    
    
    thir_Sprite->runAction(Sequence::create(movethird,callFunc2, NULL));

}
void SplashScene::movesecondtoLeft()
{

    //TEST的第一个“T”继续从右往左移到达最左边
    MoveBy *movefirstT3 = MoveBy::create(MOVE_SPEED, Point(-spriteSize.width,0));
    fir_Sprite->runAction(movefirstT3);
    
    //TEST的E从左往右移，相当于交换位置
    MoveBy *movesecond =MoveBy::create(MOVE_SPEED, Point(spriteSize.width,0));
    //调用SpriteFadeOut()函数，动画淡出；
    CallFunc *callFunc1 =CallFunc::create(CC_CALLBACK_0(SplashScene::spriteFadeOut, this));
    
    sec_Sprite->runAction(Sequence::create(movesecond,callFunc1, NULL));

    
}
void SplashScene::spriteFadeOut()
{
//定义4个fadeout函数
    FadeOut *fadeout1 =FadeOut::create(2.0f);
    FadeOut *fadeout2 =FadeOut::create(2.0f);
    FadeOut *fadeout3 =FadeOut::create(2.0f);
    FadeOut *fadeout4 =FadeOut::create(2.0f);
    sec_Sprite->runAction(fadeout2);
    thir_Sprite->runAction(fadeout3);
    four_Sprite->runAction(fadeout4);
    //跳转至菜单界面
    CallFunc *callfuncMenuScence =CallFunc::create(CC_CALLBACK_0(SplashScene::gotoMenuScene, this));
    
    fir_Sprite->runAction(Sequence::create(fadeout1,callfuncMenuScence, NULL));
    
}
void SplashScene::gotoMenuScene()
{

    
    
}

