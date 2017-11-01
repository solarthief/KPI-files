#include "ATM_function.h"
#include <boost/range/adaptor/reversed.hpp>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <map>
#include <fstream> 
#include <queue>

#define DELIMITER std::map<int,int>{}

//Distributed resource:
namespace Bank{
  //accounts - map of client`s accounts, 
  //first parameter - id, second parameter - amount of money
  std::map<int, int> accounts;
  //currency - all available currency in an ATM
  //first parameter - value of banknote, second parameter - amount of speific banknote
  std::map<uint8_t, int> currency;
}

//Additional parameters for transmit data between threads
namespace TransactionParam{ 
  //Account id
  int id(0);
  //Amount of money to withdraw
  int money(0);
  std::ofstream file (std::string (std::to_string (std::chrono::system_clock::now ().time_since_epoch ().count ()) + ".dat"));
  bool has_cash(false);
}

//// Variables needed for implementation of Dekker`s algorithm
//namespace DekkerImp{
//  std::atomic<bool> flag0 (false), flag1 (false);
//  std::atomic<int> turn(0);
//  std::atomic<bool> working (true);
//}
//
//
//void GetDemand (std::atomic<bool>& program_is_running){
//  while (program_is_running.load (std::memory_order_relaxed)){
//    DekkerImp::flag0.store (true, std::memory_order_relaxed);
//    std::atomic_thread_fence (std::memory_order_seq_cst);
//
//
//    while (DekkerImp::flag1.load (std::memory_order_relaxed)){
//      if (DekkerImp::turn.load (std::memory_order_relaxed) != 0){
//        DekkerImp::flag0.store (false, std::memory_order_relaxed);
//        while (DekkerImp::turn.load (std::memory_order_relaxed) != 0){}
//        DekkerImp::flag0.store (true, std::memory_order_relaxed);
//        std::atomic_thread_fence (std::memory_order_seq_cst);
//      }
//    }
//    std::atomic_thread_fence (std::memory_order_acquire);
//
//    if (!TransactionParam::has_cash){
//     //critical section
//      int id = 0;
//      int money = 0;      
//      PrintValues ("Bank accounts:  ", Bank::accounts);
//      
//      while (!TransactionParam::has_cash){
//        std::cout << "Enter account id: ";
//        std::cin >> id;
//        std::cout << "Enter amount of money to withdraw: ";
//        std::cin >> money;
//        if (Bank::accounts[id] >= money){
//          TransactionParam::id = id;
//          TransactionParam::money = money;
//          TransactionParam::has_cash = true;
//        } else{
//          std::cout << "Not enough money on bank account" << std::endl;
//        }
//
//      }
//      std::this_thread::sleep_for (std::chrono::milliseconds (1000));
//    }
//    DekkerImp::turn.store (1, std::memory_order_relaxed);
//    std::atomic_thread_fence (std::memory_order_release);
//    DekkerImp::flag0.store (false, std::memory_order_relaxed);
//  }
//}
//
//void GetCash (std::atomic<bool>& program_is_running){
//  while (program_is_running.load (std::memory_order_relaxed)){
//    DekkerImp::flag1.store (true, std::memory_order_relaxed);
//    std::atomic_thread_fence (std::memory_order_seq_cst);
//
//
//    while (DekkerImp::flag0.load (std::memory_order_relaxed)){
//      if (DekkerImp::turn.load (std::memory_order_relaxed) != 1){
//        DekkerImp::flag1.store (false, std::memory_order_relaxed);
//        while (DekkerImp::turn.load (std::memory_order_relaxed) != 1){}
//        DekkerImp::flag1.store (true, std::memory_order_relaxed);
//        std::atomic_thread_fence (std::memory_order_seq_cst);
//      }
//    }
//    std::atomic_thread_fence (std::memory_order_acquire);
//
//    //critical section
//    
//    if (TransactionParam::has_cash){
//      PrintValues ("Withdraw info", std::map<int, int>{ {TransactionParam::id, TransactionParam::money} });
//      PrintValues ("ATM av. currency: ", Bank::currency);
//
//
//      //Algo for defining amount of cash needed to be withdrawn from ATM
//      //Uses buffer values
//      auto buf_currency (Bank::currency);
//      auto buf_money = TransactionParam::money;
//
//      //using boost reverse adaptor for implementating simple greedy algorithm
//      //This cycle is eval reducing of cash count in ATM for all banknotes in ATM
//      //starting from highest banknote
//      for (auto& cur : boost::adaptors::reverse (buf_currency)){
//        while (cur.second > 0 && buf_money >= cur.first){
//          cur.second--;
//          buf_money -= cur.first;
//        }
//      }
//      //If withdraw is possible, then swap buffer and actual currency values
//      //and substract withdrawn money from user account 
//      if (buf_money == 0){
//        std::swap (buf_currency, Bank::currency);
//        Bank::accounts[TransactionParam::id] -= TransactionParam::money;
//        PrintValues ("After withdraw ATM av. currency:  ", Bank::currency);
//      }
//      //else print error message
//      else{
//        PrintValues ("Can`t withdraw such amount of money", std::map<int, int>{});
//      }
//              
//      TransactionParam::has_cash = false;
//      std::this_thread::sleep_for (std::chrono::milliseconds (1000));
//    }
//    DekkerImp::turn.store (0, std::memory_order_relaxed);
//    std::atomic_thread_fence (std::memory_order_release);
//    DekkerImp::flag1.store (false, std::memory_order_relaxed);
//  }
//}
 
