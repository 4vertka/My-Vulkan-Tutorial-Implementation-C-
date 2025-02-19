#include "./engine.hpp"

#include "stb_image.h"                           

#include "./tiny_obj_loader.h"

int main() {
    HelloTriangle app;

    try {
        app.run();
    }catch( const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;    
    }

    return EXIT_SUCCESS;
}
