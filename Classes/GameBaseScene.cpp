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
Vector<Sprite*>GameBaseScene::pathMark_vector;
TMXTiledMap *GameBaseScene::_map;
TMXLayer *GameBaseScene::landlayer;
int GameBaseScene::blank_land_tiledID;

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
    addpathMake();
    //addPlayerAnimation();
    addPlayer();
    addDice();
    addroundcounts();
    refreshround();
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

    randnumber =rand()%6 +1;
   GetWalkPath::getInstance()->getpath(playerone, randnumber, Shuzu, Hang, Lie);
    std::vector<int> hangvector =GetWalkPath::getInstance()->getPathhang_vector();
    std::vector<int> lievector =GetWalkPath::getInstance()->getPathlie_vector();
    for (int i=0; i<hangvector.size(); i++) {
        log("走到了第%d行,第%d列",hangvector[i],lievector[i]);
    }
//    log("%d",hangvector.size());
    NotificationCenter::getInstance()->postNotification("go_message", String::createWithFormat("%d",0));
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
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameBaseScene::messagereceived), "buy_land_msg",NULL);
    

}
void GameBaseScene::messagereceived(cocos2d::Ref *data)
{
    String  *srcData =(String*)data;
    Vector<String*>message_vector =Util::splitString(srcData->getCString(), "-");
    
    int retMsgType =message_vector.at(0)->intValue();
    Vector<Node*> vecMenuItem = getMenu()->getChildren();
    Size winSize =Director::getInstance()->getWinSize();
    switch (retMsgType) {
        case 0://隐藏GO按钮
        {
            for (auto it =vecMenuItem.begin(); it!=vecMenuItem.end(); it++)
        {
            Node *node =dynamic_cast<Node*>(*it);
            MoveBy *moveby =MoveBy::create(0.3f, Point((node->getContentSize().width)*3,0));
            node->runAction(moveby);
        }
            
            char stop[20];
            sprintf(stop, "dice_%02d.png",randnumber);
            diceframe->setSpriteFrame(dice_framecache->getSpriteFrameByName(stop));
            diceframe->pause();
            break;
        }
        case 1: //显示GO按钮
        {
            for (auto it =vecMenuItem.begin(); it!=vecMenuItem.end(); it++)
            {
                Node *node =dynamic_cast<Node*>(*it);
                MoveBy *moveby =MoveBy::create(0.3f, Point(-(node->getContentSize().width)*3,0));
                node->runAction(moveby);
            }
            roundcount+=1;
            refreshround();
            diceframe->resume();
        }
        case 2://购买空地
        {
            buy_land_x =message_vector.at(1)->floatValue();
            buy_land_y =message_vector.at(2)->floatValue();
            //调用showbuylandDialog，跳出弹窗
            showbuylandDialog(2);
            
        
        }
        
    }
    
}
void GameBaseScene::addpathMake()
{
    Sprite *mark1 =Sprite::create("mark1.png");
    Sprite *mark2 =Sprite::create("mark2.png");
    Sprite *mark3 =Sprite::create("mark3.png");
    Sprite *mark4 =Sprite::create("mark4.png");
    Sprite *mark5 =Sprite::create("mark5.png");
    Sprite *mark6 =Sprite::create("mark6.png");
    //
    mark1->setAnchorPoint(Point(0,0));
    mark2->setAnchorPoint(Point(0,0));
    mark3->setAnchorPoint(Point(0,0));
    mark4->setAnchorPoint(Point(0,0));
    mark5->setAnchorPoint(Point(0,0));
    mark6->setAnchorPoint(Point(0,0));

//设置为不可见
    mark1->setVisible(false);
    mark2->setVisible(false);
    mark3->setVisible(false);
    mark4->setVisible(false);
    mark5->setVisible(false);
    mark6->setVisible(false);
    //
    addChild(mark1);
    addChild(mark2);
    addChild(mark3);
    addChild(mark4);
    addChild(mark5);
    addChild(mark6);

    //
    pathMark_vector.pushBack(mark1);
    pathMark_vector.pushBack(mark2);
    pathMark_vector.pushBack(mark3);
    pathMark_vector.pushBack(mark4);
    pathMark_vector.pushBack(mark5);
    pathMark_vector.pushBack(mark6);


}
void GameBaseScene::drawpathcolor(std::vector<int> hangvector, std::vector<int> lievector)
{
//减去当前位置
    //int stepcounts =hangvector.size()-1;
    //从容器取出标记放在相应位置
    for (int i=1; i<hangvector.size(); i++) {
        pathMark_vector.at(i-1)->setPosition(Point(lievector[i]*34,hangvector[i]*32));
        pathMark_vector.at(i-1)->setVisible(true);
    }
}
void GameBaseScene::addDice()
{
    dice_framecache =SpriteFrameCache::getInstance();
    dice_framecache->addSpriteFramesWithFile("dice.plist", "dice.png");
    
    Vector<SpriteFrame*> dice_vector;
    char name[20];
    for (int i=1; i<=6; i++) {
        sprintf(name, "dice_%02d.png",i);
        dice_vector.pushBack(dice_framecache->getSpriteFrameByName(name));
        
    }
    //
    if (!AnimationCache::getInstance()->getAnimation("dice_animation")) {
        AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(dice_vector,0.1), "dice_animation");
    }
    dice_animate =Animate::create(AnimationCache::getInstance()->getAnimation("dice_animation"));
    dice_animate->retain();
    
    //
    diceframe =Sprite::createWithSpriteFrame(dice_framecache->getSpriteFrameByName("dice_01.png"));
    diceframe->setPosition(Point(visibleSie.width-90,visibleSie.height/3));
    addChild(diceframe);
    
    diceframe->runAction(RepeatForever::create(dice_animate));

}

