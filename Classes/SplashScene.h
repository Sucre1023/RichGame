//
//  SplashScene.h
//  RichGame
//
//  Created by Sucre on 14/12/21.
//
//

#ifndef __RichGame__SplashScene__
#define __RichGame__SplashScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class SplashScene:public Layer
{
private:
const double MOVE_SPEED =0.5f;
Sprite* fir_Sprite ;//first.png图片精灵
Sprite* sec_Sprite ;// second.png图片精灵
Sprite* thir_Sprite;// third.png图片精灵
Sprite* four_Sprite;// four.png图片精灵
Size visibleSize;//窗口大小
Size spriteSize;//每张图片的尺寸大小
public:
    static Scene *createScene();
    virtual bool  init();
void movesecondtoLeft();//second.png往左移
void movethirdtoLeft();//third.png往左移
void initMoveSprite();   //初始化图片方法
void startMoveSprite(float dt);//开始移动方法
void gotoMenuScene();//动画结束后进入MenuScene场景方法
void spriteFadeOut();//动画逐渐消失方法
    CREATE_FUNC(SplashScene);
};
#endif /* defined(__RichGame__SplashScene__) */
