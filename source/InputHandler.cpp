#include "InputHandler.h"


//-----------------------------------------------------------------------------
// Initialize anything related to the input handling
//-----------------------------------------------------------------------------

bool InputHandler::Init()
{
    // Make sure the SDL joystick subsystem is initialised
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    // Enumerate all the joysticks/joypads and add them to the member vector
    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* temp_gamepad = SDL_JoystickOpen(i);

            if (temp_gamepad)
            {
                gamepads.push_back(temp_gamepad);

                // Initialize the default values for the stick
                gamepadStickValues.push_back(std::make_pair(new Vector2(0,0), new Vector2(0,0)));

                // Create temp buttons for initialization
                std::vector<bool> temp_buttons;

                for (int j = 0; j < SDL_JoystickNumButtons(temp_gamepad); j++)
                {
                    temp_buttons.push_back(false);
                }

                // Add the initialized buttons to the gamepad
                gamepadButtonStates.push_back(temp_buttons);
            }
            else
            {
                std::cout << SDL_GetError() << std::endl;
                return false;
            }

            // Enable the joystick event polling
            SDL_JoystickEventState(SDL_ENABLE);

            std::cout << "Initialised " << gamepads.size() << " joystick(s)\n";
        }
    }

    // Initialize all the keys to there current state
    currentKeyStates = SDL_GetKeyboardState(nullptr);

    return true;
}


//-----------------------------------------------------------------------------
// Grabs all the key states from the keyboard and the gampad buttons
//-----------------------------------------------------------------------------

void InputHandler::GetInput()
{
    while (SDL_PollEvent(&inputEvent))
    {
        if (inputEvent.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (inputEvent.type == SDL_KEYDOWN || inputEvent.type == SDL_KEYUP)
        {
            // Get all the key states from the keyboard
            currentKeyStates = SDL_GetKeyboardState(nullptr);
        }
        else if (inputEvent.type == SDL_JOYBUTTONDOWN)
        {
            GamepadButtonPressed(inputEvent);
        }
        else if (inputEvent.type == SDL_JOYBUTTONUP)
        {
            GamepadButtonReleased(inputEvent);
        }
        else if (inputEvent.type == SDL_JOYAXISMOTION)
        {
            GamepadStickMoved(inputEvent);
        }
    }
}


//-----------------------------------------------------------------------------
// Returns true if the scancode is down
//-----------------------------------------------------------------------------

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
    if (currentKeyStates[key])
    {
        return true;
    }

    return false;
}


//-----------------------------------------------------------------------------
// Clean up anything that needs to be cleaned up
//-----------------------------------------------------------------------------

void InputHandler::Cleanup()
{
    // Close all the handles for the opened joysticks
    for (unsigned int i = 0; i < gamepads.size(); i++)
    {
        SDL_JoystickClose(gamepads[i]);
    }
}


//-----------------------------------------------------------------------------
// Returns the state of the gamepad button (down = true, up = false)
//-----------------------------------------------------------------------------

bool InputHandler::IsGamepadButtonDown(int joystickId, int buttonNumber)
{
    return gamepadButtonStates[joystickId][buttonNumber];
}


//-----------------------------------------------------------------------------
// Handles the SDL_JOYBUTTONDOWN event on the gamepad controller
//-----------------------------------------------------------------------------

void InputHandler::GamepadButtonPressed(const SDL_Event& e)
{
    // Get the controller that the event fired on
    int controllerIndex = e.jbutton.which;

    // Hold the button that was pressed
    Uint8 button = e.jbutton.button;

    gamepadButtonStates[controllerIndex][button] = true;
}


//-----------------------------------------------------------------------------
// Handles the SDL_JOYBUTTONUP event on the gamepad controller
//-----------------------------------------------------------------------------

void InputHandler::GamepadButtonReleased(const SDL_Event& e)
{
    // Get the controller that the event fired on
    int controllerIndex = e.jbutton.which;

    // Hold the button that was released
    Uint8 button = e.jbutton.button;

    gamepadButtonStates[controllerIndex][button] = false;
}


void InputHandler::GamepadStickMoved(const SDL_Event& e)
{
    // Get the controller that the event fired on
    int controllerId = e.jaxis.which;

    if (e.jaxis.axis == 0)
    {
        if (e.jaxis.value > GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].first->SetX(1);
            //std::cout << "axis x value " << e.jaxis.value << " (move right)" << std::endl;
        }
        else if (e.jaxis.value < -GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].first->SetX(-1);
            //std::cout << "axis x value " << e.jaxis.value << " (move left)" << std::endl;
        }
        else
        {
            gamepadStickValues[controllerId].first->SetX(0);
        }
    }   
    else if (e.jaxis.axis == 1)
    {
        if (e.jaxis.value > GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].first->SetY(1);
            //std::cout << "axis y value " << e.jaxis.value << " (move down)" << std::endl;
        }
        else if (e.jaxis.value < -GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].first->SetY(-1);
            //std::cout << "axis y value " << e.jaxis.value << " (move up)" << std::endl;
        }
        else
        {
            gamepadStickValues[controllerId].first->SetY(0);
        }
    }
    else if (e.jaxis.axis == 3)
    {
        if (e.jaxis.value > GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].second->SetX(1);
            //std::cout << "axis y value " << e.jaxis.value << " (move right)" << std::endl;
        }
        else if (e.jaxis.value < -GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].second->SetX(-1);
            //std::cout << "axis y value " << e.jaxis.value << " (move left)" << std::endl;
        }
        else
        {
            gamepadStickValues[controllerId].second->SetX(0);
        }
    }
    else if (e.jaxis.axis == 4)
    {
        if (e.jaxis.value > GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].second->SetY(1);
            //std::cout << "axis y value " << e.jaxis.value << " (move down)" << std::endl;
        }
        else if (e.jaxis.value < -GAMEPAD_DEAD_ZONE)
        {
            gamepadStickValues[controllerId].second->SetY(-1);
            //std::cout << "axis y value " << e.jaxis.value << " (move up)" << std::endl;
        }
        else
        {
            gamepadStickValues[controllerId].second->SetY(0);
        }
    }
}


int InputHandler::GetGamepadStickYValue(int stick, int controllerId)
{
    if (gamepadButtonStates.size() > 0)
    {
        if (stick == GAMEPAD_LEFT_STICK)
        {
            return gamepadStickValues[controllerId].first->GetY();
        }
        else if (stick == GAMEPAD_RIGHT_STICK)
        {
            return gamepadStickValues[controllerId].second->GetY();
        }
    }

    return 0;
}


int InputHandler::GetGamepadStickXValue(int stick, int controllerId)
{
    if (gamepadButtonStates.size() > 0)
    {
        if (stick == GAMEPAD_LEFT_STICK)
        {
            return gamepadStickValues[controllerId].first->GetX();
        }
        else if (stick == GAMEPAD_RIGHT_STICK)
        {
            return gamepadStickValues[controllerId].second->GetX();
        }
    }

    return 0;
}


bool InputHandler::IsQuited()
{
    return quit;
}