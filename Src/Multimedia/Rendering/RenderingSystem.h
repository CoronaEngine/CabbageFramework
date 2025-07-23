#pragma once

class RenderingSystem
{
  public:
    static RenderingSystem &get();

    void mainloop();
};