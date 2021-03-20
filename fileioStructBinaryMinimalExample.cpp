#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define FILENAME "data.bin"

struct Vertex
{
    size_t x{};
    size_t y{};
    std::string z{};
};

void writeVectorToBinary(std::vector<Vertex> &v);
void readVectorFromBinary(std::vector<Vertex> &v);
void printVector(std::vector<Vertex> &v);

int main()
{
std::vector<Vertex> vertices;
vertices.push_back({1,2,"three"});
vertices.push_back({4,5,"six"});

writeVectorToBinary(vertices);
printVector(vertices);
readVectorFromBinary(vertices);
printVector(vertices);

int firstNumber = 1, secondNumber = 2;

double result1 = ((double)firstNumber) /secondNumber;
double result2 = static_cast<double>(firstNumber)/secondNumber;
std::cout << result1 << std::endl;
std::cout << result2 << std::endl;
std::cout <<result1 + result2 << std::endl;

std::cin.get();
return 0;
}


void writeVectorToBinary(std::vector<Vertex> &v)
{
  size_t size = v.size();
  //Open Binary file, to write out data
  std::ofstream file(FILENAME, std::ios::binary);
  if(!file)
    std::cout << "Something went wrong" << std::endl;
  //Store/Write the vector size
  file.write(reinterpret_cast<const char*>(&size), sizeof(size));
  //Store/Write the data of the vector out
  file.write(reinterpret_cast<const char*>(v.data()), sizeof(v[0])*size);
  //Close binary file
  file.close();
}

void readVectorFromBinary(std::vector<Vertex> &v)
{
//Clear Vector just for the proof of concept
v.clear();
size_t size{};
//Open Binary file to read in data
std::ifstream file(FILENAME,std::ios::binary);
if(!file)
  std::cout << "Something went wrong" << std::endl;
//Read the vector size
// file.read(reinterpret_cast<char*>(&size), sizeof(size));
file.read((char*)(&size), sizeof(size)); //c-style cast
//Resize vector now that its known
v.resize(size);
//Read vector data in
// file.read(reinterpret_cast<char*>(v.data()), sizeof(v[0])*size);
file.read((char*)(v.data()), sizeof(v[0])*size);
//Close binary file
file.close();
}

void printVector(std::vector<Vertex> &v)
{
  for(size_t i{}; i < v.size(); ++i ){
    std::cout << "\n------Vector" << i << "--------" << std::endl;
    std::cout << v[i].x << std::endl;
    std::cout << v[i].y << std::endl;
    std::cout << v[i].z << std::endl;
  }
}
