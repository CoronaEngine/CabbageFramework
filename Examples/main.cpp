#include <filesystem>
#include <iostream>
#include <thread>

#include <entt/entt.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "CabbageEngine.h"

CabbageEngine::Scene::Camera *globalCamera = nullptr;
GLFWwindow *globalWindow = nullptr;

// 摄像头控制参数
float movementSpeed = 2.5f;     // 移动速度
float mouseSensitivity = 0.1f;  // 鼠标灵敏度
float yaw = -90.0f;             // 偏航角
float pitch = 0.0f;             // 俯仰角
bool firstMouse = true;         // 是否是第一次鼠标输入
float lastX = 400, lastY = 400; // 上次鼠标位置

void updateCameraFront()
{
    ktm::fvec3 front;
    front.x = cos(ktm::radians(yaw)) * cos(ktm::radians(pitch));
    front.y = sin(ktm::radians(pitch));
    front.z = sin(ktm::radians(yaw)) * cos(ktm::radians(pitch));
    globalCamera->forward = ktm::normalize(front);
}

// 处理键盘输入
void processInput(float deltaTime)
{
    float cameraSpeed = movementSpeed * deltaTime;

    if (glfwGetKey(globalWindow, GLFW_KEY_W) == GLFW_PRESS)
        globalCamera->pos += cameraSpeed * globalCamera->forward;
    if (glfwGetKey(globalWindow, GLFW_KEY_S) == GLFW_PRESS)
        globalCamera->pos -= cameraSpeed * globalCamera->forward;
    if (glfwGetKey(globalWindow, GLFW_KEY_A) == GLFW_PRESS)
        globalCamera->pos -= ktm::normalize(ktm::cross(globalCamera->forward, globalCamera->worldUp)) * cameraSpeed;
    if (glfwGetKey(globalWindow, GLFW_KEY_D) == GLFW_PRESS)
        globalCamera->pos += ktm::normalize(ktm::cross(globalCamera->forward, globalCamera->worldUp)) * cameraSpeed;
    if (glfwGetKey(globalWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        globalCamera->pos += cameraSpeed * globalCamera->worldUp;
    if (glfwGetKey(globalWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        globalCamera->pos -= cameraSpeed * globalCamera->worldUp;
}

// 鼠标回调函数
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从下到上的
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 限制俯仰角，防止翻转
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // 更新摄像头前方向量
    updateCameraFront();
}

int main()
{
    entt::registry registry;
    auto entiry = registry.create();

    std::vector<CabbageEngine::Scene> scenes(2);

    std::filesystem::path resourcePath = std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path() / "Examples//TestCase//AddModelTest//armadillo.obj ";
    std::filesystem::path resourcePath2 = std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path() / "Examples//TestCase//vampire//dancing_vampire.dae ";

    CabbageEngine::Actor actor1(scenes[0], resourcePath.string());
    CabbageEngine::Actor actor2(scenes[0], resourcePath.string());
    CabbageEngine::Actor actor3(scenes[1], resourcePath2.string());
    std::thread([&]() {
        if (glfwInit() >= 0)
        {
            std::vector<GLFWwindow *> windows(scenes.size());

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            for (size_t i = 0; i < scenes.size(); i++)
            {
                windows[i] = glfwCreateWindow(800, 800, "Cabbage Engine", nullptr, nullptr);
                scenes[i].setDisplaySurface(glfwGetWin32Window(windows[i]));
            }

            // 注册回调函数
            globalWindow = windows[0];
            globalCamera = &scenes[0].getCamera();
            glfwSetCursorPosCallback(globalWindow, mouse_callback);

            // 隐藏光标并捕获它
            glfwSetInputMode(globalWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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

            // 计时变量，用于平滑移动
            auto lastTime = std::chrono::high_resolution_clock::now();

            while (!shouldClosed())
            {
                // 计算帧时间
                auto currentTime = std::chrono::high_resolution_clock::now();
                float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
                lastTime = currentTime;

                // 处理输入
                processInput(deltaTime);

                glfwPollEvents();
            }
            for (size_t i = 0; i < windows.size(); i++)
            {
                glfwDestroyWindow(windows[i]);
            }
            glfwTerminate();
        }
    }).detach();

    while (true)
    {
        scenes[0].setSunDirection(ktm::fvec3(0.5f, 1.0f, 0.0f));
        CabbageEngine::update();
    }

    return 0;
}