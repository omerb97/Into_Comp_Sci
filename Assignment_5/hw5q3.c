#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EDGE_CUT 2

void PrintLength();
void PrintArray();
void PrintSum();
void PrintExist();
void PrintDoNotExist();
void swap(int* num1, int* num2);
void bubble_sort (int* array, int length);
bool bubble (int* array, int length);
bool three_digit_exists (int* array, int length, int requiredSum);

//main function that initiates the program and calls all the other functions
int main (){
    int arrayLength;
    int requiredSum;
    int *array;
    PrintLength();
    scanf("%d", &arrayLength);
    array = (int*)malloc(sizeof(int)*arrayLength);
    PrintArray();
    for (int i=0;i<arrayLength;i++){ // gets the array input
        int num;
        scanf("%d", &num);
        array[i] = num;
    }
    bubble_sort(array, arrayLength);
    PrintSum();
    scanf("%d", &requiredSum);
    bool result = three_digit_exists(array, arrayLength, requiredSum);
    if (result)
        PrintExist();
    else
        PrintDoNotExist();

    free(array);
    return 0;
}

// function that finds whether the function has the 3 numbers
bool three_digit_exists (int* array, int length, int requiredSum){
    int right, left;
    int fixedEdge = length-EDGE_CUT;
    for (int i = 0; i<fixedEdge; i++){ // goes through the whole array numbers as num1 of the three numbers
        left = i+1; //the minimum number after num1
        right = length-1; // maximum of the array
        while (left<right){//cuts the array from both ends
            if (array[i] + array[right] + array[left] == requiredSum)
                return true;
            if (array[i] + array[right] + array[left] < requiredSum)
                left++;
            if (array[i] + array[right] + array[left] > requiredSum)
                right--;
        }
    }
    return false;
}

//initiates the bubble sort
void bubble_sort (int* array, int length){
    int notSorted = true;
    while ((length>1) && notSorted){
        notSorted = bubble(array, length--);
    }
}

//sorts the array from minimum to maximum using the bubble method
bool bubble (int* array, int length){
    int swapped = false;
    for (int i= 1; i<length; i++){
        if (array[i-1]>array[i]){
            swap(&array[i], &array[i-1]);
            swapped =true;
        }
    }
    return swapped;
}

//swaps two numbers in the array (for the bubble sort)
void swap (int* num1, int* num2){
    int tempNum = *num1;
    *num1 = *num2;
    *num2= tempNum;
}


int* ArrayInput (int* array, int length){
    if (length==0){
        return array;
    } else{
        int num;
        scanf("%d", &num);
        array[length-1]= num;
        return ArrayInput(array, length-1);
    }
}
void PrintLength()
{
    printf("Please enter length:\n");
}

void PrintArray()
{
    printf("Please enter array:\n");
}

void PrintSum()
{
    printf("Please enter sum:\n");
}

void PrintExist()
{
    printf("Such elements do exist.");
}

void PrintDoNotExist()
{
    printf("Such elements do not exist.");
}