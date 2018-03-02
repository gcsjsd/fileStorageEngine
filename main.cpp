#include <iostream>
#include <string>

#include "file.h"

int main(int argc, char *argv[]) {
    file instance;
    std::string command(argv[1]);
    if(command=="add"){
        std::string type(argv[2]);
        std::string file(argv[3]);

        instance.add(type, file);
    }else if(command=="del"){
        std::string type(argv[2]);
        std::string file(argv[3]);

        instance.del(type, file);
    }else if(command=="list"){
        if(argc==3){
            std::
        }
    }
    return 0;
}