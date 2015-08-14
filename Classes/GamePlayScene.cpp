//
//  GamePlayScene.cpp
//  unctouchable
//
//  Created by Vinova on 8/15/15.
//
//

#include "GamePlayScene.h"
#include "BlockHouse.h"
#include "Monster.h"
#include "Bullet.h"
#include "EndGameScene.h"

namespace unt {
    float GEN_MONSTER_DELAY = 1.f;
    
    Scene* GamePlayScene::createScene()
    {
        Scene *scene = Scene::create();
        auto *layer = GamePlayScene::create();
        
        scene->addChild(layer);
        
        return scene;
    }
    
    bool GamePlayScene::init()
    {
        if (!Node::init())
            return false;
        
        auto winSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        setContentSize(winSize);
        setPosition(winSize / 2);
        
        blockHouse = BlockHouse::create();
        addChild(blockHouse);
        
        auto *touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(GamePlayScene::onTouchCancelled, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        genMonsterTimer = GEN_MONSTER_DELAY;
        
        this->scheduleUpdate();
        return true;
    }
    
    bool GamePlayScene::onTouchBegan(cocos2d::Touch *t, cocos2d::Event *e)
    {
        auto pos = this->convertToNodeSpace(t->getLocation());
        this->blockHouse->setTarget(pos);
        this->blockHouse->setFireable(true);
        return true;
    }
    
    void GamePlayScene::onTouchMoved(cocos2d::Touch *t, cocos2d::Event *e)
    {
        auto pos = this->convertToNodeSpace(t->getLocation());
        this->blockHouse->setTarget(pos);
    }
    
    void GamePlayScene::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e)
    {
        this->blockHouse->setFireable(false);
    }
    
    void GamePlayScene::onTouchCancelled(cocos2d::Touch *t, cocos2d::Event *e)
    {
        this->blockHouse->setFireable(false);
    }
    
    void GamePlayScene::update(float dt)
    {
        genMonsterTimer -= dt;
        if (genMonsterTimer <= 0)
        {
            genMonsterTimer = GEN_MONSTER_DELAY;
            
            this->generateMonster();
        }
        
        this->checkCollision();
    }
    
    void GamePlayScene::generateMonster()
    {
        static Color4F COLORS[] = {Color4F::RED, Color4F::GREEN, Color4F::MAGENTA, Color4F::YELLOW};
        
        Color4F color = COLORS[rand() % 4];
        
        auto winsize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        Vec2 ratio((rand_0_1() < 0.5)?-0.5f:0.5f, rand_0_1() - 0.5f);
        if (rand_0_1() < 0.5)
        {
            ratio = Vec2(ratio.y, ratio.x);
        }
        Vec2 pos(ratio.x * winsize.width, ratio.y * winsize.height);
        
        Vec2 dir = blockHouse->getPosition() - pos;
        
        Monster *monster = Monster::create(color, dir);
        monster->setPosition(pos);
        addChild(monster);
        
        monsters.pushBack(monster);
    }
    
    void GamePlayScene::addBullet(unt::Bullet *bullet)
    {
        addChild(bullet);
        bullets.pushBack(bullet);
    }
    
    void GamePlayScene::checkCollision()
    {
        for (int i = 0; i < bullets.size(); ++i) {
            Bullet *bullet = bullets.at(i);
            
            for (int j = 0; j < monsters.size(); ++j)
            {
                Monster *monster = monsters.at(j);
                
                if ((bullet->getPosition() - monster->getPosition()).lengthSquared() <= 100.f)
                {
                    bullet->removeFromParent();
                    bullet = nullptr;
                    monster->removeFromParent();
                    monster = nullptr;
                    monsters.erase(j);
                    break;
                }
            }
            
            if (!bullet)
            {
                bullets.erase(i);
                --i;
            }
        }
        
        for (Monster *monster : monsters)
        {
            if ((monster->getPosition() - blockHouse->getPosition()).lengthSquared() <= 100)
            {
                // lose game
                Director::getInstance()->replaceScene(EndGameScene::createScene());
            }
        }
    }
}