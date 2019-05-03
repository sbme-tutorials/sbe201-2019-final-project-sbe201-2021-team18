#ifndef CODE
#define CODE
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stack> 

struct Node
{// Tree node
	char ch;
	int freq;
	Node *left, *right;	
};

Node* createNode(char ch, int freq, Node* left, Node* right)
{// Function to creat a new node
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
	node->right = right;

    return node;
}

struct comp
{// Comparison object to be used to order the heap
	bool operator()(Node* l, Node* r)
	{// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

void createfreqtree(std::unordered_map<char, int>&freq,
					const std::string& text)
{	//We count frequency of appearance of each character
	// and store it in a map
	for (char ch: text)
    {
		freq[ch]++;
	}
}

void createHuffmantree(std::priority_queue<Node*, std::vector<Node*>, comp>
					&Huffmantree,const std::unordered_map<char, int> &freq)
	{// We put every point in our freq map to the Huffmantree
	for (auto point: freq) {
		Huffmantree.push(createNode(point.first, point.second, nullptr, nullptr));
	}

	//then we organize our tree by letting only one element "the parent"
	//in the priority queue and access the rest by using the pointer in the Node
	while (Huffmantree.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = Huffmantree.top();
		Huffmantree.pop();
		Node *right = Huffmantree.top();
		Huffmantree.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		Huffmantree.push(createNode('\0', sum, left, right));
	}
}

void encode(Node* Huffmantree_Root, std::vector<bool> codeforchar,
			std::unordered_map<char, std::vector<bool> > &huffmanCodes)
{// traverse the Huffman Tree and store Huffman Codes
// in a map.

	if (Huffmantree_Root == nullptr)
		return;

	// found a leaf node
	if (!Huffmantree_Root->left && !Huffmantree_Root->right)
		huffmanCodes[Huffmantree_Root->ch] = codeforchar;

	codeforchar.push_back(false);
	encode(Huffmantree_Root->left, codeforchar, huffmanCodes);
	codeforchar.pop_back();

	codeforchar.push_back(true);
	encode(Huffmantree_Root->right, codeforchar, huffmanCodes);
	codeforchar.pop_back();
}

void printhuffmanCode(std::unordered_map<char,std::vector<bool>> huffmanCode){
    std::cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCode) {
		std::cout << pair.first << " ";
		for(auto a: pair.second)
		{
			if(a)
				std::cout<<"1";
			else
				std::cout<<"0";
		}
		std::cout<<"\n";
	}
}

void printVecof_bool(std::vector<bool> vec)
{
	for(auto vecn:vec)
		std::cout<<vecn;
	std::cout<<"\n";
}

std::string fromvectostr(std::vector<bool> &vec)
{
    std::string str;
    /*
   
    unsigned long int size=vec.size();
    for ( int i = sizeof(size)*8; i>0; i-=8)
    {
        char c=0;
		for (int j=1;(i+j>0)&&(j<8); j++ )
		{
            c += size<<((i-j));
		}
		str+=c;
    }
    */
	for (int i = 0; i < vec.size(); i+=8)
	{
		char c=0;
		for (int j = 0; i+j<vec.size()&&j < 8; j++ )
		{
			c =c+ (vec[i+j]<<(7-j));
		}
		str+=c;
	}	
    return str;
}

std::string Encode_atext(std::string text)
{
	// Create a freq map to store freq of every char in the text.
	std::unordered_map<char, int> freq;
	createfreqtree(freq,text);

	// Create a priority queue to store live nodes of Huffman tree;
	std::priority_queue<Node*, std::vector<Node*>, comp>  Huffmantree;
	createHuffmantree(Huffmantree,freq);

	// root stores pointer to root of Huffman Tree
	Node* root = Huffmantree.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map.
	std::unordered_map<char, std::vector<bool> >  huffmanCode;
	std::vector<bool> temp;
	encode(root, temp, huffmanCode);

    //printhuffmanCode(huffmanCode);

    std::vector<bool> codedtext;
	for (char ch: text) {
		for(auto a : huffmanCode[ch])
    		codedtext.push_back(a);
	}
    
    std::cout << "\nEncoded std::string is :\n";
    printVecof_bool(codedtext);

    std::string unreadable_str=fromvectostr(codedtext);
	//std::cout<< unreadable_str<<"\n";

    return unreadable_str;
}

std::vector<bool> fromstrtovec(std::string &str)
{
    std::vector<bool> vec;
	vec.clear();
	std::stack<bool> Stack;
	for (int i = str.size()-1; i>=0; i--)
	{
		char ch=str[i];
		for (int j=7; j >= 0; j--)
		{
			char x=ch<<j;
			if ((x)<0)
				Stack.push(true);
			else
				Stack.push(false);
		}
	}
	int x=Stack.size();
	for (int i = 0; i < x; i++)
	{
		vec.push_back(Stack.top());
		Stack.pop();
	}
    return vec;
	
}

void decode(Node* Huffmantree_Root, int &index,
			std::vector<bool> coded,std::string &str)
{// traverse the Huffman Tree and decode the encoded std::string
	if (Huffmantree_Root == nullptr)
		return;

	// found a leaf node
	if (!Huffmantree_Root->left && !Huffmantree_Root->right)
	{
		str += Huffmantree_Root->ch;
		return;
	}

	index++;

	if (coded[index] == false)
		decode(Huffmantree_Root->left, index, coded,str);
	else
		decode(Huffmantree_Root->right, index, coded,str);
}

std::string decoded_totext(std::string unreadable_str,std::string text )
{


    //just to get the root pointer.

	// Create a freq map to store freq of every char in the text.
	std::unordered_map<char, int> freq;
	createfreqtree(freq,text);

	// Create a priority queue to store live nodes of Huffman tree;
	std::priority_queue<Node*, std::vector<Node*>, comp>  Huffmantree;
	createHuffmantree(Huffmantree,freq);

	// root stores pointer to root of Huffman Tree
	Node* root = Huffmantree.top();





    std::vector<bool>vec =fromstrtovec(unreadable_str);

	//std::cout << "\nEncoded std::string is :\n";
	//printVecof_bool(vec);

    // traverse the Huffman Tree again and this time
	// decode the encoded std::string
	int index = -1;
	std::string temp;
	while (index < (int)vec.size()-2) {
		decode(root, index, vec,temp);
	}

    //std::cout << "\nDecoded std::string is: \n";
	//std::cout<<temp2<<"\n";

}





















#endif