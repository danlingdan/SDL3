#include "actor.h"
#include "scene.h"
#include "../raw/stats.h"
#include "../affiliate/affiliate_bar.h"

void Actor::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    // 根据碰撞盒大小来限制移动区域
    glm::vec2 margin_top_left = glm::vec2(0);
    glm::vec2 margin_bottom_right = glm::vec2(0);
    if (collider_) {
        margin_top_left = collider_->getOffset();
        margin_bottom_right = collider_->getOffset() + collider_->getSize();
    }
    position_ = glm::clamp(position_, glm::vec2(0) - margin_top_left, game_.getCurrentScene()->getWorldSize() - margin_bottom_right);
}

void Actor::update(float dt)
{
    ObjectWorld::update(dt);
    updateHealthBar();
}


void Actor::takeDamage(float damage)
{
    if (!stats_) return;
    stats_->takeDamage(damage);
}

bool Actor::getIsAlive() const
{
    if (!stats_) return true;
    return stats_->getIsAlive();
}

void Actor::updateHealthBar()
{
    if (!stats_ || !health_bar_) return;
    health_bar_->setPercentage(stats_->getHealth() / stats_->getMaxHealth());
}