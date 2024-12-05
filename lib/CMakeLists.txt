add_subdirectory(tilengine)
add_subdirectory(entt)

target_include_directories( main PRIVATE tilengine/include)
target_link_libraries  ( main PRIVATE Tilengine )
target_link_libraries  ( main PRIVATE EnTT )
