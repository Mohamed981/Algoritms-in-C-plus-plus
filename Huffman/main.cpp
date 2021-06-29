#include <Windows.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <queue>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Node
{
    char data;
    int frequency;
    Node *left, *right;
};


struct comp
{
    bool operator()(Node* l, Node* r)
    {
        // highest priority item has lowest frequency
        return l->frequency > r->frequency;
    }
};


std::string current_working_directory()
{
    char* cwd = _getcwd( 0, 0 ) ; // **** microsoft specific ****
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
}

vector<string> get_all_files_names_within_folder(string folder)
{
    vector<string> names;
    string search_path = folder +"/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                names.push_back(fd.cFileName);
            }
        }
        while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

int assertGoodFile(const char* fileName)
{
    ifstream fileOrDir(fileName);
    //This will set the fail bit if fileName is a directory (or do nothing if it is already set
    fileOrDir.seekg(0, ios::end);
    if( !fileOrDir.good())
    {
        return 0;
    };
    return 1;
}


void huffman(Node* root, string encodedString,unordered_map<char, string> &huffmanTree)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right)
        huffmanTree[root->data] = encodedString;

    huffman(root->left, encodedString + "0", huffmanTree);
    huffman(root->right, encodedString + "1", huffmanTree);
}
Node * newNode(char inputData, int inputFrequency,Node* left, Node* right)
{


    Node * node = new Node();
    node->data = inputData;
    node->frequency = inputFrequency;
    node->left = left;
    node->right = right;
    return node;
}

