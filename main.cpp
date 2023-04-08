#include "splashkit.h"
#include "player.h"
#include "platform.h"
#include <iostream>
#include <fstream>

#define JUMP_HEIGHT -10
#define SPEED 5
#define PLAYER_HEIGHT 125
#define PLAYER_WIDTH 100
#define START_HEIGHT 600

void load_resources()
{
    //todo
    load_bitmap("background", "background.png");
    load_bitmap("floor", "desert-floor.png");
    load_bitmap("player-idle-l", "hoppy-l.png");
    load_bitmap("player-jump-l", "hoppy-jump-l.png");
    load_bitmap("player-idle-r", "hoppy-r.png");
    load_bitmap("player-jump-r", "hoppy-jump-r.png");
    load_bitmap("platform-xs", "platform-xs.png");
    load_bitmap("platform-s", "platform-s.png");
    load_bitmap("platform-m", "platform-m.png");
    load_bitmap("platform-l", "platform-l.png");
    load_bitmap("platform-xl", "platform-xl.png");
    load_font("game-font", "caslon.ttf");
    open_window("Hoppy Roo", 600, 800);
}

void handle_input(player_data &player)
{
    if ( (key_down(LEFT_KEY) || key_down(A_KEY)) && player.x > 0 )
    {
        player.x = player.x - SPEED;
        player.face = LEFT;
    }
    if ( (key_down(RIGHT_KEY) || key_down(D_KEY)) && player.x < screen_width() - PLAYER_WIDTH )
    {
        player.x = player.x + SPEED;
        player.face = RIGHT;
    }

}

void handle_state(player_data &player)
{
    if ( player.vel < 0 )
    {
        player.state = JUMP;
    }
    else 
    {
        player.state = IDLE;
    }
}

bool boundary_exceeded(double y)
{
    if ( y > screen_height() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// int game_loop()
// {
//     //todo
// }

// int main_menu()
// {
//     //todo
// }

int main()
{
    player_data player;
    platform_data platform;
    int high_score = 0;
    load_resources();
    player = new_player(300, START_HEIGHT);
    platform = new_platform(100, 300, SMALL);
    double floorY = START_HEIGHT;

    do
    {
        process_events();
        handle_input(player);
        handle_state(player);
        draw_bitmap("background", -400, -100);
        draw_bitmap("floor", 0, floorY);
        draw_bitmap(player_bitmap(player), player.x, player.y);
        draw_bitmap(platform_bitmap(platform), platform.x, platform.y);
        draw_text(std::to_string(high_score), COLOR_WHITE, "game-font", 32, 10, 10);
        player.y += player.vel;
        high_score = -(player.highest_y);
        
        if ( player.highest_y > player.y - START_HEIGHT)
        {
            player.highest_y = player.y - START_HEIGHT;
        }

        if ( boundary_exceeded(floorY) )
        {
            floorY = 2000;
        }
        else
        {
            floorY -= player.vel;
        }

        if ( boundary_exceeded(player.y) )
        {
            return 0;
        }

        if ( player.vel < 0)
        {
            platform.y -= player.vel;
        }

        if ( player.y >= floorY )
        {
            player.vel = JUMP_HEIGHT;
        }
        else
        {
            player.vel += player.acc;
        }


        refresh_screen(60);
    } while ( ! quit_requested() );
    
    return 0;
}