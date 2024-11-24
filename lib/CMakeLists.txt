set( PNG_SHARED          OFF CACHE BOOL "" FORCE )
set( PNG_EXECUTABLES     OFF CACHE BOOL "" FORCE )
set( PNG_BUILD_ZLIB      OFF CACHE BOOL "" FORCE )

set( ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( ZLIB_ROOT ${CMAKE_BIN_DIRECTORY}/lib/zlib-1.3.1 )
set( ZLIB_USE_STATIC_LIBS "ON")

set( SDL_SHARED  OFF CACHE BOOL "" FORCE )
set( SDL_TEST    OFF CACHE BOOL "" FORCE )
set( SDL_STATIC  ON  CACHE BOOL "" FORCE )

add_subdirectory(zlib-1.3.1)
add_subdirectory(libpng-1.6.44)
add_subdirectory(sdl2)
add_subdirectory(tileengine)

target_include_directories( main PRIVATE tileengine/include)
target_link_directories( main PRIVATE libpng-1.6.44 )
target_link_libraries  ( main PRIVATE SDL2::SDL2main SDL2::SDL2-static )
target_link_libraries  ( main PRIVATE Tilengine )
