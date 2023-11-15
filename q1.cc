/**
 * @file q1.cc
 * 
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;


int sparseRodCutting(const unordered_map<int, int>& prices, int length);


int main() {

    ofstream fout("output_q1.csv");

    //map to hold prices
    //keys are lengths, values are prices
    unordered_map<int, int> prices = {{1,1}, {2,5}, {4,9}, {6,17}, {8,20}, {10,30}, {12,36}, {16,48}};

    vector<int> lengths = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};

    fout << "Sparse Rod Cutting Algorithm" << endl;
    fout << "Length,Runtime(microseconds)" << endl;
    //1A Sparse Price Rod Algorithm
    for (size_t i = 0; i < lengths.size(); i++){
        auto start = high_resolution_clock::now();
        int maxRevenue = sparseRodCutting(prices, lengths[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Max Revenue for length " << lengths[i] << " is: " << maxRevenue << endl;
        cout << "Time to run for " << lengths[i] << " is: " << duration.count() << " microseconds" << endl;
        fout << lengths[i] << "," << duration.count() << endl;
    }
    fout.close();

}


int sparseRodCutting(const unordered_map<int, int>& prices, int length) {
    unordered_map<int, int> maxRevenue; //O(1) lookup

    // Base case: no rod
    maxRevenue[0] = 0; //O(1) lookup

    for (int i = 1; i <= length; ++i) { //O(n)
        int maxVal = -1;

        // Iterate over all possible cuts for the current length
        for (const auto& entry : prices) { //O(n)
            int cutLength = entry.first; //O(1) lookup
            int cutPrice = entry.second; //O(1) lookup

            if (cutLength <= i) { //O(1)
                // Calculate the maximum revenue for the current length
                maxVal = max(maxVal, cutPrice + maxRevenue[i - cutLength]); //O(1)
            }
        }

        // Store the maximum revenue for the current length
        maxRevenue[i] = maxVal; //O(1)
    }

    return maxRevenue[length]; //O(1)
}