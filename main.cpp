#include "splashkit.h"
#include "player.h"
#include "platform.h"
#include <iostream>
#include <fstream>

#define JUMP_HEIGHT -10
#define SPEED 5
#define START_HEIGHT 600
#define PLAYER_WIDTH 100

struct floor_data
{
    double x;
    double y;
};

floor_data create_floor(double x, double y)
{
    floor_data result;

    result.x = x;
    result.y = y;

    return result;
}

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

void start_game(player_data &player, const floor_data &floor, bool &start_flag)
{
    if ( key_down(SPACE_KEY) && start_flag )  
    {
        player.vel = JUMP_HEIGHT;
        start_flag = false;
    }
    else if ( player.y >= floor.y )  player.vel = 0;
    else    player.vel += player.acc;
}

void is_landing(player_data &player, platform_data &platform)
{
    if  ((player.height > platform.y && player.height < platform.y + platform.height) && player.vel > 0 && ((player.x > platform.x && player.x < platform.width)
    || (player.width > platform.x && player.width < platform.width)) )
    {
        player.vel = JUMP_HEIGHT;
    }
}

int game_loop(player_data &player, platform_data &platform, floor_data &floor)
{
    int high_score = 0;
    bool start_flag = true;
    do
    {
        process_events();
        handle_input(player);
        handle_state(player);
        start_game(player, floor, start_flag);
        is_landing(player, platform);
        // is_landing(player, platform2);
        draw_bitmap("background", -400, -100);
        draw_bitmap("floor", floor.x, floor.y);
        draw_bitmap(player_bitmap(player), player.x, player.y);
        draw_bitmap(platform_bitmap(platform), platform.x, platform.y);
        // draw_bitmap(platform_bitmap(platform2), platform2.x, platform2.y);
        draw_text(std::to_string(high_score), COLOR_WHITE, "game-font", 32, 10, 10);
        draw_text(std::to_string(player.height), COLOR_WHITE, "game-font", 32, 10, 50);
        draw_text(std::to_string(platform.y), COLOR_WHITE, "game-font", 32, 10, 80);
        player.y += player.vel;
        player.height += player.vel;
        high_score = -(player.highest_y);
        
        if ( player.highest_y > player.y - START_HEIGHT )   player.highest_y = player.y - START_HEIGHT;

        if ( boundary_exceeded(floor.y) )   floor.y = 2000;
        else floor.y -= player.vel;

        if ( boundary_exceeded(player.y) )  return 0;
        if ( player.vel < 0)    platform.y -= player.vel;
        // if ( player.vel < 0)    platform2.y -= player.vel;

        refresh_screen(60);
    } while ( ! quit_requested() );
    return 0;
}

// int main_menu()
// {
//     //todo
// }

int main()
{
    player_data player;
    platform_data platform;
    // platform_data platform2;
    floor_data floor;

    load_resources();
    player = new_player(300, START_HEIGHT);
    platform = new_platform(100, 300, MEDIUM);
    // platform2 = new_platform(300, -100, MEDIUM);
    floor = create_floor(0, START_HEIGHT);
    game_loop(player, platform, floor);

    return 0;
}