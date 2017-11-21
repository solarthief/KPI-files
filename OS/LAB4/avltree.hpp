#pragma once
#include <iostream>
#include <memory>
#include <algorithm>

//avl tree
template<typename T>
class avltree{
private:
  struct _node;

  //interface functions
public:
  avltree<T> () : nil (new _node){
    root = nil;
    root->left = nil;
    root->right = nil;
    root->parent = nil;
    root->balance_factor = 0;
    
  }

  ~avltree<T> (){
    ClearPath (root);
    delete nil;
  }


  bool Insert (T key){
    _node* node = new _node{ 0,key, nil,nil,nil };

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
      Rebalance (y_tmp_node);
    }  
    
    return true;
  }

  bool Delete (T key){
    _node* node_to_delete = FindNodeByKey (root, key);
    _node* tmp=nullptr;
    if (node_to_delete != nil){
      if (node_to_delete->left == nil)
        Transplant (node_to_delete, node_to_delete->right);
      else{
        if(node_to_delete->right == nil)
          Transplant (node_to_delete, node_to_delete->left);
        else{
          tmp = TreeMinimum (node_to_delete->right);
          if (tmp->parent != node_to_delete){
            Transplant (tmp, tmp->right);
            tmp->right = node_to_delete->right;
            tmp->right->parent = tmp;
          }
          Transplant (node_to_delete, tmp);
          tmp->left = node_to_delete->left;
          tmp->left->parent = tmp;
        } 
      } 
      if(tmp!=nullptr)
        Rebalance (tmp);
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

  void Rebalance (_node* node){
    SetBalanceFactor (node);

    if (node->balance_factor == -2){
      if (Height(node->left->left) >= Height (node->left->right))
        node = RotateRight (node);
      else
        node = RotateLeftRight (node);
    } else{
      if (node->balance_factor == 2){
        if (Height (node->right->right) >= Height (node->right->left))
          node = RotateLeft (node);
        else
          node = RotateRightLeft (node);
      }
    }

    if (node->parent != nil){
      Rebalance (node->parent);
    } else{
      root = node;
    }
      
  }

  void PrintNode (_node* node = root, unsigned int node_level=0){
    if (node != nil){
      auto level_buf = node_level;
      while (level_buf--){
        std::cout << "||";
      }
      std::cout << node->key<<"  || Node height: "<<Height(node)<< "  || Balance Factor: " << node->balance_factor<< std::endl;
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
    //if(node!=nil)
      delete node;
  }


  _node* RotateLeft (_node* node){
    _node* tmp = node->right;
    tmp->parent = node->parent;
    node->right = tmp->left;
    if (node->right != nil){
      node->right->parent = node;
    }
    tmp->left = node;
    node->parent = tmp;
    if (tmp->parent != nil){
      if (tmp->parent->right == node)
        tmp->parent->right = tmp;
      else
        tmp->parent->left = tmp;
    }
    SetBalanceFactor (node);
    SetBalanceFactor (tmp);
    return tmp;
  }

  _node* RotateRight (_node* node){
    _node* tmp = node->left;
    tmp->parent = node->parent;
    node->left = tmp->right;
    if (node->left != nil){
      node->left->parent = node;
    }
    tmp->right = node;
    node->parent = tmp;
    if (tmp->parent != nil){
      if (tmp->parent->right == node)
        tmp->parent->right = tmp;
      else
        tmp->parent->left = tmp;
    }
    SetBalanceFactor (node);
    SetBalanceFactor (tmp);
    return tmp;
  }

  _node*   RotateLeftRight (_node* node){
    node->left = RotateLeft (node->left);
    return RotateRight (node);
  }

  _node*   RotateRightLeft (_node* node){
    node->right = RotateRight (node->right);
    return RotateLeft (node);
  }

  _node* FindNodeByKey (_node* node, T key, bool print_path = false){

    while (node != nil){
      if (print_path){
        std::cout << node->key;
      }
      if (node->key == key){
        std::cout << std::endl;
        return node;
      }
      if (print_path)
        std::cout << "-->";
      node = (key<node->key) ? node->left : node->right;
    }
    if (print_path)
      std::cout << "nil" << std::endl;
    return node;
  }


  void SetBalanceFactor (_node* node){
    node->balance_factor = Height (node->right) - Height (node->left);
  }

  int32_t Height (_node* node){
    return (node != nil) ? (1+std::max(Height(node->left), Height(node->right))) : (-1);
  }

  _node* TreeMinimum (_node* node){
    while (node->left != nil){
      node = node->left;
    }
    return node;
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

  //private data
private:
  struct _node{
    int32_t balance_factor;
    T key;
    _node* left;
    _node* right;
    _node* parent;
  };

  _node* root;
  _node* nil;
};
