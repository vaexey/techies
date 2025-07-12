#include <Arduino.h>

#define HAL_PRESENT

// Number of binary inputs
// #define HAL_IX_COUNT ( sizeof(HAL_Mega_IX_pins) / sizeof(uint8_t) )
#define HAL_IX_COUNT 1

// Number of binary outputs
// #define HAL_QX_COUNT ( sizeof(HAL_Mega_QX_pins) / sizeof(uint8_t) )
#define HAL_QX_COUNT 1

extern uint8_t HAL_Mega_IX_pins[HAL_IX_COUNT];
extern bool HAL_Mega_IX_inverted[HAL_QX_COUNT];
extern uint8_t HAL_Mega_QX_pins[HAL_QX_COUNT];
extern bool HAL_Mega_QX_inverted[HAL_QX_COUNT];

// Read binary input
#define HAL_IX_READ(index) ( digitalRead(HAL_Mega_IX_pins[( index )]) ^ HAL_Mega_IX_inverted[( index )] )
#define HAL_IX_INIT(index) ( pinMode(HAL_Mega_IX_pins[( index )], INPUT_PULLUP) )

// Write binary output
#define HAL_QX_WRITE(index, state) ( digitalWrite(HAL_Mega_QX_pins[( index )], ( state ) ^ HAL_Mega_QX_inverted[( index )]) )
#define HAL_QX_INIT(index) ( pinMode(HAL_Mega_QX_pins[( index )], OUTPUT) )

typedef uint8_t HAL_IX_Address_t;
typedef uint8_t HAL_QX_Address_t;

typedef unsigned long HAL_Time_Type;

#define HAL_Time (millis())