#pragma once
#include "../core/object.h"

class Timer : public Object         // 创建的时候，默认为为 !active
{
protected:
    float timer_ = 0;
    float interval_ = 3.0f;
    bool time_out_ = false;
public:
    static Timer* addTimerChild(Object* parent, float interval = 3.0f);

    virtual void update(float dt) override;

    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    bool timeOut();
    float getProgress() { return timer_ / interval_; }

    // setters and getters
    float getTimer() const { return timer_; }
    void setTimer(float timer) { timer_ = timer; }
    float getInterval() const { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
};