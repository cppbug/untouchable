//
//  Bullet.cpp
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#include "Bullet.h"

namespace unt {
    float BULLET_TTL = 10.f;
    float BULLET_SPEED = 300.f;
    int Bullet::TAG = 1;
    
    bool Bullet::initWithDirection(cocos2d::Vec2 dir)
    {
        if (!Node::init())
            return false;
        
        auto *drawNode = DrawNode::create();
        drawNode->drawSolidCircle(Vec2::ZERO, 2.5f, 2 * M_PI, 16, 1, 1, Color4F::BLUE);
        addChild(drawNode);
        
        ttl = BULLET_TTL;
        velocity = dir.getNormalized() * BULLET_SPEED;
        
        this->scheduleUpdate();
        return true;
    }
    
    void Bullet::update(float dt)
    {
        ttl -= dt;
        this->setPosition(this->getPosition() + velocity * dt);
        
        if (ttl <= 0)
        {
            this->removeFromParent();
        }
    }
    
    Bullet* Bullet::createWithDirection(cocos2d::Vec2 dir)
    {
        Bullet *bullet = new (std::nothrow) Bullet;
        bullet->initWithDirection(dir);
        bullet->autorelease();
        
        return bullet;
    }
}