#include <stdio.h>
#include <iostream>

#include "svq/app.h"

int main( int argc, char * argv[] ) {
    svq::App app;

    if (!app.init()) {
        std::cerr << "app not initialized properly !" << std::endl;
        return -1;
    }

    int ret = app.run();

    return ret;
}
