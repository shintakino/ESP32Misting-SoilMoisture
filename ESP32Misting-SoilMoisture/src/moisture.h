#ifndef MOISTURE_H
#define MOISTURE_H

enum Action { WATER, IDLE };

// Simple moisture-to-action mapping for unit tests
int moisture_to_action(int moisture_adc, int dry_threshold);

#endif // MOISTURE_H
