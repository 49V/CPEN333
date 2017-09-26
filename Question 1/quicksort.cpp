#include <iostream>
#include <array>
#include <thread>
#include <vector>
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
	// Let's get parallel
	//Create threads
	
	//Pass the data
	
	//Wait for threads to finish
	
	//Clean up
	
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
	quicksort(v1, 0, v1.size() - 1);
	
	// Sort v2 using parallel algorithms
	parallel_quicksort(v2, 0, v2.size() - 1);
	
	std::cout << "V1 Is Sorted = " << is_sorted(v1) << std::endl;
	std::cout << "V2 Is Sorted = " << is_sorted(v2) << std::endl;
	
	return 0;
}