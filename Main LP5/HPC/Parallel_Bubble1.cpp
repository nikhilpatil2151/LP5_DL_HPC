#include <iostream>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; ++i)
        for (int j = 0; j < n-i-1; ++j)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// Parallel Bubble Sort (Odd-Even Transposition)
void parallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int phase = i % 2;
        #pragma omp parallel for
        for (int j = phase; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Utility to copy array
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; ++i)
        dest[i] = source[i];
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n], seqArr[n], parArr[n];

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    // Display original array
    cout << "\nOriginal Array:\n";
    printArray(arr, n);

    // Copy to both sorting arrays
    copyArray(arr, seqArr, n);
    copyArray(arr, parArr, n);

    // Sequential sort
    double start = omp_get_wtime();
    sequentialBubbleSort(seqArr, n);
    double end = omp_get_wtime();
    cout << "\nSequentially Sorted Array:\n";
    printArray(seqArr, n);
    cout << "Sequential Time: " << end - start << " seconds\n";

    // Parallel sort
    start = omp_get_wtime();
    parallelBubbleSort(parArr, n);
    end = omp_get_wtime();
    cout << "\nParallelly Sorted Array:\n";
    printArray(parArr, n);
    cout << "Parallel Time: " << end - start << " seconds\n";

    return 0;
}
