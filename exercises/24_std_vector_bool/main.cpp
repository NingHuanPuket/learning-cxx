#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true); // 使用构造函数初始化100个元素为true
    ASSERT(vec[0], "Make this assertion pass."); // 期望 vec[0] 为 true
    ASSERT(vec[99], "Make this assertion pass."); // 期望 vec[99] 为 true
    ASSERT(vec.size() == 100, "Make this assertion pass."); // size 应该是 100
    ASSERT(sizeof(vec) == sizeof(std::vector<bool>), "Fill in the correct value."); // `sizeof(vec)` 为 std::vector<bool> 对象的大小

    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`."); // `vec[20]` 现在是 false，使用 `!` 确认
    }

    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value."); // size 应该变成 101
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`."); // `vec[100]` 是新添加的元素，应为 false
    }

    {
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`"); // `vec[30]` 应该是 true
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`"); // 修改后 `ref` 应该是 false
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`."); // `vec[30]` 也应该是 false
    }
    
    return 0;
}
