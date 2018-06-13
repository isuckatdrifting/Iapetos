#include "Door.h"

Door *Door::createDoor(int doorType, const string &doorStyle, const Size &winSize)
{
	Door *pRet = new (std::nothrow) Door();
	if (pRet && pRet->init(doorType, doorStyle, winSize))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Door::init(int doorType, const string &doorStyle, const Size &winSize)
{
	if (!Sprite::init())
	{
		return false;
	}
	auto phyBody = PhysicsBody::createBox(Size(64, 40), PHYSICSBODY_MATERIAL_DEFAULT);
	//静态
	phyBody->setDynamic(false);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(0.5f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//碰撞、监听筛选
	phyBody->setCategoryBitmask(0x50);	// 0101_0000(50)
	phyBody->setCollisionBitmask(0x8F);   // 1000_1111(8F)
	phyBody->setContactTestBitmask(0x09); //0000_1001(09)
	this->addComponent(phyBody);

	Texture2D *texture_door = Director::getInstance()->getTextureCache()->addImage(doorStyle);
	Sprite *door_ = Sprite::createWithTexture(texture_door, Rect(0, 0, 64, 48));
	Sprite *door_center = Sprite::createWithTexture(texture_door, Rect(64, 0, 64, 48));
	this->addChild(door_);
	this->addChild(door_center);
	this->setRotation(270 + doorType * 90);
	//设置位置
	switch (doorType)
	{
	case (0):
	{
		this->setPosition(36, winSize.height / 2);
		this->getPhysicsBody()->setPositionOffset(Vec2(-16, 0));
		break;
	}
	case (1):
	{
		this->setPosition(winSize.width / 2, winSize.height - 36);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, 16));
		break;
	}
	case (2):
	{
		this->setPosition(winSize.width - 36, winSize.height / 2);
		this->getPhysicsBody()->setPositionOffset(Vec2(16, 0));
		break;
	}
	case (3):
	{
		this->setPosition(winSize.width / 2, 36);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, -16));
		break;
	}
	}

	this->setTag(0); //门tag=0
	return true;
}