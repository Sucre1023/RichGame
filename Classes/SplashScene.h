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
const double MOVE_SPEED =0.5f;
void movefirstToLeft();
void movesecondToLeft();

void initMoveSprite();   //初始化图片方法
void startMoveSprite(float dt);//开始移动方法
void gotoMenuScene();//动画结束后进入MenuScene场景方法
void spriteFadeOut();//动画逐渐消失方法
Sprite* fir_Sprite ;//main.png图片精灵
Sprite* sec_Sprite ;// ke.png图片精灵
Sprite* thir_Sprite;// ji.png图片精灵
Sprite* four_Sprite;// cheng.png图片精灵
Size visibleSize;//窗口大小
Size spriteSize;//每张图片的尺寸大小
#endif /* defined(__RichGame__SplashScene__) */
