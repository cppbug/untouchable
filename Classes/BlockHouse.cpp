//
//  BlockHouse.cpp
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#include "BlockHouse.h"
#include "Bullet.h"
#include "GamePlayScene.h"

namespace unt {
    float FIRE_DELAY = .5f;
    
    bool BlockHouse::init()
    {
        if (!Node::init())
            return false;
        
        this->firePoint = Vec2(15.f, 0.f);
        
        DrawNode *drawNode = DrawNode::create();
        addChild(drawNode);
        
        drawNode->drawSolidCircle(Vec2::ZERO, 10.f, 2 * M_PI, 64, 1, 1, Color4F::BLUE);
        drawNode->drawRect(Vec2(0, -3.f), Vec2(firePoint.x, 3.f), Color4F::BLUE);
        
        setFireable(false);
        fireTime = 0;
        
        this->scheduleUpdate();
        return true;
    }
    
    void BlockHouse::update(float dt)
    {
        fireTime -= dt;
        if (fireTime <= 0)
        {
            fireTime = FIRE_DELAY;
            if (getFireable())
            {
                this->fireBullet();
            }
        }
    }
    
    void BlockHouse::setTarget(cocos2d::Vec2 target)
    {
        this->target = target;
        float angle = target.getAngle();
        angle = -CC_RADIANS_TO_DEGREES(angle);
        this->setRotation(angle);
    }
    
    void BlockHouse::fireBullet()
    {
        float rotation = getRotation();
        float angleInRad = -CC_DEGREES_TO_RADIANS(rotation);
        Vec2 realFirePoint = firePoint.rotateByAngle(Vec2::ZERO, angleInRad);
        Vec2 dir = target - realFirePoint;
        
        Bullet *bullet = Bullet::createWithDirection(dir);
        bullet->setPosition(realFirePoint);
        
        static_cast<GamePlayScene *>(getParent())->addBullet(bullet);
    }
}