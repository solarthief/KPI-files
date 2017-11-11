#pragma once
#include <iostream>

//Red-black tree
template<typename T>
class rbtree{
private:
  struct _node;

 //interface functions
public:
  rbtree<T> (): nil(new _node){
    root = nil;
    root->left = nil;
    root->right = nil;
    root->parent = nil;
    root->color = NodeColor::BLACK;
  }

  bool Insert (T key){
    _node* node =new _node{ NodeColor::RED,key, nil,nil,nil };

    _node* y_tmp_node = nil;
    _node* x_tmp_node = root;

    while (x_tmp_node != nil){
      y_tmp_node = x_tmp_node;
      if (node->key < x_tmp_node->key){
        x_tmp_node = x_tmp_node->left;
      } else{
        x_tmp_node = x_tmp_node->right;
      }
    }
    node->parent = y_tmp_node;
    if (y_tmp_node == nil){
      root = node;
    } else{
      if (node->key < y_tmp_node->key){
        y_tmp_node->left = node;
      } else{
        y_tmp_node->right = node;
      }
    }
    node->left = nil;
    node->right = nil;
    node->color = NodeColor::RED;

    FixInsert (node);
    return true;
  }

  /*bool Delete (T key){
    _node* node_to_delete = FindNodeByKey (root,key);
    _node* y_tmp_node = node_to_delete;
    _node* x_tmp_node;
    NodeColor tmp_original_color = y_tmp_node;

    if (node_to_delete == nil){
      x_tmp_node
    }
  }*/




  bool Find (T key);
  void PrintTree (){
    PrintNode (root, 0);
  }

//private methods
private:
  
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
    root->color = NodeColor::BLACK;   
  }


  void PrintNode (_node* node, unsigned int node_level){
    if (node != nil){
      auto level_buf = node_level;
      while (level_buf--){
        std::cout << "++";
      }
      std::cout << node->key << std::endl;
      PrintNode (node->left, node_level + 1);
      PrintNode (node->right, node_level + 1);
    }
  }

 

  void RotateLeft (_node* node){
    _node* tmp_node = node->right;
    node->right = tmp_node->left;
    if (tmp_node->left != nil)
      tmp_node->left->parent = node;
    tmp_node->parent = node->parent;
    if (node->parent == nil)
      root = tmp_node;
    else{
      if (node == node->parent->left)
        node->parent->left = tmp_node;
      else
        node->parent->right = tmp_node;
    }
    tmp_node->left = node;
    node->parent = tmp_node;
  }

  void RotateRight (_node* node){

    _node* tmp_node = node->left;    
    node->left = tmp_node->right;
    if (tmp_node->right != nil)
      tmp_node->right->parent = node;
    tmp_node->parent = node->parent;
    if (node->parent == nil)
      root = tmp_node;
    else{
      if (node == node->parent->right)
        node->parent->right = tmp_node;
      else
        node->parent->left = tmp_node;
    }
    tmp_node->right = node;
    node->parent = tmp_node;
 }

  void Transplant (_node* u_node, _node* v_node){
    if (u_node->parent == nil){
      root = v_node;
    } else{
      if (u_node == u_node->parent->left){
        u_node->parent->left = v_node;
      } else{
        u_node->parent->right = v_node;
      }
    }
    v_node->parent = u_node->parent;
  }

  _node* FindNodeByKey (_node* node, T key){
    if (node->key == key){
      return node;
    }
    return ((node->key < key) ? FindNodeByKey (node->left, key) : FindNodeByKey (node->right, key));
  }

  /*inline _node* Parent (_node* node){
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
  }*/


//private data
private:
  enum class NodeColor{ RED, BLACK };
  
  struct _node{
    NodeColor color;
    T key;
    _node* left;
    _node* right;
    _node* parent;    
  };

  _node* root;
  _node* nil;
};
