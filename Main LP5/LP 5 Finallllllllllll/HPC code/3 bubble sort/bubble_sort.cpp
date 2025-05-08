#include <iostream>
#include <omp.h>
using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter the size of array : ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements : ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int arr1[n], arr2[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
    }

    sequentialBubbleSort(arr1, n);
    parallelBubbleSort(arr2, n);

    cout << "Sorted array using Sequential method : ";
    for (int i = 0; i < n; i++)
        cout << arr1[i] << " ";
    cout << "\nSorted array using Parallel method: ";
    for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";
    cout << endl;

    return 0;
}

// inputs :
//  Enter the size of array : 8
//  Enter the elements : 9 7 3 1 6 2 8 5
