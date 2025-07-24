#include "ISystem.h"


ISystem::ISystem(const entt::entity &ownerScene) : ownerScene(ownerScene), running(false)
{

}

ISystem::~ISystem()
{
}