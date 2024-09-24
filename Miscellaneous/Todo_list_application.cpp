/*

This code defines a TodoList class with three methods: AddItem, RemoveItem, and PrintList. The AddItem method adds an item to the list, the RemoveItem method removes an item at a specific index, and the PrintList method prints out the entire list of items.

In the main function, it creates an instance of the TodoList class and then enters a loop that repeatedly displays a menu of options to the user and performs the corresponding action based on the user's input. The user can add items, remove items, and print the list, and also can quit the program.

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TodoList {
 private:
  vector<string> list_;

 public:
  void AddItem(string item) {
    list_.push_back(item);
  }

  void RemoveItem(int index) {
    if (index >= 0 && index < list_.size()) {
      list_.erase(list_.begin() + index);
    }
  }

  void PrintList() {
    for (int i = 0; i < list_.size(); i++) {
      cout << i + 1 << ": " << list_[i] << endl;
    }
  }
};

int main() {
  TodoList list;

  while (true) {
    cout << "1. Add item" << endl;
    cout << "2. Remove item" << endl;
    cout << "3. Print list" << endl;
    cout << "4. Quit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
      string item;
      cout << "Enter item: ";
      cin.ignore();
      getline(cin, item);
      list.AddItem(item);
    } else if (choice == 2) {
      int index;
      cout << "Enter index: ";
      cin >> index;
      list.RemoveItem(index - 1);
    } else if (choice == 3) {
      list.PrintList();
    } else if (choice == 4) {
      break;
    }
  }

  return 0;
}
