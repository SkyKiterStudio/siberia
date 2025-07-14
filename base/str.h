#ifndef _STR_H_
#define _STR_H_

#include "dyn_array.h"

namespace siberia::base {
    class String {
    private:
        DynamicArray<char> arr;
    public:
        String() {
            arr.append(0);
        }
        String(char buf) {
            arr.append(buf);
            arr.append(0);
        }
        String(int num) {
            do {
                arr.append(num % 10 + '0');
                num /= 10;
            } while (num);
            arr.reverse();
            arr.append(0);
        }
        String(char *buf) {
            for (; *buf; buf++) arr.append(*buf);
            arr.append(0);
        }

        String(const char *buf) {
            for (; *buf; buf++) arr.append(*buf);
            arr.append(0);
        }

        bool operator<(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) < 0; }
        bool operator>(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) > 0; }
        bool operator<=(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) <= 0; }
        bool operator>=(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) >= 0; }
        bool operator!=(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) != 0; }
        bool operator==(const String &other) const { return strcmp(arr.buffer(), other.arr.buffer()) == 0; }

        String operator+(const String &other) {
            String res = *this;
            res.arr = arr;
            res.arr.remove(res.arr.size() - 1);
            res.arr += other.arr;
            return res;
        }

        String operator+=(const String &other) {
            arr.remove(arr.size() - 1);
            arr += other.arr;
            return *this;
        }

        char &operator[](int i) { return arr[i]; }
        char operator[](int i) const { return arr[i]; }

        char *c_str() {
            return arr.buffer();
        }

        void reverse() {
            arr.reverse();
        }

        int size() { return arr.size() - 1; }
    };
}

#endif