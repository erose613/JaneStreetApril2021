#include <stdio.h>

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
    return m * intPow(m, n - 1);
}

void swapElements(int arr[], int index1, int index2) {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

double getProbability(int arr[], int round, int index, double memo[16][16]) {
    if (!round) {
        if (index % 2) return (double)arr[index - 1] / (double)(arr[index] + arr[index - 1]);
        else return (double)arr[index + 1] / (double)(arr[index] + arr[index + 1]);
    }
    if (memo[round][index] != 0.0) return memo[round][index];
    int x1 = intPow(2, round);
    int x2 = 2 * x1;
    int i;
    double res = 0;
    if (index % x2 >= x1) {
        i = x1 * (index / x1);
        for (int j = 0; j < x1; j++) {
            res += getProbability(arr, round - 1, i - j - 1, memo) * (double)arr[i - j - 1] / (double)(arr[i - j - 1] + arr[index]);
        }
    }
    else {
        i = x1 * (index / x1 + 1);
        for (int j = 0; j < x1; j++) {
            res += getProbability(arr, round - 1, i + j, memo) * (double)arr[i + j] / (double)(arr[i + j] + arr[index]);
        }
    }
    res = res * getProbability(arr, round - 1, index, memo);
    memo[round][index] = res;
    return res;
}

int main() {
    int bracket[16] = { 1, 16, 8, 9, 5, 12, 4, 13, 6, 11, 3, 14, 7, 10, 2, 15 };
    double memo[16][16] = { 0 }; // Initialize memoization table to zeros
    double prob, bestProb = 0;
    double initProb = getProbability(bracket, 3, 14, memo);
    printf("The initial probability is %lf\n", initProb);
    int bestSwap[2] = { 0 };
    for (int i = 0; i < 16; i++) {
        for (int j = i + 1; j < 16; j++) {
            // Clear memoization table for each iteration
            for (int k = 0; k < 16; k++) {
                for (int l = 0; l < 16; l++) {
                    memo[k][l] = 0;
                }
            }
            swapElements(bracket, i, j);
            int index = findIndex(bracket, 16, 2);
            prob = getProbability(bracket, 3, index, memo);
            printf("Swapping %d and %d yields a probability of %lf\n", bracket[i], bracket[j], prob);
            if (prob > bestProb) {
                bestProb = prob;
                bestSwap[0] = i;
                bestSwap[1] = j;
            }
            swapElements(bracket, i, j);
        }
    }
    printf("The best swap is %d and %d, with a probability increase of %lf\n", bracket[bestSwap[0]], bracket[bestSwap[1]], bestProb - initProb);
    return 0;
}
