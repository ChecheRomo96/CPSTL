#include <iostream>
#include <CPvector>
#include <CPstring>
#include <CPiterator.h>
#include <cassert>


static void TestBeginEndArray() {
    int arr[5] = { 10, 20, 30, 40, 50 };

    int* b = cpstd::begin(arr);
    int* e = cpstd::end(arr);

    assert(b == &arr[0]);
    assert(e == &arr[5]);
    assert((e - b) == 5);

    std::cout << "[OK] begin/end con array\n";
}

static void TestBeginEndVector() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::vector<int>::iterator b = cpstd::begin(v);
    std::vector<int>::iterator e = cpstd::end(v);

    assert(*b == 1);
    assert((e - b) == 3);

    std::cout << "[OK] begin/end con vector\n";
}

static void TestIteratorTraitsPointer() {
    typedef cpstd::iterator_traits<int*> traits;

    // Si compila, ya resolvió:
    // difference_type, value_type, pointer, reference, iterator_category
    traits::difference_type d = 7;
    (void)d;

    int x = 123;
    traits::pointer p = &x;
    traits::reference r = *p;

    assert(p == &x);
    assert(r == 123);

    std::cout << "[OK] iterator_traits<int*>\n";
}

static void TestReverseIteratorRawPointer() {
    int arr[5] = { 10, 20, 30, 40, 50 };

    cpstd::reverse_iterator<int*> rbegin(arr + 5);
    cpstd::reverse_iterator<int*> rend(arr);

    assert(*rbegin == 50);
    assert(rbegin[0] == 50);
    assert(rbegin[1] == 40);

    cpstd::reverse_iterator<int*> it = rbegin;
    ++it;
    assert(*it == 40);

    --it;
    assert(*it == 50);

    assert(rbegin != rend);
    assert((rend - rbegin) == 5);

    std::cout << "[OK] reverse_iterator con punteros\n";
}

static void TestReverseIteratorComparison() {
    int arr[4] = { 1, 2, 3, 4 };

    cpstd::reverse_iterator<int*> a(arr + 4); // apunta a 4
    cpstd::reverse_iterator<int*> b(arr + 3); // apunta a 3

    assert(*a == 4);
    assert(*b == 3);

    // En reverse_iterator, el orden está invertido
    assert(a < b);
    assert(b > a);
    assert(a <= b);
    assert(b >= a);

    std::cout << "[OK] comparaciones de reverse_iterator\n";
}

static void TestBackInserterLValue() {
    std::vector<int> v;

    cpstd::back_insert_iterator<std::vector<int> > it = cpstd::back_inserter(v);

    *it = 10;
    ++it;
    *it = 20;
    it++;

    assert(v.size() == 2);
    assert(v[0] == 10);
    assert(v[1] == 20);

    std::cout << "[OK] back_inserter con lvalues\n";
}

static void TestBackInserterRValue() {
    std::vector<std::string> v;

    cpstd::back_insert_iterator<std::vector<std::string> > it = cpstd::back_inserter(v);

    std::string s = "hola";
    *it = s;                  // copia
    *it = std::string("mundo"); // rvalue / move si aplica

    assert(v.size() == 2);
    assert(v[0] == "hola");
    assert(v[1] == "mundo");

    std::cout << "[OK] back_inserter con copy/move\n";
}

int main() {
    std::cout << "=== Iniciando pruebas de iterators CPSTL ===\n";

    TestBeginEndArray();
    TestBeginEndVector();
    TestIteratorTraitsPointer();
    TestReverseIteratorRawPointer();
    TestReverseIteratorComparison();
    TestBackInserterLValue();
    TestBackInserterRValue();

    std::cout << "=== Todas las pruebas pasaron ===\n";
    return 0;
}