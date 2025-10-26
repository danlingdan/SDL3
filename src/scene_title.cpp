#include "scene_title.h"
#include "screen/hud_text.h"
#include <cmath>
#include "screen/hud_button.h"
#include "scene_main.h"
#include <fstream>

void SceneTitle::init()
{
    Scene::init();
    loadData("assets/score.dat");
    SDL_ShowCursor();
    //game_.playMusic("assets/bgm/Spooky music.mp3");
    auto size = glm::vec2(game_.getScreenSize().x / 2.0f, game_.getScreenSize().y / 3.0f);
    HUDText::addHUDTextChild(this, "幽 灵 逃 生", game_.getScreenSize() / 2.0f - glm::vec2(0, 100), size, "assets/font/VonwaonBitmap-16px.ttf", 64);
    auto score_text = "最高分: " + std::to_string(game_.getHighScore());
    HUDText::addHUDTextChild(this, score_text, game_.getScreenSize() / 2.0f + glm::vec2(0, 100), glm::vec2(200, 50), "assets/font/VonwaonBitmap-16px.ttf", 32);
    button_start_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(-200, 200), "assets/UI/A_Start1.png", "assets/UI/A_Start2.png", "assets/UI/A_Start3.png", 2.0f);
    button_credits_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(0, 200), "assets/UI/A_Credits1.png", "assets/UI/A_Credits2.png", "assets/UI/A_Credits3.png", 2.0f);
    button_quit_ = HUDButton::addHUDButtonChild(this, game_.getScreenSize() / 2.0f + glm::vec2(200, 200), "assets/UI/A_Quit1.png", "assets/UI/A_Quit2.png", "assets/UI/A_Quit3.png", 2.0f);

    auto text = game_.loadTextFile("assets/credits.txt");
    credits_text_ = HUDText::addHUDTextChild(this, text, game_.getScreenSize() / 2.0f, glm::vec2(500, 500), "assets/font/VonwaonBitmap-16px.ttf", 16);
    credits_text_->setBgSizeByText();
    credits_text_->setActive(false);
}

bool SceneTitle::handleEvents(SDL_Event& event)
{
    if (credits_text_->getActive()) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            credits_text_->setActive(false);
            return true;
        }

    }
    if (Scene::handleEvents(event)) return true;
    return false;
}

void SceneTitle::update(float dt)
{
    color_timer_ += dt;
    updateColor();
    if (credits_text_->getActive()) {
        return;
    }
    Scene::update(dt);
    checkButtonQuit();
    checkButtonStart();
    checkButtonCredits();
}

void SceneTitle::render()
{
    renderBackground();
    Scene::render();
}

void SceneTitle::clean()
{
    Scene::clean();
}

void SceneTitle::loadData(const std::string& file_path)
{
    int score = 0;
    std::ifstream file(file_path, std::ios::binary);    // 以二进制形式保存
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&score), sizeof(score));
        file.close();
    }
    game_.setHighScore(score);
}

void SceneTitle::renderBackground()
{
    game_.drawBoundary(glm::vec2(30.0f), game_.getScreenSize() - glm::vec2(30.0f), 10.0f, boundary_color_);
}

void SceneTitle::updateColor()
{
    boundary_color_.r = 0.5f + 0.5f * sinf(color_timer_ * 0.9f);
    boundary_color_.g = 0.5f + 0.5f * sinf(color_timer_ * 0.8f);
    boundary_color_.b = 0.5f + 0.5f * sinf(color_timer_ * 0.7f);
}

void SceneTitle::checkButtonQuit()
{
    if (button_quit_->getIsTrigger()) {
        game_.quit();
    }
}

void SceneTitle::checkButtonStart()
{
    if (button_start_->getIsTrigger()) {
        auto scene = new SceneMain();
        game_.safeChangeScene(scene);
    }
}

void SceneTitle::checkButtonCredits()
{
    if (button_credits_->getIsTrigger()) {
        credits_text_->setActive(true);
    }
}