int decompress(ifstream &compressedFILE,ofstream &decompressedFILE)
{
    cout<<endl<<"Decompressing"<<endl;

    unordered_map<string, unsigned char> CodeAndChar; //Unordered map that has the huffman code as key, and the character itself as the value
    std::vector<unsigned char> buffer( (std::istreambuf_iterator<char>(compressedFILE)),std::istreambuf_iterator<char>()); //Reading all contents of the compressed file in one vector in binary mode, then converting the binary stream to character.
    vector<unsigned char>::iterator it=buffer.begin();//Iterator that points to the beginning of the reading

    for(it; it!=buffer.end(); it++)//In this loop, I am searching for the character followed by its huffman code until terminating characters "--" are found.
    {
        if(*(it)=='-'&&*(it+1)=='-')//Check for the terminating character which is --, if it is found
        {
            it+=2;
            break;
        }

        unsigned char value;
        string key;

        value=*(it);//In the same format they are stored in the compressed file. First, I take the first character from the file, and store it in the value variable.
        it++;
        while(*(it)!='$')//Note that each pair of character-huffman code is separated by a '$' as the delimiter. For example, g100$t110$x001. We'll iterate until the delimiter is found in this loop
        {
            key+=*(it);
            it++;
        }

        CodeAndChar.insert({key,value});//After parsing the pair of huffman code, and character put them in the hashmap.
    }


    int padded_zeros =*(it)-'0';//Get the number of padded zeros from the text file. I used -'0' to convert it to integer (not necessary anyway since it is a small number<8).
    it++;

    int finalsize;
    vector<unsigned char> encodedchars;//Vector to hold the characters stored in the compressed file.
    for(it; it!=buffer.end(); it++)
    {
        if(*(it)=='-'&&*(it+1)=='-'&&*(it+2)=='-')//Search stops until delimiter is found which is --
        {
            finalsize =((it+3) - buffer.begin());
            break;
        }

        encodedchars.push_back((*it));//Push all characters found to the vector of characters.
    }


    //"Decoded string bits"
    string decodedString;
    for(auto it3: encodedchars)
        decodedString+= bitset<8>(it3).to_string();// Convert every char in the compressed file to its 8 bit binary equivalent

    decodedString.erase (decodedString.end()-8-padded_zeros, decodedString.end());//Remove the padded zeros from string of bits including the EOF


    int j=1;//j represents the step from a substring
    int i=0;//i represents the starting index from a substring  Ex string test = "Ahmed" ..if i =0,j=2.. then test.substr(i,j) means starting from index 0, step 2 characters, and get a new string
    //between those indices. //Result whould be Ahm (It is inclusive of the starting index)
    vector<char> decompressedVECTOR;//Vector to hold the original message as it is decoded by it's huffman code.
    for(int i=0; i+j<=decodedString.length();)
    {

//In this loop, I am trying to map each huffmancode to its specific character in the following example
//Let 0011110 be the string you have to map. And a = 0011 & b = 110.. We'll search through the string as follows
//Check first bit (has value of 0 now) in the hashmap. Found? No -> check first two bits in hashmap (00). Found? No -> check first three bits in the hashmap (001). Found? No ->
//check first 4 bits in the hashmap (0011)? Found, yes, then obtain the character for the specified code. And make the starting point for the check from the last found index.
//which means that the next time you will start checking in the same manner, but starting from the 5th bit till the end of string.

        unordered_map<std::string,unsigned char>::iterator it4 =CodeAndChar.find(decodedString.substr(i,j));//Searching in hashmap returns an iterator.
        if(it4==CodeAndChar.end()) //If the returned iterator doesn't point to a result, it will point to the end of the hashmap, which means that it didn't find the code in the hashmap.
            j++;//Then we'll search for a larger string.
        else // If there is a character found, the iterator will point to the entry which has the pair code, and character, where it4->first is the code, and it->4 is the character.
        {
            if(it4->second!='\r')
                decompressedVECTOR.push_back(it4->second);//if the found character is \r we will skip putting it in the output string, as it will be followed by \n anyways, and \n in windows is converted to \r\n


            i+=j;//Starting next loop where I found the character in the hashmap
            j=1;//Resetting the step variable to 1 to start from single step.
        }
    }



    for(auto it6: decompressedVECTOR)
        decompressedFILE<<it6;//Writting to the output file.


    cout<<"Decompressing done"<<endl;

    return finalsize;
    //decompressedFILE.close();
}
void compress(std::vector<unsigned char> data,ofstream &outputFILE)
{

    vector<char> outputVECTOR;
    cout<<"Compressing"<<endl;

    unordered_map<unsigned char, int> frequencies;
    for (int i = 0; i < data.size(); i++)
        frequencies[data.at(i)]++;


    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto pair: frequencies) pq.push(newNode(pair.first, pair.second, nullptr, nullptr));
    while (pq.size()!=1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->frequency + right->frequency;
        pq.push(newNode('\0', sum, left, right));
    }
    Node* root = pq.top();


    unordered_map<char, string> huffmanTree;
    huffman(root, "", huffmanTree);

    for(auto it:huffmanTree)
        outputFILE<<it.first<<it.second<<"$";

    outputFILE.flush();
    outputFILE<<"--";

    string enocdedbits;
    for (char ch: data)
        enocdedbits += huffmanTree[ch];


    int padded_zeros=0;
    int remainder = enocdedbits.length()%8;
    if(remainder!=0)
        padded_zeros = 8-remainder;
    outputFILE<<padded_zeros;


    for(int i=0; i<padded_zeros; i++)
        enocdedbits+='0';

    stringstream stringStream(enocdedbits);
    while (stringStream.good())
    {
        bitset<8> bits;
        stringStream >> bits;
        unsigned char c = char(bits.to_ulong());
        outputFILE << c;
    }


    outputFILE<<"---";
    outputFILE.flush();

    cout<<"Compressing done"<<endl;
}

