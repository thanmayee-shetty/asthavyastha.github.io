
#include <iostream>
#include<algorithm>
using namespace std;

// Function to swap two elements
// void swap(int& a, int& b) {
//     int t = a;
//     a = b;
//     b = t;
// }

// Partition function
int Partition(int A[], int l, int r) {
    int p = A[l];
    int i = l;
    int j = r + 1;

    while (true) {
        while (A[++i] < p) {
            if (i == r) break;
        }
        while (A[--j] > p) {
            if (j == l) break;
        }
        if (i >= j) break;
        swap(A[i], A[j]);
    }
    swap(A[l], A[j]);
    return j;
}

// Quicksort function
void QuickSort(int A[], int l, int r) {
    if (l < r) {
        int s = Partition(A, l, r);
        QuickSort(A, l, s - 1);
        QuickSort(A, s + 1, r);
    }
}

// Utility function to print the array
void PrintArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// Main function
int main() {
    int A[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(A) / sizeof(A[0]);

    cout << "Unsorted array: ";
    PrintArray(A, n);

    QuickSort(A, 0, n - 1);

    cout << "Sorted array: ";
    PrintArray(A, n);
    return 0;
}

