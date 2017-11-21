#include <iostream>
#include <string>
#include "avltree.hpp"

int main (){


   
    
    { 
      std::cout << std::endl << std::endl << "Test case N1" << std::endl << std::endl;
      avltree<std::string> test_tree;
      test_tree.Insert ("a1");
      test_tree.Insert ("a2");
      test_tree.Insert ("a3");
      test_tree.Insert ("a4");
      test_tree.Insert ("a5");
      test_tree.Insert ("a6");
      test_tree.Insert ("a7");
      test_tree.Insert ("a8");
      test_tree.Insert ("a9");

      test_tree.PrintTree ();


    }
  

    {
      std::cout << std::endl << std::endl<< "Test case N2" << std::endl << std::endl;
      avltree<std::string> test_tree;
      test_tree.Insert ("9a");
      test_tree.Insert ("8a");
      test_tree.Insert ("7a");      
      test_tree.Insert ("6a");
      test_tree.Insert ("5a");
      test_tree.Insert ("4a");
      test_tree.Insert ("3a");
      test_tree.Insert ("2a");
      test_tree.Insert ("1a");

      test_tree.PrintTree ();
      std::cout <<std::endl<< "Path to node 2a:";
      test_tree.Find ("2a");
    }


    {
      std::cout << std::endl << std::endl << "Test case N3" << std::endl << std::endl;
      avltree<std::string> test_tree;
      test_tree.Insert ("9a");
      test_tree.Insert ("8a");
      test_tree.Insert ("7a");      
      test_tree.Insert ("6a");
      test_tree.Insert ("5a");
      test_tree.Insert ("4a");
      test_tree.Insert ("3a");
      test_tree.Insert ("2a");
      test_tree.Insert ("1a");
      
      test_tree.Delete ("8a");
      test_tree.PrintTree ();
    }


  system ("pause");
  return 0;
}