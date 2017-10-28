#include "Planer.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <queue>
#include <string>

#define TMAX 250

std::vector<VData> ProcessPlanerFCFS (std::vector<Process>& i_processes, bool LIFO){

std::vector<VData> data;
std::deque<Process> process_queue;
size_t process_id = 0;
size_t max_process = i_processes.size ();
long long time_counter=0;
long long current_exec_start=0;
long long current_exec_end=0;
bool working_on_process = false;
Process current_process;

std::sort (i_processes.begin (), i_processes.end (), [&](const Process& i_first_proc, const Process& i_second_proc){
  return i_first_proc.m_income_to_queue_time < i_second_proc.m_income_to_queue_time; });

for (time_counter = 0; time_counter < TMAX; ++time_counter){
  while (process_id < max_process && time_counter == i_processes[process_id].m_income_to_queue_time){
    process_queue.push_back (i_processes[process_id]);
    process_id++;
  }

  current_exec_end = time_counter;   
  if (!working_on_process && !process_queue.empty ()){
    current_process = (LIFO) ? process_queue.back () : process_queue.front ();
    if (!LIFO){
      process_queue.pop_front ();
    }
    else{
      process_queue.pop_back ();
    }
    working_on_process = true;
    current_exec_start = current_exec_end;
  }
  
  if (working_on_process && current_exec_end - current_exec_start == current_process.m_expected_exec_time-1){
      data.push_back ({ { current_exec_start , current_exec_end+1 } ,current_process});
      working_on_process = false;    
  }
}

return data;
}   

std::vector<VData> ProcessPlanerLCFS (std::vector<Process>& i_processes){
  return ProcessPlanerFCFS (i_processes, true);
}

///////////////////////////////////////////////////////////////////////////////////////

void WriteDataToFile (const std::vector<VData>& i_data, const std::string& i_path){
  std::ofstream file (i_path);
  if (file){
    file << std::setw (10)<<"Process" << std::setw (17) << "Income"
      << std::setw (18) << "Expected exec" << std::setw (15) << "Start exec"
      << std::setw (15) << "End exec" << std::setw (12) << "Delay"
      << std::setw (15) << "Total" << std::endl;

    long long all_delay = 0;
    long long all_total = 0;
    long long delay; 
    long long total;
    for (auto& proc_data : i_data){
       all_delay+= delay = proc_data.m_time.m_start_exec_time - proc_data.m_process.m_income_to_queue_time;
       all_total+= total = delay + proc_data.m_process.m_expected_exec_time;

      file << std::endl << std::setw (10)<< "P"+std::to_string( proc_data.m_process.m_id )<< std::setw (15) << proc_data.m_process.m_income_to_queue_time << std::setw (15)
        << proc_data.m_process.m_expected_exec_time << std::setw (15) << proc_data.m_time.m_start_exec_time << std::setw (15)
        << proc_data.m_time.m_end_exec_time << std::setw (15) << delay << std::setw (15) << total << std::endl;
    }
    
    file << std::endl << "Average delay time: " << double (all_delay) / i_data.size () << std::endl;
    file << "Average total exec time: " << double (all_total) / i_data.size () << std::endl<<std::endl;
  }
}

std::vector<VData> ProcessPlanerSJF (std::vector<Process>& i_processes){
  std::vector<VData> data;
  std::priority_queue<Process> process_queue;
  size_t process_id = 0;
  size_t max_process = i_processes.size ();
  long long time_counter = 0;
  long long current_exec_start = 0;
  long long current_exec_end = 0;
  bool working_on_process = false;
  Process current_process;

  std::sort (i_processes.begin (), i_processes.end (), [&](const Process& i_first_proc, const Process& i_second_proc){
    return i_first_proc.m_income_to_queue_time < i_second_proc.m_income_to_queue_time; });

  for (time_counter = 0; time_counter < TMAX; ++time_counter){
    while (process_id < max_process && time_counter == i_processes[process_id].m_income_to_queue_time){
      process_queue.push_back (i_processes[process_id]);
      process_id++;
    }

    current_exec_end = time_counter;
    if (!working_on_process && !process_queue.empty ()){
      current_process = (LIFO) ? process_queue.back () : process_queue.front ();
      if (!LIFO){
        process_queue.pop_front ();
      } else{
        process_queue.pop_back ();
      }
      working_on_process = true;
      current_exec_start = current_exec_end;
    }

    if (working_on_process && current_exec_end - current_exec_start == current_process.m_expected_exec_time - 1){
      data.push_back ({ { current_exec_start , current_exec_end + 1 } ,current_process });
      working_on_process = false;
    }
  }

  return data;
}



std::vector<Process> GetUserProcesses (){
  std::vector<Process> tmp_processes;
  char ch = 'y';
  long long id, income_time, exec_time;
  while (ch == 'y'){
    std::cout << "\nEnter new process:\n";
    std::cout << "Id: ";
    std::cin >> id;
    std::cout << "Income time: ";
    std::cin >> income_time;
    std::cout << "Exec time: ";
    std::cin >> exec_time;
    tmp_processes.push_back ({id,income_time,exec_time});
    std::cout << "Press y to continue  ";
    std::cin >> ch;

  } 
  return tmp_processes;
}