#pragma once
#include <cassert>
#include <string>

#include "raytmx.h"

namespace Tilemap {
    [[nodiscard]] inline TmxLayer GetLayerFromMap(const TmxMap &map, const std::string &layer_name)
    {
        for (unsigned int i = 0; i < map.layersLength; ++i) {
            TmxLayer layer = map.layers[i];
            if (layer_name == layer.name)
                return layer;
        }
        return {};
    }

    [[nodiscard]] inline TmxObjectGroup GetObjectGroup(const TmxMap &map, const std::string &layer_name)
    {
        for (unsigned int i = 0; i < map.layersLength; ++i) {
            TmxLayer layer = map.layers[i];
            if (layer_name == layer.name && layer.type == LAYER_TYPE_OBJECT_GROUP)
                return layer.exact.objectGroup;
        }
        return {};
    }
    
    [[nodiscard]] inline TmxTileLayer GetTileLayer(const TmxMap &map, const std::string &layer_name)
    {
        for (unsigned int i = 0; i < map.layersLength; ++i) {
            TmxLayer layer = map.layers[i];
            if (layer_name == layer.name && layer.type == LAYER_TYPE_TILE_LAYER)
                return layer.exact.tileLayer;
        }
        return {};
    }
    
    [[nodiscard]] inline TmxLayer GetLayer(const TmxMap &map, const std::string &layer_name)
    {
        for (unsigned int i = 0; i < map.layersLength; ++i) {
            TmxLayer layer = map.layers[i];
            if (layer_name == layer.name)
                return layer;
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

    inline void UpdateGroupPosition(const TmxObjectGroup &object_group)
    {
        for (unsigned int i = 0; i < object_group.objectsLength; ++i) {
            ++object_group.objects[i].y;
        }
    }

    [[nodiscard]] inline Vector2 GetPlayerSpawnPosition(const TmxMap &map)
    {
        TmxObjectGroup group  = GetObjectGroup(map, "player");
        TmxObject      player = GetObjectFromGroup(group, "player");
        return {static_cast<float>(player.x), static_cast<float>(player.y)};
    }

    [[nodiscard]] inline bool GetPropertyFromObject(const TmxObject &object, const std::string &name)
    {
        for (unsigned int i = 0; i < object.propertiesLength; i++) {
            const TmxProperty property = object.properties[i];
            if (property.name == name && property.type == PROPERTY_TYPE_BOOL)
                return property.boolValue;
        }
        return {};
    }
}
