#pragma once

class GeometrySystem
{
  public:
    static GeometrySystem &get(); // Singleton

    void mainloop();
};