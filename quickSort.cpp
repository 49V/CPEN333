#include <iostream>
#include <array>
#define ARRAY_SIZE ((sizeof(array)) / (sizeof(array[0])))

void Quicksort(int start, int end, int *array);
int Partition(int start, int end, int *array);

void QuickSort(int start, int end, int *array){

   int partitionIndex;

   // We still need to sort our array
    if(start < end){
		
		//std::cout << "Start :" << start << "End: " << end << std::endl;
        partitionIndex = Partition(start, end, array);
        QuickSort(start, partitionIndex - 1, array);
        QuickSort(partitionIndex + 1, end, array);
    }

   // We have reached the base case
   else{
      return;
   }

}

int Partition(int start,int end, int *array){
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

int main() {
	int array[] = {7, 2, 1, 6, 8, 5, 3 ,4 };
	
	for(int i = 0; i < ARRAY_SIZE; i++){
		std::cout << array[i] << " ";
		}
	std::cout << std::endl;
	
	QuickSort(0, ARRAY_SIZE - 1, array);
	
	for(int i = 0; i < ARRAY_SIZE; i++){
		std::cout << array[i] << " ";
		}
	std::cout << std::endl;
	
}