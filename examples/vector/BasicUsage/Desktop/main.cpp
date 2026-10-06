// cpstd::vector: building, growing, inserting, erasing and the capacity that
// makes push_back cheap.

#include <CPvector>

#include <stdio.h>

namespace {
    void Print(const char* label, const cpstd::vector<int>& v) {
        printf("%-28s [", label);
        for (cpstd::size_t i = 0; i < v.size(); ++i) {
            printf(i == 0 ? "%d" : ", %d", v[i]);
        }
        printf("]  size %u, capacity %u\n", static_cast<unsigned>(v.size()),
               static_cast<unsigned>(v.capacity()));
    }
}

int main() {
    cpstd::vector<int> v = {3, 1, 4};
    Print("{3, 1, 4}", v);

    v.push_back(1);
    v.push_back(5);
    Print("push_back(1), push_back(5)", v);

    v.insert(v.begin() + 1, 2, 9);
    Print("insert 2 x 9 at 1", v);

    v.erase(v.begin(), v.begin() + 3);
    Print("erase first 3", v);

    cpstd::vector<int> grown;
    unsigned reallocations = 0;
    cpstd::size_t capacity = grown.capacity();
    for (int i = 0; i < 100; ++i) {
        grown.push_back(i);
        if (grown.capacity() != capacity) {
            ++reallocations;
            capacity = grown.capacity();
        }
    }
    printf("100 push_backs: %u reallocations, capacity %u\n", reallocations,
           static_cast<unsigned>(grown.capacity()));

    cpstd::vector<int> reserved;
    reserved.reserve(100);
    const cpstd::size_t before = reserved.capacity();
    for (int i = 0; i < 100; ++i) {
        reserved.push_back(i);
    }
    printf("reserve(100) first: capacity unchanged = %s\n",
           reserved.capacity() == before ? "yes" : "no");

    const bool ok = v.size() == 4 && v[0] == 1 && v[1] == 4 && v[3] == 5 && reallocations <= 8 &&
                    reserved.capacity() == before && grown[99] == 99;
    printf("Self-check: %s\n", ok ? "ok" : "FAILED");
    return ok ? 0 : 1;
}
