//
// Created by aboba on 9/26/2023.
//

#ifndef LABB1_ARRLIST_H
#define LABB1_ARRLIST_H

#include <iostream>
#include <vector>

using namespace std;


template<typename T>
class arrList {
private:
    T *array{};
    int size{};
    int capacity{};
    const int INITIAL_CAPACITY = 10;

    int find(T key) {
        for (int i = 0; i < size; i++) {
            if (array[i] == key) {
                return i;
            }
        }
        return -1;
    }

    void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void quickSortRecur(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            quickSortRecur(low, pivotIndex - 1);
            quickSortRecur(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        T pivot = array[high];
        int index = (low - 1);

        for (int i = low; i <= high - 1; i++) {
            if (array[i] < pivot) {
                index++;
                swap(array[index], array[i]);
            }
        }

        swap(array[index + 1], array[high]);
        return (index + 1);
    }

    void merge(int left, int middle, int right) {
        int subArrayOne = middle - left + 1;
        int subArrayTwo = right - middle;

        T *leftArray = new T[subArrayOne];
        T *rightArray = new T[subArrayTwo];

        for (int i = 0; i < subArrayOne; i++) {
            leftArray[i] = array[left + i];
        }
        for (int i = 0; i < subArrayTwo; i++) {
            rightArray[i] = array[middle + 1 + i];
        }

        int i = 0, j = 0;
        int k = left;

        while (i < subArrayOne && j < subArrayTwo) {
            if (leftArray[i] <= rightArray[j]) {
                array[k] = leftArray[i];
                i++;
            } else {
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < subArrayOne) {
            array[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < subArrayTwo) {
            array[k] = rightArray[j];
            j++;
            k++;
        }

        delete[] leftArray;
        delete[] rightArray;
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

    arrList() {
        array = new T[INITIAL_CAPACITY];
        capacity = INITIAL_CAPACITY;
    }

    size_t getSize() {
        return size;
    }

    T* getArrayList(){
        return array;
    }

    void add(T data) {
        if (size == capacity) {
            grow_capacity();
        }
        array[size] = data;
        size++;
    }

    bool insert(T key, T data) {
        int key_index = find(key);
        if (key_index == -1) {
            return false;
        }
        if (size == capacity) {
            grow_capacity();
        }
        key_index++;
        for (int i = size; i > key_index; i--) {
            array[i] = array[i - 1];
        }
        array[key_index] = data;
        size++;
        return true;
    }

    bool remove(T key) {
        int key_index = find(key);
        if (key_index == -1) {
            return false;
        }
        for (int i = key_index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        return true;
    }

    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            swap(array[i], array[minIndex]);
        }
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            T key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    void showList() {
        for (int i = 0; i < size; i++) {
            //cout << " Data in node " << i+1 << " = " << array[i] << endl;
            cout << array[i] << endl;
        }
    }

    void quickSort() {
        quickSortRecur(0, size - 1);
    }

    //taken algorithm and code from this site and rebuild it for myself:https://www.geeksforgeeks.org/merge-sort/

    void mergeSort() {
        mergeSort(0, size - 1);
    }

    friend ostream &operator<<(ostream &out, vector<T> &vectorOut);

    void grow_capacity() {
        capacity *= 2;
        T *new_items = new T[capacity];
        for (int i = 0; i < size; i++) {
            new_items[i] = array[i];
        }
        delete[] array;
        array = new_items;
    }

    ~arrList() {
        delete[] array;
    }
};

#endif //LABB1_ARRLIST_H



