#include "CAnimation.h"
#include <SDL/SDL_timer.h>

CAnimation::CAnimation(){
    currentFrame = 0;
    MaxFrame = 0;
    FrameInc = 1;

    FrameRate = 100; //ms
    OldTime = 0;

    Oscillate = false;

}

void CAnimation::OnAnimate(){

    // when time is more than oldtime+FrameRate we update frame else we dont
    if( OldTime + FrameRate > SDL_GetTicks()){
        return;
    }

    OldTime = SDL_GetTicks();


    currentFrame += FrameInc;

    if(Oscillate){
        if(FrameInc > 0){
            if(currentFrame >= MaxFrame - 1 ){
                FrameInc = -FrameInc;                
            }
        }

        else if( currentFrame <= 0){
            FrameInc = -FrameInc;
        }
    }
    
    else if(currentFrame >= MaxFrame )
        currentFrame = 0;

}

void CAnimation::SetFrameRate(int Rate){
    FrameRate = Rate;
}

void CAnimation::SetCurrentFrame(int Frame){
    if(Frame < 0  or Frame >= MaxFrame)
        return;

    currentFrame = Frame;
}

int CAnimation::GetCurrentFrame(){
    return currentFrame;
}
