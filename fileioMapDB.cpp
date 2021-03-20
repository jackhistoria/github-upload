#include <iostream>
#include <map>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{

  std::map<std::string, std::string> db{{"Key1","value"},{"Key2","value"}};
  std::fstream mydata;

  //PRINT MAP
  for(const auto &[k,v] : db)
    std::cout << k << " " << v << std::endl;

  //WRITE MAP TO FILE
  //Open File in write mode
  mydata.open("data.data", std::ios::out);
  if(!mydata.is_open())
  std::cout << "Could not open file!" << std::endl;

  //Write data to file
  for(const auto &[k,v] : db)
    mydata << k <<" " << v << std::endl;
  //Close file
  mydata.close();

  //proof of concept, DESTROY MAP VALUES
  db.clear();

  //READ MAP BACK IN FROM FILE
  std::string key , value;

  //Open Data in read mode
  mydata.open("data.data", std::ios::in);
  if(!mydata.is_open())
    std::cout << "Could not open file!" << std::endl;

  //Read data back to map
  while(mydata >> key >> value)
    db[key] = value;

  //Close File again
  mydata.close();

  //PRINT MAP
  for(const auto &[k,v] : db){
    std::cout << k << " " << v << std::endl;
  }

  std::cin.get();
  return 0;
}
