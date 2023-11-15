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
    unordered_map<int, int> maxRevenue;

    // Base case: no rod
    maxRevenue[0] = 0;

    for (int i = 1; i <= length; ++i) {
        int maxVal = -1;

        // Iterate over all possible cuts for the current length
        for (const auto& entry : prices) {
            int cutLength = entry.first;
            int cutPrice = entry.second;

            if (cutLength <= i) {
                // Calculate the maximum revenue for the current length
                maxVal = max(maxVal, cutPrice + maxRevenue[i - cutLength]);
            }
        }

        // Store the maximum revenue for the current length
        maxRevenue[i] = maxVal;
    }

    return maxRevenue[length];
}