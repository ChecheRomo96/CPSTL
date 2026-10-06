// Self-checking CPSTL firmware for the ATmega328P, built with the bare AVR-GCC
// toolchain (no Arduino core, no C++ standard library).
//
// Building it proves every module compiles and links for AVR; running it (on
// an Uno or under simavr) checks the results. The verdict goes to USART0 at
// 9600 baud as "CPSTL AVR smoke: PASS" or "... FAIL <n>", where n is the first
// failing check. The MCU then sleeps with interrupts off, which also ends a
// simavr run.

#include <CPSTL.h>
#include <CPlimits.h>
#include <CPmemory.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <stdlib.h>

// cpstd::function and cpstd::unique_ptr allocate with new. AVR-GCC alone has
// no operator new, so firmware that uses them supplies one, as the Arduino
// core does. Containers do not need it: they allocate with malloc in the C
// allocation mode this firmware is built with.
void* operator new(size_t size) { return malloc(size); }
void operator delete(void* ptr) noexcept { free(ptr); }
void operator delete(void* ptr, size_t) noexcept { free(ptr); }

namespace {

    void UartInit() {
        const uint16_t ubrr = static_cast<uint16_t>(F_CPU / 16UL / 9600UL - 1UL);
        UBRR0H = static_cast<uint8_t>(ubrr >> 8);
        UBRR0L = static_cast<uint8_t>(ubrr);
        UCSR0B = static_cast<uint8_t>(1U << TXEN0);
        UCSR0C = static_cast<uint8_t>((1U << UCSZ01) | (1U << UCSZ00));
    }

    void UartPut(char c) {
        while ((UCSR0A & (1U << UDRE0)) == 0) {
        }
        UDR0 = static_cast<uint8_t>(c);
    }

    void UartPrint(const char* text) {
        while (*text != '\0') {
            UartPut(*text++);
        }
    }

    struct Counted {
        static int live;
        int value;
        explicit Counted(int v) : value(v) { ++live; }
        Counted(const Counted& other) : value(other.value) { ++live; }
        ~Counted() { --live; }
        Counted& operator=(const Counted&) = default;
    };
    int Counted::live = 0;

    bool Descending(int a, int b) { return a > b; }

    static_assert(cpstd::is_same<cpstd::remove_const<const int>::type, int>::value,
                  "type_traits");
    static_assert(cpstd::numeric_limits<int16_t>::max() == 32767, "numeric_limits");
    static_assert(cpstd::numeric_limits<uint8_t>::digits == 8, "numeric_limits");

    // Returns 0 when every check passes, otherwise the number of the first
    // failing check.
    int Run() {
        int check = 0;
#define CPSTL_CHECK(condition) \
    do {                       \
        ++check;               \
        if (!(condition)) {    \
            return check;      \
        }                      \
    } while (0)

        // vector: growth, insert, erase, copy, comparison
        cpstd::vector<int> v = {3, 1, 4};
        for (int i = 0; i < 20; ++i) {
            v.push_back(i);
        }
        CPSTL_CHECK(v.size() == 23 && v[3] == 0 && v[22] == 19);
        v.insert(v.begin() + 1, 2, 9);
        CPSTL_CHECK(v.size() == 25 && v[1] == 9 && v[2] == 9 && v[3] == 1);
        v.erase(v.begin() + 3, v.end());
        CPSTL_CHECK(v.size() == 3);
        cpstd::vector<int> copy(v);
        CPSTL_CHECK(copy == v && !(copy < v));
        v.shrink_to_fit();
        CPSTL_CHECK(v.capacity() == 3);

        // vector of a type with a destructor: every element destroyed once
        {
            cpstd::vector<Counted> counted;
            for (int i = 0; i < 8; ++i) {
                counted.push_back(Counted(i));
            }
            counted.erase(counted.begin(), counted.begin() + 3);
            CPSTL_CHECK(Counted::live == 5 && counted[0].value == 3);
        }
        CPSTL_CHECK(Counted::live == 0);

        // algorithm
        int values[] = {5, 3, 8, 1, 9, 2};
        cpstd::sort(values, values + 6);
        CPSTL_CHECK(values[0] == 1 && values[5] == 9);
        cpstd::sort(values, values + 6, Descending);
        CPSTL_CHECK(values[0] == 9 && values[5] == 1);
        CPSTL_CHECK(cpstd::find(values, values + 6, 8) == values + 1);
        CPSTL_CHECK(cpstd::max(3, 7) == 7 && cpstd::min(3, 7) == 3);

        // string and conversions
        cpstd::string text = "rhythm";
        text += ' ';
        text.append(cpstd::to_string(-128));
        CPSTL_CHECK(text == "rhythm -128");
        CPSTL_CHECK(text.find("-1") == 7 && text.substr(0, 3) == "rhy");
        CPSTL_CHECK(cpstd::stoi(text.substr(7)) == -128);
        text.insert(0, 2, '>');
        CPSTL_CHECK(text.size() == 13 && text[0] == '>' && text.c_str()[13] == '\0');
        cpstd::string empty;
        CPSTL_CHECK(empty.empty() && empty.capacity() == 0 && empty.c_str()[0] == '\0');

        // function and unique_ptr (use operator new)
        int total = 0;
        cpstd::function<void(int)> add = [&total](int amount) { total += amount; };
        add(4);
        cpstd::function<void(int)> again = add;
        again(6);
        CPSTL_CHECK(total == 10 && static_cast<bool>(add));
        cpstd::unique_ptr<Counted> owned(new Counted(42));
        CPSTL_CHECK(owned->value == 42 && Counted::live == 1);
        owned.reset();
        CPSTL_CHECK(!owned && Counted::live == 0);

        // stack and queue adapters over cpstd::vector
        {
            cpstd::stack<int> lifo;
            cpstd::queue<int> fifo;
            for (int i = 0; i < 10; ++i) {
                lifo.push(i);
                fifo.emplace(i);
            }
            lifo.pop();
            fifo.pop();
            CPSTL_CHECK(lifo.size() == 9 && lifo.top() == 8);
            CPSTL_CHECK(fifo.size() == 9 && fifo.front() == 1 && fifo.back() == 9);
        }

        // iterator helpers
        CPSTL_CHECK(cpstd::distance(copy.begin(), copy.end()) == 3);
        CPSTL_CHECK(*cpstd::next(copy.begin()) == 9);

#undef CPSTL_CHECK
        return 0;
    }

    void PrintNumber(int n) {
        char digits[6];
        int count = 0;
        do {
            digits[count++] = static_cast<char>('0' + n % 10);
            n /= 10;
        } while (n > 0 && count < 5);
        while (count > 0) {
            UartPut(digits[--count]);
        }
    }
}

int main() {
    UartInit();
    const int failed = Run();
    if (failed == 0) {
        UartPrint("CPSTL AVR smoke: PASS\n");
    } else {
        UartPrint("CPSTL AVR smoke: FAIL ");
        PrintNumber(failed);
        UartPut('\n');
    }
    while ((UCSR0A & (1U << TXC0)) == 0) {
    }
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    for (;;) {
        sleep_cpu();
    }
}