//Implementation of semaphore method notify(or Dijkstra's P)
inline void Semaphore::notify (){
  std::unique_lock<std::mutex> lock (mtx);
  count++;
  if (count <= 0)
    cv.notify_one ();
}

//Implementation of semaphore method notify(or Dijkstra's V)
inline void Semaphore::wait (){
  std::unique_lock<std::mutex> lock (mtx);
  count--;
  if (count < 0){
    cv.wait (lock);
  }
}
//namespace SemImp{
//  Semaphore free(1);
//} 
//void GetDemand (std::atomic<bool>& program_is_running){
//  while (program_is_running.load (std::memory_order_relaxed)){
//    SemImp::free.wait ();      
//     //critical section
//      int id = 0;
//      int money = 0;
//      PrintValues ("Bank accounts:  ", Bank::accounts);
//      while (!TransactionParam::has_cash){
//        std::cout << "Enter account id: ";
//        std::cin >> id;
//        std::cout << "Enter amount of money to withdraw: ";
//        std::cin >> money;
//        if (Bank::accounts[id] >= money){
//          TransactionParam::id = id;
//          TransactionParam::money = money;
//          TransactionParam::has_cash = true;
//        } else{
//          std::cout << "Not enough money on bank account" << std::endl;
//        }
//      }
//      std::this_thread::sleep_for (std::chrono::milliseconds (1000));      
//    SemImp::free.notify ();
//  }
//}
//
//void GetCash (std::atomic<bool>& program_is_running){
//  while (program_is_running.load (std::memory_order_relaxed)){
//    SemImp::free.wait ();
//    //critical section
//    
//      PrintValues ("Withdraw info", std::map<int, int>{ {TransactionParam::id, TransactionParam::money} });
//      PrintValues ("ATM av. currency: ", Bank::currency);
//
//
//      //Algo for defining amount of cash needed to be withdrawn from ATM
//      //Uses buffer values
//      auto buf_currency (Bank::currency);
//      auto buf_money = TransactionParam::money;
//
//      //using boost reverse adaptor for implementating simple greedy algorithm
//      //This cycle is eval reducing of cash count in ATM for all banknotes in ATM
//      //starting from highest banknote
//      for (auto& cur : boost::adaptors::reverse (buf_currency)){
//        while (cur.second > 0 && buf_money >= cur.first){
//          cur.second--;
//          buf_money -= cur.first;
//        }
//      }
//      //If withdraw is possible, then swap buffer and actual currency values
//      //and substract withdrawn money from user account 
//      if (buf_money == 0){
//        std::swap (buf_currency, Bank::currency);
//        Bank::accounts[TransactionParam::id] -= TransactionParam::money;
//        PrintValues ("After withdraw ATM av. currency:  ", Bank::currency);
//      }
//      //else print error message
//      else{
//        PrintValues ("Can`t withdraw such amount of money", std::map<int, int>{});
//      }
//              
//      TransactionParam::has_cash = false;
//      std::this_thread::sleep_for (std::chrono::milliseconds (1000));      
//    SemImp::free.notify ();
//  }
//}

