/*
 * Binary search tree (BST)
 * NOTES:
 *  - BST is tree that has the following properties:
 *      - the left subtree of a node 'A' should contain all the nodes with lesser value than 'A'
 *      - the right subtree of a node 'A' should contain all the nodes with higher value than 'A'
 *      - the left and right subtree also must be a binary search tree
 *  - in BST, a node at max can have two children (left, right)
 *  - it is like having sorted data in tree
 *
 * BENEFITS:
 *  - complexity of Insert, Delete is log2(n)
 *      - it is log2(n) because it can always have only 2 children
 *  - as it maintains sorted elements you have all advantages of data being sorted
 * 
 * COMPLEXITY:
 * - Search, Insert, Delete Complexity: log2(n)
 * - Space Complexity: O(n)
 * 
 * - more info:
 *      - https://www.youtube.com/watch?v=hD7jsNkgie4&list=PLk6CEY9XxSIBG2Gv6-d1WE3Uxqx94o5B2&index=16
 */

#include <iostream>

struct Node
{
    int m_data;
    Node* m_right;
    Node* m_left;
    Node(int data) : m_data(data), m_right{ nullptr }, m_left{ nullptr } {}
};

Node* insert(Node *head, int data)
{
    if(head == nullptr)
        return new Node(data);
    if(head->m_data > data)
        head->m_left = insert(head->m_left, data);
    else
        head->m_right = insert(head->m_right, data);
    return head; // this is actually not needed, but it is set in order to satisfy return type Node*
}

void printInOrder(Node *head)
{
    if(head == nullptr)
        return;
    printInOrder(head->m_left);
    std::cout << head->m_data << " ";
    printInOrder(head->m_right);
}

int main()
{
    int nodeAmount, val;
    std::cin >> nodeAmount;
    std::cin >> val; // insert value for the head node
    Node* head = insert(nullptr, val); // create head node
    nodeAmount--; // head node is created, decrease amount of nodes
    while(nodeAmount--)
    {
        std::cin >> val;
        insert(head, val);
    }
    printInOrder(head);

    return 0;
}