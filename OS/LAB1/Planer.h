#pragma once
#include <vector>

struct Process{
  long long m_id;
  long long m_income_to_queue_time;
  long long m_expected_exec_time; 
};


struct TimeData{
  long long m_start_exec_time;
  long long m_end_exec_time;
};

struct VData{
  TimeData m_time;
  Process m_process;
};


std::vector<VData> ProcessPlanerFCFS (std::vector<Process>& i_processes, bool LIFO=false);
std::vector<VData> ProcessPlanerLCFS (std::vector<Process>& i_processes);
std::vector<VData> ProcessPlanerSJF (std::vector<Process>& i_processes);

void WriteDataToFile (const std::vector<VData>& i_data,const std::string& i_path);

std::vector<Process> GetUserProcesses ();