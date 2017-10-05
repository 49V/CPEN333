#include <C:/Users/Khiem/Documents/School/CPEN333/Libraries/library/include/cpen333/process/subprocess.h>
#include <C:/Users/Khiem/Documents/School/CPEN333/Libraries/library/include/cpen333/process/mutex.h>
#include <cstring>

int main() {

  // shared inter-process mutex
  cpen333::process::mutex mutex("system_logger");

  // list of child processes
  std::vector<cpen333::process::subprocess> processes;

  const int numberOfProcesses = 20;
  const int numberOfMessages = 100;
  const std::string logfile = "system_log.txt";
  std::string childName;
  
  for (int i = 0; i < nprocesses; ++i) {
	  
    std::vector<std::string> cmd;

	// Relative comman
    cmd.push_back("./systemLoggerChild"); //Relative command path 
	// Adds a number to identify child
	childName = std::to_string(i); // Uses an index to identify unique children
	cmd.push_back(childName); 
	cmd.push_back(logfile); // Passes the logfile
	cmd.push_back(std::to_string(nmessages)); // 
	
	processes.push_back({cmd});
	
  }

  // wait for processes to finish
  for (auto& process : processes) {
    process.join();
  }
  
  // unlink mutex since we and all child processes are done with it
  mutex.unlink();

  // pause, waiting for keyboard input
  cpen333::pause();
  return 0;
}

