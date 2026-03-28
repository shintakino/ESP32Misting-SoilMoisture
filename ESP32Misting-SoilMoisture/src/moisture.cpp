#include "moisture.h"

int moisture_to_action(int moisture_adc, int dry_threshold) {
    // If moisture reading is below dry_threshold, recommend watering
    return (moisture_adc < dry_threshold) ? WATER : IDLE;
}
