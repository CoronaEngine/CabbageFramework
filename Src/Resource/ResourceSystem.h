#pragma once

#include <assimp/Importer.hpp>
#include <concurrencpp/concurrencpp.h>

class ResourceSystem
{
  public:
    static ResourceSystem &get();

  private:
    Assimp::Importer importer;

    std::shared_ptr<std::thread> mainloopThread;

  public:
    const aiScene *loadScene(const std::string &path);
    const unsigned char *loadTexture(const std::string &path);
    const aiScene *loadModel(const std::string &path);
    const aiScene *loadAnimation(const std::string &path);

    void start();
    void mainloop();
};