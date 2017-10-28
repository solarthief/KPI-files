#include <iostream>
#include "Planer.h"

int main (){

  std::vector<Process> processes_avr = {
    {1,0,6},{2,3,2},
    {3,10,1},{4,10,3},
    {5,12,4},{6,13,10},
    {7,30,10},{8,35,8}};
  std::vector<Process> processes_1 = {
    {1,0,10},{2,1,8},
    {3,2,6},{4,3,4},
    {5,4,2},{6,5,1}
  };
  std::vector<Process> processes_2 = {
    { 1,0,10 },{ 2,1,1 },
    { 3,2,2 },{ 4,3,4 },
    { 5,4,6 },{ 6,5,8 }
  };

  //auto ui_processes = GetUserProcesses ();

  auto dataFIFO = ProcessPlanerFCFS (processes_avr);
  auto dataLIFO = ProcessPlanerLCFS (processes_avr);
  auto dataFIFO_1 = ProcessPlanerFCFS (processes_1);
  auto dataLIFO_1 = ProcessPlanerLCFS (processes_1);
  auto dataFIFO_2 = ProcessPlanerFCFS (processes_2);
  auto dataLIFO_2 = ProcessPlanerLCFS (processes_2);
  //auto dataFIFO_ui = ProcessPlanerFCFS (ui_processes);
  //auto dataLIFO_ui = ProcessPlanerLCFS (ui_processes);
  WriteDataToFile (dataFIFO, "FIFO_AVR.dat");
  WriteDataToFile (dataLIFO, "LIFO_AVR.dat");
  WriteDataToFile (dataFIFO_1, "FIFO_1.dat");
  WriteDataToFile (dataLIFO_1, "LIFO_1.dat");
  WriteDataToFile (dataFIFO_2, "FIFO_2.dat");
  WriteDataToFile (dataLIFO_2, "LIFO_2.dat");
 //WriteDataToFile (dataFIFO_ui, "FIFO_ui.dat");
  //WriteDataToFile (dataLIFO_ui, "LIFO_ui.dat");

  system("pause");
  return 0;
}