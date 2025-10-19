#include "player.h"
#include "core/scene.h"

void Player::init()
{
    Actor::init();
    max_speed_ = 500.0f;
}

void Player::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Player::update(float dt)
{
    Actor::update(dt);
    keyboardControl();
    velocity_ *= 0.9f;
    move(dt);
    syncCamera();
}

void Player::render()
{
    Actor::render();
    game_.drawBoundary(render_position_, render_position_ + glm::vec2(20.0f), 5.0f, { 1.0, 0.0, 0.0, 1.0 });
}

void Player::clean()
{
    Actor::clean();
}

void Player::keyboardControl()
{
    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W]) {
        velocity_.y = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        velocity_.y = max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        velocity_.x = -max_speed_;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        velocity_.x = max_speed_;
    }
}

void Player::move(float dt)
{
    setPosition(position_ + velocity_ * dt);
    position_ = glm::clamp(position_, glm::vec2(0), game_.getCurrentScene()->getWorldSize());
}

void Player::syncCamera()
{
    game_.getCurrentScene()->setCameraPosition(position_ - game_.getScreenSize() / 2.0f);
}
