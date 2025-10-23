#include "effect.h"
#include "../core/scene.h"

Effect* Effect::addEffectChild(Object* parent, const std::string& file_path, glm::vec2 pos, float scale, ObjectWorld* next_object)
{
    auto effect = new Effect();
    effect->init();
    effect->sprite_ = SpriteAnim::addSpriteAnimChild(effect, file_path, scale);
    effect->sprite_->setLoop(false);
    effect->setPosition(pos);
    effect->setNextObject(next_object);
    if (parent) parent->addChild(effect);
    return effect;
}

void Effect::update(float dt)
{
    ObjectWorld::update(dt);
    checkFinish();
}


void Effect::checkFinish()
{
    if (sprite_->getFinish())
    {
        need_remove_ = true;
        if (next_object_) {
            game_.getCurrentScene()->safeAddChild(next_object_);
        }
    }
}
