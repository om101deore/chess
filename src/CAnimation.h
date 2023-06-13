#pragma once

#include <SDL/SDL.h>

class CAnimation{
    private:
    int currentFrame;
    int FrameInc;

    private:
    int FrameRate; // milliseconds
    long OldTime;

    public:
    int MaxFrame;
    bool Oscillate;

    public:
    CAnimation();
    void OnAnimate();

    public:
    void SetFrameRate(int Rate);
    void SetCurrentFrame(int Frame);
    int GetCurrentFrame();

};


