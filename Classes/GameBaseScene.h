//
//  GameBaseScene.h
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#ifndef __RichGame__GameBaseScene__
#define __RichGame__GameBaseScene__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include"RicherPlayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GameBaseScene:public Layer
{
public:
    int Hang;//地图总行数
    int Lie;//地图总列数
    bool** Shuzu;//行列数数组
    std::vector<Vec2>wayLayerPass_vector;//保存way图层道路砖块的坐标
    virtual void initShuzu();
    void setWayPass();//在way图层把道路在数组中的位置设置为true；
    SpriteFrameCache *player1;//
    SpriteFrameCache *player2;
    void addPlayerAnimation();//添加人物的动画
    Size visibleSie;
    virtual bool init();
    static Scene*createScene();
//    
    Animate * player1_left_animate;
    Animate * player1_right_animate;
    Animate * player1_down_animate;
    Animate * player1_up_animate;
    
    Animate * player2_left_animate;
    Animate * player2_right_animate;
    Animate * player2_down_animate;
    Animate * player2_up_animate;
    
    RicherPlayer *playerone;
    RicherPlayer *playertwo;

    TMXTiledMap *_map;
    virtual void addMap();
    CREATE_FUNC(GameBaseScene);
private:
    //void drawTable(int playnumber);//根据人数绘画右边信息栏的表格
    void addPlayer();//添加人物
    Sprite *rightbanner;
    Sprite *player_1;
    Sprite *player_2;
    void addbutton();
    void buttonpressd(Ref *p);

};
#endif /* defined(__RichGame__GameBaseScene__) */
