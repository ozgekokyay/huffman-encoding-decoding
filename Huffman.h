//
// Created by ozge kokyay on 22.12.2020.
//

#ifndef INC_4_HUFFMAN_H
#define INC_4_HUFFMAN_H
#include "vector"
#include "string"
#include "queue"
#include "map"
#include "ostream"
#include <bits/stdc++.h>

using namespace std;
struct HuffmanNode {
    char character;
    int freq;
    HuffmanNode *left, *right;

    friend ostream &operator<<(ostream &os, const HuffmanNode &n)
    {
        os << (n.character != '\n' && (n.character) != '\0' ? std::string(1, (n.character)) : "") << (n.character != '\0' ? "," : "") << n.freq;
        return os;
    }
};


class Comparator {
public:
    /**
     * comparator operator for priority queue
     * @param p1
     * @param p2
     * @return
     */
    int operator()(HuffmanNode *p1, HuffmanNode *p2);
};


class Huffman {
private:

    /// root node of the huffman tree
    HuffmanNode* root = new HuffmanNode;


    /// encodingSave is the name of file that frequency table
    string encodingSave = "freqTable.txt";

    /**
    *  this queue store the character and its frequency in increasing order
    */
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Comparator> pQueue;
    int length = 500;

    /**
     * maps store characters and their binary encodings
     */
    map<char, string> correspondingBinary;
    map<string, char> correspondingCharacter;

   /**
    * write to output of every character and its frequency
    */
    void createFrequencyTable(string line);
    /**
     * create priority queue and build tree
     */
    void createQueue();
    /**
     * clear tree nodes
     * @param root
     */
    void clearTree(HuffmanNode * root);
    /**
     * read tree and store in maps
     */
    void encodeTree(HuffmanNode* root, const string &current_code);
    /**
     * list tree in a tree shape
     * @param root
     * @param space
     */
    void printTree(HuffmanNode *root, int space);
    /**
     * print binary encoding to command shell
     * @param line
     */
    void printEncoding(string line);


public:
    /**
     * reads input file and encode
     * @param inputFile
     */
    void encode(string inputFile);
    /**
     * read file and decode
     */
    void decode(string inputFile);
    /**
     * print tree
     */
    void listTree();
    /**
     * print the corresponding binary code for any character
     * @param c
     */
    void encodingChar(string c);
};



#endif //INC_4_HUFFMAN_H
