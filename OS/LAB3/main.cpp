#include "support_structures.h"
#include <cstdlib>
#include <list>
#include <iostream>
#include <iomanip>



int main (int argc, char** argv){

  srand (1488);

  Memory mem (4096, 4);
  std::list<Program> programs;
  for (int i = 0; i < 10; ++i){
    programs.push_back (Program{ 1000 + i,(rand () % 386) * 4 });
  }
  std::cout << "Welcome to Memory Distr. Programm(v0.03alpha)" << std::endl;
  int tact_count = 0;
  while (!programs.empty()){


    auto program = programs.front ();
    programs.pop_front ();

    if (!mem.AssignProgram (program))
      programs.push_front (program);   

    std::cout << "Tact N: " << tact_count << std::endl;
    mem.PrintStatus ();


    if (rand () % 10 > 4){
      int part_to_free = rand () % mem.PartsQuantity ();

      std::cout << "Free memory part N " << part_to_free <<
        " with program id=" << mem.GetProgramByPart (part_to_free).id << std::endl << std::endl;

      mem.FreePart (part_to_free);
    }


    ++tact_count;
  }
  system ("pause");
  return 0;
}