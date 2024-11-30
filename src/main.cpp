#include "game.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{
    const bool is_initialized = Platformer2D::Init();
    if (is_initialized == false) {
        std::cerr << "Can't launch Tilengine..." << std::endl;
        return EXIT_FAILURE;
    } 
    Platformer2D::Run();
    Platformer2D::Close();
    return EXIT_SUCCESS;
}
