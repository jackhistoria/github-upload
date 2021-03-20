#include <iostream>
#include <fstream>
#include <vector>

#define FILENAME "channels.txt"

int main()
{
  std::fstream infile;
  std::vector<double> xChannel;

  xChannel.push_back(123);
  xChannel.push_back(456);

  //Print vector
  for(double element : xChannel)
    std::cout << element << std::endl;

  //Write data to file for testing purpose
  infile.open(FILENAME, std::ios::out);
  if(!infile.is_open())
    std::cout << "Could not open file!" << std::endl;

  //write elements to file with for:each loop
  for(double element : xChannel)
    infile << element << std::endl;

  //Close file
  infile.close();
  //Delete vector items for proof of conecpt
  xChannel.clear();

  //Read data back into vector from file
  infile.open(FILENAME, std::ios::in);
    if(!infile.is_open())
      std::cout << "Couldnot open file!" << std::endl;

  //Read data back to vector
  double value{};
  while(infile >> value){
    xChannel.push_back(value);
  }
  //Close file
  infile.close();

  //Print vector
  for(double element : xChannel)
    std::cout << element << std::endl;

  std::cin.get();
  return 0;
}
