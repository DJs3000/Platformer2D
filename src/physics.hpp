#pragma once
#include <box2d/box2d.h>
#include <vector>
#include <unordered_map>
#include <string>

typedef struct tmx_object_group TmxObjectGroup;
typedef struct tmx_map TmxMap;

namespace Physics {
    struct Body final {
	    b2BodyId id     = {};
        b2Vec2   extent = {};
    };
    
    // Each entry of map correspond to layer, i.e "static_colliders" have their own set of bodies and etc.
    using ObjectsTable = std::unordered_map<std::string, std::vector<Body>>;

    [[nodiscard]] ObjectsTable CreatePhysicsBodies(const TmxMap &map, const b2WorldId world);
    [[nodiscard]] std::vector<Body> UpdatePhysicsBodiesFromTmxMap(const TmxMap &map, const b2WorldId world);
    [[nodiscard]] std::vector<Body> InitObjects(const TmxMap &map, const TmxObjectGroup &object_group, const b2WorldId world);
    void Update(const std::vector<Body> &bodies, TmxObjectGroup &object_group);
    void Update(TmxMap &map, const ObjectsTable &table);
}
