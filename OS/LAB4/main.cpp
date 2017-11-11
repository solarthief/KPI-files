
#include <string>
#include "rbtree.hpp"





int main (){
  rbtree<std::string> test_tree;
  test_tree.Insert ("a");
  test_tree.Insert ("ab");
  test_tree.Insert ("ac");
  test_tree.Insert ("ba");
  test_tree.Insert ("ca");
  test_tree.Insert ("abc");
  test_tree.Insert ("acb");
  test_tree.Insert ("aaa");

  test_tree.Insert ("zabc");
  test_tree.Insert ("zzacb");
  test_tree.Insert ("zaaa");


  test_tree.PrintTree ();

  test_tree.Delete ("ca");

  test_tree.PrintTree ();

  system ("pause");
  return 0;
}