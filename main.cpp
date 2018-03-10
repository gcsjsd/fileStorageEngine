#include <iostream>
#include <string>

#include "SFArchive.h"

int main(int argc, char *argv[]) {
   if(argc<=1){
        SFArchive::info();
    }else{

        std::string command(argv[1]);

        if(command=="add"){

            std::string archiveName(argv[2]);
            std::string fileName(argv[3]);

            SFArchive instance(archiveName);
            instance.add(fileName);
        }else if(command=="del"){

            std::string archiveName(argv[2]);
            std::string fileName(argv[3]);

            SFArchive instance(archiveName);
            instance.del(fileName);
        }else if(command=="-l"||command=="list"){
            if(argc==4){
                //std::cout << "list0" << std::endl;
                std::string archiveName(argv[2]);
                std::string fileName(argv[3]);

                SFArchive instance(archiveName);
                instance.list(fileName);
            }else{
                std::string archiveName(argv[2]);

                SFArchive instance(archiveName);
                instance.list();
            }
        }else if(command=="extract"){
                std::string archiveName(argv[2]);
                std::string fileName(argv[3]);

                SFArchive instance(archiveName);
                instance.extract(fileName);
        }else if(command=="find"){
                std::string archiveName(argv[2]);
                std::string content(argv[3]);

                SFArchive instance(archiveName);
                instance.search(content);

        }else if(command=="-v"){
            SFArchive::version();
        }else{
            SFArchive::error();
        }
    return 0;
	}
}
