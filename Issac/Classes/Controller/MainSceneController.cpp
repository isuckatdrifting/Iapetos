#include "MainSceneController.h"
#include "Scene/MainScene.h"
#include "RoomSceneController.h"

USING_NS_CC;
using namespace std;

Scene * MainSceneController::createScene()
{
    return create();
}

bool MainSceneController::init()
{
    if (!Scene::init())
    {
        return false;
    }


    auto l = Label::createWithTTF("Controlled", "fonts/simhei.ttf", 30);
    l->setPosition(640, 600);
    addChild(l);

    scene_ = MainScene::create();
    scene_->set_event_listener(this);
    addChild(scene_);

    return true;
}

void MainSceneController::on_touch_began(Touch* touch, Event* event)
{
    cocos2d::log("main_scene_on_touch");
}

void MainSceneController::on_mouse_down(Event *event)
{
    cocos2d::log("main_scene_on_click");
    //TODO 程序失焦自动暂停
    //TODO 用AOP方式管理Scene和Service
    //auto room = RoomSceneController::createScene();
    //Director::getInstance()->pushScene(room);
}

int MainSceneController::check_key(EventKeyboard::KeyCode keyCode)
{
    //TODO 上下切换目录，回车确认
    int shift = 0;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        shift = -1;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        shift = 1;
        break;
    case EventKeyboard::KeyCode::KEY_ENTER:
            shift = 0;
            if(scene_->model.menun == 0){
                auto room = RoomSceneController::createScene();
                TransitionScene* tx = TransitionFade::create(0.7, room);
                Director::getInstance()->pushScene(tx);
            }
            break;
    default: break;
    }
    return shift;
}

void MainSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    scene_->model.shiftMenu(check_key(keyCode));//MainSceneModel( check_key(keyCode) )
}

void MainSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);

//    if (key_map_.empty())
//    {
//        scene_->set_model(MainSceneModel( 0 ));
//    }
//    else
//    {
//        keyCode = key_map_.begin()->first;
//        scene_->set_model(MainSceneModel( check_key(keyCode) ));
//    }

    
}