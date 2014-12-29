//
//  GameBaseScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/23.
//
//

#include "GameBaseScene.h"
#include "GetWalkPath.h"
int GameBaseScene::Hang;
int GameBaseScene::Lie;
bool** GameBaseScene::Shuzu;
Vector<RicherPlayer*>GameBaseScene::players_vector;

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
    //addPlayerAnimation();
    addPlayer();
    addbutton();
    addNotificationCenter();
   
 
    return true;
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
void GameBaseScene::addPlayer()
{
    
    //人物1 右侧信息栏
    Sprite *player_1 =Sprite::create("player1.png");
    player_1->cocos2d::Node::setPosition(visibleSie.width-120,visibleSie.height-70);
    addChild(player_1);
    
    player_1_money = Label::create();
    //player_1_money->setString("$");
    player_1_money->setSystemFontSize(25);
    player_1_money->setPosition(visibleSie.width-50,visibleSie.height-50);
    addChild(player_1_money);
   player_1_strength =Label::create();
   // player_1_strength->setString("+");
    player_1_strength->setSystemFontSize(25);
    player_1_strength->setPosition(visibleSie.width-50,visibleSie.height-90);
    addChild(player_1_strength);
    //
    Sprite *player_2 =Sprite::create("player2.png");
    player_2->cocos2d::Node::setPosition(visibleSie.width-120,visibleSie.height-300);
    addChild(player_2);
    
    player_2_money =Label::create();
   // player_2_money->setString("$");
    player_2_money->setSystemFontSize(25);
    player_2_money->setPosition(visibleSie.width-50,visibleSie.height-270);
    addChild(player_2_money);
    player_2_strength =Label::create();
   // player_2_strength->setString("+");
    player_2_strength->setSystemFontSize(25);
    player_2_strength->setPosition(visibleSie.width-50,visibleSie.height-310);
    addChild(player_2_strength);
    
    //随机种子
    struct timeval now;
    gettimeofday(&now, NULL);//计算时间种子
    unsigned rand_seed =(unsigned)(now.tv_sec*1000 +now.tv_usec/1000);//初始化随机数
    srand(rand_seed);
    //在地图上添加人物
    playerone =RicherPlayer::create("player1",1, false);
       int rand_way =rand()%(wayLayerPass_vector.size());//随机选一个id
       Vec2 vec2_player1 =wayLayerPass_vector.at(rand_way);//根据id选取一个位置的坐标
        vec2_player1.y +=32;//使人物居于道路中间
//显示人物1的金钱、能力
    char money1[20];
    sprintf(money1, "$ %d",playerone->getMoney());
    char strength1[20];
    sprintf(strength1, "+ %d",playerone->getStrength());
    getPlayer_1_money()->setString(money1);
    getPlayer_1_strnegth()->setString(strength1);
    
    playerone->setPosition(vec2_player1);
    playerone->setAnchorPoint(Point(0,0.5));
    addChild(playerone);
    players_vector.pushBack(playerone);
    
    playertwo =RicherPlayer::create("player2",2, false);
//显示人物2的金钱、能力
    char money2[20];
    sprintf(money2, "$ %d",playertwo->getMoney());
    char strength2[20];
    sprintf(strength2, "+ %d",playertwo->getStrength());
    getPlayer_2_money()->setString(money2);
    getPlayer_2_strength()->setString(strength2);
    
    int rand_way_1 =rand()%(wayLayerPass_vector.size());//随机选一个id
    Vec2 vec2_player2 =wayLayerPass_vector.at(rand_way_1);//根据id选取一个位置的坐标
    vec2_player2.y +=32;//使人物居于道路中间
    
    playertwo->setPosition(vec2_player2);
    playertwo->setAnchorPoint(Point(0,0.5));
    addChild(playertwo);
    players_vector.pushBack(playertwo);
    
}

void GameBaseScene::addbutton()
{
    
    //    Sprite *Gobtn =Sprite::create("go1.png");
    //    Gobtn->setPosition(visibleSie.width-90,visibleSie.height/5);
    //    addChild(Gobtn);
    Menu *menu =Menu::create();
    setMenu(menu);
    menu->setPosition(Point::ZERO);
    MenuItemImage *gobtnmenu =MenuItemImage::create("go1.png","go1.png",this,menu_selector(GameBaseScene::buttonpressd));
    gobtnmenu->setPosition(visibleSie.width-90,visibleSie.height/5);
    menu->addChild(gobtnmenu);
    addChild(menu);
    
}
void GameBaseScene::buttonpressd(cocos2d::Ref *p)
{
//
    randnumber =rand()%5 +1;
   GetWalkPath::getInstance()->getpath(playerone, randnumber, Shuzu, Hang, Lie);
    std::vector<int> hangvector =GetWalkPath::getInstance()->getPathhang_vector();
    std::vector<int> lievector =GetWalkPath::getInstance()->getPathlie_vector();
    for (int i=0; i<hangvector.size(); i++) {
        log("走到了第%d行,第%d列",hangvector[i],lievector[i]);
    }
//    log("%d",hangvector.size());
    NotificationCenter::getInstance()->postNotification("go_message", String::create("0"));
    playerone->startgo(hangvector, lievector);
    

}
void GameBaseScene::onExit()
{
    CC_SAFE_DELETE(Shuzu);
    Layer::onExit();

}
void GameBaseScene::addNotificationCenter()
{
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameBaseScene::messagereceived), "go_message", NULL);

}
void GameBaseScene::messagereceived(cocos2d::Ref *data)
{
    int retMsgType =((String*)data)->intValue();
    Vector<Node*> vecMenuItem = getMenu()->getChildren();
    Size winSize =Director::getInstance()->getWinSize();
    
    if (retMsgType ==0)
    {
        for (auto it =vecMenuItem.begin(); it!=vecMenuItem.end(); it++)
        {
            Node *node =dynamic_cast<Node*>(*it);
            MoveBy *moveby =MoveBy::create(0.3f, Point((node->getContentSize().width)*3,0));
            node->runAction(moveby);
        }
    }
    else if(retMsgType ==1){
    
        for (auto it =vecMenuItem.begin(); it!=vecMenuItem.end(); it++) {
            Node *node =dynamic_cast<Node*>(*it);
            MoveBy *moveby =MoveBy::create(0.3f, Point(-(node->getContentSize().width)*3,0));
            node->runAction(moveby);
        }
    
    }
    

}
