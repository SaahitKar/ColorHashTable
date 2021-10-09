/*
 * SSK190013
 * Saahit Karumuri
 */

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <cstring>
#include <cmath>
#include <limits>

using namespace std;

class ColorEntry {
public:
	std::string name;
	int red;
	int green;
	int blue;
	bool isActive;
	ColorEntry *next;
	// Default Constructor
	ColorEntry() {
		name = " ";
		red = 0, green = 0, blue = 0;
		isActive = true;
		next = nullptr;
	}
	//Overloaded Constructor
	ColorEntry(std::string n, int r, int g, int b) {
		name = n;
		red = r, green = g, blue = b;
		isActive = true;
		next = nullptr;
	}
	// Get & Set for Name
	std::string getName() {
		return name;
	}
	void setGreen(std::string n) {
		name = n;
	}
	// Get & Set for Red
	int getRed() {
		return red;
	}
	void setRed(int r) {
		red = r;
	}
	// Get & Set for Green
	int getGreen() {
		return green;
	}
	void setGreen(int g) {
		green = g;
	}
	// Get & Set for Blue
	int getBlue() {
		return blue;
	}
	void setBlue(int b) {
		blue = b;
	}
	// Get & Set for Active
	bool getActive() {
		return isActive;
	}
	void setActive(bool a) {
		isActive = a;
	}
};

class NameHash {
public:
	ColorEntry **storage;
	int storageSize;
	int numItems;
	int loadCapacity;
	int hash(std::string name);
	void insert(ColorEntry *data);
	ColorEntry* search(std::string name);
	void deleteColor(ColorEntry *data);
	NameHash* resize(int sizeNum);
	bool isPrime(int num);
	NameHash(int size);
	NameHash();
};

//Overloaded Constructor
NameHash::NameHash(int size) {
	storageSize = size;
	numItems = 0;
	storage = new ColorEntry*[size];
	loadCapacity = 1;
	//Set each value in the array as nullptr
	for (int i = 0; i < size; i++) {
		storage[i] = nullptr;
	}
}

//Default Constructor
NameHash::NameHash() {
	storageSize = 0;
	numItems = 0;
	loadCapacity = 1;
	storage = new ColorEntry*[1];
}

int NameHash::hash(std::string name) {
	int init = 5381;
	int total = init;
	//Loop through each letter to create the hash value
	for (long unsigned int i = 0; i < name.length(); i++) {
		total = total * 33 + (int) name[i];
		total = total % storageSize;
	}
	return total % storageSize;
}

void NameHash::insert(ColorEntry *data) {
	int hashValue = hash(data->getName()), tempLoad = 0;
	numItems++;
	ColorEntry *loc = storage[hashValue];
	//check if the color at hashvalue is null
	if (loc == nullptr) {
		//replace the ptr at loc for the ColorEntry
		ColorEntry *temp = new ColorEntry();
		tempLoad++;
		temp = data;
		//set next ptr to nullptr
		temp->next = nullptr;
		storage[hashValue] = temp;
		//check if the next value @ hashValue is null
	} else if (loc->next == nullptr) {
		ColorEntry *temp = new ColorEntry();
		temp = data;
		tempLoad++;
		temp->next = storage[hashValue];
		storage[hashValue] = temp;
		//check if the loc at has multiple values at that value
	} else {
		//loop through each value to find the ending value
		while (loc->next != nullptr) {
			tempLoad++;
			loc = loc->next;
		}
		//set the value @ hashvalue equal to the data
		ColorEntry *temp = new ColorEntry();
		temp = data;
		temp->next = storage[hashValue];
		storage[hashValue] = temp;
	}
	//find the loadCapacity
	loc = storage[hashValue];
	//loop through each value of @ storage & add to the loadCapacity
	while (loc != nullptr) {
		if (loc != nullptr) {
			tempLoad++;
		}
		loc = loc->next;
	}
	loadCapacity = std::max(tempLoad, 1);
}
//
ColorEntry* NameHash::search(std::string name) {
	ColorEntry *nullp = nullptr;
	for (int i = 0; i < storageSize; i++) {
		ColorEntry *loc = storage[i];
		//find the name @ i & if equal
		while (loc != nullptr) {
			if (loc->getName() == name) {
				//return the pointer
				return loc;
			}
			loc = loc->next;
		}
	}
	//return nullptr
	return nullp;
}

