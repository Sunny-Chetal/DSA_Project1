#include <iostream>
#include <sstream>
#include <iomanip>
#include "AVLTree.h"

using namespace std;

int main(){
	int n;
	AVLTree t;
	cin >> n;
	cin.ignore(1000, '\n');
	for(int i = 0; i < n; i++) {
		string line;
		getline(cin, line);

		stringstream ss(line);
		string command;
		ss >> command;
		if(command == "insert") {
			string name;
			string ufid;
			ss >> quoted(name);
			ss >> ufid;
			t.insert(ufid, name);
		}

		else if(command == "remove") {
			string ufid;
			if (!(ss >> ufid)) {
				cout << "unsuccessful" << endl;
				continue;

			};
			bool notNum = false;
			for(int k = 0; k < (int)ufid.length(); k++) {
				if (!isdigit(ufid[k])) {
					notNum = true;
				}
			}
			if ((int)ufid.length() != 8) {
				cout << "unsuccessful" << endl;
				continue;
			}
			if (notNum) {
				cout << "unsuccessful" << endl;
			}
			else {
				int id = stoi(ufid);
				t.remove(id);
			}

		}

		else if(command == "search") {
			string parameter;
			ss >> quoted(parameter);
			bool num = false;
			for(int j = 0; j < (int)parameter.length(); j++) {
				if (isdigit(parameter[j])) {
					num = true;
				}
			}
			if(num) {
				int id = stoi(parameter);
				t.search(id);
			}
			else {
				t.search(parameter);
			}
		}
		else if(command == "printInorder") {
			t.printInOrder();
		}
		else if(command == "printPreorder") {
			t.printPreOrder();
		}
		else if(command == "printPostorder") {
			t.printPostOrder();
		}
		else if(command == "printLevelCount") {
			t.printLevelOrder();
		}
		else if(command == "removeInorder") {
			int number;
			ss >> number;
			t.removeInOrder(number);
		}
		else {
			cout << "unsuccessful" << endl;
		}
	}
	return 0;
}