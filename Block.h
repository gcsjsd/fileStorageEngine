//
// Created by zhaowei on 3/8/18.
//

#ifndef FILESTORAGE_BLOCK_H
#define FILESTORAGE_BLOCK_H
#define AVA 0
#define TXT 1
#define BIN 2
#define PIC 3
#define DEL 4

#define chunk_size 5120
#define block_size 72 // the block in the header
#define name_size 20 //file name size
#define maxFileNumber 20 // how many blocks in a header
#define header_size 1440
#define chunk_num 100

typedef struct block{
  int type; //AVA, TXT, BIN, PIC, DEL
  char name[name_size]; // file name
  int size;// file size
  bool exist = false;
  std::vector<int> chunks;// chunks it has
  char date[10]; // 03/08/2018
}block_i;

#endif //FILESTORAGE_BLOCK_H
