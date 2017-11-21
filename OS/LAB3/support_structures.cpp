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

bool Memory::FreeProgram (int program_id){
  int part_id = GetMemoryPartByProgram (program_id);
  if (part_id == -1)
    return false;
  FreePart (part_id);
  return true;
}


void Memory::PrintStatus (){  
  for (auto part : parts){
    std::cout << "||" << "Shift:" <<
      std::setw (12) << part.shift << "|| ";    
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
  for (auto part : parts){
    std::cout << "||" << "Prog. begin:" <<
      std::setw (6) << ((!part.free) ? (part.shift) : (0)) << "|| ";    
  }
  std::cout << std::endl; 
  for (auto part : parts){
    std::cout << "||" << "Prog. end:" <<
      std::setw (8) << ((!part.free)?(part.program.size + part.shift):(0)) << "|| ";    
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

int Memory::GetMemoryPartByProgram (int program_id){
  int index = 0;
  for (auto& part : parts){
    if (part.program.id == program_id)
      return index;
    ++index;
  }
  return -1;
}

size_t Memory::PartsQuantity (){
  return parts.size ();
}

int Memory::GetAbsoluteAddress (int program_id, int virtual_address){
  int part_id;
  if ((part_id = GetMemoryPartByProgram (program_id)) == -1)
    return -1;
  return  ((parts[part_id].size>= virtual_address) ? parts[part_id].shift + virtual_address : -1);
}

bool Memory::ReadNWord (int program_id, int virtual_address, int word_to_read){
  int part_id = GetMemoryPartByProgram (program_id);

  if ((virtual_address + word_to_read * 4) > parts[part_id].size)
    return false;


  std::cout << "Read " << word_to_read << " words from programm " << program_id << " from virt. address=" << virtual_address <<
    " and abs. address=" << GetAbsoluteAddress (program_id, virtual_address)<<std::endl;

  return true;   
}



bool Memory::WriteNWord (int program_id, int virtual_address, int word_to_write){
  int part_id = GetMemoryPartByProgram (program_id);

  if ((virtual_address + word_to_write * 4) > parts[part_id].size)
    return false;


  std::cout << "Write " << word_to_write << " words to programm " << program_id << " from virt. address=" << virtual_address <<
    " and abs. address=" << GetAbsoluteAddress (program_id, virtual_address) << std::endl;

  return true;
}

bool Memory::IsAllMemoryFree (){
  for (auto& part : parts){
    if (!part.free)
      return false;
  }
  return true;
 }

Program& Memory::GetProgramByPart (int part_id){
  return parts[part_id].program;
} 


bool Memory::IsPartOccupied (int part_id){
  return !parts[part_id].free;
}
