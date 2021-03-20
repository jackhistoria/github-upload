//9 stellige Zählerummer
//Datum
//Wert 1 5 stellig
//Wert 2 5 stellig
//4 Heizungen
//csv file gespeichert
//Verbrauch berechnen>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>    //std::numeric_limits (input check)
#include <algorithm> //std::sort

void sortVector(std::vector<int> &v);
void printVector(std::vector<int> &v);
void fillVectorWithAllNumbers(std::fstream &file, std::streampos &startPos, std::vector<int> &v);
void truncAndWriteVectorToFile (std::vector<int> &vScores, std::fstream &file, std::string filename);
void openFile(std::fstream &file, std::string filename);
int insert();

int main()
{

  //READ IN STUFF
  std::string filename = "myfile.bin";
  std::fstream file;
  std::vector<int> vScores;
  int input{}, place{};

  openFile(file, filename);
  std::streampos startPos = file.tellg(); //store curser starting position

  fillVectorWithAllNumbers(file, startPos, vScores);

  while(true){
    std::cout <<"Select an option: \n1. Show content\n2. Add new number\n3. Sort Vector\n4. Empty file\n5. Add number to special Place\n6. Remove number from special place\n7. Discard changes and exit\n8. Write and exit"<< std::endl;
    input = insert();

    switch(input){
      case 1:
          std::system("clear");
          printVector(vScores);
        break;
        case 2:
          std::cout << "Enter a new Number to add to the document" << std::endl;
          input = insert();
          vScores.push_back(input);
        break;
        case 3:
          sortVector(vScores);
        break;
        case 4:
          vScores.clear();
        break;
        case 5:
          std::cout <<"Add number:";
          input = insert();
          std::cout << "To place number:";
          place = insert();
          if(place <= vScores.size() && place >= 1)
          vScores.emplace(vScores.begin() + place-1, input);
          else
          std::cout << "Place exceeds vector"<< std::endl;
        break;
        case 6:
          std::cout <<"Remove number on place:";
          place = insert();
          if(place <= vScores.size() && place >= 1)
          vScores.erase(vScores.begin() + place-1);
          else
          std::cout << "Place exceeds vector"<< std::endl;
        break;
        case 7:
          return 0;
        break;
        case 8:
          truncAndWriteVectorToFile(vScores, file, filename);
          return 0;
        break;
      }
  }
}




int insert()
{
  int input{};
  //while (!(std::cin >> data.input) || data.input < 2 || data.input > 8)
  while (!(std::cin >> input))
  {
       std::cin.clear();
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       std::cout << "Invalid Input. Not a Number "<< "\n";
  }

  return input;
}

void truncAndWriteVectorToFile (std::vector<int> &vScores, std::fstream &file, std::string filename)
{
  file.close();
  file.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);

  //write vector data in an array and store it in the file
  int nums[vScores.size()];
  for(int i = 0; i < vScores.size(); ++i)
  {
    nums[i] = vScores[i];
  }

  file.write(reinterpret_cast<char*>(&nums), sizeof(nums));
  // for(int elements: vScores){
  //   file << elements << std::endl;
  // }
  file.close();
}

void openFile(std::fstream &file, std::string filename)
{
  file.open(filename, std::ios::binary | std::ios::in);
  //std::fstream file("myfile.txt", std::ios::in | std::ios::out);
  if(!file.is_open())
  {
    std::cout << "Could not open file!" << std::endl;
  }
}

void fillVectorWithAllNumbers(std::fstream &file, std::streampos &startPos, std::vector<int> &v)
{
file.clear();
file.seekg(startPos);
v.clear();
int number = 3;
while(file.read(reinterpret_cast<char*>(& number), sizeof(number))){
  v.push_back(number);
}
if(!file.eof()){
  std::cout << "Bad score/read--exiting";
}

}

void printVector(std::vector<int> &v)
{
  if(v.empty()){
    std::cout << "Document is empty" << std::endl;
  }else{
  for(int i = 0; i < v.size(); ++i)
    std::cout << "Place Number " << i+1 << ":---"<< v.at(i)<< std::endl;

  // for(int elements: v){
  //   std::cout << "Place Number " << .at(this)<< elements << std::endl;
  // }
  std::cout << "Vector size: " << v.size() << std::endl;
  std::cout << "___________________" << std::endl;
  }
}

void sortVector(std::vector<int> &v)
{
  std::cout << "Sorted order: " << std::endl;
  std::sort(v.begin(), v.end());
}
