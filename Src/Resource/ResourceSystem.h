#pragma once

#include <memory>
#include <thread>

#include <assimp/Importer.hpp>

class ResourceSystem
{
  private:
    ResourceSystem() = default;

  public:
    ~ResourceSystem();

  public:
    static ResourceSystem &get();

  private:
    Assimp::Importer importer;

    std::atomic_bool running{true};
    std::shared_ptr<std::thread> mainloopThread;

  public:
    const aiScene *loadScene(const std::string &path);
    const unsigned char *loadTexture(const std::string &path);
    const aiScene *loadModel(const std::string &path);
    const aiScene *loadAnimation(const std::string &path);

    void start();
    void stop();
    void mainloop();
};