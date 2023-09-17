

/*Write a program that uses a map to assign “codes” to each letter of the alphabet.For
example :
map<char, char> codes =
{ {'A', '%'}, {'a', '9'}, {'B', '@'}, {'b', '#'}, etc ... };
Using this example, the letter ‘A’ would be assigned the symbol%, the letter ‘a’ would
be assigned the number 9, the letter ‘B’ would be assigned the symbol @, and so forth.
The program should open a specified text file, read its contents, then use the map to
write an encrypted version of the file’s contents to a second file. Each character in
the second file should contain the code for the corresponding character in the first
file. */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <set>
#include<fstream>
using namespace std;

unordered_map<char, char> createKey();
string readFile(string);
string encoder(string&, unordered_map<char, char>);
unordered_map<char, char> createReverseKey(unordered_map<char, char>);

int main() {
	unordered_map<char, char> keyMap;
	unordered_map<char, char> reverseMap;
	string uncoded;
	string encoded;
	string decoded;
	srand(time(0));
	keyMap = createKey();
	uncoded = readFile("content.txt");
	encoded = encoder(uncoded, keyMap);
	cout << encoded << endl;
	ofstream storer;
	storer.open("encodedText.txt");
	storer << encoded << endl;
	storer.close();
	reverseMap = createReverseKey(keyMap);
	decoded = encoder(encoded, reverseMap);
	storer.open("decodedText.txt");
	storer << decoded << endl;
	storer.close();
	cout << "github change test" << endl; 
	
}

unordered_map<char, char> createKey() {
	unordered_map<char, char> charMap;
	char storage;
	set<char> checker;
	const string KEYS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,'.!?~!@#$%^&*();: ";
	for (char element : KEYS) {
		storage = rand() % (137 - 41) + 41;
		while (checker.find(storage) != checker.end()) {
			storage = rand() % (137 - 41) + 41;
		}
		charMap[element] = storage;
		checker.insert(storage);
	}
	return charMap;
}

string readFile(string f) {
	ifstream file;
	string storage;
	string returned;
	file.open(f);
	if (!file) {
		cout << "Error. File was not opened" << endl;
		exit(-1);
	}
	getline(file, storage);
	
	while (file) {
		returned += storage;
		getline(file, storage);
	}
	file.close();
	return returned;
}
string encoder(string& e, unordered_map<char, char> k) {
	string s;
	for (char element : e) {
		s += k[element];
	}
	return s;
}
unordered_map<char, char> createReverseKey(unordered_map<char, char> r) {
	unordered_map<char, char> reverseMap;
	char first;
	for (pair<char, char> element : r) {
		first = element.second;
		reverseMap[first] = element.first;
	}
	return reverseMap;
}