/*   Convert this program to C++

*   change to C++ io

*   change to one line comments

*   change defines of constants to const

*   change array to vector<>

*   inline any short function

*/

#include <iostream>
#include <vector>

// This allows you to avoid writing the std:: prefix when using cout, vector, or string.
using namespace std;

const int N = 40; // Declare a constant for the size of the vector.

/**
 * @brief Calculates the sum of all elements in a vector.
 * 
 * @param array The input vector containing integers.
 * @return The total sum of all elements in the vector.
 */
int sumArray(const vector<int> &array)
{
    int sum = 0; // Initialize sum to 0.

    // Loop through each element in the vector and add it to the sum.
    for (int num : array)
    {
        sum += num;
    }

    return sum; // Return the final computed sum.
}

int main()
{
    int accum = 0;        // Initialize accum to store the final sum.
    vector<int> array(N); // Create a vector with N elements.

    // Fill the vector with sequential values (0, 1, 2, ..., N-1).
    for (int i = 0; i < N; ++i)
    {
        array[i] = i;
    }

    // Calculate the sum of the vector elements.
    accum = sumArray(array);

    // Print the sum using C++'s standard output.
    cout << "sum is " << accum << endl;

    return 0; // Return 0 to indicate successful program execution.
}
