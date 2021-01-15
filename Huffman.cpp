#include "Huffman.h"
#include "fstream"
#include "string"
using namespace std;

/// compare priority queue by frequency of nodes
int Comparator::operator()(HuffmanNode *p1, HuffmanNode *p2)
{
    return p1->freq > p2->freq;
}

/// delete all nodes in the tree
void Huffman::clearTree(HuffmanNode* root)
{
    if (root == nullptr) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}

/// encode input file and print encoded text
void Huffman::encode(string inputFile)
{
    ifstream input(inputFile);
    string line;
    if(input.is_open()){
        while( getline(input, line)){
            createFrequencyTable(line);
            createQueue();
            string current_code = "";
            encodeTree(root, current_code);
            printEncoding(line);
            clearTree(root);
            root = NULL;
        }
    }
    input.close();
}

/// save characters and their frequencies to txt file
void Huffman::createFrequencyTable(string line)
{
    unordered_map<char, int> d;
    int count = 0;
    // read chars and find their occurences
    for(char i : line)
    {
        d[i]++;
    }
    for(auto it : d){
        count++;
    }

    ofstream out(encodingSave);
    // add size of the table at the top of file
    out<<count<<endl;

    for (auto& it : d) {
        if(it.first == ' '){ // if char is space use '+' instead when storing
            out << "+ "<<it.second<<endl;
        }
        else {
            out << it.first<<" "<<it.second<<endl;
        }
    }
    out.close();
}

/// create priority queue and build tree
void Huffman::createQueue() {
    ifstream file(encodingSave);
    string line;

    if(file.is_open()){
        int size;
        file >> size;
        for(int i = 0; i<size; i++){
            int freq;
            char character;
            // read character and frequency from the txt file
            file >> character >> freq;
            HuffmanNode* newNode = new HuffmanNode;
            newNode->character = character;
            newNode->freq = freq;
            newNode->left = nullptr;
            newNode->right = nullptr;
            pQueue.push(newNode);
        }
    }
    file.close();
    /// if pQueue has more than 1 element rearrange nodes and build the tree
    while(pQueue.size() > 1){
        HuffmanNode* newNode = new HuffmanNode;
        int a = pQueue.top()->freq;
        newNode->left = pQueue.top();
        pQueue.pop();
        if(!pQueue.empty()){
            a += pQueue.top()->freq;
            newNode->right = pQueue.top();
            pQueue.pop();
        }
        newNode->character = '\0';
        newNode->freq = a;
        pQueue.push(newNode);
    }
    /// root node of the tree
    root = pQueue.top();
    pQueue.pop();
}

/// read tree and store in maps
void Huffman::encodeTree(HuffmanNode *root, const string &current_code) {
    if (root == nullptr)
        return;

    if (root->character != '\0')
    {
        /// fill the maps for characters and their codes
        correspondingBinary[(root->character)] = current_code;
        correspondingCharacter[current_code] = root->character;

        if (current_code.size() < length) {
            length = current_code.size();
            return;
        }
        return;
    }
    encodeTree(root->left, current_code + "0");
    encodeTree(root->right, current_code + "1");
}

/// prints tree in tree shape
void Huffman::printTree(HuffmanNode *root, int space){
    int count = 1;
    if (root == nullptr)
        return;
    space += count;
    printTree(root->right, space);
    for (int i = count; i < space; i++)
        cout<<"\t";
    if(root->character == '\0' ){
        cout << "* -- \n";
    }
    else {
        cout << "-- "<<root->character << " \n";
    }
    printTree(root->left, space);
}

/// list the trees elements in a tree shape
void Huffman::listTree() {
    createQueue();

    string current_code = "";
    encodeTree(root, current_code);
    printTree(root, 1);
    clearTree(root);
    root = NULL;
}


void Huffman::encodingChar(string c) {
    createQueue();
    string current_code = "";
    encodeTree(root, current_code);
    char character = c.c_str()[0];
    for (auto i = correspondingBinary.begin(); i != correspondingBinary.end(); i++) {
        if (i->first == character){
            cout << i->second <<endl;
            return;
        }
    }
    clearTree(root);
    root = NULL;
}

void Huffman::decode(string inputFile) {
    ifstream file(inputFile);
    createQueue();
    string current_code = "";
    encodeTree(root, current_code);

    string line;
    if(file.is_open()) {
        while (getline(file, line)) {
            string s = line;
            string ans;
            HuffmanNode* curr = root;
            for(int i=0; i<s.size(); i++){
                if(s[i]=='0'){
                    curr = curr->left;
                }
                else {
                    curr = curr->right;
                }
                if( curr != nullptr && !curr->right && !curr->left){ //reached leaf node
                    if(curr->character == '+'){
                        ans = ans + " ";
                        curr = root;
                    }
                    else{
                        ans=ans + curr->character;
                        curr = root;
                    }
                }
            }
            cout << ans;
        }
    }
    clearTree(root);
    root == NULL;
}

void Huffman::printEncoding(string line) {
    for (char c : line) {
        for (auto i = correspondingBinary.begin(); i != correspondingBinary.end(); i++) {
            if (i->first == c) {
                cout << i->second;
            }
            else if( c == ' '){
                cout<<correspondingBinary['+'];
            }
        }
    }
    cout<<endl;
}

