#include <iostream>
#include <string>

#include "SFArchive.h"

int main(int argc, char *argv[]) {
  if(argc<=1) {
    SFArchive::info();
  }else {
    std::string command(argv[1]);
    if(command=="add") {
      if (argc != 4) {
        SFArchive::error();
        return 0;
      }
      std::string archiveName(argv[2]);
      std::string fileName(argv[3]);
      SFArchive instance(archiveName);
      instance.add(fileName);
    } else if(command=="del") {
      if (argc != 4) {
        SFArchive::error();
        return 0;
      }
      std::string archiveName(argv[2]);
      std::string fileName(argv[3]);
      std::ifstream archive(archiveName);
      if (archive.tellg() == -1) {
        std::cout << "archive " + archiveName << " doesn't exist... try ./sfarchive add [archiveName] [filename] to create an archive." << std::endl;
        archive.close();
        return 0;
      }
      archive.close();
      SFArchive instance(archiveName);
      instance.del(fileName);
    }else if(command=="-l"||command=="list") {
      if(argc==4) {
        //std::cout << "list0" << std::endl;
        std::string archiveName(argv[2]);
        std::string fileName(argv[3]);
        std::ifstream archive(archiveName);
        if (archive.tellg() == -1) {
          std::cout << "archive " + archiveName << " doesn't exist... try ./sfarchive add [archiveName] [filename] to create an archive." << std::endl;
          archive.close();
          return 0;
        }
        archive.close();
        SFArchive instance(archiveName);
        instance.list(fileName);
      }else {
        if (argc != 3) {
          SFArchive::error();
          return 0;
        }
        std::string archiveName(argv[2]);
        std::ifstream archive(archiveName);
        if (archive.tellg() == -1) {
          std::cout << "archive " + archiveName << " doesn't exist..." << std::endl << "try ./sfarchive add [archiveName] [filename] to create an new archive and add file." << std::endl;
          archive.close();
          return 0;
        }
        archive.close();
        SFArchive instance(archiveName);
        instance.list();
      }
    }else if(command=="extract") {
      if (argc != 4) {
        SFArchive::error();
        return 0;
      }
      std::string archiveName(argv[2]);
      std::string fileName(argv[3]);
      std::ifstream archive(archiveName);
      if (archive.tellg() == -1) {
        std::cout << "archive " + archiveName << " doesn't exist..." << std::endl << "try ./sfarchive add [archiveName] [filename] to create an new archive and add file." << std::endl;
        archive.close();
        return 0;
      }
      archive.close();
      SFArchive instance(archiveName);
      instance.extract(fileName);
    }else if(command=="find") {
      if (argc != 4) {
        SFArchive::error();
      }
      std::string archiveName(argv[2]);
      std::string content(argv[3]);
      std::ifstream archive(archiveName);
      if (archive.tellg() == -1) {
        std::cout << "archive " + archiveName << " doesn't exist..." << std::endl << "try ./sfarchive add [archiveName] [filename] to create an new archive and add file." << std::endl;
        archive.close();
        return 0;
      }
      archive.close();
      SFArchive instance(archiveName);
      instance.search(content);
    }else if(command=="-v") {
      SFArchive::version();
    }else {
      SFArchive::error();
    }
    return 0;
	}
}
