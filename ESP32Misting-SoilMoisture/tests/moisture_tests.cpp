#include "moisture.h"
#include <assert.h>
#include <stdio.h>

int main() {
    // Basic sanity tests for mapping logic
    if (moisture_to_action(300, 500) != WATER) {
        printf("Test failed: expected WATER\n");
        return 1;
    }
    if (moisture_to_action(700, 500) != IDLE) {
        printf("Test failed: expected IDLE\n");
        return 2;
    }
    printf("moisture_tests passed\n");
    return 0;
}
