### __Introduction__
In computer science a lot of data is encoded to be used efficiently,
to be able to give instructions to a computer to carry out, information must be passed as bits (i.e. 1's and 0's).
So, movies, Video games, photographs, text and more are encoded as strigs of bits in a computer,
and when dealing with those strings computers execute billions of instructions per second (a movie depending on the
quality and size can be billions of bits of data).
So, an efficient method for compression is needed to encode data without losing information.
We will be exploring the Huffman Compression Algorithm as an example on efficient compression methods.

### __Functions__

List of handmade structs used:
* Node: just a normal tree node but holds 2 variables a charactar and integer.
* strings:will be the main input and output of our functions.
* unordered map:used to create the structure of huffman tree.
* priority queue:will be used to organize the unordered map.
* bool vectors:will be used to holds the set of encrypted text by using "true" and "false" as "1"& "0".
* comp: a struct built to help our priority queue to organize the map.

Basic functions:

Function | Description
--------- | ------------
createNode | Creat a tree node.


Functions of Encryption:

Function | Description
--------- | ------------
Encode_atext  |The main function of encryption.
createfreqtree | Creat frequency tree "a map which have a key of specific char and value of it's frequancy in the main text"
createHuffmantree | Creat huffman tree "using priority queue to organize the freqtree .Then taking the least 2 freq and make the a child of a new node with a freq = sum of the 2 least freq and iterate until there is one node in the queue"
createHuffmancodes | Create a map of keys as the char used in the text and values as vector of bools expresing the place of the node in the huffman tree.
encode | Takes the original text and create a vector of bools as the output using the Huffmancodes tree
printhuffmanCode | Printing huffmancodes map each keyy with it's value. 
printVecof_bool  |Print the output vector of "encode" as a string of 1 and 0.
fromvectostr  |Takes the vector of bools and transfer it to string of char (every 8 bools in the vec is transformed to 1 char).
addsizeofvectostr|Adding the true size of the vector to the encrypted string.



Functions of Decryption:

--------- | ------------
decoded_totext  |The main function of decryption.
getsizeofvecfromstr|Get the size of the original vector and delete the size chars.
fromstrtovec |Transform the encrypted string to the encrypted vector of bools
decode   | Decoding the vector of bools to original string using the huffmantree.




### __A Simple Block Daigram:__
![](pic.jpg)
