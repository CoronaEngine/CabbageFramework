#pragma once

class AudioSystem
{
  public:
    static AudioSystem &get(); // Singleton

    void mainloop();
};