#pragma once
#include "core/scene.h"

class HUDButton;
class HUDText;
class UIMouse;
class SceneTitle : public Scene
{
protected:
    SDL_FColor boundary_color_ = { 0.5, 0.5, 0.5, 1 };
    float color_timer_ = 0;

    HUDButton* button_start_ = nullptr;
    HUDButton* button_credits_ = nullptr;
    HUDButton* button_quit_ = nullptr;
    HUDText* credits_text_ = nullptr;
    UIMouse* ui_mouse_ = nullptr;

public:
    void init() override;
    bool handleEvents(SDL_Event& event) override;
    void update(float dt) override;
    void render() override;
    void clean() override;

    virtual void loadData(const std::string& file_path) override;

private:
    void renderBackground();
    void updateColor();
    void checkButtonQuit();
    void checkButtonStart();
    void checkButtonCredits();
};