//
// Bug-624
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=624
//

#include "Bug-624.h"

////////////////////////////////////////////////////////
//
// Bug624Layer
//
////////////////////////////////////////////////////////
Bug624Layer::~Bug624Layer()
{
    Device::setAccelerometerEnabled(false);
}

bool Bug624Layer::init()
{
    if(BugsTestBaseLayer::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto label = Label::createWithFont("Layer1", "fonts/Marker Felt.ttf", 36.0f);

        label->setPosition(Point(size.width/2, size.height/2));
        addChild(label);
        
        Device::setAccelerometerEnabled(true);
        auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Bug624Layer::onAcceleration,  this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        schedule(schedule_selector(Bug624Layer::switchLayer), 5.0f);

        return true;
    }
    
    return false;
}

void Bug624Layer::switchLayer(float dt)
{
    unschedule(schedule_selector(Bug624Layer::switchLayer));

    auto scene = Scene::create();    
    scene->addChild(Bug624Layer2::create(), 0);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene, Color3B::WHITE));
}

void Bug624Layer::onAcceleration(Acceleration* acc, Event* event)
{    
    log("Layer1 accel");
}

////////////////////////////////////////////////////////
//
// Bug624Layer2
//
////////////////////////////////////////////////////////
Bug624Layer2::~Bug624Layer2()
{
    Device::setAccelerometerEnabled(false);
}

bool Bug624Layer2::init()
{
    if(BugsTestBaseLayer::init())
    {
        auto size = Director::getInstance()->getWinSize();
        auto label = Label::createWithFont("Layer2", "fonts/Marker Felt.ttf", 36.0f);

        label->setPosition(Point(size.width/2, size.height/2));
        addChild(label);
        
        Device::setAccelerometerEnabled(true);
        auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Bug624Layer2::onAcceleration, this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        schedule(schedule_selector(Bug624Layer2::switchLayer), 5.0f);

        return true;
    }

    return false;
}

void Bug624Layer2::switchLayer(float dt)
{
    unschedule(schedule_selector(Bug624Layer::switchLayer));

    auto scene = Scene::create();    
    scene->addChild(Bug624Layer::create(), 0);
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, scene, Color3B::RED));
}

void Bug624Layer2::onAcceleration(Acceleration* acc, Event* event)
{    
    log("Layer2 accel");
}
