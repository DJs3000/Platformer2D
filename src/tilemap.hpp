#pragma once
#include <cassert>

#include "raytmx.h"

namespace Tilemap {
    [[nodiscard]] inline TmxLayer GetLayerFromMap(const TmxMap *map, const std::string &layer_name)
    {
        assert(map != nullptr);
        for (unsigned int i = 0; i < map->layersLength; ++i) {
            TmxLayer layer = map->layers[i];
            if (layer_name == layer.name)
                return layer;
        }
        return {};
    }

    [[nodiscard]] inline TmxObjectGroup GetObjectGroupFromLayer(const TmxMap *map, const std::string &layer_name)
    {
        assert(map != nullptr);
        for (unsigned int i = 0; i < map->layersLength; ++i) {
            TmxLayer layer = map->layers[i];
            if (layer_name == layer.name && layer.type == LAYER_TYPE_OBJECT_GROUP)
                return layer.exact.objectGroup;
        }
        return {};
    }

    [[nodiscard]] inline TmxObject GetObjectFromGroup(const TmxObjectGroup &object_group, const std::string &name)
    {
        for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
            TmxObject object = object_group.objects[i];
            if (name == object.name)
                return object;
        }
        return {};
    }

    [[nodiscard]] inline Vector2 GetPlayerSpawnPosition(const TmxMap *map)
    {
        assert(map != nullptr);
        TmxObjectGroup group  = GetObjectGroupFromLayer(map, "player");
        TmxObject      player = GetObjectFromGroup(group, "player");
        return {static_cast<float>(player.x), static_cast<float>(player.y)};
    }
}
