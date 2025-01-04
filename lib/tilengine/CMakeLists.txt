cmake_minimum_required(VERSION 3.6)

project(Tilengine)

# Dependencies
set( PNG_SHARED          OFF CACHE BOOL "" FORCE )
set( PNG_EXECUTABLES     OFF CACHE BOOL "" FORCE )

set( SDL_SHARED          OFF CACHE BOOL "" FORCE )
set( SDL_TEST            OFF CACHE BOOL "" FORCE )
set( ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set( SDL_STATIC          ON  CACHE BOOL "" FORCE )
set( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE)
add_subdirectory(zlib-1.3.1)
add_subdirectory(libpng-1.6.44)
add_subdirectory(SDL-2.30.9)

file(GLOB SOURCES
     "src/*.c"
)


# main library
list(REMOVE_ITEM SOURCES "src/Test.c")
add_library(${PROJECT_NAME} ${SOURCES})

if (UNIX AND NOT APPLE)
	set(CMAKE_C_FLAGS "-m64 -msse2")
elseif (UNIX AND APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "framework")
endif()

target_link_libraries  ( ${PROJECT_NAME} PRIVATE png_static)
target_link_libraries  ( ${PROJECT_NAME} PRIVATE SDL2::SDL2-static )

target_include_directories(${PROJECT_NAME} PRIVATE include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -fpic -DLIB_EXPORTS")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-result -Wno-format-truncation")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/Tilengine.h
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# test executable
#add_executable(Test src/Test.c)
#target_include_directories(Test PRIVATE include)
#target_link_libraries(Test PRIVATE "Tilengine")
#target_link_libraries(Test PRIVATE "c")
#target_link_libraries(Test PRIVATE "z")
#target_link_libraries(Test PRIVATE "png")
#target_link_libraries(Test PRIVATE "m")

# samples
#add_subdirectory(samples)
