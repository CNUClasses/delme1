//============================================================================
// Name        : 12_delme.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <time.h>
#include <mutex>
#include <chrono>


using namespace std;

volatile bool bDoWork = true;

const int MILLI_1 = 1;
const int MILLI_1000 = 1000;

mutex m;

void threadfunc(int iThread) {

	//run loop until bDoWork = false
	while (bDoWork) {	//while(true)
		m.lock();
		cout << "Thread:" << iThread << " working..." << endl;
		m.unlock();

		//snooze for a bit to simulate work
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}
	m.lock();
	cout << "Thread:" << iThread << " exiting" << endl;
	m.unlock();
}

int main() {
	//create a bunch of threads
	std::vector<std::thread> threads;
	for (int i = 0; i < 20; ++i) {
		threads.push_back(std::thread(threadfunc, i));
	}

	//let em run a bit
	std::this_thread::sleep_for(std::chrono::milliseconds(MILLI_1000));

	//ask them all to stop
	bDoWork = false;

	//wait for em to finish
	for (auto& thread : threads) {
		thread.join();
	}

	cout << "All threads done!" << endl;

	return 0;
}
