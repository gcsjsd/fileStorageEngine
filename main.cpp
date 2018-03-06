#include <iostream>
#include <string>

#include "SFArchive.h"

int main(int argc, char *argv[]) {
    SFArchive instance;
    std::string command(argv[1]);
    if(argc<=2){
        instance.info();
    }else if(command=="add"){
        std::string type(argv[2]);
        std::string file(argv[3]);
        instance.add(type, file);
    }else if(command=="del"){
        std::string type(argv[2]);
        std::string file(argv[3]);

        instance.del(type, file);
    }else if(command=="list"){
        if(argc==3){
            std::string content(argv[2]);
            instance.l(content);
        }else{
            instance.l();
        }
    }else if(command=="search"){
        std::string content(argv[2]);
        instance.search(content);
    }else if(command=="-v"){
        instance.version();
    }else{
        instance.error();
    }
    return 0;
}