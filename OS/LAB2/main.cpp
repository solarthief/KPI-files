#include "ATM_function.h"



int main (){

  InitBankValues ();
  std::atomic<bool> running{ true };
  std::thread p0 (GetDemand, std::ref(running));
  std::thread p1 (GetCash, std::ref(running));

  p0.join ();
  p1.join ();
  return 0;
}