#include <bits/stdc++.h>
using namespace std;

/*================================
    INITIALIZE THE MAP
=================================*/
map<string, int> buildFrequencyTable(string input) //function that returns a map of the characters and their occurences
{ 
    map<string, int>characterCountMap;
    for(int i=0;i<input.length();i++){
        int count=0;
        for(int j=0;j<input.length();j++){
            if(input[i]==input[j]){
                
                count++; 
            }
        }
        string character = "";
        character+="'";
        character+=input[i];

        character+="'";
        characterCountMap.insert(pair<string,int>(character,count));
    }
    characterCountMap.insert (pair<string,int>("'LF'",1));
    return characterCountMap;

} 
//--------------------------------------------------------------------------------------------
void printMap(){ //function that prints the map (used for testing)
    cout<<"Enter a message: ";
    string word;
    getline(cin,word);
    map<string, int>:: iterator itr; 
    map<string, int>test=buildFrequencyTable(word);; 
    
    cout<<endl;
    for (itr =test.begin(); itr !=test.end(); itr++){
            cout <<itr->first << ": " << itr->second << "\n"; 
        
    }
}
//----------------------------------------------------------------------------------------------

/*==========================================
    BINARY TREE
===========================================*/
struct HuffmanNode {//Huffman Node struct{

    string character;
    int occurences; 
    HuffmanNode *rightChild;
    HuffmanNode *leftChild;
};
HuffmanNode* createNode(int value,string input){ //creates a node with a character and its occurences
    HuffmanNode *temp = new HuffmanNode();
    temp->character = input;
    temp->occurences = value;
    temp->rightChild=NULL;
    temp->leftChild = NULL;
    return temp;
}
HuffmanNode* createNode(int value){//creates a node that carries the number of occureneces
    HuffmanNode *temp = new HuffmanNode();
    temp->character="'NO VALUE'";
    temp->occurences = value;
    temp->rightChild=NULL;
    temp->leftChild = NULL;
    return temp;
}
void addNode(HuffmanNode* &root,string input,int value){
    if(root==NULL){
        root = createNode(value,input);
    }
    else if(root->leftChild==NULL){
        addNode(root->leftChild,input,value);     
    }
    else{
        addNode(root->rightChild,input,value);
    }
}
//--------------------
void addNode(HuffmanNode* &root,int value){
    if(root==NULL){
        root = createNode(value);
    }
    else if(root->leftChild==NULL){
        addNode(root->leftChild,value);     
    }
    else{
        addNode(root->rightChild,value);
    }
}
//--------------------
void printNode(HuffmanNode* root,string path){
    if(root!=NULL){
        cout<<root->character<<" : "<<root->occurences<<" Path: "<<path<<endl;
        printNode(root->leftChild,path+"L");
        printNode(root->rightChild,path+"R");
    }
}

/*==========================================
    PRIORITY QUEUE
===========================================*/
void sortQueue(queue<HuffmanNode*> &inputQ){ //sorts the queue everytime we add a new node 
    vector <HuffmanNode*> temp;
    while(!inputQ.empty()){
        temp.push_back(inputQ.front());
        inputQ.pop();
    }

    for(int i=0;i<temp.size();i++){
        for(int j=0;j<temp.size();j++){
            HuffmanNode* tempr=temp[i];
            if((temp[i]->occurences)>temp[j]->occurences){
                temp[i]=temp[j];
                temp[j]=tempr;
            }
        }
    }
    reverse(temp.begin(),temp.end());
    for(int i=0;i<temp.size();i++){
        inputQ.push(temp[i]);
    }

}

queue<HuffmanNode*> createPQ(map<string, int> freqTable){ //creates the priority queue

    queue<HuffmanNode*> CharNodes;

    map<string, int>:: iterator itr; 


    HuffmanNode* root = NULL;
    for (itr =freqTable.begin(); itr !=freqTable.end(); itr++){
        HuffmanNode* temp = createNode(itr->second,itr->first);
        CharNodes.push(temp);

    }

    sortQueue(CharNodes);
    return CharNodes;
    
}
/*==========================================
    CREATE TREE
===========================================*/

void CreateTree(queue<HuffmanNode*> &inputQ){ //creation of the tree in the queue
    HuffmanNode* firstNode = inputQ.front();
    inputQ.pop();
    HuffmanNode* secondNode = inputQ.front();
    inputQ.pop();
    HuffmanNode* temp= createNode(firstNode->occurences+secondNode->occurences);
    temp->leftChild = firstNode;
    temp->rightChild = secondNode;
    inputQ.push(temp);

    sortQueue(inputQ);

 

}

HuffmanNode* buildEncodingTree(map<string, int> freqTable){ //builds the final tree
    queue<HuffmanNode*> temp;
    temp=createPQ(freqTable);

    int size = temp.size();

    for(int i=0;i<size-1;i++){
        CreateTree(temp);
    }
    return temp.front();
}
/*==========================================
    ENCODE
===========================================*/

void encode(HuffmanNode* root,map<string, string>&encodedData,string code){ //finds the binary value of each character
    if(root!=NULL){
        if(root->character!="'NO VALUE'")
        encodedData.insert(pair<string,string>(root->character,code));
        encode(root->leftChild,encodedData, code+"0");
        encode( root->rightChild,encodedData, code+"1");
    } 
}
map<string, string> buildEncodingMap(HuffmanNode* encodingTree){ //returns a map of the characters and their binary value
    map<string, string>encodedData;
    encode(encodingTree,encodedData,"");
    return encodedData;
}
void encodeData( const string  &input,  map<string,string>encodingMap, string & output){  //encodes the message

    map<string, string>:: iterator itr; 
    for(int i=0;i<input.length();i++){
        string charToString = "'";
        charToString+=input[i];
        charToString+="'";
        for (itr =encodingMap.begin(); itr !=encodingMap.end(); itr++){
            if(itr->first==charToString){
                output+=itr->second;
            }
        
        
    }

    }

}
/*==========================================
    DECODE
===========================================*/
void decodeData(const string& input, HuffmanNode* encodingTree, string& output){
    HuffmanNode* current=encodingTree;
    for(int i=0;i<=input.length();i++){
        if(current->rightChild==NULL && current->leftChild==NULL){
            if(current->character!="'LF'"){
                output+=current->character[1];
            }
            current=encodingTree;
        }
        if(input[i]=='0'){
            current=current->leftChild;
        }
        if(input[i]=='1'){
            current=current->rightChild;
        }
    }
}

//==============================================================================================
//==============================================================================================
//==============================================================================================
int main(){
    cout<<"By Adam Helal(201901349) and Youssef Itani(201900604)\n "<<endl;
    cout<<"Enter a Message: ";
    string message;
    getline(cin,message);
    map<string, int> freqTable = buildFrequencyTable(message);
    map<string, string> Data = buildEncodingMap(buildEncodingTree(freqTable));
    string output="";
    encodeData(message, Data,output);
    cout<<"Encoded Message : "<<output<<endl;

    string decode="";
    decodeData(output,buildEncodingTree(freqTable),decode);
    cout<<"Decoded Message : "<<decode;
}
