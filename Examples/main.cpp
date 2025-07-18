#include "Components.hpp"

int main(int argc, char **argv)
{
    entt::registry registry;

    entt::entity actor1 = registry.create();
    registry.emplace<ActorHostComponent>(actor1, ActorHostComponent{});
    registry.emplace<ActorDeviceComponent>(actor1, ActorDeviceComponent{});
    registry.emplace<ActorPoseComponent>(actor1, ActorPoseComponent{});

    entt::entity actor2 = registry.create();
    registry.emplace<ActorHostComponent>(actor2, ActorHostComponent{});
    registry.emplace<ActorDeviceComponent>(actor2, ActorDeviceComponent{});
    registry.emplace<ActorPoseComponent>(actor2, ActorPoseComponent{});

    entt::entity scene1 = registry.create();
    registry.emplace<SceneHostComponent>(scene1, SceneHostComponent{});
    registry.emplace<SceneDeviceComponent>(scene1, SceneDeviceComponent{});

    entt::entity scene2 = registry.create();
    registry.emplace<SceneHostComponent>(scene2, SceneHostComponent{});
    registry.emplace<SceneDeviceComponent>(scene2, SceneDeviceComponent{});

    auto actorsView = registry.view<ActorHostComponent, ActorDeviceComponent, ActorPoseComponent>();
    auto scenesView = registry.view<SceneHostComponent, SceneDeviceComponent>();

    auto a1_actorPose = actorsView.get<ActorPoseComponent>(actor1);
    auto a2_actorHost = actorsView.get<ActorPoseComponent>(actor2);
    auto s1_scenehost = scenesView.get<SceneHostComponent>(scene1);
    auto s2_scenedevice = scenesView.get<SceneDeviceComponent>(scene2);
}