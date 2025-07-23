#pragma once

class AnimationSystem
{
    public:
        static AnimationSystem& get();

        void mainloop();
};