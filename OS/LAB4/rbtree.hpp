#pragma once
#include <memory>


//Red-black tree
template<typename T>
class rbtree{
private:
  struct _node;


 //interface functions
public:
  rbtree<T> () = delete;
  rbtree<T> (T val): nil(new _node){
    tree = new _node (val);
    tree->left = nil;
    tree->right = nil;
    tree->parent = nil;
    tree->color = NodeColor::BLACK;
  }


  bool Insert (T value){
    _node* node = new _node (value);
    InsertRecursive (tree, node);
    FixInsert (node);
    return true;
  }

  bool Delete (T value);
  bool Find (T value);
  void PrintTree (){
    PrintNode (tree, 0);
  }


//private methods
private:
  void InsertRecursive (_node* root, _node* node){
    if (root != nil){
      if (root->value <= node->value){
        if (root->right != nil){
          InsertRecursive (root->right, node);
          return;
        } else
          root->right = node;
      } else{
        if (root->left != nil){
          InsertRecursive (root->left, node);
          return;
        } else
          root->left = node;
      }
    }
    node->parent = root;
    node->left = nil;
    node->right = nil;
    node->color = NodeColor::RED;
  }


  void FixInsert (_node* node){
    while (node->parent->color == NodeColor::RED){
      if (node->parent == node->parent->parent->left){
        _node* tmp_node = node->parent->parent->right;
        if (tmp_node->color == NodeColor::RED){
          node->parent->color = NodeColor::BLACK;
          tmp_node->color = NodeColor::BLACK;
          node->parent->parent->color = NodeColor::RED;
          node = node->parent->parent;
        }
        else{
          if (node == node->parent->right){
            node = node->parent;
            RotateLeft (node);
          }
          node->parent->color = NodeColor::BLACK;
          node->parent->parent->color = NodeColor::RED;
          RotateRight (node->parent->parent);
        } 
      } else{
        _node* tmp_node = node->parent->parent->left;
        if (tmp_node->color == NodeColor::RED){
          node->parent->color = NodeColor::BLACK;
          tmp_node->color = NodeColor::BLACK;
          node->parent->parent->color = NodeColor::RED;
          node = node->parent->parent;
        } else{
          if (node == node->parent->left){
            node = node->parent;
            RotateRight (node);
          }
          node->parent->color = NodeColor::BLACK;
          node->parent->parent->color = NodeColor::RED;
          RotateLeft (node->parent->parent);
        }


      }
       
    }

    tree->color = NodeColor::BLACK;






    ////Case 1: node is root node 
    //if (Parent (node) == nullptr){
    //  node->color = NodeColor::BLACK;
    //} 
    ////Case 2: node`s parent is BLACK
    //else if (Parent (node)->color == NodeColor::BLACK){
    //  return;
    //}
    ////Case 3: node`s uncle is RED
    //else if (Uncle (node)->color == NodeColor::RED){
    //  Parent (node)->color = NodeColor::BLACK;
    //  Uncle (node)->color = NodeColor::BLACK;
    //  Grandparent (node)->color = NodeColor::RED;
    //  FixInsert (Grandparent(node));
    //}
    ////Case 4: node`s uncle is BLACK
    //else{
    //  _node* p = Parent (node);
    //  _node* g = Grandparent (node);

    //  if (node == g->left->right){
    //    RotateLeft (p);
    //    node = node->left;
    //  } else if (node==g->right->left){
    //    RotateRight (p);
    //    node = node->right;
    //  }

    //  p = Parent (node);
    //  g = Grandparent (node);

    //  if (node == p->left)
    //    RotateRight (g);
    //  else
    //    RotateLeft (g);

    //  p->color = NodeColor::BLACK;
    //  g->color = NodeColor::RED;
    //} 

  }


  void PrintNode (_node* node, unsigned int node_level){
    if (node != nil){
      auto level_buf = node_level;
      while (level_buf--){
        std::cout << "++";
      }
      std::cout << node->value << std::endl;
      PrintNode (node->left, node_level + 1);
      PrintNode (node->right, node_level + 1);
    }
  }


  inline bool IsRed (_node* node){
    return node->color == RED;
  }


  void RotateLeft (_node* node){
    _node* tmp_node = node->right;
    node->right = tmp_node->left;
    if (tmp_node->left != nil)
      tmp_node->left->parent = node;
    tmp_node->parent = node->parent;
    if (node->parent == nil)
      tree = tmp_node;
    else if (node == node->parent->left)
      node->parent->left = tmp_node;
    else
      node->parent->right = tmp_node;
    tmp_node->left = node;
    node->parent = tmp_node;

    //if (tmp_node != nullptr){
    //  node->right = tmp_node->left;
    //  tmp_node->left = node;
    //  tmp_node->parent = node->parent;
    //  node->parent = tmp_node;
    //}
  }

  void RotateRight (_node* node){
    _node* tmp_node = node->right;
    
    node->left = tmp_node->right;
    if (tmp_node->right != nil)
      tmp_node->right->parent = node;
    tmp_node->parent = node->parent;
    if (node->parent == nil)
      tree = tmp_node;
    else if (node == node->parent->right)
      node->parent->right = tmp_node;
    else
      node->parent->left = tmp_node;
    tmp_node->right = node;
    node->parent = tmp_node;    
    
    
    
   /* if (tmp_node != nullptr){
      node->left = tmp_node->right;
      tmp_node->right = node;
      tmp_node->parent = node->parent;
      node->parent = tmp_node;
    }*/
  }

  inline void ColorFlip (_node* node){
    node->color = (node->color==RED) ? BLACK: RED;
  }

  inline _node* Parent (_node* node){
    return node->parent;
  }

  inline _node* Sibling (_node* node){
    _node* p = Parent (node);
    if (p == nullptr)
      return nullptr;
    return (node == p->left) ? p->right : p->left;
  }

  inline _node* Grandparent (_node* node){
    _node* p = Parent (node);
    return (p == nullptr) ? nullptr : Parent (p);
  }

  inline _node* Uncle (_node* node){
    _node* p = Parent (node);
    _node* g = Grandparent (node);
    return (g==nullptr) ?nullptr : Sibling(p);
  }


//private data
private:
  enum class NodeColor{ RED, BLACK };
  
  struct _node{
    NodeColor color;
    T value;
    _node* left;
    _node* right;
    _node* parent;
    _node () :color (NodeColor::BLACK), left (nullptr),
      right (nullptr), parent (nullptr){};
    _node (T val) : color (NodeColor::RED), value (val), left(nullptr),
                    right(nullptr), parent(nullptr) {};
  };

  _node* tree=nullptr;
  _node* nil;
};
