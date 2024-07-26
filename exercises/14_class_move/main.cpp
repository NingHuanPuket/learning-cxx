#include "../exercise.h"
#include <utility> // For std::move

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]), cached(1), capacity(capacity) {
        if (capacity > 0) {
            cache[0] = 0;
            if (capacity > 1) {
                cache[1] = 1;
            }
        }
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr;
        other.cached = 0;
        other.capacity = 0;
    }

    // 移动赋值运算符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            // 释放当前对象的资源
            delete[] cache;

            // 转移资源
            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;

            // 清空源对象
            other.cache = nullptr;
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 缓存优化斐波那契计算
    size_t operator[](int i) {
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        if (i <= cached) {
            return cache[i];
        }
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i;
        return cache[i];
    }

    // const 方法重载
    size_t operator[](int i) const {
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        if (i <= cached) {
            return cache[i];
        }
        throw std::runtime_error("Value not calculated");
    }

    // 检查对象是否有效
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
