#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include "common.h"

namespace siberia::base {
    template <typename T>
    class DynamicArray {
    private:
        T *arr;
        int len, capacity_;

        void adjust_capacity(int new_len) {
            if (new_len < capacity_ / 2) {
                T *new_arr = (T *) malloc(capacity_ / 2 * sizeof(T));
                memset(new_arr, 0, capacity_ / 2 * sizeof(T));
                for (int i = 0; i < new_len; i++) new_arr[i] = arr[i];
                free(arr);
                arr = new_arr;
                capacity_ /= 2;
            } else if (new_len >= capacity_) {
                T *new_arr = (T *) malloc(capacity_ * 2 * sizeof(T));
                memset(new_arr, 0, capacity_ * 2 * sizeof(T));
                for (int i = 0; i < len; i++) new_arr[i] = arr[i];
                free(arr);
                arr = new_arr;
                capacity_ *= 2;
            }
        }
        void init_arr(int new_len) {
            if (new_len == 0) capacity_ = 1;
            else capacity_ = new_len;
            arr = (T *) malloc(capacity_ * sizeof(T));
            memset(arr, 0, capacity_ * sizeof(T));
            len = new_len;
        }
    public:
        DynamicArray() {
            init_arr(0);
        }
        DynamicArray(int len) {
            init_arr(len);
        }
        DynamicArray(T *buf, int len) : len(len), capacity_(len) {
            init_arr(len);
            for (int i = 0; i < len; i++) append(buf[i]);
        }
        DynamicArray(const DynamicArray<T> &other) {
            init_arr(other.len);
            for (int i = 0; i < len; i++) arr[i] = other.arr[i];
        }
        DynamicArray(DynamicArray<T> &&other) {
            arr = other.arr;
            len = other.len;
            capacity_ = other.capacity_;
            other.arr = NULL;
        }
        DynamicArray &operator=(const DynamicArray<T> &other) {
            free(arr);
            init_arr(other.len);
            for (int i = 0; i < len; i++) arr[i] = other.arr[i];
            return *this;
        }
        DynamicArray &operator=(DynamicArray<T> &&other) {
            free(arr);
            arr = other.arr;
            len = other.len;
            capacity_ = other.capacity_;
            other.arr = NULL;
            return *this;
        }
        ~DynamicArray() { free(arr); }
        void append(const T &value) {
            adjust_capacity(len + 1);
            arr[len++] = value;
        }

        void insert(int index, const T &value) {
            adjust_capacity(len + 1);
            for (int i = len - 1; i >= index; i++) arr[i + 1] = arr[i];
            arr[index] = value;
            len++;
        }

        void remove(int index) {
            for (int i = index; i < len - 1; i++) arr[i] = arr[i + 1];
            adjust_capacity(len - 1);
            len--;
        }

        void extend(const DynamicArray<T> &other) {
            for (int i = 0; i < other.size(); i++) append(other[i]);
        }

        bool empty() const { return !len; }

        void clear() {
            free(arr);
            init_arr(0);
        }

        void reverse() {
            for (int i = 0; i < len / 2; i++) {
                T temp = arr[i];
                arr[i] = arr[len - 1 - i];
                arr[len - 1 - i] = temp;
            }
        }

        T &operator[](int index) {
            return arr[index];
        }

        const T &operator[](int index) const {
            return arr[index];
        }

        DynamicArray<T> operator+(const DynamicArray<T> &other) {
            DynamicArray<T> res = *this;
            for (int i = 0; i < other.size(); i++) res.append(other[i]);
            return res;
        }

        DynamicArray<T> operator+=(const DynamicArray<T> &other) {
            for (int i = 0; i < other.size(); i++) append(other[i]);
            return *this;
        }

        int size() const { return len; }
        int capacity() const { return capacity_; }
        T *buffer() const { return arr; }
    };
}

#endif