int main()
{

    while(1)
    {
        cout<<"-------------------------------------------------"<<endl;
        string currentDirectory = current_working_directory();
        cout <<"Current directory: "<< currentDirectory << endl;

        int inputIntger;
        cout<<"Choose:"<<endl<<"0: for compression"<<endl<<"1: for decompression"<<endl<<"Any number: for exiting"<<endl<<"(Make sure to remove any previous file if it already exists)"<<endl;
        cin>>inputIntger;
        if(inputIntger==2)
            break;


        if(!inputIntger)//If compression is selected
        {
            string input;
            cout<<"Please enter file name (followed by type extension) or folder name"<<endl;
            cin>>input;
            int isFile = assertGoodFile(input.c_str()); //Checking if it is a file or folder.
            struct stat info;
            if(isFile)//If a file is detected
            {
                //Compression
                std::ifstream inputFILE(input.c_str(),ios::binary);
                std::vector<unsigned char> data( (std::istreambuf_iterator<char>(inputFILE)),std::istreambuf_iterator<char>() );


                cout<<"Please enter output compressed file name (followed by .bin)"<<endl;
                string output;
                cin>>  output;

              //  std::ofstream outputFILE(output.c_str(),ios::binary);
              ofstream outputFILE("output.txt");
                outputFILE<<1;
                //Execution time
                auto start = high_resolution_clock::now();
                compress(data,outputFILE);
                auto stop = high_resolution_clock::now();

                //Compression ratio
                inputFILE.seekg(0,ios::end);
                float inputfilesize = inputFILE.tellg();
                outputFILE.seekp(0,ios::end);
                float outputfilesize = outputFILE.tellp();



                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken: "<< duration.count() << " microseconds" << endl;

                cout<<std::setprecision(10)<<"Compression ratio: "<<inputfilesize/outputfilesize<<endl<<endl;


                inputFILE.close();
                outputFILE.close();
            }
            else if(stat( input.c_str(), &info ) == 0)//If a folder is detected
            {

                cout<<"Please enter output compressed file name (followed by .bin)"<<endl;
                string output;
                cin>>output;


                vector<string> names=  get_all_files_names_within_folder(input);
                ifstream inputFILES[names.size()];
                std::ofstream outputFILE(output.c_str(),ios::binary|ios::app);

                int i=0;
                int number_of_files=names.size();
                char number_of_filesC =number_of_files +'0';
                outputFILE<<number_of_filesC;//Put number of files in a saved file.



                auto start = high_resolution_clock::now();
                for(auto it:names)
                {
                    string current =  current_working_directory()+"\\" + input+"\\"+it;
                    cout<<current<<endl;
                    inputFILES[i].open(current.c_str(),ios::binary);
                    std::vector<unsigned char> data( (std::istreambuf_iterator<char>(inputFILES[i])),std::istreambuf_iterator<char>() );
                    inputFILES[i].close();
                    compress(data,outputFILE);
                    i++;
                }

                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken: "<< duration.count() << " microseconds" << endl;
                outputFILE.close();


            }else  //Not a Valid input
                cout<<"Enter a valid Input"<<endl;
        }
        else if(inputIntger==1) //Decompression
        {


            cout<<"Please enter input compressed file name (followed by .bin)"<<endl;
            string input1;
            cin>>  input1;
            /////Decompression
            std::ifstream compressedFILE(input1.c_str(),ios::binary);
            if(compressedFILE){
            char number_of_files_c;
            compressedFILE.get(number_of_files_c);
            int number_of_files= number_of_files_c - '0';


            std::ofstream decompressedFILES[number_of_files];


            auto start = high_resolution_clock::now();
            for(int i=0; i<number_of_files; i++)
            {

                string filename;
                filename+=input1.substr(0,input1.size()-4);
                if(number_of_files>1)
                    filename+=to_string(i);
                filename+=".txt";


                decompressedFILES[i].open(filename.c_str(),ios::out); //Opening the output file of decompression
                int finalsize=  decompress(compressedFILE,decompressedFILES[i]);
                decompressedFILES[i].close();
                if(number_of_files>1)
                    compressedFILE.seekg(finalsize+1, ios_base::beg);
                    cout<<"--------------------------->"<<filename<<endl;
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken: "<< duration.count() << " microseconds" << endl;

            }else  //File not found
            cout<<"Compressed File not found"<<endl;
        }else  //Exiting
            exit(0);
    }


    return 0;
}
