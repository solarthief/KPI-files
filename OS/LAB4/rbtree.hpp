#pragma once
#include <iostream>
#include <memory>

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

  ~rbtree<T> (){    
    ClearPath (root);
    delete nil;
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

  bool Delete (T key){

    _node* node_to_delete = FindNodeByKey (root,key);
    _node* y_tmp_node = node_to_delete;
    _node* x_tmp_node = nullptr;
    NodeColor tmp_original_color = y_tmp_node->color;
    if (node_to_delete != nil){
      if (node_to_delete->left == nil){
        x_tmp_node = node_to_delete->right;
        Transplant (node_to_delete, node_to_delete->right);
      } else{
        if (node_to_delete->right == nil){
          x_tmp_node = node_to_delete->left;
          Transplant (node_to_delete, node_to_delete->left);
        } else{
          y_tmp_node = TreeMinimum (node_to_delete->right);
          tmp_original_color = y_tmp_node->color;
          x_tmp_node = y_tmp_node->right;
          if (y_tmp_node->parent == node_to_delete){
            x_tmp_node->parent = y_tmp_node;
          } else{
            Transplant (y_tmp_node, y_tmp_node->right);
            y_tmp_node->right = node_to_delete->right;
            y_tmp_node->right->parent = y_tmp_node;
          }
          Transplant (node_to_delete, y_tmp_node);
          y_tmp_node->left = node_to_delete->left;
          y_tmp_node->left->parent = y_tmp_node;
          y_tmp_node->color = node_to_delete->color;
        }
      }

      if (tmp_original_color == NodeColor::BLACK){
        FixDelete (x_tmp_node);
      }
      return true;
    }
    return false;
  }




  bool Find (T key){
    return (FindNodeByKey (root, key, true) != nil);
  }

  void PrintTree (){
    PrintNode (root);
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


  void PrintNode (_node* node, unsigned int node_level=0){
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


  void ClearPath (_node* node){
    if (node->left != nil){
      ClearPath (node->left);
    }
    if (node->right != nil){
      ClearPath (node->right);
    }
    delete node;
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

  _node* FindNodeByKey (_node* node, T key, bool print=false){    
    while (node != nil){
      if (print){
        std::cout << node->key ;
      }
      if (node->key == key){
        std::cout << std::endl;
        return node;
      } 
      if (print)
        std::cout << "-->";
      node = (key<node->key) ?node->left : node->right;
    }
    if (print)
      std::cout << "nil" << std::endl;
    return node;
  }

  _node* TreeMinimum (_node* node){
    while (node->left != nil){
      node = node->left;
    }
    return node;
  }


  void FixDelete (_node* node){

    while (node != root && node->color == NodeColor::BLACK){
      if (node == node->parent->left){
        _node* tmp_node = node->parent->right;
        if (tmp_node->color == NodeColor::RED){
          tmp_node->color = NodeColor::BLACK;
          node->parent->color = NodeColor::RED;
          RotateLeft (node->parent);
          tmp_node = node->parent->right;
        }
        if (tmp_node->left->color == NodeColor::BLACK && tmp_node->right->color == NodeColor::BLACK){
          tmp_node->color = NodeColor::RED;
          node = node->parent;
        } else{
          if (tmp_node->right->color == NodeColor::BLACK){
            tmp_node->left->color = NodeColor::BLACK;
            tmp_node->color = NodeColor::RED;
            RotateRight (tmp_node);
            tmp_node = node->parent->right;
          }
          tmp_node->color = node->parent->color;
          node->parent->color = NodeColor::BLACK;
          tmp_node->right->color = NodeColor::BLACK;
          RotateLeft (node->parent);
          node = root;
        }
      } else{
        _node* tmp_node = node->parent->left;
        if (tmp_node->color == NodeColor::RED){
          tmp_node->color = NodeColor::BLACK;
          node->parent->color = NodeColor::RED;
          RotateRight (node->parent);
          tmp_node = node->parent->left;
        }
        if (tmp_node->right->color == NodeColor::BLACK && tmp_node->left->color == NodeColor::BLACK){
          tmp_node->color = NodeColor::RED;
          node = node->parent;
        } else{
          if (tmp_node->left->color == NodeColor::BLACK){
            tmp_node->right->color = NodeColor::BLACK;
            tmp_node->color = NodeColor::RED;
            RotateLeft (tmp_node);
            tmp_node = node->parent->left;
          }
          tmp_node->color = node->parent->color;
          node->parent->color = NodeColor::BLACK;
          tmp_node->left->color = NodeColor::BLACK;
          RotateRight (node->parent);
          node = root;
        }
      }
    }
    node->color = NodeColor::BLACK;
  } 


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
