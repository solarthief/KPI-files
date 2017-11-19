#pragma once
#include <vector>
#include <string>


struct Program{
  Program (int _id = 0, int _size = 0) :
    id (_id), size (_size){
  }
  int id;
  int size;
};

struct Part{
  int size;
  Program program;
  bool free;
  Part (int s) :size (s), free (true), program (0, 0){}
};

class Memory{
public:
  Memory (int total_size, int quantity) :
    parts (quantity, Part (total_size / quantity)){
    for(int i=0; i< quantity/2;++i )
    parts.push_back (Part ( (total_size / quantity) * 2));
  }
  bool AssignProgram (Program& program);
  bool FreeProgram (int program_id);
  void FreePart (int part_id);
  size_t PartsQuantity ();
  void PrintStatus ();
  template<typename T>
    void PrintValue (std::string val_name, int shift, T val, bool count_use=false);
  Program& GetProgramByPart (int part_id);
private:
  int FindFreePart (int size);
private:
  std::vector<Part> parts;
};