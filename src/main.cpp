#include "game.hpp"
#include "error.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{
    try {
        const bool is_initialized = Platformer2D::Init();
        if (is_initialized == false) {
            std::cerr << "Can't launch Tilengine..." << std::endl;
            return EXIT_FAILURE;
        } 
        Platformer2D::Run();
        Platformer2D::Close();
        return EXIT_SUCCESS;
    } catch(const std::exception &ex) {
        Error::LogError(ex.what()); 
        Platformer2D::Close();
        return EXIT_FAILURE;
    } catch(...) {
        Error::LogError("Unknown error!");
        Platformer2D::Close();
        return EXIT_FAILURE;
    }
}
