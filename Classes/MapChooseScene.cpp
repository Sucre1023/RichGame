//
//  MapChooseScene.cpp
//  RichGame
//
//  Created by Sucre on 14/12/22.
//
//

#include "MapChooseScene.h"
#include "SeaScene.h"
Scene *MapChooseScene::createScene()
{
    auto scene =Scene::create();
    auto layer =MapChooseScene::create();
    scene->addChild(layer);
    return scene;


}
bool MapChooseScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize =Director::getInstance()->getVisibleSize();
    //添加背景
    Sprite *bg =Sprite::create("stage_background2.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    currentpage =1;
    addChild(bg);
    addscrollview();
    //添加触摸监听
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    auto listener =EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//不往下传递触摸，吞噬触摸
    listener->onTouchBegan =CC_CALLBACK_2(MapChooseScene::onTouchBegan, this);
    listener->onTouchEnded =CC_CALLBACK_2(MapChooseScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
//创建3个关卡图片sprite，并添加到Layer类容器spritesContainer对象中，水平排列显示
void MapChooseScene::addscrollview()
{
    Point center =Point(visibleSize.width/2,visibleSize.height/2);
    mapcontainer =Layer::create();
  //创建3张地图
    Sprite *beach =Sprite::create("beach_item.png");
    Sprite *sea =Sprite::create("sea_item.png");
    Sprite *moon =Sprite::create("moon_item.png");
    beach->setScale(1.5);
    sea->setScale(1.5);
    moon->setScale(1.5);
    beach->setPosition(visibleSize.width/2,visibleSize.height/2);
    sea->setPosition(visibleSize.width *1.5,visibleSize.height/2);
    moon->setPosition(visibleSize.width*2.5,visibleSize.height/2);
    mapcontainer->addChild(beach);
    mapcontainer->addChild(sea);
    mapcontainer->addChild(moon);
    
    //设置存放map的容器
    mapcontainer->setPosition(Point::ZERO);
    mapcontainer->setContentSize(Size(visibleSize.width *3,visibleSize.height));
   //scrollview创建设置
    scrollview =ScrollView::create();
    scrollview->setContainer(mapcontainer);//设置容器
    scrollview->setDirection(ScrollView::Direction::HORIZONTAL);//水平显示
    scrollview->setTouchEnabled(true);
    scrollview->setPosition(Point::ZERO);
    scrollview->setViewSize(visibleSize);//每个关卡图片显示的大小
    scrollview->setContentOffset(Point::ZERO,true);
    scrollview->setContentSize(Size(visibleSize.width * 3, visibleSize.height));//scrollview 大小同spritesContainer相同
    scrollview->setDelegate(this);
    scrollview->setBounceable(false);
    addChild(scrollview);
    
    
}
bool MapChooseScene::onTouchBegan(Touch*touch, Event*event)
{
    beginingpoint =Director::getInstance()->convertToGL(touch->getLocationInView());
    return true;

}
void MapChooseScene::onTouchEnded(Touch *touch, Event *event)
{
    Point end =Director::getInstance()->convertToGL(touch->getLocationInView());
    float distance =end.x -beginingpoint.x;
    if (fabs(distance) > 50 ) {
    
        adjustscrollview(distance);
    }else{
        if (currentpage ==2) {
            auto scene =TransitionFade::create(2, SeaScene::createScene());
            Director::getInstance()->pushScene(scene);
        }
    
    }

}

void MapChooseScene::adjustscrollview(float t)
{
    if (t<0)
    {
        currentpage ++;
    }else
    {
        currentpage --;
    }
    
    if (currentpage <1)
    {
        currentpage = 1;
    }
    
    if(currentpage > 3)
    {
        currentpage = 3;
    }
    
    Point adjustPos = Point(-visibleSize.width * (currentpage-1), 0);
    scrollview->setContentOffset(adjustPos, true);

}