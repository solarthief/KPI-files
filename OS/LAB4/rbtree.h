#pragma once
#include <memory>


//Red-black tree
template<typename T>
class rbtree{
private:
  struct _node;


 //interface functions
public:

  bool Insert (T value);
  bool Delete (T value);
  bool Find (T value);
  void PrintTree ();


//private methods
private:
  bool IsRed (_node* node);
  _node* RotateLeft (_node* node);
  _node* RotateRight (_node* node);
  void ColorFlip (_node* node);
  _node* Parent (_node* node);
  _node* Sibling (_node* node);
  _node* Grandparent (_node* node);
  _node* Uncle (_node* node);


//private data
private:
  enum class node_colour{ RED, BLACK };
  struct _node{
    node_colour color;
    T item;
    _node* left, right, parent;
    _node (T val) : color (RED), item (val), left(nullptr),
                    right(nullptr), parent(nullptr) {};
  };

  _node* tree;
};
