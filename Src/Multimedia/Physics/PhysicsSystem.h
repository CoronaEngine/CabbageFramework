#pragma once

class PhysicsSystem
{
  public:
    static PhysicsSystem &get();

    void mainloop();
};