#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

//recursive
int binarySearch(int *arr, int left, int right, int targetElement)
{
    int middle = (right + left) / 2;
    if (right <= left) //'<' -> edge case for 'right' becoming index of -1
    {
        if (arr[left] > targetElement)
            return left; //return position of left element as target position if it is larger than the target element
        else
            return left+1; //return one position to the right of the left element if the left element is smaller than the target element
    }

    if (arr[middle] > targetElement)
        return binarySearch(arr, left , middle-1, targetElement); //search first-half of array
    else
        return binarySearch(arr, middle+1, right, targetElement); //search second-half of array
}

/*Change the way this works.*/
void insertionSortModified(int arr[],int left,int right)
{

    for (int i = left+1; i <= right; ++i) //loop starts at first element of unsorted part of array (1) since first element (0) is considered already sorted (thus forming the start of the sorted array)
    {
        int j = i - 1; //point to last element of sorted array for binary search and to shift all elements to the right
        int targetElement = arr[i]; //store target element (first element of unsorted part of array) for binary search comparison and to prevent being overwritten when shifting occurs
        int targetLocation = binarySearch(arr, left, j, targetElement); //search and retrieve the target location

        //shift all elements in the sorted part of the array to the right to create a spot for inserting the target element in the target location
        while (j >= targetLocation)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[targetLocation] = targetElement; //place the target element in the correct spot
    }

}
int partition(int array[],int left, int right){

    int pivot = array[((left + right) / 2)];
    int temp = array[right];
    array[right] = pivot;
    array[((left + right) / 2)] = temp;

   int i=left-1;
   for(int j=left;j<right;j++){
      if(array[j]<=pivot){
         i=i+1;
         int tmp=array[i];
         array[i]=array[j];
         array[j]=tmp;
      }
   }
   int tmp=array[i+1];
   array[i+1]=array[right];
   array[right]=tmp;
   return i+1;
}



void quickSortModified(int arr[], int left, int right,int threshold){

   if(right-left <= threshold){
      insertionSortModified(arr,left,right);
   }
   else{
      int i = partition(arr,left,right);
      quickSortModified(arr,left,i-1, threshold);
      quickSortModified(arr,i+1,right, threshold);
   } 
}

void quickSortModified(int arr[],int size,int threshold){
   quickSortModified(arr,0,size-1,threshold);
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[],int left,int right){
   int curr;
   int i, j;
   for(i=left+1;i<=right;i++){
      curr=arr[i];
      for(j=i;j>0 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}

void quickSortStandard(int arr[], int left, int right,int threshold){
   if(right-left <= threshold){
      insertionSortStandard(arr,left,right);
   }
   else{
      int i = partition(arr,left,right);
      quickSortStandard(arr,left,i-1, threshold);
      quickSortStandard(arr,i+1,right, threshold);
   }
}
void quickSortStandard(int arr[],int size,int threshold){
   quickSortStandard(arr,0,size-1,threshold);
}

