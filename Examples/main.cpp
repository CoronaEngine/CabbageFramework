#include <filesystem>
#include <iostream>
#include <thread>

#include <ECS/ECSWorld.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "CabbageFramework.h"


int main()
{
    ECSWorld::get();
    std::atomic_bool running = true;

    std::vector<CabbageFramework::Scene> scenes;

    std::thread([&]() {
        if (glfwInit() >= 0)
        {
            scenes.resize(4);
            std::vector<GLFWwindow *> windows(scenes.size());

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            for (size_t i = 0; i < scenes.size(); i++)
            {
                windows[i] = glfwCreateWindow(800, 800, "Cabbage Engine", nullptr, nullptr);
                scenes[i].setDisplaySurface(glfwGetWin32Window(windows[i]));
            }

            auto shouldClosed = [&]() {
                for (size_t i = 0; i < windows.size(); i++)
                {
                    if (glfwWindowShouldClose(windows[i]))
                    {
                        return true;
                    }
                }
                return false;
            };

            while (!shouldClosed())
            {
                glfwPollEvents();
            }
            for (size_t i = 0; i < windows.size(); i++)
            {
                glfwDestroyWindow(windows[i]);
            }
            glfwTerminate();
            running = false;
        }
    }).detach();

    while (running)
    {
        // logic to update the scenes and actors
    }

    return 0;
}