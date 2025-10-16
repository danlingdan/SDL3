#include "game.h"
#include "../scene_main.h"

void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16); // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4); // 设置音效音量

    // SDL3_TTF初始化
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }
    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "创建窗口或渲染器失败: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 计算帧延迟（纳秒级）
    frame_delay_ = 1000000000 / FPS_;

    // 创建场景
    current_scene_ = new SceneMain();
    current_scene_->init();
}

void Game::run()
{
    while (is_running_) {
        auto start = SDL_GetTicksNS();  // 纳秒级时间戳

        handleEvents();
        update(dt_);  // 使用计算出的dt_更新游戏状态
        render();

        auto end = SDL_GetTicksNS();

        auto elapsed = end - start;
        if (elapsed < frame_delay_) {
            SDL_DelayNS((frame_delay_ - elapsed));  // 纳秒级延迟
            dt_ = frame_delay_ / 1.0e9;  // 纳秒转换为秒
        }
        else {
            dt_ = elapsed / 1.0e9;  // 纳秒转换为秒
        }

        SDL_Log("FPS: %f", 1.0 / dt_);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            current_scene_->handleEvents(event);
        }
    }
}

void Game::update(float dt)
{
    current_scene_->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    current_scene_->render();
    SDL_RenderPresent(renderer_);
}

void Game::clean()
{
    if (current_scene_) {
        current_scene_->clean();
        delete current_scene_;
    }

    // ... 其他清理代码 ...
}