NameHash* NameHash::resize(int sizeNum) {
	int temp = sizeNum * 2;
	//check for the the temp is prime
	while (isPrime(temp) == false) {
		temp++;
	}
	//
	//return a new sized NameHash object
	NameHash *newSized = new NameHash(temp);
	return newSized;
}

void NameHash::deleteColor(ColorEntry *data) {
	//delete value
	int hashValue = hash(data->getName());
	storage[hashValue] = nullptr;
}

bool NameHash::isPrime(int num) {
	//code to check if the number is prime
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			//when a value is divisible, it's false
			return false;
		}
	}
	//or it's true
	return true;
}

class ColorHash {
public:
	int storageSize;
	ColorEntry **storage;
	int numCollision;
	int sizeNum;
	void insert(ColorEntry *data);
	int hash(int r, int g, int b);
	ColorEntry* search(int r, int g, int b);
	void deleteColor(int key);
	void lazyDelete(ColorEntry *data);
	ColorHash* resize(int sizeNum);
	bool isPrime(int num);
	ColorHash(int size);
	ColorHash();
};
//Overloaded Constructor
ColorHash::ColorHash(int size) {
	storageSize = size;
	storage = new ColorEntry*[size];
	numCollision = 0, sizeNum = 0;
	//
	for (int i = 0; i < size; i++) {
		storage[i] = nullptr;
	}
}
//Default Constructor
ColorHash::ColorHash() {
	storageSize = 0;
	storage = new ColorEntry*[0];
	numCollision = 0, sizeNum = 0;
}

int ColorHash::hash(int r, int g, int b) {
	//use a double hash function to find the hashValue
	int h1 = ((65536 * r) + (256 * g) + (b)) % 263;
	int h2 = 73 - (r + g + b) % 73;
	int hashValue = (h1 + numCollision * h2) % storageSize;
	if (storage[hashValue] != nullptr) {
		//if collision occurs, run the hashFunction
		//with num Collision
		numCollision++;
		hashValue = (h1 + numCollision * h2) % storageSize;
	}
	//return the hashValue
	return hashValue;
}

ColorEntry* ColorHash::search(int r, int g, int b) {
	for (long unsigned int i = 0; i < (long unsigned) storageSize; i++) {
		if (storage[i] == nullptr) {
		}
		//if there's a value at storage
		if (storage[i] != nullptr) {
			//if the RGB value is equal to the desired RGB value of the color
			if (storage[i]->getRed() == r && storage[i]->getGreen() == g
					&& storage[i]->getBlue() == b) {
				//return the ColorEntry Object
				return (storage[i]);
			}
		}
	}
	//return a nullptr object
	ColorEntry *loc = new ColorEntry();
	return (loc);
}

void ColorHash::insert(ColorEntry *data) {
	//get the hash value
	int hashValue = hash(data->getRed(), data->getGreen(), data->getBlue());
	//if hashValue is empty
	if (storage[hashValue] == nullptr) {
		//insert it at that value
		storage[hashValue] = data;
		sizeNum++;
		//if hashvalue isn't empty
	} else {
		numCollision++;
		//calculate a new hashvalue
		hashValue = hash(data->getRed(), data->getGreen(), data->getBlue());
		while (storage[hashValue] != nullptr) {
			//while the color is empty, loop through until an empty slot is reached
			numCollision++;
			hashValue = hash(data->getRed(), data->getGreen(), data->getBlue());
			//when the slot is empty, stop the loop
			if (storage[hashValue] == nullptr) {
				break;
			}
		}
		//insert it at that value
		storage[hashValue] = data;
		sizeNum++;
	}
	//reset the value of numCollion
	numCollision = 1;
}

ColorHash* ColorHash::resize(int sizeN) {
	//check if the size is prime
	int temp = sizeN * 2;
	while (isPrime(temp) == false) {
		temp++;
	}
	//return a new sized color hash object
	ColorHash *newSized = new ColorHash(temp);
	return newSized;
}

