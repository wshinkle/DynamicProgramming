#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int getNumWays(int x, vector<int> coins, int num_coins);
void changeCombos(vector<int> coins, int experimentAmount);

int main(int argc, char **argv)
{
    ofstream fout("output_q2.csv");
    vector<int> currency = {1, 5, 10, 25, 50, 100, 200, 1000, 2000};
    vector<int> wizard = {1, 29, 493};
    vector<int> experiment1 = {10, 50, 100, 500, 1000, 1500, 2000, 3000, 5000};
    vector<int> experiment2 = {10, 25, 50, 100, 200, 500};

    // 2A. Original algorithm with US currency
    cout << "Starting US currency experiment" << endl;
    fout << "Original Algorithm with US Currency" << endl;
    fout << "Experiment,Runtime(microseconds)" << endl;
    for (int i = 0; i < experiment1.size(); i++)
    {
        auto start = high_resolution_clock::now();
        getNumWays(experiment1[i], currency, 9);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to run for  " << experiment1[i] << " is: " << duration.count() << " microseconds" << endl;
        fout << experiment1[i] << "," << duration.count() << endl;
    }
    fout << endl;
    // 2B. Original algorithm with wizard currency
    cout << "Starting wizard currency experiment" << endl;
    fout << "Original Algorithm with Wizard Currency" << endl;
    fout << "Experiment,Runtime(microseconds)" << endl;
    for (int i = 0; i < experiment1.size(); i++)
    {
        auto start = high_resolution_clock::now();
        getNumWays(experiment1[i], wizard, 3);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to run for " << experiment1[i] << " is: " << duration.count() << " microseconds" << endl;
        fout << experiment1[i] << "," << duration.count() << endl;
    }
    fout << endl;

    // 2C.1 Custom algorithm with US currency
    cout << "Starting custom US currency experiment" << endl;
    fout << "Custom Algorithm with US Currency" << endl;
    fout << "Experiment,Runtime(microseconds)" << endl;
    for (int i = 0; i < experiment2.size(); i++)
    {
        auto start = high_resolution_clock::now();
        changeCombos(currency, experiment2[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to run for " << experiment2[i] << " is: " << duration.count() << " microseconds" << endl;
        fout << experiment2[i] << "," << duration.count() << endl;
    }
    fout << endl;
    // 2C.2 Custom algorithm with wizard currency
    cout << "Starting custom wizard currency experiment" << endl;
    fout << "Custom Algorithm with Wizard Currency" << endl;
    fout << "Experiment,Runtime(microseconds)" << endl;
    for (int i = 0; i < experiment2.size(); i++)
    {
        auto start = high_resolution_clock::now();
        changeCombos(wizard, experiment2[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to run for " << experiment2[i] << " is: " << duration.count() << " microseconds" << endl;
        fout << experiment2[i] << "," << duration.count() << endl;
    }
    fout.close();
}   

int getNumWays(int x, vector<int> coins, int num_coins)
{
    vector<int> ways(x + 1, 0);
    ways[0] = 1;
    for (int i = 0; i < num_coins; i++)
    {
        for (int j = coins[i]; j <= x; j++)
        {
            ways[j] += ways[j - coins[i]];
        }
    }
    return ways[x];
}

void changeCombos(vector<int> coins, int experimentAmount)
{
    int num_coins = coins.size();
    vector<vector<vector<int>>> combinations(experimentAmount + 1); //O(n)

    // Initialize the base case: there is one way to make change for amount 0 (using 0 coins)
    combinations[0].push_back({}); //O(1)

    for (int i = 0; i < num_coins; i++) //O(n)
    {
        for (int j = coins[i]; j <= experimentAmount; j++) //O(n)
        {
            for (int k = 0; k < combinations[j - coins[i]].size(); k++) //O(n)
            {
                vector<int> temp_combination = combinations[j - coins[i]][k];
                temp_combination.push_back(coins[i]);
                combinations[j].push_back(temp_combination);
            }
        }
    }
    size_t num_combinations = combinations[experimentAmount].size();
    cout << "There are " << num_combinations << " ways to make change for " << experimentAmount << " cents." << endl;
    for (size_t i = 0; i < num_combinations; i++)
    {
        cout << "Combination " << i + 1 << ": [";
        for (size_t j = 0; j < combinations[experimentAmount][i].size(); j++)
        {   
            if(j == combinations[experimentAmount][i].size() - 1){
                cout << combinations[experimentAmount][i][j];
                break;
            }
            cout << combinations[experimentAmount][i][j] << ", ";
        }
        cout << "]" <<endl;
    }
}