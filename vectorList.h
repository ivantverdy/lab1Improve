//
// Created by aboba on 9/26/2023.
//

#ifndef LABB1_VECTORLIST_H
#define LABB1_VECTORLIST_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class vectorList {
private:
    vector<T> vec{};


    void merge(int left, int middle, int right) {
        int subVectorOne = middle - left + 1;
        int subVectorTwo = right - middle;

        vector<T> leftVector(vec.begin() + left, vec.begin() + left + subVectorOne);
        vector<T> rightVector(vec.begin() + middle + 1, vec.begin() + middle + 1 + subVectorTwo);

        int i = 0, j = 0;
        int k = left;

        while (i < subVectorOne && j < subVectorTwo) {
            if (leftVector[i] <= rightVector[j]) {
                vec[k] = leftVector[i];
                i++;
            } else {
                vec[k] = rightVector[j];
                j++;
            }
            k++;
        }

        while (i < subVectorOne) {
            vec[k] = leftVector[i];
            i++;
            k++;
        }

        while (j < subVectorTwo) {
            vec[k] = rightVector[j];
            j++;
            k++;
        }
    }

    void mergeSort(int begin, int end) {
        if (begin >= end)
            return;

        int mid = begin + (end - begin) / 2;
        mergeSort(begin, mid);
        mergeSort(mid + 1, end);
        merge(begin, mid, end);
    }

public:

    vectorList() = default;

    void showList() {
        cout << vec;
    }

    vector<T> getVectorList() {
        return vec;
    }

    void add(T data) {
        vec.push_back(data);
    }

    void remove(T &key) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == key) {
                vec.erase(vec.begin()+i);
            }
        }
    }

    void removeLast() {
        vec.pop_back();
    }

    void insert(T key, T data) {
        vec.insert(key, data);
    }

    void quickSort() {
        sort(vec.begin(), vec.end());
    }

    size_t getSize(){
        return vec.size();
    }

    void insertionSort() {
        for (int i = 1; i < vec.size(); i++) {
            T key = vec[i];
            int j = i - 1;
            while (j >= 0 && vec[j] > key) {
                vec[j + i] = vec[j];
                j--;
            }
            vec[j + 1] = key;
        }
    }

    void mergeSort() {
        mergeSort(0, vec.size() - 1);
    }

    friend ostream &operator<<(ostream &out, vector<T> &vectorOut);
    friend ostream &operator<<(ostream &out, vectorList<T> &vectorOut);
};


#endif //LABB1_VECTORLIST_H
