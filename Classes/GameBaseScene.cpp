//
//  GameBaseScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#include "GameBaseScene.h"
#include "GetWalkPath.h"
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
      initShuzu();
     setWayPass();
    addPlayerAnimation();
    addPlayer();
    addbutton();
    
   
 
    return true;
}
void GameBaseScene::addPlayer()
{
    
    //人物1 右侧信息栏
    player_1 =Sprite::create("player1.png");
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
  player_2 =Sprite::create("player2.png");
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
    
    //随机种子
    struct timeval now;
    gettimeofday(&now, NULL);//计算时间种子
    unsigned rand_seed =(unsigned)(now.tv_sec*1000 +now.tv_usec/1000);//初始化随机数
    srand(rand_seed);
    //在地图上添加人物
    SpriteFrame *spf1 =player1->getSpriteFrameByName("player1_anim_01.png");//从精灵缓存帧中取第一张图片
    playerone =RicherPlayer::create("player1",spf1, false);
    
    int rand_way =rand()%(wayLayerPass_vector.size());//随机选一个id
    Vec2 vec2_player1 =wayLayerPass_vector.at(rand_way);//根据id选取一个位置的坐标
    vec2_player1.y +=32;//使人物居于道路中间
    
    playerone->setPosition(vec2_player1);
    playerone->setAnchorPoint(Point(0,0.5));
    addChild(playerone);
    
    SpriteFrame *spf2 =player2->getSpriteFrameByName("player2_anim_01.png");//从精灵缓存帧中取第一张图片
    playertwo =RicherPlayer::create("player2", spf2, false);
    
    int rand_way_1 =rand()%(wayLayerPass_vector.size());//随机选一个id
    Vec2 vec2_player2 =wayLayerPass_vector.at(rand_way_1);//根据id选取一个位置的坐标
    vec2_player2.y +=32;//使人物居于道路中间
    
    playertwo->setPosition(vec2_player2);
    playertwo->setAnchorPoint(Point(0,0.5));
    addChild(playertwo);

}
void GameBaseScene::setWayPass()
{
    TMXLayer *waylayer =_map->layerNamed("way");//获取way图层
    Size waysize =waylayer->getLayerSize();
    for (int i =0; i<waysize.width; i++) {
        for (int j=0; j<waysize.height; j++) {
            Sprite * waysprite =waylayer->tileAt(Point(i,j));//选择指定位置的砖块对象并返回
            if(waysprite){
                float x =waysprite->getPositionX();
                float y =waysprite->getPositionY();
                
                int lie =x/34;
                int hang =y/32;
                
                Shuzu[hang][lie] =true;
                //获取位置保存到wayLayerPass_vector中
                Vec2 p =waysprite->getPosition();
                wayLayerPass_vector.push_back(p);
                log("道路坐标: hang = %d  lie = %d",hang,lie);
                
            }
            
        }
    }
    

}
void GameBaseScene::addbutton()
{
    
    //    Sprite *Gobtn =Sprite::create("go1.png");
    //    Gobtn->setPosition(visibleSie.width-90,visibleSie.height/5);
    //    addChild(Gobtn);
    Menu *menu =Menu::create();
    menu->setPosition(Point::ZERO);
    MenuItemImage *gobtnmenu =MenuItemImage::create("go1.png","go1.png",this,menu_selector(GameBaseScene::buttonpressd));
    gobtnmenu->setPosition(visibleSie.width-90,visibleSie.height/5);
    menu->addChild(gobtnmenu);
    addChild(menu);
    
}
void GameBaseScene::buttonpressd(cocos2d::Ref *p)
{
    
    GetWalkPath::getInstance()->getpath(playerone, 5, Shuzu, 20, 29);
    std::vector<int> hangvector =GetWalkPath::getInstance()->getpathhang_vector();
    std::vector<int> lievector =GetWalkPath::getInstance()->getpahtlie_vector();
    for (int i=0; i<5; i++) {
        log("走到了第%d行,第%d列",hangvector[i],lievector[i]);
    }

}

