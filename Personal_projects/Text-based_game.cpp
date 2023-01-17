#include <iostream>
using namespace std;

int main() {
  int health = 100;
  int monsterHealth = 100;
  int damage;

  cout << "Welcome to the game! You are being attacked by a monster." << endl;

  while (health > 0 && monsterHealth > 0) {
    cout << "Your health: " << health << endl;
    cout << "Monster's health: " << monsterHealth << endl;
    cout << "Enter the amount of damage you want to deal: ";
    cin >> damage;

    monsterHealth -= damage;
    cout << "You dealt " << damage << " damage to the monster." << endl;

    if (monsterHealth <= 0) {
      cout << "You defeated the monster!" << endl;
      break;
    }

    damage = rand() % 20 + 1;
    health -= damage;
    cout << "The monster dealt " << damage << " damage to you." << endl;
  }

  if (health <= 0) {
    cout << "You died. Game over." << endl;
  }

  return 0;
}
