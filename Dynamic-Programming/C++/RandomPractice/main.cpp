#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include "User.h"

using C = ACCOUNT_TYPE;

std::mutex myMutex;

void ManageBank(int threadID, Bank* b) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> pay(0.0, 1000.0);
    std::uniform_int_distribution<int> date(0, 2);
    // Date d0(11, 25, 2023), d1, d2(12, 5, 2023);
    // Date d[] = {d0, d1, d2};

    std::lock_guard<std::mutex> lock(myMutex);

    Transaction t0("TARGET", pay(generator)), t1, t2("PAY", pay(generator));
    // Transaction t0("TARGET", pay(generator), d[date(generator)]), t1;
    // Transaction t2("PAY", pay(generator), d[date(generator)]);
    // t1.date = d0;
    // t1.date.setDate(d[date(generator)]);
    // t2.date.printDate();
    
    std::cout << "Thread " << threadID << " is running (inside critical section)\n";  
    b->withdraw(t0, C::CHECKING);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    b->deposit(t2, C::CHECKING);

    t0.date.random();
    t1.date.random();
    t2.date.random();
}

int main() {
    User u1;
    Bank *b1 = u1.getBank();
    Date d0(11, 25, 2023), d1, d2(12, 5, 2023);
    const int numThreads = 20;  // Number of threads

    // Create a vector to store thread objects
    std::vector<std::thread> threads;

    // Launch multiple threads
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(ManageBank, i, b1));
    }

    // Join threads to the main thread
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\nAll threads have finished\n";
    // b1->getAccount<C::CHECKING>().printaccountBalance();
    b1->printTransactionHistory();
    // u1.getBank().getAccount<C::CHECKING>().printaccountBalance();
    
    return 0;
}