void GameBaseScene::addroundcounts()
{
    roundcount =0;
    SpriteFrameCache *round_framecache =SpriteFrameCache::getInstance();
    round_framecache->addSpriteFramesWithFile("digital_round.plist");
    char name[20];
    memset(name, 0, 20);
    for (int i=0; i<10; i++) {
        sprintf(name, "digital_%d.png",i);
        round_picture_vector.pushBack(round_framecache->getSpriteFrameByName(name));
    }

}

void GameBaseScene::refreshround()
{
    //刷新前把之前显示的隐藏
    for (auto it =refresh_round_vector.begin(); it!=refresh_round_vector.end(); it++) {
        (*it)->setVisible(false);
    }
    
    refresh_round_vector.clear();
    int count =roundcount;
    Sprite *sp;
    //游戏开始的回合
    if (count ==0) {
        sp = Sprite::createWithSpriteFrame(round_picture_vector.at(0));
        addChild(sp);
        refresh_round_vector.pushBack(sp);
    }
    while (count !=0) {
        sp =Sprite::createWithSpriteFrame(round_picture_vector.at(count%10));
        addChild(sp);
        refresh_round_vector.pushBack(sp);
        count =count/10;
    }
    //取图时是倒序取得，所以要把顺序反一下
    refresh_round_vector.reverse();
    //显示图片
    for(int i =0;i<refresh_round_vector.size();i++)
    {
        Sprite *st =refresh_round_vector.at(i);
        st->setPosition(Point((visibleSie.width-90)+(i*25),visibleSie.height/10));
        st->setVisible(true);
    }

}

void GameBaseScene::buylandpopuplayer()
{
    buyland =PopupLayer::create("dialog_bg.png");
    buyland->setTitle("购买提示");
    buyland->setContentText("",20,60,250);
    buyland->setcallbackfunc(this, callfuncN_selector(GameBaseScene::buylandcallback));
    buyland->addButton("button_bg1.png", "button_bg2.png", "确定",1);
    buyland->addButton("button_bg1.png", "button_bg2.png", "取消",0);
    this->addChild(buyland);
    buyland->setVisible(false);
        
}

void GameBaseScene::buylandcallback(cocos2d::Node *p)
{
    if (p->getTag() == 1)
    {
    switch (buyland->getTag())
    {
        case 2:
           // landlayer->setTileGID(uint32_t gid, <#const cocos2d::Vec2 &tileCoordinate#>)
            break;
            
        default:
            break;
    }
    }
}
void GameBaseScene::showbuylandDialog(int landtag)
{
  String show_msg ="";
    switch (landtag) {
        case 2:
            show_msg =String::createWithFormat("你想用$ %d买下这块土地吗?",1000)->getCString();
            break;
        case 3:
            show_msg =String::createWithFormat("你想用$ %d买下这块土地吗?",2000)->getCString();
            break;
    }
    buyland->setTag(landtag);
    buyland->getContentlabel()->setString(show_msg.getCString());
    buyland->setVisible(true);
    

}