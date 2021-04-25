#ifndef PLATFORM_COMMON_H_202104
#define PLATFORM_COMMON_H_202104

struct Button_State
{
    bool is_down;
    bool changed;
};

enum
{ // Anonymous enum to represent button press types for the Input struct
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,

    // BUTTON_COUNT should be the last item
    // (as it will have the integer value of the number of buttons above)
    BUTTON_COUNT,
};

struct Input
{
    Button_State buttons[BUTTON_COUNT];
};

#endif