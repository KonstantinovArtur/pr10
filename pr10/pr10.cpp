#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        std::vector<int> temp(arr.size());
        MergeSortRecursive(arr, temp, 0, arr.size() - 1);
    }

private:
    void MergeSortRecursive(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        MergeSortRecursive(arr, temp, left, mid);
        MergeSortRecursive(arr, temp, mid + 1, right);
        Merge(arr, temp, left, mid, right);
    }

    void Merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
        int leftEnd = mid;
        int rightStart = mid + 1;
        int leftIndex = left;
        int rightIndex = rightStart;
        int index = left;

        while (leftIndex <= leftEnd && rightIndex <= right) {
            if (arr[leftIndex] <= arr[rightIndex]) {
                temp[index++] = arr[leftIndex++];
            }
            else {
                temp[index++] = arr[rightIndex++];
            }
        }

        while (leftIndex <= leftEnd) {
            temp[index++] = arr[leftIndex++];
        }

        while (rightIndex <= right) {
            temp[index++] = arr[rightIndex++];
        }

        for (index = left; index <= right; ++index) {
            arr[index] = temp[index];
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> arr(10);
    std::cout << "Введите 10 чисел: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> arr[i];
    }

    MergeSort sorter;


    auto sortFunc = [&sorter](std::vector<int>& array) {
        sorter.Sort(array);
        };

  
    std::thread sortingThread(sortFunc, std::ref(arr));

  
    sortingThread.join();

   
    std::cout << "Отсортированный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
