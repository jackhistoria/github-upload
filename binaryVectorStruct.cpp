//9 stellige Zählerummer
//Datum
//Wert 1 5 stellig
//Wert 2 5 stellig
//4 Heizungen
//csv file gespeichert
//Verbrauch berechnen>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Record {
    int a, b;
    std::string Raum;
    Record(int a, int b, std::string Raum) : a(a), b(b), Raum(Raum) {}
    Record() : a(), b() {}
};

bool output(Record vehicle) {
  std::string plateNumber("12345");
  std::ofstream out(plateNumber, std::ios::binary);
  if (!out)
    return false;

  out.write(reinterpret_cast<char*>(&vehicle.a), sizeof(int));
  out.write(reinterpret_cast<char*>(&vehicle.b), sizeof(int));

  // Write the size of the string.
  int size = vehicle.Raum.size();
  out.write(reinterpret_cast<char*>(&size), sizeof(int));

  // Write the string data.
  const char *p = vehicle.Raum.data();
  size_t size2 = vehicle.Raum.size();
  out.write(p, size2);

  return true;
}

bool input(Record &vehicle) {
  std::string plateNumber("12345");
  std::ifstream in(plateNumber, std::ios::binary);
  if (!in)
    return false;

  in.read(reinterpret_cast<char*>(&vehicle.a), sizeof(int));
  in.read(reinterpret_cast<char*>(&vehicle.b), sizeof(int));

  // Read in the size of the string.
  int size = 0;
  in.read(reinterpret_cast<char*>(&size), sizeof(int));

  // Read in the string.
  char str[1000];
  in.read(str, size);
  vehicle.Raum = str;

  return true;
}

int main() {
    Record v(1, 2, "hello");

    if (!output(v)) {
        std::cerr << "Error writing file.\n";
        return 1;
    }

    Record w;
    if (!input(w)) {
        std::cerr << "Error reading file.\n";
        return 1;
    }

    std::cout << w.a << ", " << w.b << ", " << w.Raum << '\n';

    int pause;
    std::cin >> pause;
    return 0;
}
