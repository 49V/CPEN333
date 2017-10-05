#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <thread>

#include <C:/Users/Khiem/Documents/School/CPEN333/Libraries/library/include/cpen333/process/mutex.h>

void run_logger(const std::string& processname,
                const std::string& filename,
                int message_count) {

  std::default_random_engine eng;
  std::uniform_int_distribution<int> rnd(20, 150);

  // mutex
  cpen333::process::mutex mutex("system_logger");

  for (int i = 0; i < message_count; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(rnd(eng)));

    // open file for "append"
    std::ofstream logfile;
    logfile.open(filename, std::ios_base::out | std::ios_base::app);
	
	// Locks the file and the command line (Just for neatness)
	std::unique_lock<cpen333::process::mutex> lock(mutex);
    logfile << processname << ": " << "message " << i << std::endl;
    std::cout << processname << ": " << "message " << i << std::endl;
	lock.unlock();
	
    logfile.close();

  }

}

int main(int argc, char* argv[]) {
	
  if (argc < 4) {
    std::cout << " Error: need to pass in a process name, logfile, and number of messages" << std::endl;
    return -1;
  }

  run_logger(argv[1], argv[2], std::atoi(argv[3]));

  return 0;
}

