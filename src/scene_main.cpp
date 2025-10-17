#include "scene_main.h"
#include "player.h"

void SceneMain::init()
{

	world_size_ = game_.getScreenSize() * 3.0f; // 世界大小为屏幕的3倍
    camera_position_ = world_size_ / 2.0f - game_.getScreenSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);

}

void SceneMain::handleEvents(SDL_Event& event)
{
}

void SceneMain::update(float dt)
{

    player_->update(dt);

}

void SceneMain::render()
{
    renderBackground();
    player_->render();

}

void SceneMain::clean()
{
    player_->clean();
    delete player_;
}

void SceneMain::renderBackground()
{
    auto start = -camera_position_;
    auto end = world_size_ - camera_position_;
    game_.drawGrid(start, end, 80.0f, { 0.5, 0.5, 0.5, 1.0 });
    game_.drawBoundary(start, end, 5.0f, { 1.0, 1.0, 1.0, 1.0 });
}



