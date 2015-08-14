//
//  Monster.cpp
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#include "Monster.h"

namespace unt {
    float MONSTER_SPEED = 100.f;
    int Monster::TAG = 2;
    
    bool Monster::init(const cocos2d::Color4F &color, Vec2 dir)
    {
        if (!Node::init())
            return false;
        
        auto *drawNode = DrawNode::create();
        drawNode->drawSolidCircle(Vec2::ZERO, 7.f, 2 * M_PI, 32, 1, 1, color);
        // draw eyes
        drawNode->drawSolidCircle(Vec2(4.f, 2.5f), 1.5f, 2 * M_PI, 32, 1, 1, Color4F::BLACK);
        drawNode->drawSolidCircle(Vec2(4.f, -2.5f), 1.5f, 2 * M_PI, 32, 1, 1, Color4F::BLACK);
        addChild(drawNode);
        
        velocity = dir.getNormalized() * MONSTER_SPEED;
        this->setRotation(-CC_RADIANS_TO_DEGREES(dir.getAngle()));
        
        this->scheduleUpdate();
        return true;
    }
    
    void Monster::update(float dt)
    {
        this->setPosition(this->getPosition() + velocity * dt);
    }
    
    Monster* Monster::create(const cocos2d::Color4F &color, Vec2 dir)
    {
        Monster *monster = new Monster;
        monster->init(color, dir);
        monster->autorelease();
        return monster;
    }
}