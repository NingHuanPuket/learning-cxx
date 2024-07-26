#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

struct TaggedUnion {
    DataType type;
    union {
        float f;
        double d;
    };

    // 帮助函数，用于确定正确的数据类型
    TaggedUnion(DataType t) : type(t) {
        if (t == DataType::Float) {
            f = 0.0f;
        } else {
            d = 0.0;
        }
    }

    // 析构函数来避免未定义行为
    ~TaggedUnion() {
        // 不需要具体实现，因为union成员不会被显式地析构
    }
};

// 定义一个模板化的 sigmoid 函数
template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    if (x.type == DataType::Float) {
        ans.f = sigmoid(x.f);
    } else if (x.type == DataType::Double) {
        ans.d = sigmoid(x.d);
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(fabs(yf.f - (1 / (1 + std::exp(-5.f)))) < 1e-6, "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch"); // Fixed here
    ASSERT(fabs(yd.d - (1 / (1 + std::exp(-5.0)))) < 1e-6, "sigmoid double");
    return 0;
}
