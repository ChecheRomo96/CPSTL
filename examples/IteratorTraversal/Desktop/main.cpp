#include <CPiterator.h>
#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> samples;
    samples.push_back(7);
    samples.push_back(11);
    samples.push_back(13);

    printf("Forward: ");
    for (cpstd::vector<int>::iterator it = samples.begin(); it != samples.end(); ++it) {
        printf("%d ", *it);
    }
    printf("\nReverse: ");
    for (cpstd::vector<int>::reverse_iterator it = samples.rbegin(); it != samples.rend(); ++it) {
        printf("%d ", *it);
    }
    printf("\n");
    return 0;
}