void GameBaseScene::addPlayerAnimation()
{
//加载Player1
    player1 =SpriteFrameCache::getInstance();
    player1->addSpriteFramesWithFile("player1_anim.plist", "player1_anim.png");
  //加载player2
    player2 =SpriteFrameCache::getInstance();
    player2->addSpriteFramesWithFile("player2_anim.plist", "player2_anim.png");
    //player1四个方向的Vector
    Vector<SpriteFrame*> player1_left;
    Vector<SpriteFrame*> player1_right;
    Vector<SpriteFrame*> player1_up;
    Vector<SpriteFrame*> player1_down;
//palye2
    Vector<SpriteFrame*> player2_left;
    Vector<SpriteFrame*> player2_right;
    Vector<SpriteFrame*> player2_up;
    Vector<SpriteFrame*> player2_down;
    //
    char name[20];
    memset(name, 0, 20);//将前20个字节替换为0 并返回name；清零
    //取出1-4张图片是向左动画保存到player1_left容器里
    for (int i=1; i<=4; i++)
    {
        sprintf(name, "player1_anim_%02d.png",i);//把1-4张图片写入name
        player1_left.pushBack(player1->getSpriteFrameByName(name));
        
        sprintf(name, "player2_anim_%02d.png",i);
        player2_left.pushBack(player2->getSpriteFrameByName(name));
    }
    //5-8 向右
    for (int i=5; i<=8; i++)
    {
        sprintf(name, "player1_anim_%02d.png",i);//把1-4张图片写入name
        player1_right.pushBack(player1->getSpriteFrameByName(name));
        
        sprintf(name, "player2_anim_%02d.png",i);
        player2_right.pushBack(player2->getSpriteFrameByName(name));
    }
    //9-12 向下
    for (int i=9; i<=12; i++)
    {
        sprintf(name, "player1_anim_%02d.png",i);//把1-4张图片写入name
        player1_down.pushBack(player1->getSpriteFrameByName(name));
        
        sprintf(name, "player2_anim_%02d.png",i);
        player2_down.pushBack(player2->getSpriteFrameByName(name));
    }
//13-16 向上
    for (int i=13; i<=16; i++)
    {
        sprintf(name, "player1_anim_%02d.png",i);//把1-4张图片写入name
        player1_up.pushBack(player1->getSpriteFrameByName(name));
        
        sprintf(name, "player2_anim_%02d.png",i);
        player2_up.pushBack(player2->getSpriteFrameByName(name));
    }
    //用vector创建动作
    Animation*player1_left_animation =Animation::createWithSpriteFrames(player1_left, 0.1f);
    Animation*player1_right_animation =Animation::createWithSpriteFrames(player1_right, 0.1f);
    Animation*player1_down_animation =Animation::createWithSpriteFrames(player1_down, 0.1f);
    Animation*player1_up_animation =Animation::createWithSpriteFrames(player1_up, 0.1f);
    
    Animation*player2_left_animation =Animation::createWithSpriteFrames(player2_left, 0.1f);
    Animation*player2_right_animation =Animation::createWithSpriteFrames(player2_right, 0.1f);
    Animation*player2_down_animation =Animation::createWithSpriteFrames(player2_down, 0.1f);
    Animation*player2_up_animation =Animation::createWithSpriteFrames(player2_up, 0.1f);
    //根据动作创建动画
    player1_left_animate =Animate::create(player1_left_animation);
    player1_right_animate =Animate::create(player1_right_animation);
    player1_down_animate =Animate::create(player1_down_animation);
    player1_up_animate =Animate::create(player1_up_animation);

    player2_left_animate =Animate::create(player2_left_animation);
    player2_right_animate =Animate::create(player2_right_animation);
    player2_down_animate =Animate::create(player2_down_animation);
    player2_up_animate =Animate::create(player2_up_animation);

}