void ColorHash::lazyDelete(ColorEntry *data) {
	//find the hash value
	int hashValue = hash(data->getRed(), data->getGreen(), data->getBlue());
	//lazy delete the value at that slot
	if (storage[hashValue]->getName() != " ") {
		data->setActive(false);
	}
}

bool ColorHash::isPrime(int num) {
	//code to check if the number is prime
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			//when a value is divisible, it's false
			return false;
		}
	}
	//or it's true
	return true;
}

int main() {
	int option = 0;
	string fileName = "";
	string colorName = "";
	vector<ColorEntry*> c;
	int r = -1, g = -1, b = -1;
	//
	NameHash *nhash = new NameHash(83);
	ColorHash *chash = new ColorHash(83);
	//loop through until exit is entered
	while (option != 4) {
		//print main menu
		cout << "Main Menu: " << endl << "1: Load File " << endl
				<< "2: Search by Name " << endl << "3: Search by Color" << endl
				<< "4: Exit " << endl << endl;
		cout << "Enter option >>> " << endl;
		cin >> option;
		//validate if number is entered
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter option >>> " << endl;
			cin >> option;
			if (!cin.fail()) {
				break;
			}
		}
		//validate if possible option is entered
		while (option != 1 && option != 2 && option != 3 && option != 4) {
			cout << "Enter option >>> " << endl;
			cin >> option;
		}
		//exit the program if exit option is entered
		if (option == 4) {
			cout << endl << "Program Exited.";
			break;
		}
		//load file is entered
		if (option == 1) {
			nhash = new NameHash(83);
			chash = new ColorHash(83);
			//enter the name of the file
			cout << "Name of File >>> " << endl;
			cin >> fileName;
			ifstream inputFile;
			inputFile.open(fileName.c_str());
			//clear through the name hash object
			for (int i = 0; i < nhash->storageSize; i++) {
				nhash->storage[i] = nullptr;
			}
			nhash->numItems = 0;
			nhash->loadCapacity = 1;
			nhash->storageSize = 83;
			//create temporary name & color hash objects
			NameHash *nhashN = new NameHash();
			ColorHash *chashN = new ColorHash();
			nhashN = new NameHash(83);
			chashN = new ColorHash(83);
			//clear through the name hash temp object
			for (int i = 0; i < nhashN->storageSize; i++) {
				nhashN->storage[i] = nullptr;
			}
			nhashN->numItems = 0;
			nhashN->loadCapacity = 1;
			nhashN->storageSize = 83;
			//
			string line = "";
			int stoR = 0, stoG = 0, stoB = 0, iter = 0;
			string breakLine = "";
			//loop through until the end of the file is reached
			while (!(inputFile.eof())) {
				getline(inputFile, line);
				iter++;
			}
			inputFile.clear();
			inputFile.seekg(0);
			//calculate the load factor for the probing hash table
			double loadF = ((double) iter / (double) chashN->storageSize) * 100;
			while (loadF > 60) {
				chashN = chashN->resize(chashN->storageSize);
				loadF = ((double) iter / (double) chashN->storageSize) * 100;
			}
			while (!(inputFile.eof())) {
				//split the string into multiple segments
				getline(inputFile, line);
				istringstream stream(line);
				//create a vector to get each value
				vector<string> stringtoColor;
				for (string s; stream >> s;) {
					stringtoColor.push_back(s);
				}
				//translate RGB from string to int
				stoR = stoi(stringtoColor.at(1));
				stoG = stoi(stringtoColor.at(2));
				stoB = stoi(stringtoColor.at(3));
				nhashN->numItems++;
				//Color object with the value of the name & RGB value
				ColorEntry *obj = new ColorEntry(stringtoColor.at(0), stoR,
						stoG, stoB);
				//insert into both hash tables
				nhashN->insert(obj);
				chashN->insert(obj);
				c.push_back(obj);
			}
			int it = nhashN->storageSize;
			//loop until the load Capacity < 4
			while (nhashN->loadCapacity > 4) {
				//create a temp name hash pointer
				NameHash *ptrN = nhashN->resize(it);
				it = ptrN->storageSize;
				//insert the colors into the temp name hash
				for (long unsigned int i = 0; i < c.size(); i++) {
					ColorEntry *ptr = c.at(i);
					ptrN->insert(ptr);
				}
				nhashN = ptrN;
				int v = 0;
				//loop through each object at the array
				for (int i = 0; i < nhashN->storageSize; i++) {
					ColorEntry *loc = nhashN->storage[i];
					v = 0;
					while (loc != nullptr) {
						v++;
						loc = loc->next;
					}
					//calculate the new load capacity after resize
					nhashN->loadCapacity = max(nhashN->loadCapacity, v);
				}
			}
			//set the main name hash to the temp name hash
			nhash = nhashN;
			chash = chashN;
			loadF = ((double) chashN->sizeNum / (double) chashN->storageSize)
					* 100;
			//Display Report
			cout << endl << "*****************************************" << endl;
			cout << "Load Complete." << endl << endl;
			//Display Report for the Name Hash Table
			cout << "Number of Items in Name Hash Table >>> "
					<< nhashN->numItems << endl;
			cout << "Size of Name Hash Table >>> " << nhashN->storageSize
					<< endl;
			cout << "Load Factor >>> " << nhashN->loadCapacity << endl << endl;
			//Display Report for the Color Hash Table
			cout << "Number of Items in Color Hash Table >>> "
					<< chashN->sizeNum << endl;
			cout << "Size of Color Hash Table >>> " << chashN->storageSize
					<< endl;
			cout << "Load Factor >>> " << loadF << "%" << endl << endl;
			nhashN = new NameHash(83);
			c.clear();
			//Search by the name of the color
		} else if (option == 2) {
			cout << "Name of Color >>> " << endl;
			cin >> colorName;
			//search for the color object
			ColorEntry *loc = nhash->search(colorName);
			//check if the color is equal to the name desired
			if (loc != nullptr && loc->getName() == colorName) {
				//print all of the values of the color
				cout << endl << "Name: " << loc->getName() << endl << "Red: "
						<< loc->getRed() << endl << "Green: " << loc->getGreen()
						<< endl << "Blue: " << loc->getBlue() << endl << endl;
			} else {
				//print out the invalid color object
				cout << endl << "Color Can't Be Found." << endl << endl;
			}
			//Look Up Color by Color Name
		} else if (option == 3) {
			//loop until valid red number is entered
			while (r < 0 || r > 255) {
				//prompt for red value
				cout << "Enter Red Value >>> " << endl;
				cin >> r;
				//if not a number is entered, loop until valid
				while (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					//enter a red value
					cout << "Enter Red Value >>> " << endl;
					cin >> r;
					//if cin is valid, stop the loop
					if (!cin.fail()) {
						break;
					}
				}
			}
			//loop until valid green number is entered
			while (g < 0 || g > 255) {
				//prompt for green value
				cout << "Enter Green Value >>> " << endl;
				cin >> g;
				//if not a number is entered, loop until valid
				while (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					//enter a green value
					cout << "Enter Green Value >>> " << endl;
					cin >> g;
					//if cin is valid, stop the loop
					if (!cin.fail()) {
						break;
					}
				}
			}
			//loop until valid blue number is entered
			while (b < 0 || b > 255) {
				//prompt for blue value
				cout << "Enter Blue Value >>> " << endl;
				cin >> b;
				//if not a number is entered, loop until valid
				while (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					//enter a green value
					cout << "Enter Blue Value >>> " << endl;
					cin >> b;
					//if cin is valid, stop the loop
					if (!cin.fail()) {
						break;
					}
				}
			}
			//search for the color object
			ColorEntry *loc = chash->search(r, g, b);
			//check if the color is equal to the RGB value
			if (loc != nullptr && loc->getName() != " ") {
				//print all of the values of the color
				cout << endl << "Name: " << loc->getName() << endl << "Red: "
						<< loc->getRed() << endl << "Green: " << loc->getGreen()
						<< endl << "Blue: " << loc->getBlue() << endl << endl;
			} else {
				//print out the invalid color object
				cout << endl << "Color Can't Be Found." << endl << endl;
			}
			//reset the rgb input ints
			r = -1, g = -1, b = -1;
		}
	}
	return 0;
}
