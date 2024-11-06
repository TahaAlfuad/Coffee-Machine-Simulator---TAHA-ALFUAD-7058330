#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);

bool isValid( const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int [nRows], int [nCols], int arr2d[nRows][nCols]);
void trans_matrix(int [nRows], int [nCols], const int mat[nRows][nCols], int matt[nCols][nRows]);
bool found_duplicate(int arr[], int length);


int main() {
int arr[SIZE];
int arr2d[nRows][nCols];
int test_pos;

for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1; 
    }

for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = (i * nCols) + (j + 1);
        }
    }


print_array(arr, SIZE);


int pos_remove = 5; 
    printf("\nRemoving element at position %d:\n", pos_remove);
    remove_element(arr, SIZE, pos_remove);

    // after removing
print_array(arr, SIZE);
print_matrix(arr2d,nRows);

test_pos = 19; 
    if (isValid(arr, SIZE, test_pos)) {
        printf("Position %d is valid in the array.\n", test_pos);
    } else {
        printf("Position %d is invalid in the array.\n", test_pos);
    }
    
 test_pos = 25; 
    if (isValid(arr, SIZE, test_pos)) {
        printf("Position %d is valid in the array.\n", test_pos);
    } else {
        printf("Position %d is invalid in the array.\n", test_pos);
    }

 test_pos = 12; 
    if (isValid(arr, SIZE, test_pos)) {
        printf("Position %d is valid in the array.\n", test_pos);
    } else {
        printf("Position %d is invalid in the array.\n", test_pos);
    }
    
  test_pos = 56; 
    if (isValid(arr, SIZE, test_pos)) {
        printf("Position %d is valid in the array.\n", test_pos);
    } else {
        printf("Position %d is invalid in the array.\n", test_pos);
    }

//Call to different functions
}





void print_array(int array[], int length){
   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

bool isValid(const int arr[], int length, int pos) {
    if(pos >= 0 && pos < length){
        return true;
    } else { 
        return false;
    }
}

void remove_element(int arr[], int length, int pos) {
    
    if (!isValid(arr, length, pos)) {
        printf("Position %d is invalid. No element will be removed.\n", pos);
        return; 
    }

  
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }

    printf("Element at position %d has been removed.\n", pos);
}