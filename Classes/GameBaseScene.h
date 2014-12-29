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
   static int Hang;//地图总行数
   static int Lie;//地图总列数
   static bool** Shuzu;//行列数数组
    std::vector<Vec2>wayLayerPass_vector;//保存way图层道路砖块的坐标
    virtual void initShuzu();
    void setWayPass();//在way图层把道路在数组中的位置设置为true；
    Size visibleSie;
    virtual bool init();
    static Scene*createScene();
    
    static Vector<RicherPlayer*>players_vector;//存放人物的容器
//
    
    RicherPlayer *playerone;
    RicherPlayer *playertwo;

    TMXTiledMap *_map;
    virtual void addMap();
    void onExit();
    void buttonpressd(Ref *p);

    //
    static Vector<Sprite*> pathMark_vector;//存放行走路径标记的容器
    void addpathMake();//添加标记
    static void drawpathcolor(std::vector<int>hangvector,std::vector<int>lievector);//绘制路径标记
    
    CREATE_FUNC(GameBaseScene);
private:
    //void drawTable(int playnumber);//根据人数绘画右边信息栏的表格
    void addPlayer();//添加人物
    Sprite *rightbanner;
  //添加消息机制
    void addNotificationCenter();
    void messagereceived(Ref *data);
    CC_SYNTHESIZE(Menu*, _menu, Menu);
    void addbutton();
    int randnumber;
    CC_SYNTHESIZE(Label*, player_1_money, Player_1_money);
    CC_SYNTHESIZE(Label*, player_2_money, Player_2_money);
    CC_SYNTHESIZE(Label*, player_1_strength, Player_1_strnegth);
    CC_SYNTHESIZE(Label*, player_2_strength, Player_2_strength);



};
#endif /* defined(__RichGame__GameBaseScene__) */
