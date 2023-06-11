/*
    Probleam: Heap Sort.

    Test cases:
    Input:
    4
    4 3 2 6

    Output:
    2 3 4 6
    29


    Input:
    5
    2 3 3 4 6

    Output:
    2 3 3 4 6
    41




    Getting index value
    Parent To Child:
        left: 2i +1
        right: 2i + 2

    Child to Parent: (x-1)/2
*/

#include <iostream>
#include <vector>
using namespace std;
class Heap {
public:
    vector<int> heap;
    void add(int data) {
        heap.push_back(data);
        int x = heap.size() - 1;
        int parent = (x - 1) / 2;
        while (heap[parent] > heap[x]) {
            int temp = heap[parent];
            heap[parent] = heap[x];
            heap[x] = temp;

            x = parent;
            parent = (parent - 1) / 2;
        }
        sort();
    }
    bool isEmpty() {
        return heap.empty();
    }
    int peek() {
        return heap.at(0);
    }
    void remove(int idx) {
        if (idx == heap.size() - 1) {
            heap.erase(heap.begin() + idx);
            return;
        }
        heap[idx] = heap[heap.size() - 1];
        heap.erase(heap.begin() + heap.size() - 1);
        heapify(heap, idx, heap.size());
    }
    void heapify(vector<int>& arr, int idx = 0,
        int last = 0, bool isMaxHeep = true) {
        if (idx == last - 1) {
            return;
        }
        int left = (2 * idx) + 1;
        int right = (2 * idx) + 2;
        int minIdx = idx;
        if (left < last && (!isMaxHeep ? arr[minIdx] < arr[left]
            : arr[minIdx] > arr[left])) {
            minIdx = left;
        }
        if (right < last && (!isMaxHeep ? arr[minIdx] < arr[right]
            : arr[minIdx] > arr[right])) {
            minIdx = right;
        }
        if (minIdx != idx) {
            int temp = arr[minIdx];
            arr[minIdx] = arr[idx];
            arr[idx] = temp;
            heapify(arr, minIdx, last, isMaxHeep);
        }
    }

    void sort(bool isDsc = false) {
        for (int i = heap.size() / 2;i >= 0;i--) {
            heapify(heap, i, heap.size(), isDsc);
        }
        for (int i = heap.size() - 1;i >= 0;i--) {
            int temp = heap[i];
            heap[i] = heap[0];
            heap[0] = temp;
            heapify(heap, 0, i, isDsc);
        }
    }

    int findMinimumAmount() {
        if (heap.size() <= 1) {
            return 0;
        }
        int sum = heap[0] + heap[1];
        heap.erase(heap.begin(), heap.begin() + 2);
        add(sum);
        int minimumAmount = findMinimumAmount();
        return sum + minimumAmount;
    }

    void print(vector<int> heap) {
        for (int i = 0;i < heap.size();i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};
int main() {
    int n;
    cin >> n;
    Heap* heap = new Heap();
    for (int i = 0;i < n;i++) {
        int a;
        cin >> a;
        heap->add(a);
    }
    heap->print(heap->heap);
    cout << heap->findMinimumAmount();
    return 0;
}