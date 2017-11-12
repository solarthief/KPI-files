
#include <iostream>
#include <string>
#include "rbtree.hpp"





int main (){

  {
    rbtree<std::string> test_tree;
    test_tree.Insert ("a");
    test_tree.Insert ("ab");
    test_tree.Insert ("ac");
    test_tree.Insert ("ba");
    test_tree.Insert ("ca");
    test_tree.Insert ("1a");
    test_tree.Insert ("a5");
    test_tree.Insert ("a3");

    test_tree.Insert ("9n");
    test_tree.Insert ("z5");
    test_tree.Insert ("zz");

    test_tree.Find ("ca");

    test_tree.PrintTree ();

    test_tree.Delete ("ca");

    test_tree.Find ("ca");
    test_tree.PrintTree ();
  }
  
  system ("pause");
  return 0;
}