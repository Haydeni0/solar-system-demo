#ifndef PLATFORM_COMMON_H_202104
#define PLATFORM_COMMON_H_202104

struct Button_State
{
    bool is_down; // "Is the button pressed down?"
    bool changed; // "Did the button just change in this frame?"
};

enum Button_Type
{ // Anonymous enum to represent button press types for the Input struct
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_SPACE,
    BUTTON_OEM_MINUS,
    BUTTON_OEM_PLUS,

    // BUTTON_COUNT should be the last item
    // (as it holds the integer value of the number of buttons above)
    BUTTON_COUNT,
};

struct Input
{ // Defines a vector holding the state of all buttons
// The layout of this is defined in the Button_Type enumeration
    Button_State buttons[BUTTON_COUNT];
};

#endif