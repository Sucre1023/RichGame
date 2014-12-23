//
//  MenuScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/22.
//
//

#include "MenuScene.h"
#include "MapChooseScene.h"
Scene *MenuScene::createScene()
{
    auto scene =Scene::create();
    auto layer =MenuScene::create();
    scene->addChild(layer);
    return scene;
    
}

bool MenuScene::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
        
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    //添加背景
    Sprite *backgroundsprite =Sprite::create("background.png");
    backgroundsprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(backgroundsprite);
    addMenuSprites();
    return true;
}
void MenuScene::addMenuSprites()
{
    //单人游戏按钮
    Scale9Sprite *btnNormal =Scale9Sprite::create("normal_menu.png");
    Scale9Sprite *btnPress =Scale9Sprite::create("press_menu.png");
    Label *singlegamelabel =Label::create("单人游戏","",20);
    ControlButton *singlegamebtn =ControlButton::create(singlegamelabel,btnNormal);//创建controlbutton
    singlegamebtn->setBackgroundSpriteForState(btnPress, Control::State::SELECTED);//singlebutton按下效果图片
    singlegamebtn->setPosition(visibleSize.width-200,visibleSize.height-300);
    singlegamebtn->setPreferredSize(Size(222,50));
    singlegamebtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);  //按钮回调
    singlegamebtn->setTag(10001);//设置tag
    addChild(singlegamebtn);
    //多人游戏按钮
    Scale9Sprite *btnNormals =Scale9Sprite::create("normal_menu.png");
    Scale9Sprite *btnPresss =Scale9Sprite::create("press_menu.png");
    Label *morepersonlabel =Label::create("多人游戏","",20);
    ControlButton *morepersongamebtn =ControlButton::create(morepersonlabel,btnNormals);//创建controlbutton
    morepersongamebtn->setBackgroundSpriteForState(btnPresss, Control::State::SELECTED);//singlebutton按下效果图片
    morepersongamebtn->setPosition(visibleSize.width-200,visibleSize.height-400);
    morepersongamebtn->setPreferredSize(Size(222,50));
    morepersongamebtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);  //按钮回调
    morepersongamebtn->setTag(10002);//设置tag
    addChild(morepersongamebtn);
    //退出游戏按钮
    Scale9Sprite *btnNormalss =Scale9Sprite::create("normal_menu.png");
    Scale9Sprite *btnPressss =Scale9Sprite::create("press_menu.png");
    Label *quitegamelabel =Label::create("退出游戏","",20);
    ControlButton *quitegamebtn =ControlButton::create(quitegamelabel,btnNormalss);//创建controlbutton
    quitegamebtn->setBackgroundSpriteForState(btnPressss, Control::State::SELECTED);//singlebutton按下效果图片
    quitegamebtn->setPosition(visibleSize.width-200,visibleSize.height-600);
    quitegamebtn->setPreferredSize(Size(222,50));
    quitegamebtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);  //按钮回调
    quitegamebtn->setTag(10003);//设置tag
    addChild(quitegamebtn);
//设置声音开关
    Scale9Sprite *btnNormalmusic =Scale9Sprite::create("normal_menu.png");
    Scale9Sprite *btnPressmusic =Scale9Sprite::create("press_menu.png");
    bool music_on =UserDefault::getInstance()->getBoolForKey("music_on",true);
    if (music_on) {
        setmusic =Label::create("声音开","",20);
    }else{
    
        setmusic =Label::create("声音关","",20);
    }
    ControlButton *musicbtn =ControlButton::create(setmusic,btnNormalmusic);//创建controlbutton
    musicbtn->setBackgroundSpriteForState(btnPressmusic, Control::State::SELECTED);//singlebutton按下效果图片
    musicbtn->setPosition(visibleSize.width-200,visibleSize.height-500);
    musicbtn->setPreferredSize(Size(222,50));
    musicbtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown),Control::EventType::TOUCH_DOWN);  //按钮回调
    musicbtn->setTag(10004);//设置tag
    addChild(musicbtn);

}
void MenuScene::menuTouchDown(Ref *pSender, Control::EventType event)
{
    ControlButton *button =(ControlButton*)pSender;
    int tag =button->getTag();
    switch (tag) {
        case 10001:
        {
            Director::getInstance()->pushScene(MapChooseScene::createScene());
            break;
        }
        case 10002:
        {
            break;
        }
        case 10003:
        {
            break;
        }
         
        case 10004:
        {
            bool music_on =UserDefault::getInstance()->getBoolForKey("music_on",true);
            if (music_on) {
                UserDefault::getInstance()->setBoolForKey("music_on", false);
                button->setTitleForState("声音关", Control::State::NORMAL);
            }else{
                UserDefault::getInstance()->setBoolForKey("music_on", true);
                button->setTitleForState("声音开", Control::State::NORMAL);
            
            }
            break;
        }
        default:
            break;
    }



}