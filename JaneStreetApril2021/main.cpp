#include "common.h"

int findIndex(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

int intPow(int m, int n) {
    if (!n) return 1;
    return m * intPow(m, n-1);
}

void swapElements(int arr[], int index1, int index2) {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

double getProbability(int arr[], int round, int index, map<pair<int, int>, double>& memo) {
    if (!round) {
        if (index % 2) return double(arr[index - 1]) / double(arr[index] + arr[index - 1]);
        else return double(arr[index + 1]) / double(arr[index] + arr[index + 1]);
    }
    if (memo.count({ round,index })) return memo[{round, index}];
    int x1 = intPow(2, round);
    int x2 = 2 * x1;
    int i;
    double res = 0;
    if (index % x2 >= x1) {
        i = x1 * (index / x1);
        for (int j = 0; j < x1; j++) {
            res += getProbability(arr, round - 1, i - j - 1, memo) * double(arr[i - j - 1])/double(arr[i - j - 1] + arr[index]);
        }
    }
    else {
        i = x1 * (index / x1 + 1);
        for (int j = 0; j < x1; j++) {
            res += getProbability(arr, round - 1, i + j, memo) * double(arr[i + j]) / double(arr[i + j] + arr[index]);
        }
    }
    res = res * getProbability(arr, round - 1, index, memo);
    memo[{round, index}] = res;
    return res;
}

int main() {
	int bracket[16] = {1, 16, 8, 9, 5, 12, 4, 13, 6, 11, 3, 14, 7, 10, 2, 15};
    map<pair<int, int>, double> memo;
    double prob, bestProb = 0, initProb = getProbability(bracket, 3, 14, memo);
    cout << "The initial probability is " << initProb << endl;
    pair<int, int> bestSwap;
    for (int i = 0; i < 16; i++) {
        for (int j = i+1; j < 16; j++) {
            memo.clear();
            swapElements(bracket, i, j);
            int index = findIndex(bracket, 16, 2);
            prob = getProbability(bracket, 3, index, memo);
            cout << "Swapping " << bracket[i] << " and " << bracket[j] << " yields a probability of " << prob << endl;
            if (prob > bestProb) {
                bestProb = prob;
                bestSwap = {i ,j};
            }
            swapElements(bracket, i, j);
        }
    }
    cout << "The best swap is " << bracket[bestSwap.first] << " and " << bracket[bestSwap.second] << " with a probability increase of " << bestProb - initProb << endl;
    return 0;
}