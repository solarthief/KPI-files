#pragma once#include <map>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

void GetDemand (std::atomic<bool>& program_is_running);
void GetCash (std::atomic<bool>& program_is_running);
void InitBankValues ();
template<typename T>
void PrintValues (const std::string& title, T& cont);

class Semaphore{
public:
  Semaphore (int _count = 0)
    : count (_count){}
  inline void notify ();
  inline void wait ();

private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
};




