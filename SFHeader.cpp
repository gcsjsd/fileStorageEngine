#include "SFHeader.h"


vector<int> SFHeader:: getEmptyChunks(){
    std:: size_t found = SFHeader.find('}');
    std:: string info = header.substr(1, found-1);
    std:: stringstream ss(info);
    std:: vector<int> chunks;

    for(int i=0; ss>>i; ){
        chunks.push_back(i);
    }

    return chunks;
}