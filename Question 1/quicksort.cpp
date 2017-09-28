#include <iostream>
#include <array>
#include <thread>
#include <typeinfo>
#include <vector>
#include <math.h>
#include <chrono>
#define ARRAY_SIZE ((sizeof(array)) / (sizeof(array[0])))

void parallel_quicksort(std::vector<int>& array, int start, int end);
void quicksort(std::vector<int>& array, int start, int end);
int partition(std::vector<int>& array, int start, int end);
int is_sorted(std::vector<int>& array);

int partition(std::vector<int>& array, int start,int end){
    
	int pivot = array[end];
    int temp;
    int partitionIndex = start;

    for(int i = start; i < end; i++){
        if(array[i] <= pivot){
            temp = array[partitionIndex];
            // Put the lesser array value at the pivot index
            array[partitionIndex] = array[i];
            array[i] = temp;
            partitionIndex++;
        } 
   }
   
   // Make sure to place our pivot where it belongs
   temp = array[partitionIndex];
   array[partitionIndex] = pivot;
   array[end] = temp;
   
    return partitionIndex;
}

void quicksort(std::vector<int>& array, int start, int end){

   int partitionIndex;

   // We still need to sort our array
    if(start < end){
		
	    partitionIndex = partition(array, start, end);
        quicksort(array, start, partitionIndex - 1);
        quicksort(array, partitionIndex + 1, end);
    }

   // We have reached the base case
   else{
      return;
   }

}

void parallel_quicksort(std::vector<int>& array, int start, int end){
	
	const int NUMBER_OF_THREADS = 4;
	int numberOfPartitions, timesPartitioned;
	std::thread* threads[NUMBER_OF_THREADS];

	numberOfPartitions = NUMBER_OF_THREADS;
	timesPartitioned = int((log(numberOfPartitions) / log(2)) + 0.5);
	std::vector<int> partitionIndex (3, 0); 
		
	//Step 1: Partition your arrays
	// The number of threads you create has to be a multiple of 2^n if you want to assign one thread to each quicksort call
	
	partitionIndex[0] = partition(array, 0 ,array.size() - 1);
	partitionIndex[1] = partition(array, 0, partitionIndex[0] - 1);
	partitionIndex[2] = partition(array, partitionIndex[0] + 1, array.size() - 1);
		
	// Sort  the partition indices
	quicksort(partitionIndex, 0, partitionIndex.size() - 1);
		
	for(int i = 0; i < partitionIndex.size(); ++i){
		std::cout << "Index: " << i << " = " << partitionIndex[i] << std::endl;
	}
	
	//Step 2: Create threads and call parallel quicksort on partitioned arrays
	for(int j = 0; j < NUMBER_OF_THREADS; ++j){
		
		//std::cout << "J: " << j << std::endl;
		switch(j){
			case 0:
				//std::cout << "Case 0 " << "INDEX: " << partitionIndex[j] - 1 << std::endl;
				threads[j] = new std::thread(quicksort, std::ref(array), 0, partitionIndex[j] - 1);
				break;
			
			case (NUMBER_OF_THREADS - 1):
				//std::cout << "Case 1 " << "INDEX: " << partitionIndex[j - 1] + 1 << std::endl;
				threads[j] = new std::thread(quicksort, std::ref(array), partitionIndex[j - 1] + 1, array.size() - 1);
				break;
			
			default:
				//std::cout << "Case 2 " << "INDEX 1: " << partitionIndex[j - 1] + 1 << " INDEX 2: " << partitionIndex[j] - 1 << std::endl;
				threads[j] = new std::thread(quicksort, std::ref(array), partitionIndex[j - 1] + 1, partitionIndex[j] - 1);
				break;
		}
	}
	
	//Step 3: Finish and delete threads
	for(int i = 0; i < NUMBER_OF_THREADS; ++i){
		threads[i]->join();
		delete threads[i];
		threads[i] = nullptr;
	}
	return;
	
}

int is_sorted(std::vector<int>& array){
	
	for(int i = 0; i < array.size() - 1; i++){
		
		if(array[i + 1] >= array[i])
		{
			//Do nothing
		}
		
		else if(array[i + 1] < array[i]){
			std::cout << "PROBLEM INDEX AT " << i << " ";
			return 0;
		}
		
	}
	
	return 1;
	
}

int main() {
		
	const int VECTOR_SIZE = 10000000;
	std::vector<int> v1(VECTOR_SIZE, 0);
	
	// Populate with random integers
	for(int i = 0; i < VECTOR_SIZE; ++i){
		v1[i] = rand();
	}
	 	
	// Copy all contents
	std::vector<int> v2 = v1;	
	
	// Sort v1 using sequential algorithm
	auto t1 = std::chrono::high_resolution_clock::now();
	quicksort(v1, 0, v1.size() - 1);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = t2 - t1;
	auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    long ms = duration_ms.count();
	std::cout << "V1 Took: " << ms << std::endl;
	
	// Sort v2 using parallel algorithms
	t1 = std::chrono::high_resolution_clock::now();
	parallel_quicksort(v2, 0, v2.size() - 1);
	t2 = std::chrono::high_resolution_clock::now();
	duration = t2 - t1;
	duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    ms = duration_ms.count();
	std::cout << "V2 Took: " << ms << std::endl;
	
	std::cout << "V1 Is Sorted = " << is_sorted(v1) << std::endl;
	std::cout << "V2 Is Sorted = " << is_sorted(v2) << std::endl;
	
	return 0;
}