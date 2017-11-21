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
  while (!programs.empty () || !mem.IsAllMemoryFree ()){
    std::cout << "Tact N: " << tact_count << std::endl;
    mem.PrintStatus ();
    
    if (!programs.empty () && mem.AssignProgram (programs.front ()))
      programs.pop_front ();

    if (rand () % 10 > 5 ){
      int part_to_free = rand () % mem.PartsQuantity ();
      int n_words = rand () % 256;
      int virt_addr = (rand () % 256) * 4;
      if (mem.IsPartOccupied (part_to_free)){       
        std::cout << "Tring to read " << n_words << " words from program " << mem.GetProgramByPart (part_to_free).id <<
          std::endl;
        std::cout << "Reading :" << (mem.ReadNWord (mem.GetProgramByPart (part_to_free).id, virt_addr, n_words) ? "success" : "failure") << std::endl;
      }
      if (mem.IsPartOccupied ((part_to_free == 0) ? 1 : part_to_free - 1)){
        n_words = rand () % 256;
        virt_addr = (rand () % 256) * 4;
        std::cout << "Tring to write " << n_words << " words to program " << mem.GetProgramByPart ((part_to_free == 0) ? 1 : part_to_free - 1).id <<
          std::endl;
        std::cout << "Writing :" <<
          (mem.WriteNWord (mem.GetProgramByPart ((part_to_free == 0) ? 1 : part_to_free - 1).id, virt_addr, n_words) ? "success" : "failure") << std::endl;
      }
      if (mem.IsPartOccupied (part_to_free)){
        std::cout << "Free memory part N " << part_to_free <<
          " with program id=" << mem.GetProgramByPart (part_to_free).id << std::endl << std::endl;

        mem.FreePart (part_to_free);
      }
    }


    ++tact_count;
  }
  mem.PrintStatus ();
  system ("pause");
  return 0;
}