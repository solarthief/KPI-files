#include  "support_structures.h"
#include <iostream>
#include <iomanip>

bool Memory::AssignProgram (Program& program){

  int free_part;

  if ((free_part = FindFreePart (program.size)) == -1)
    return false;

  parts[free_part].program = program;
  parts[free_part].free = false;
  return true;
}


void Memory::PrintStatus (){
  int shift = 0;
  for (auto part : parts){
    std::cout << "||" << "Shift:" <<
      std::setw (12) << shift << "|| ";
    shift+=part.size;
  }

  std::cout << std::endl;
  for (auto part : parts){
    std::cout << "||" << "Status:" <<
      std::setw (11) << ((part.free) ? "Free" : "Occupied") << "|| ";
  }
  std::cout << std::endl;
  for (auto part : parts){
    std::cout << "||" << "Size:" <<
      std::setw (13) << part.size << "|| ";
  }
  std::cout << std::endl;
  for (auto part : parts){
    std::cout << "||" << "Program:" <<
      std::setw (10) << part.program.id << "|| ";
  }
  std::cout << std::endl;
  for (auto part : parts){
    std::cout << "||" << "Prog. size:" <<
      std::setw (7) << part.program.size << "|| ";
  }
  std::cout << std::endl;
  shift = 0;
  for (auto part : parts){
    std::cout << "||" << "Prog. begin:" <<
      std::setw (6) << ((!part.free) ? (shift) : (0)) << "|| ";
    shift += part.size;
  }
  std::cout << std::endl;
  shift = 0;
  for (auto part : parts){
    std::cout << "||" << "Prog. end:" <<
      std::setw (8) << ((!part.free)?(part.program.size + shift):(0)) << "|| ";
    shift += part.size;
  }

  std::cout << std::endl;
  std::cout << std::endl;
}

int Memory::FindFreePart (int size){
  int count = 0;
  for (auto part : parts){
    if (part.free && part.size>=size)
      return count;
    ++count;
  }
  return -1;
}

void Memory::FreePart (int part_id){
  if (part_id < parts.size ()){
    parts[part_id].program = Program();
    parts[part_id].free = true;
  }
}

size_t Memory::PartsQuantity (){
  return parts.size ();
}

Program& Memory::GetProgramByPart (int part_id){
  return parts[part_id].program;
}

template<typename T>
void Memory::PrintValue (std::string val_name, int shift, T val, bool count_use){
  int count = 0;
  for (auto part : parts){
    std::cout << "||" << val_name <<
      std::setw (shift) << val*((count_use)?count:1) << "|| ";
    ++count;
  }
  std::cout << std::endl;
}