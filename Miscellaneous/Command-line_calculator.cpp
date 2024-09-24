#include <iostream>
using namespace std;

int main() {
  double num1, num2;
  char op;

  cout << "Enter the first number: ";
  cin >> num1;
  cout << "Enter the operator (+, -, *, /): ";
  cin >> op;
  cout << "Enter the second number: ";
  cin >> num2;

  if (op == '+') {
    cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
  } else if (op == '-') {
    cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
  } else if (op == '*') {
    cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
  } else if (op == '/') {
    if (num2 == 0) {
      cout << "Cannot divide by zero." << endl;
    } else {
      cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
    }
  } else {
    cout << "Invalid operator." << endl;
  }

  return 0;
}
