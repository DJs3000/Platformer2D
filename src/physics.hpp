#pragma once
#include <box2d/box2d.h>
#include <vector>

typedef struct tmx_object_group TmxObjectGroup;

namespace Physics {
    struct Body {
	    b2BodyId id     = {};
        b2Vec2   extent = {};
    };
    
    [[nodiscard]] std::vector<Body> InitObjects(const TmxObjectGroup &object_group, const b2WorldId world);
    void Update(const std::vector<Body> &bodies, TmxObjectGroup &object_group);
}
