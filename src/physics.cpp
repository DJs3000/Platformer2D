#include "physics.hpp"
#include "raytmx.h"
#include "tilemap.hpp"

#include <cstdint>

namespace 
{
    [[nodiscard]] std::vector<Physics::Body> CreateStaticBodies(const TmxMap &map, const b2WorldId world);
    [[nodiscard]] std::vector<Physics::Body> CreateDynamicBodies(const TmxMap &map, const b2WorldId world);
}

std::vector<Physics::Body> Physics::InitObjects(const TmxMap &map, const TmxObjectGroup &object_group, b2WorldId world)
{
    std::vector<Body> bodies = {};
    bodies.reserve(object_group.objectsLength);
    for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
        const bool is_collision_enabled = Tilemap::GetPropertyFromObject(object_group.objects[i], "collision");
        if (is_collision_enabled == true) {
            const float width       = static_cast<float>(object_group.objects[i].width);
            const float height      = static_cast<float>(object_group.objects[i].height);
            const b2Vec2 box_extent = {0.5f * width, 0.5f * height};
            
            b2Polygon box_polygon = b2MakeBox(box_extent.x, box_extent.y);

            b2BodyDef body_def = b2DefaultBodyDef();
            body_def.position  = {
                .x = static_cast<float>(object_group.objects[i].x + box_extent.x),
                .y = static_cast<float>(object_group.objects[i].y - box_extent.y),
            };

            const bool is_static = Tilemap::GetPropertyFromObject(object_group.objects[i], "static");
            if (is_static == false)
                body_def.type = b2_dynamicBody;

            const b2BodyId body_id = b2CreateBody(world, &body_def); 
            b2ShapeDef shape_def   = b2DefaultShapeDef();

            b2CreatePolygonShape(body_id, &shape_def, &box_polygon);
            bodies.emplace_back(Body{body_id, box_extent});  
        }
    }
    auto f = CreateStaticBodies(map, world);
    return bodies;
}

void Physics::Update(TmxMap &map, const ObjectsTable &table)
{
    for (const auto &[layer_name, bodies] : table) {
        TmxObjectGroup object_group = Tilemap::GetObjectGroup(map, layer_name);
        for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
            const b2Vec2 position = b2Body_GetWorldPoint(bodies[i].id, {-bodies[i].extent.x, -bodies[i].extent.y});
            b2Rot rotation        = b2Body_GetRotation(bodies[i].id);
            float radians         = b2Rot_GetAngle(rotation);

            object_group.objects[i].x           = position.x;
            object_group.objects[i].y           = position.y;
            object_group.objects[i].rotation    = RAD2DEG * radians;
        }
    }
}

void Physics::Update(const std::vector<Body> &bodies, TmxObjectGroup &object_group)
{
    for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
	    const b2Vec2 position = b2Body_GetWorldPoint(bodies[i].id, {-bodies[i].extent.x, -bodies[i].extent.y});
        b2Rot rotation        = b2Body_GetRotation(bodies[i].id);
        float radians         = b2Rot_GetAngle(rotation);

        object_group.objects[i].x           = position.x;
        object_group.objects[i].y           = position.y;
        object_group.objects[i].rotation    = RAD2DEG * radians;
    }
}

Physics::ObjectsTable Physics::CreatePhysicsBodies(const TmxMap &map, const b2WorldId world)
{
    ObjectsTable table = {};
    table.insert({"static_bodies", CreateStaticBodies(map, world)});
    table.insert({"dynamic_bodies", CreateDynamicBodies(map, world)});
    return table;
}

//
//std::vector<Physics::Body> Physics::UpdatePhysicsBodiesFromTmxMap(const TmxMap &map, const b2WorldId world)
//{
//    return {};
//}

namespace 
{
    std::vector<Physics::Body> CreateStaticBodies(const TmxMap &map, const b2WorldId world)
    {
        std::vector<Physics::Body> bodies       = {};
        TmxObjectGroup             object_group = Tilemap::GetObjectGroup(map, "static_bodies");
        
        bodies.reserve(object_group.objectsLength);
        for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
            const bool is_collision_enabled = Tilemap::GetPropertyFromObject(object_group.objects[i], "collision");
            if (is_collision_enabled == true) {
                const float width       = static_cast<float>(object_group.objects[i].width);
                const float height      = static_cast<float>(object_group.objects[i].height);
                const b2Vec2 box_extent = {0.5f * width, 0.5f * height};
                
                b2Polygon box_polygon = b2MakeBox(box_extent.x, box_extent.y);

                b2BodyDef body_def = b2DefaultBodyDef();
                body_def.position  = {
                    .x = static_cast<float>(object_group.objects[i].x + box_extent.x),
                    .y = static_cast<float>(object_group.objects[i].y + box_extent.y),
                };

                const b2BodyId body_id = b2CreateBody(world, &body_def); 
                b2ShapeDef shape_def   = b2DefaultShapeDef();

                b2CreatePolygonShape(body_id, &shape_def, &box_polygon);
                bodies.emplace_back(Physics::Body{body_id, box_extent});  
            }
        }
        return bodies;
    }

    std::vector<Physics::Body> CreateDynamicBodies(const TmxMap &map, const b2WorldId world)
    {
        std::vector<Physics::Body> bodies       = {};
        TmxObjectGroup             object_group = Tilemap::GetObjectGroup(map, "dynamic_bodies");

        bodies.reserve(object_group.objectsLength);
        for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
            const bool is_collision_enabled = Tilemap::GetPropertyFromObject(object_group.objects[i], "collision");
            if (is_collision_enabled == true) {
                const float width       = static_cast<float>(object_group.objects[i].width);
                const float height      = static_cast<float>(object_group.objects[i].height);
                const b2Vec2 box_extent = {0.5f * width, 0.5f * height};
                
                b2Polygon box_polygon = b2MakeBox(box_extent.x, box_extent.y);

                b2BodyDef body_def = b2DefaultBodyDef();
                body_def.position  = {
                    .x = static_cast<float>(object_group.objects[i].x + box_extent.x),
                    .y = static_cast<float>(object_group.objects[i].y - box_extent.y),
                };
                body_def.type = b2_dynamicBody;

                const b2BodyId body_id = b2CreateBody(world, &body_def); 
                b2ShapeDef shape_def   = b2DefaultShapeDef();

                b2CreatePolygonShape(body_id, &shape_def, &box_polygon);
                bodies.emplace_back(Physics::Body{body_id, box_extent});  
            }
        }
        return bodies;
    }
}
