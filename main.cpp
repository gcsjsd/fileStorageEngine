#include <iostream>
#include <string>

#include "SFArchive.h"

int main(int argc, char *argv[]) {
    SFArchive instance;
    std::string command(argv[1]);
    std::cout << command << std::endl;
    if(argc<=1){
        instance.info();
    }else if(command=="add"){
        std::string type(argv[2]);
        std::string file(argv[3]);
        instance.add(type, file);
    }else if(command=="del"){
        std::string type(argv[2]);
        std::string file(argv[3]);

        instance.del(type, file);
    }else if(command=="-l"||command=="list"){
        if(argc==3){
            std::cout << "list0" << std::endl;
            std::string content(argv[2]);
            instance.list(content);
        }else{
            std::cout << "list1" << std::endl;
            instance.list();
        }
    }else if(command=="extract"){
        std::string content(argv[2]);
        std::string name(argv[3]);
        instance.extract(content, name);
    }else if(command=="find"){
        std::string content(argv[2]);
        instance.search(content);
    }else if(command=="-v"){
        instance.version();
    }else{
        instance.error();
    }
    return 0;
}
