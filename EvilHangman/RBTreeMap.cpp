#include "RBTreeMap.h"
using namespace std;
template<class K, class T>
class RBTREE {

    node<K,T>* root;

public:
    RBTREE() : root(nullptr) {}

    node<K,T>* GetRoot(){ return root; }
// Inserting Words to the red black tree
    void addNode(K key,T word) {
        if(root == nullptr){
            root = new node<K,T>;
            root->key = key;
            root->word=word;
            root->parent = nullptr;
            root->black = 0;
            cout << "Word inserted";
        }
        else {
            auto rootnode = GetRoot();
            node<K,T>* newnode = new node<K,T>;
            newnode->key = key;
            newnode->word=word;

            while(rootnode != nullptr){
                if(rootnode->key > key){
                    if(rootnode->left == nullptr){
                        rootnode->left = newnode;
                        newnode->black = 1;
                        newnode->parent = rootnode;
                        cout << "Word inserted";
                         break;
                      }
                    else {
                       rootnode = rootnode->left;
                      }
                } else {
                    if(rootnode->right == nullptr){
                        rootnode->right = newnode;
                        newnode->black = 1;
                        newnode->parent = rootnode;
                        cout << "Word inserted";
                        break;
                      }
                    else {
                        rootnode = rootnode->right;
                       }
                }
            }
            RB_Balance(newnode);
        }
    }
//balancing the red black tree
    void RB_Balance(node<K,T>* z) {
        while(z->parent->black == 1) {
            auto grandparent = z->parent->parent;
            auto uncle = GetRoot();
            if(z->parent == grandparent->left) {
                if(grandparent->right) {
                  uncle = grandparent->right;
                }
                if(uncle->black == 1){
                    z->parent->black = 0;
                    uncle->black = 0;
                    grandparent->black = 1;
                    if(grandparent->key != root->key){
                      z = grandparent;
                     }
                    else {
                       break;
                     }
                }
                else if(z == grandparent->left->right) {
                    LeftRotate(z->parent);
                }
                else {
                    z->parent->black = 0;
                    grandparent->black = 1;
                    RightRotate(grandparent);
                    if(grandparent->key != root->key){
                       z = grandparent;
                     }
                    else {
                       break;
                     }
                }
            }
            else {
                if(grandparent->left) {
                  uncle = grandparent->left;
                }
                if(uncle->black == 1){
                    z->parent->black = 0;
                    uncle->black = 0;
                    grandparent->black = 1;
                    if(grandparent->key != root->key){
                      z = grandparent;
                    }
                    else {
                       break;
                     }
                }
                else if(z == grandparent->right->left){
                    RightRotate(z->parent);
                }
                else {
                    z->parent->black = 0;
                    grandparent->black = 1;
                    LeftRotate(grandparent);
                    if(grandparent->key != root->key){
                      z = grandparent;
                     }
                    else {
                       break;
                      }
                }
            }
        }
        root->black = 0;
    }
    node<K,T>* TreeSearch(string stuff) {
        auto temp = GetRoot();
        if(temp == nullptr) {
          return nullptr;
        }

        while(temp) {
            if(stuff == temp->key){
              return temp;
            }
            else if(stuff < temp->key){
               temp = temp->left;
             }
            else {
               temp = temp->right;
             }
        }
        return nullptr;
    }
/*left rotate*/
    void LeftRotate(node<K,T>* x) {
        node<K,T>* newNode = new node<K,T>;
        if(x->right->left) {
           newNode->right = x->right->left;
          }
        newNode->left = x->left;
        newNode->key = x->key;
        newNode->black = x->black;
        x->key = x->right->key;

        x->left = newNode;
        if(newNode->left){
          newNode->left->parent = newNode;
        }
        if(newNode->right){
          newNode->right->parent = newNode;
        }
        newNode->parent = x;

        if(x->right->right){
          x->right = x->right->right;
        }
        else {
          x->right = nullptr;
         }

        if(x->right){
           x->right->parent = x;
         }
    }
/*right rotate tree*/
    void RightRotate(node<K,T>* y) {
        node<K,T>* newNode = new node<K,T>;
        if(y->left->right){
          newNode->left = y->left->right;
        }
        newNode->right = y->right;
        newNode->key = y->key;
        newNode->black = y->black;

        y->key = y->left->key;
        y->black = y->left->black;

        y->right = newNode;
        if(newNode->left){
          newNode->left->parent = newNode;
         }
        if(newNode->right){
          newNode->right->parent = newNode;
        }
        newNode->parent = y;

        if(y->left->left){
          y->left = y->left->left;
         }
        else {
           y->left = nullptr;
         }

        if(y->left){
          y->left->parent = y;
         }
    }
