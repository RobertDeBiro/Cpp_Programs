#include <iostream>

struct LinkedList
{
    int data;
    LinkedList* next;
};

void printLinkedList(LinkedList* root)
{
    while(root)
    {
        std::cout << root->data << ' ';
        root = root->next;
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    LinkedList *root, *second, *third;

    root = new LinkedList;
    second = new LinkedList;
    third = new LinkedList;

    root->data = 10;
    root->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = nullptr;

    printLinkedList(root);

    std::cout << "*****************************************************\n";
    return 0;
}