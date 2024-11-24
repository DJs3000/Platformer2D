add_subdirectory(tilengine)

target_include_directories( main PRIVATE tilengine/include)
target_link_libraries  ( main PRIVATE Tilengine )
