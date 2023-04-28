#include <vector>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() {}

    bool empty() const {
        return heap.empty();
    }

    int size() const {
        return heap.size();
    }

    void push(T val) {
        heap.push_back(val);
        int index = heap.size() - 1;
        while (index > 0 && heap[parent(index)].first < heap[index].first) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    T top() const {
        return heap.front();
    }

    void pop() {
        if (heap.size() == 1) {
            heap.pop_back();
        } else {
            heap[0] = heap.back();
            heap.pop_back();
            heapify(0);
        }
    }

private:
    std::vector<T> heap{};

    int parent(int index) const {
        return (index - 1) / 2;
    }

    int left(int index) const {
        return 2 * index + 1;
    }

    int right(int index) const {
        return 2 * index + 2;
    }

    void heapify(int index) {
        int largest = index;
        int l = left(index);
        int r = right(index);

        if (l < (int)heap.size() && heap[l].first > heap[largest].first)
            largest = l;

        if (r < (int)heap.size() && heap[r].first > heap[largest].first)
            largest = r;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapify(largest);
        }
    }
};
