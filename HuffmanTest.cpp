#include <iostream>
#include "Huffman.hpp"
#include <fstream>

using namespace std;

int main(){

  fstream file; //object of fstream class
  std::string x;
  cout << "Please Enter kind of operation ( Encode or Decode )"<<endl;
  cin >> x;  
  if (x == "Encode")
  {

  //open file in read mode
   file.open("D1.txt",ios::in);
    
   if(!file)
   {
       cout<<"Error in opening file!!!"<<endl;
       return 0;
   }   
    
   //read untill end of file is not found.
   std::string text; 

   while(!file.eof())
   {
       file >> text; //read text from file
   }
    
   file.close(); //close file
    
   //opening file "E2.txt" in out(write) mode
   file.open("E2.txt",ios::out);
    
   if(!file)
   {
       cout<<"Error in creating file!!!"<<endl;
       return 0;
   }

   //write text into file
   file<< Encode_atext (text)<<endl;
   //closing the file
   file.close();
  }

  else if (x == "Decode") 
  {
      //again open file in read mode
   file.open("D1.txt",ios::in);
    
   if(!file)
   {
       cout<<"Error in opening file!!!"<<endl;
       return 0;
   }   
    
   //read untill end of file is not found.
   std::string text; 

   while(!file.eof())
   {
       file >> text; //read text from file
   }
    
   file.close(); //close file
    
   //opening file "E2.txt" in out(write) mode
   file.open("D2.txt",ios::out);
    
   if(!file)
   {
       cout<<"Error in creating file!!!"<<endl;
       return 0;
   }

   //write text into file
   file<< Encode_atext (text)<<endl;
   //closing the file
   file.close();
  }

  else 
  {
      cout << "invalid order"<<endl;
  }
   return 0;
}
