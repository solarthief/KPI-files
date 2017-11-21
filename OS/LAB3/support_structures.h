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
  int shift;
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
    int shift = 0;
    for (auto& part : parts){
      part.shift = shift;
      shift += part.size;
    }
  }
  bool IsAllMemoryFree ();
  bool AssignProgram (Program& program);
  bool FreeProgram (int program_id);
  bool ReadNWord (int program_id, int virtual_address, int word_to_read);
  bool WriteNWord (int program_id, int virtual_address, int word_to_write);
  bool IsPartOccupied (int part_id);
  void FreePart (int part_id); 

  size_t PartsQuantity ();
  int GetAbsoluteAddress (int program_id, int virtual_address);
  void PrintStatus ();
  Program& GetProgramByPart (int part_id);

private:
  int GetMemoryPartByProgram (int program_id);
  int FindFreePart (int size);
private:
  std::vector<Part> parts;
};