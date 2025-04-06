#include <raylib.h>
#include "physics.hpp"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

bool Physics::Init()
{
    InitPhysics();
    return IsPhysicsEnabled();
}

void Physics::Close()
{
    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++) {
        PhysicsBody body = GetPhysicsBody(i);
        DestroyPhysicsBody(body);
    }
    ClosePhysics();
}
