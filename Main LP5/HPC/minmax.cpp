#include <iostream>
#include <omp.h>
#include <climits>
#include <cstdlib>
using namespace std;

int main() {
    const int n = 100000;
    int* arr = new int[n];

    // Fill array with sample data
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    // Display first 10 elements for reference
    cout << "Sample elements: ";
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << "...\n";

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    long long sum = 0; // safer with large arrays
    double avg = 0.0;

    double start = omp_get_wtime();

    // Parallel Reduction
    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
        sum += arr[i];
    }

    avg = static_cast<double>(sum) / n;

    double end = omp_get_wtime();

    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Execution Time: " << end - start << " seconds\n";

    delete[] arr;
    return 0;
}
