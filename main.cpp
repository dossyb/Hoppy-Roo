#include "splashkit.h"
#include <iostream>
#include <fstream>

#define JUMP_HEIGHT -6
#define SPEED 5
#define PLAYER_HEIGHT 125
#define PLAYER_WIDTH 100
#define START_HEIGHT 600

enum player_state
{
    IDLE,
    JUMP
};

enum player_direction
{
    RIGHT,
    LEFT
};

enum platform_size
{
    EXTRA_SMALL,
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

struct player_data
{
    double x;
    double y;
    double vel;
    double acc;
    double highest_y;
    player_state state;
    player_direction face;
};

struct platform_data
{
    double x;
    double y;
    platform_size size;
};

player_data new_player(double x, double y)
{
    player_data result;

    result.x = x;
    result.y = y;
    result.vel = 0;
    result.acc = 0.05;
    result.highest_y = 0;
    result.state = IDLE;
    result.face = RIGHT;

    return result;
}

platform_data new_platform(double x, double y, platform_size size)
{
    platform_data result;

    result.x = x;
    result.y = y;
    result.size = size;

    return result;
}

bitmap player_bitmap(const player_data &player)
{
    string bitmap_name;
    bitmap_name = "player";

    if (player.face == LEFT && player.state == IDLE)
    {
        bitmap_name += "-idle-l";
    }
    if (player.face == LEFT && player.state == JUMP)
    {
        bitmap_name += "-jump-l";
    }
    if (player.face == RIGHT && player.state == IDLE)
    {
        bitmap_name += "-idle-r";
    }
    if (player.face == RIGHT && player.state == JUMP)
    {
        bitmap_name += "-jump-r";
    }

    return bitmap_named(bitmap_name);
}

bitmap platform_bitmap(const platform_data &platform)
{
    string bitmap_name;
    bitmap_name = "platform";

    switch (platform.size)
    {
        case EXTRA_SMALL:
            bitmap_name += "-xs";
            break;
        case MEDIUM:
            bitmap_name += "-m";
            break;
        case LARGE:
            bitmap_name += "-l";
            break;
        case EXTRA_LARGE:
            bitmap_name += "-xl";
            break;
        case SMALL:
        default:
            bitmap_name += "-s";
    }

    return bitmap_named(bitmap_name);
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