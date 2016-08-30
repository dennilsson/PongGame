#include "Game.h"


Game::~Game()
{
    delete scoreboard;
    delete paddle1;
    delete paddle2;
    delete ball;
    delete table;
    delete graphics;
    delete input;
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool Game::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if (RUN_IN_FULLSCREEN)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }

    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Instantiates the Graphics class that wraps the common SDL functions
    // and is used to draw to the screen
    graphics = new Graphics();
    if (!graphics->Init(window))
    {
        return false;
    }

    // Instantiates the Input class that handles the keyboard input
    input = new InputHandler();
    input->Init();

    // Create the table
    table = new Table();

    // Create our three playing objects. This is 1 ball and 2 player paddles
    ball = new Ball();
    paddle1 = new Paddle(10, 10);
    paddle2 = new Paddle(SCREEN_WIDTH - PADDLE_WIDTH - 10, 10);

    scoreboard = new Scoreboard();

    gameState = STATE_RUNNING;

    // Setting this to true will keep the gameloop running
    isRunning = true;

    return true;
}


//-----------------------------------------------------------------------------
// The Run funtion will be called from the main program in a loop.
//-----------------------------------------------------------------------------
void Game::RunFrame()
{
    frameStart = SDL_GetTicks();

    // This will handle all the input from the keyboard and gamepad controllers
    HandleInput();
    
    switch (gameState)
    {
    case STATE_RUNNING:

        // Update all the game objects
        ball->Update();
        paddle1->Update();
        paddle2->Update();

        if (ball->CheckCollision(*paddle1))
        {
            std::cout << "Collision! - Paddle1 hit the ball" << std::endl;
        }
        if (ball->CheckCollision(*paddle2))
        {
            std::cout << "Collision! - Paddle2 hit the ball" << std::endl;
        }

        // Check if the ball gets past the paddles and the player scores
        if (ball->GetX() > SCREEN_WIDTH)
        {
            std::cout << "Player 1 scored!" << std::endl;
            scoreboard->AddScore(LEFT_PADDLE);
            ball->ResetPosition();
        }
        else if (ball->GetX() < 0)
        {
            std::cout << "Player 2 scored!" << std::endl;
            scoreboard->AddScore(RIGHT_PADDLE);
            ball->ResetPosition();
        }

        // Clear the screen so its blank when we start our frame
        graphics->ClearScreen();

        // Draw the pong table
        table->Draw(graphics);

        scoreboard->Draw(graphics);

        // Draw all the game_objects to the backbuffer
        ball->Draw(graphics);
        paddle1->Draw(graphics);
        paddle2->Draw(graphics);

        if (scoreboard->GetScore(LEFT_PADDLE) == 10)
        {
            std::cout << "Left player has won\n";
            gameState = STATE_GAMEOVER;
        }
        else if (scoreboard->GetScore(RIGHT_PADDLE) == 10)
        {
            std::cout << "Right player has won\n";
            gameState = STATE_GAMEOVER;
        }

        break;
    case STATE_PAUSE:
        break;
    case STATE_GAMEOVER:

        scoreboard->Reset();

        gameState = STATE_RUNNING;
        break;
    default:
        break;
    }

    // Flip the backbuffer to the frontbuffer
    graphics->PresentScreen();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < 1000.0f / FRAMES_PER_SECONDS)
    {
        SDL_Delay((int)(1000.0f / FRAMES_PER_SECONDS - frameTime));
    }
}


void Game::HandleInput()
{
    // Update the input handler to register all the input
    input->GetInput();

    // Check if the user has quited
    if (input->IsQuited())
    {
        isRunning = false;
    }

    // Handle keyboard input for the first paddle

    if (input->IsKeyDown(SDL_SCANCODE_W))
    {
        paddle1->MoveUp();
    }
    else if (input->IsKeyDown(SDL_SCANCODE_S))
    {
        paddle1->MoveDown();
    }
    else
    {
        paddle1->StopMoving();
    }

    // Handle keyboard input for the second paddle
    
    if (input->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        paddle2->MoveDown();
    }
    else if (input->IsKeyDown(SDL_SCANCODE_UP))
    {
        paddle2->MoveUp();
    }
    else
    {
        paddle2->StopMoving();
    }


    // Handle gamepad input
    //if (input->is_gamepad_button_down(0, GAMEPAD_BUTTON_A))
    //{
    //    std::cout << "Button A pressed" << std::endl;
    //    paddle1->move_down();
    //}
    //if (input->is_gamepad_button_down(0, GAMEPAD_BUTTON_B))
    //{
    //    std::cout << "Button B pressed" << std::endl;
    //}
    //if (input->is_gamepad_button_down(0, GAMEPAD_BUTTON_X))
    //{
    //    std::cout << "Button X pressed" << std::endl;
    //    paddle1->move_up();
    //}
    //if (input->is_gamepad_button_down(0, GAMEPAD_BUTTON_Y))
    //{
    //    std::cout << "Button Y pressed" << std::endl;
    //}


    //int y_value = input->get_gamepad_stick_y_value(GAMEPAD_LEFT_STICK, 0);
    //
    //if (y_value > 0)
    //{
    //    paddle1->move_down();
    //}
    //else if (y_value < 0)
    //{
    //    paddle1->move_up();
    //}

    //
    //y_value = input->get_gamepad_stick_y_value(GAMEPAD_LEFT_STICK, 1);

    //if (y_value > 0)
    //{
    //    paddle2->move_down();
    //}
    //else if (y_value < 0)
    //{
    //    paddle2->move_up();
    //}
}


int main(int argc, char *argv[])
{
    Game *game;

    game = new Game();
    game->Init();

    while (game->IsRunning())
    {
        game->RunFrame();
    }

    delete game;

    return EXIT_SUCCESS;
}