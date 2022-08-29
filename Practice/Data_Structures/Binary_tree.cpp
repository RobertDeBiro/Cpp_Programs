/*
 * Binary tree:
 *  - a tree whose nodes can have at most two children is called binary tree
 *  - as there can only be two children of a node we call them left and right child
 * 
 * Types of binary tree:
 *  1) FULL BINARY TREE / STRICTLY BINARY TREE
 *      - every node must have two children, except the leaf nodes
 *  2) INCOMPLETE BINARY TREE / ALMOST COMPLETE BINARY TREE
 *      - every node must have two children's in all levels except last and second last level and should be filled from left to right
 *  3) COMPLETE BINARY TREE / PERFECT BINARY TREE
 *      - every node must have two children's in all the levels (Each level there should be 2^L where L is level)
 *  4) LEFT SKEWED BINARY TREE
 *      - every node should have only left children.
 *  5) RIGHT SKEWED BINARY TREE
 *      - every node should have only right children.
 */

#include <iostream>

using namespace std;

// Linked list representation of binary tree
struct Binary
{
    int m_data;
    Binary *m_left, *m_right;
    Binary(int data) : m_data{ data }, m_left{ nullptr }, m_right{ nullptr }
    {
    }
};

// Depth first search
//  - "depth first search" algorithm:
//     1) prints furthermost left path to the bottom of the tree
//        and then goes to the top step by step and prints other nodes
//     2) repeats the same thing for right side
void print_dfs(Binary* root)
{
    if(root == nullptr)
        return;
    cout << root->m_data << " ";
    print_dfs(root->m_left);
    print_dfs(root->m_right);
}

int main()
{
    // Constructing nodes
    //  - their are constructed in path that will be used for printing them
    Binary* root = new Binary(1);
    Binary* left = new Binary(2);
    Binary* left_l = new Binary(3);
    Binary* left_ll = new Binary(4);
    Binary* left_lr = new Binary(5);
    Binary* left_r = new Binary(6);
    Binary* left_rl = new Binary(7);
    Binary* left_rr = new Binary(8);
    Binary* right = new Binary(9);
    Binary* right_l = new Binary(10);
    Binary* right_ll = new Binary(11);
    Binary* right_lr = new Binary(12);
    Binary* right_r = new Binary(13);
    Binary* right_rl = new Binary(14);
    Binary* right_rr = new Binary(15);

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
       - tree looks like this:
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
    print_dfs(root);

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

    return 0;
}