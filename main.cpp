#include <iostream>
#include "string"
#include "Huffman.h"
using namespace std;
int main(int argc, char *argv[]) {
    string argv1 = argv[1];
    string argv2;
    string argv3;
    Huffman huffmanCode;

    if ( argc == 2 && argv1 =="-l") { // -l
        cout << argv1;
        huffmanCode.listTree();
    }
    else if ( argc == 3 ) { // -s character
        argv2 = argv[2];
        if(argv1 == "-s"){
            huffmanCode.encodingChar(argv2);
        }
    }
    else if (argc == 4 ){ //  -i input_file.txt -encode
        argv2 = argv[2]; //filename
        argv3 = argv[3]; //-encode or -decode
        if(argv3 == "-encode")
        {
            huffmanCode.encode(argv2);
        }
        else if (argv3 == "-decode"){
            huffmanCode.decode(argv2);
        }
    }
    return 0;
}
