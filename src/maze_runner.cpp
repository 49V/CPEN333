#include "maze_runner_common.h"

#include <cpen333/process/shared_memory.h>
#include <cpen333/process/mutex.h>
#include <cstring>
#include <chrono>
#include <thread>

class MazeRunner {

  cpen333::process::shared_object<SharedData> memory_;
  cpen333::process::mutex mutex_;

  // local copy of maze
    MazeInfo minfo_;

  // runner info
  size_t idx_;   // runner index
  int loc_[2];   // current location

 public:

  MazeRunner() : memory_(MAZE_MEMORY_NAME), mutex_(MAZE_MUTEX_NAME),
                 minfo_(), idx_(0), loc_(){

    // copy maze contents
    minfo_ = memory_->minfo;
	
    {
      // protect access of number of runners
      std::lock_guard<decltype(mutex_)> lock(mutex_);
      idx_ = memory_->rinfo.nrunners;
      memory_->rinfo.nrunners++;
    }

    // get current location
    loc_[COL_IDX] = memory_->rinfo.rloc[idx_][COL_IDX];
    loc_[ROW_IDX] = memory_->rinfo.rloc[idx_][ROW_IDX];
	
	minfo_.maze[loc_[COL_IDX]][loc_[ROW_IDX]] = 'S';

  }

  /**
   * Solves the maze, taking time between each step so we can actually see progress in the UI
   * @return 1 for success, 0 for failure, -1 to quit
   */
  int go() {

	int x = memory_->rinfo.rloc[idx_][COL_IDX];
	int y = memory_->rinfo.rloc[idx_][ROW_IDX];
	
    //==========================================================
    // TODO: NAVIGATE MAZE
    //==========================================================
	
	findPath(x, y);

    // failed to find exit
    return 0;
  }
  
  /**
  * Checks whether the coordinate given leads to a valid path
  * @param x X co-ordinate
  * @param y Y co-ordinate
  */
  
  int findPath(int x, int y){
	  
	// If our next coordinate is outside a maze wall, return false
	if(minfo_.maze[x][y] == 'X'){
		return false;
	}
	
	// If x,y is the exit, return true
	if(minfo_.maze[x][y] == 'E'){
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		memory_->rinfo.rloc[idx_][COL_IDX] = x;
		memory_->rinfo.rloc[idx_][ROW_IDX] = y;
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		return true;
	}
	
	// If x,y is not open, return false
	if(minfo_.maze[x][y] != ' ' && minfo_.maze[x][y] != 'S'){
		return false;
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	memory_->rinfo.rloc[idx_][COL_IDX] = x;
	memory_->rinfo.rloc[idx_][ROW_IDX] = y;
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	
	// Mark as a part of the solution path
	minfo_.maze[x][y] = '+';
	
	// Go North and check if we can find the path :)
	if(findPath(x, y - 1) == true){
		return true;
	}
	
	// Go East
	if(findPath(x + 1, y) == true){
		return true;
	}
	
	// Go South
	if(findPath(x, y + 1) == true){
		return true;
	}
	
	// Go West
	if(findPath(x - 1, y) == true){
		return true;
	}
	
	minfo_.maze[x][y] = 'r';
	
	return false;
	  
  }

  
  bool quit(){
	  return memory_->quit;
  }
  
};

int main() {

  MazeRunner runner;
  int mazeResult;
  
  //** ADJUST FOR WHEN TOLD TO QUIT
  while(!runner.quit()){
	mazeResult = runner.go();
  }
  
  std::cout << "END" << std::endl;
  
  return mazeResult;
}