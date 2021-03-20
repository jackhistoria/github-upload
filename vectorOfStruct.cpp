//9 stellige Zählerummer
//Datum
//Wert 1 5 stellig
//Wert 2 5 stellig
//4 Heizungen
//csv file gespeichert
//Verbrauch berechnen>#include <iostream>
//https://stackoverflow.com/questions/31212680/c-how-to-write-several-simple-vectors-to-a-binary-file-in-one-shot
//https://stackoverflow.com/questions/8067338/vector-of-structs-initialization

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> //std::sort
#include <limits>    //std::numeric_limits (input check)

struct heaterReading
{
  int YYYYMM;
  int counterNum1, room1A, room1B;
  int counterNum2, room2A, room2B;
  int counterNum3, room3A, room3B;
  int counterNum4, room4A, room4B;
};

void printDatabase(std::vector<heaterReading> &vHeaterReading);
void write(std::fstream &file, std::string &fileName, std::vector<heaterReading> &vHeaterReading);
void read(std::fstream &file, std::string &fileName, std::vector<heaterReading> &vHeaterReading);
int insert();

int main()
{
  std::string fileName = "counterReading.bin";
  std::vector<heaterReading> vHeaterReading;
  std::fstream file(fileName, std::ios::binary);
  int input = 0, place = 0;
  read(file, fileName, vHeaterReading); //Load entry at program start

  std::system("cp counterReading.bin counterReadingAutoBACKUP.bin");
  std::cout << "Backup created" << std::endl;


  while(true){
    std::cout << "Select an option:\n 1. Print all Data\n 2. Read in\n 3. Write out\n 4. Add Data\n 5. Sort data\n 6. Delete all data\n 7. Remove entry\n 8. Create manual Backup\n 9. Exit" << std::endl;
    input = insert();
    switch(input){
      case 1:
        std::system("clear");
        printDatabase(vHeaterReading);
      break;
      case 2:
        read(file, fileName, vHeaterReading);
      break;
      case 3:
        write(file, fileName, vHeaterReading);
      break;
      case 4:
        std::cout <<"Add number:";
        input = insert();
        vHeaterReading.push_back({input,1111,11,12,2222,21,22,3333,31,32,4444,41,42});
        //vHeaterReading.push_back({202001,1111,11,12,2222,21,22,3333,31,32,4444,41,42});
      break;
      case 5:
         std::cout << "Sorted order: " << std::endl;
         std::sort(vHeaterReading.begin(), vHeaterReading.end(), []
         (const heaterReading& lhs, const heaterReading& rhs){return lhs.YYYYMM < rhs.YYYYMM;});
      break;
      case 6:
       vHeaterReading.clear();
      break;
      case 7:
       std::cout <<"Remove number on place:";
       place = insert();
        if(place <= vHeaterReading.size() && place >= 1)
       vHeaterReading.erase(vHeaterReading.begin() + place-1);
        else
        std::cout << "Place exceeds vector"<< std::endl;
      break;
      case 8:
        std::system("cp counterReading.bin counterReadingManualBACKUP.bin");
        std::cout << "Backup created" << std::endl;
      break;
      case 9:
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

void read(std::fstream &file, std::string &fileName, std::vector<heaterReading> &vHeaterReading)
{
  file.open(fileName, std::ios::binary | std::ios::in );
   if(!file)
     std::cout << "Something went wrong" << std::endl;

  int size = 0;
  //read vector size
  file.read(reinterpret_cast<char*>(&size), sizeof(size));
  vHeaterReading.resize(size); //resize vector for necessary space
  //read vector data
  file.read(reinterpret_cast<char*>(vHeaterReading.data()), sizeof(vHeaterReading[0])*size);
  file.close();
}

void write(std::fstream &file, std::string &fileName, std::vector<heaterReading> &vHeaterReading)
{
  file.open(fileName, std::ios::binary | std::ios::out);
   if(!file)
     std::cout << "Something went wrong" << std::endl;

  int count = vHeaterReading.size();
  //store vector size
  file.write(reinterpret_cast<const char*>(&count), sizeof(count));
  //stor vector data
  file.write(reinterpret_cast<const char*>(vHeaterReading.data()), sizeof(vHeaterReading[0])*count);
  file.close();
}

void printDatabase(std::vector<heaterReading> &vHeaterReading)
{
  for(int i = 0; i < vHeaterReading.size(); ++i){
    std::cout << "\n\nDate YYYYMM: " << vHeaterReading[i].YYYYMM << std::endl;
    std::cout << "Counter Number 1: " << vHeaterReading[i].counterNum1<< std::endl;
    std::cout << "Room 1a: " << vHeaterReading[i].room1A << std::endl;
    std::cout << "Room 1b: " << vHeaterReading[i].room1B << std::endl;
    std::cout << "Counter Number 2: " << vHeaterReading[i].counterNum2<< std::endl;
    std::cout << "Room 2a: " << vHeaterReading[i].room2A << std::endl;
    std::cout << "Room 2b: " << vHeaterReading[i].room2B << std::endl;
    std::cout << "Counter Number 3: " << vHeaterReading[i].counterNum3<< std::endl;
    std::cout << "Room 3a: " << vHeaterReading[i].room3A << std::endl;
    std::cout << "Room 3b: " << vHeaterReading[i].room3B << std::endl;
    std::cout << "Counter Number 4: " << vHeaterReading[i].counterNum4<< std::endl;
    std::cout << "Room 4a: " << vHeaterReading[i].room4A << std::endl;
    std::cout << "Room 4b: " << vHeaterReading[i].room4B << std::endl;
    std::cout << "_________________" << std::endl;
  }
}
