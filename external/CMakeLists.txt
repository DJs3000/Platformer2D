set( BUILD_SHARED_LIBS              OFF CACHE BOOL "" FORCE )
set( BUILD_EXAMPLES                 OFF CACHE BOOL "" FORCE )
set( BUILD_GAMES                    OFF CACHE BOOL "" FORCE )
set( RAYLIB_ASEPRITE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory( raylib )
add_subdirectory( raylib-aseprite )
add_subdirectory( box2d-3.1.0 )

target_link_libraries( main PRIVATE raylib)
target_link_libraries( main PRIVATE raylib_aseprite)
target_link_libraries( main PRIVATE box2d)
