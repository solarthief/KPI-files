#pragma once#include <map>
#include <string>
#include <atomic>
#include <thread>

void GetDemand (std::atomic<bool>& program_is_running);
void GetCash (std::atomic<bool>& program_is_running);
void InitBankValues ();
template<typename T>
void PrintValues (const std::string& title, T& cont);