//Using simple  produser-consumer synchronization using 
//buffer with only one value
namespace MailImp{
  struct Message{
    int  id;
    int sum;
  };
  Semaphore empty_count (1);
  Semaphore use_queue (1);
  Semaphore full_count (0);
  std::queue<Message> buffer;
}


void GetDemand (std::atomic<bool>& program_is_running){
  while (program_is_running.load (std::memory_order_relaxed)){
    MailImp::empty_count.wait ();
    MailImp::use_queue.wait ();
    //critical section

    int id = 0;
    int money = 0;
    PrintValues ("------------------------------------------", DELIMITER);
    PrintValues ("Bank accounts:  ", Bank::accounts);

    //while account doesn`t have such amount money to withdraw
    while (!TransactionParam::has_cash){
      //enter (or re-enter) new id and sum
      std::cout << "Enter account id: ";
      std::cin >> id;
      std::cout << "Enter amount of money to withdraw: ";
      std::cin >> money;
      if (Bank::accounts[id] >= money){
        TransactionParam::id = id;
        TransactionParam::money = money;
        TransactionParam::has_cash = true;
      } else{
        std::cout << "Not enough money on bank account" << std::endl;
      }

    }
    MailImp::buffer.push ({ id,money });
    std::this_thread::sleep_for (std::chrono::milliseconds (1000));
    MailImp::use_queue.notify ();
    MailImp::full_count.notify ();
  }
}

void GetCash (std::atomic<bool>& program_is_running){
  while (program_is_running.load (std::memory_order_relaxed)){
    MailImp::full_count.wait ();
    MailImp::use_queue.wait ();
    //critical section

    PrintValues ("Withdraw info", std::map<int, int>{ {TransactionParam::id, TransactionParam::money} });
    PrintValues ("ATM av. currency: ", Bank::currency);


    //Algo for defining amount of cash needed to be withdrawn from ATM
    //Uses buffer values
    auto buf_currency (Bank::currency);
    auto transaction = MailImp::buffer.front ();
    MailImp::buffer.pop ();
    auto buf_money = transaction.sum;

    //using boost reverse adaptor for implementating simple greedy algorithm
    //This cycle is eval reducing of cash count in ATM for all banknotes in ATM
    //starting from highest banknote
    for (auto& cur : boost::adaptors::reverse (buf_currency)){
      while (cur.second > 0 && buf_money >= cur.first){
        cur.second--;
        buf_money -= cur.first;
      }
    }
    //If withdraw is possible, then swap buffer and actual currency values
    //and substract withdrawn money from user account 
    if (buf_money == 0){
      std::swap (buf_currency, Bank::currency);
      Bank::accounts[transaction.id] -= transaction.sum;
      PrintValues ("After withdraw ATM av. currency:  ", Bank::currency);
    }
    //else print error message
    else{
      PrintValues ("Can`t withdraw such amount of money", std::map<int, int>{});
    }

    TransactionParam::has_cash = false;
    std::this_thread::sleep_for (std::chrono::milliseconds (1000));
    MailImp::use_queue.notify ();
    MailImp::empty_count.notify ();
  }
}




  void InitBankValues (){
    Bank::accounts = { {1001,1500}, {1002,1700},{1003,100}, {1004,500} };
    Bank::currency = { {1,100},{2,100},{5,100},
    {10,100},{20,100},{50,100},{100,100} };
  }

  template<typename T>
  void PrintValues (const std::string& title, T& cont){
    TransactionParam::file << title<<std::endl;
    std::cout<< title << std::endl;
    for (auto& val : cont){
      TransactionParam::file << std::setw (5) << std::to_string (val.first) << " | " << val.second << std::endl;
      std::cout<< std::setw (5) << std::to_string (val.first) << " | " << val.second << std::endl;
    }
  }

