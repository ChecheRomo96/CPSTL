#include <CPSTL.h>
#include <CPexception.h>
#include <stdio.h>

// Reject an invalid sample index and report a recovery action.
int main() {
    printf("Reject an invalid sample index and report a recovery action.\n");
    const int capturedSamples = 4;
    int requestedIndex = 6;
    printf("Captured sample count: %ld\n", static_cast<long>(capturedSamples));
    printf("Valid zero-based indices: 0 through 3.\n");
    printf("Requested index: %ld\n", static_cast<long>(requestedIndex));
    if (requestedIndex < 0 || requestedIndex >= capturedSamples) {
        const cpstd::out_of_range diagnostic("requested sample is outside the capture");
        printf("Request rejected: %s\n", diagnostic.what());
        printf("Recovery: request an index from 0 through 3; no buffer access was attempted.\n");
    }
    printf("The diagnostic object carries a message; this example does not throw an exception.\n");
    return 0;
}
