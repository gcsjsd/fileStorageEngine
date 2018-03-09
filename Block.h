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
#define block_size 80 // the block in the header
#define name_size 32 //file name size
#define maxFileNumber 20 // how many blocks in a header
#define header_size (block_size * maxFileNumber)
#define chunk_num 100

typedef struct block{
  int type; //AVA, TXT, BIN, PIC, DEL
  char name[name_size]; // file name
  int size;// file size
  std::vector<int> chunks;// chunks it has
  int day;
  int month;
  int year;
}block_i;

#endif //FILESTORAGE_BLOCK_H
