#include <iostream>
#include <string>
#include "avltree.hpp"

int main (){

  {
    avltree<std::string> test_tree;
    test_tree.Insert ("a");    
    test_tree.Insert ("a3");
    test_tree.Insert ("a3");
    test_tree.Insert ("a3");
    test_tree.Insert ("a3");
    test_tree.Insert ("a3");
    test_tree.Insert ("a3");
  
    test_tree.Insert ("3a");
    test_tree.Insert ("3a");    
    test_tree.Insert ("3a");

    test_tree.Insert ("3a");


    test_tree.PrintTree ();

    test_tree.Delete ("a");
    test_tree.PrintTree ();
  }
  
  system ("pause");
  return 0;
}