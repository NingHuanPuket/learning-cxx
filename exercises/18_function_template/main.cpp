#include "../exercise.h"
#include <cmath>  // For std::fabs

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>

// 定义一个函数模板
template <typename T>
T plus(T a, T b) {
    return a + b;
}

// 对于浮点数的比较，我们定义一个辅助函数来检查近似相等
bool are_close(double a, double b, double epsilon = 1e-10) {
    return std::fabs(a - b) < epsilon;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    
    // 使用 are_close 函数比较浮点数的近似相等
    ASSERT(are_close(plus(0.1, 0.2), 0.3), "How to make this pass?");

    return 0;
}
