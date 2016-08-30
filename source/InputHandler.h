#pragma once

#include "Vector2.h"

#include <SDL.h>
#include <vector>
#include <iostream>

// This is the deadzone for the analog stick on the gamepad.
const int GAMEPAD_DEAD_ZONE = 8000;

#define GAMEPAD_LEFT_STICK  1
#define GAMEPAD_RIGHT_STICK 2

#define GAMEPAD_BUTTON_A    0
#define GAMEPAD_BUTTON_B    1
#define GAMEPAD_BUTTON_X    2
#define GAMEPAD_BUTTON_Y    3


class InputHandler
{
public:
    bool Init();
    void Cleanup();

    // Gets called each frame
    void GetInput();

    // Returns the state of the key given as parameter (down = true, up = false)
    bool IsKeyDown(SDL_Scancode key);

    // Returns the state of the gamepad button (down = true, up = false)
    bool IsGamepadButtonDown(int joystick_id, int button_number);

    int GetGamepadStickYValue(int stick, int controllerId);

    int GetGamepadStickXValue(int stick, int controllerId);

    bool IsQuited();

private:
    SDL_Event inputEvent;
    const Uint8 *currentKeyStates;

    bool isGamepadInitiazlied = false;

    bool quit = false;

    // Holds the gamepads that is detected
    std::vector<SDL_Joystick*> gamepads;

    // Holds all the states for the buttons on the gamepad. (down = true, up = false)
    std::vector<std::vector<bool>> gamepadButtonStates;
   
    // Holds the position of the gamepad's controller values
    std::vector<std::pair<Vector2*, Vector2*>> gamepadStickValues;

    // Gets called when a gamepad button is pressed
    void GamepadButtonPressed(const SDL_Event& e);

    // Gets called when a gamepad button is released
    void GamepadButtonReleased(const SDL_Event& e);

    // Gets called when the gamepad stick moves
    void GamepadStickMoved(const SDL_Event& e);
};

