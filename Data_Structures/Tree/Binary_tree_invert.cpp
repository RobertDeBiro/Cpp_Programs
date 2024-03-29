#include <iostream>
#include <algorithm>

// struct Node implements "Binary tree" abstract data structure
//  - implemented using linked list
//  - node in binary tree contains:
//      - data
//      - pointer to left and right node
struct Node
{
    int m_data;
    Node *m_left, *m_right;
    Node(int data) : m_data{ data }, m_left{ nullptr }, m_right{ nullptr } {}
};

// Depth first search
//  - "depth first search" algorithm:
//     1) prints furthermost left path to the bottom of the tree
//        and then goes to the top step by step and prints other nodes
//     2) repeats the same thing for right side
void print_dfs(Node* root)
{
    if(root == nullptr)
        return;
    std::cout << root->m_data << " ";
    print_dfs(root->m_left);
    print_dfs(root->m_right);
}

void invertBinary(Node* root)
{
    if(root == nullptr)
        return;
    std::swap(root->m_left, root->m_right);
    invertBinary(root->m_left);
    invertBinary(root->m_right);
}

int main()
{
    std::cout << "*****************************************************\n";

    // Constructing nodes
    //  - their are constructed in path that will be used for printing them
    Node* root = new Node(1);
    Node* left = new Node(2);
    Node* left_l = new Node(3);
    Node* left_ll = new Node(4);
    Node* left_lr = new Node(5);
    Node* left_r = new Node(6);
    Node* left_rl = new Node(7);
    Node* left_rr = new Node(8);
    Node* right = new Node(9);
    Node* right_l = new Node(10);
    Node* right_ll = new Node(11);
    Node* right_lr = new Node(12);
    Node* right_r = new Node(13);
    Node* right_rl = new Node(14);
    Node* right_rr = new Node(15);

    // Connect root node with its children
    root->m_left = left;
    root->m_right = right;
    // Connect left node with its children
    left->m_left = left_l;
    left->m_right = left_r;
    // Connect left_l node with its children
    left_l->m_left = left_ll;
    left_l->m_right = left_lr;
    // Connect left_r node with its children
    left_r->m_left = left_rl;
    left_r->m_right = left_rr;
    // Connect right node with its children
    right->m_left = right_l;
    right->m_right = right_r;
    // Connect right_l node with its children
    right_l->m_left = right_ll;
    right_l->m_right = right_lr;
    // Connect right_r node with its children
    right_r->m_left = right_rl;
    right_r->m_right = right_rr;

    /*
    Printing tree:
       - tree should look like this:
                            1
                          /   \ 
                         /     \ 
                        /       \ 
                       /         \ 
                      /           \ 
                     /             \ 
                    /               \ 
                   /                 \ 
                  /                   \ 
                 /                     \ 
                2                       9
              /   \                   /   \ 
             /     \                 /     \ 
            /       \               /       \ 
           /         \             /         \ 
          3           6           10         13
        /  \         / \         / \         / \ 
       /    \       /   \       /   \       /   \ 
      /      \     /     \     /     \     /     \ 
     4        5   7       8   11      12  14     15
    
    Printout should look like this:
          1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    */
    std::cout << "Binary tree: \n";
    print_dfs(root);
    std::cout << '\n';

    invertBinary(root);

    /*
    Printing inverted tree:
       - tree should look like this:
                            1
                          /   \ 
                         /     \ 
                        /       \ 
                       /         \ 
                      /           \ 
                     /             \ 
                    /               \ 
                   /                 \ 
                  /                   \ 
                 /                     \ 
                9                       2
              /   \                   /   \ 
             /     \                 /     \ 
            /       \               /       \ 
           /         \             /         \ 
         13           10          6           3
        /  \         / \         / \         / \ 
       /    \       /   \       /   \       /   \ 
      /      \     /     \     /     \     /     \ 
     15      14   12     11   8       7   5       4
    
    Printout should look like this:
          1 9 13 15 14 10 12 11 2 6 6 7 3 5 4
    */
    std::cout << "Inverted binary tree: \n";
    print_dfs(root);
    std::cout << '\n';

    // Deleting nodes
    delete root;
    delete left;
    delete left_l;
    delete left_ll;
    delete left_lr;
    delete left_r;
    delete left_rl;
    delete left_rr;
    delete right;
    delete right_l;
    delete right_ll;
    delete right_lr;
    delete right_r;
    delete right_rl;
    delete right_rr;

    std::cout << "*****************************************************\n";
    return 0;
}