#include "splashkit.h"
#include "platform.h"

#define PLATFORM_HEIGHT 50

platform_data new_platform(double x, double y, platform_size size)
{
    platform_data result;

    result.x = x;
    result.y = y;
    result.width = 0;
    result.height = PLATFORM_HEIGHT;
    result.size = size;

    return result;
}

bitmap platform_bitmap(platform_data &platform)
{
    string bitmap_name;
    bitmap_name = "platform";

    switch (platform.size)
    {
        case EXTRA_SMALL:
            bitmap_name += "-xs";
            platform.width = platform.x + 65;
            break;
        case MEDIUM:
            bitmap_name += "-m";
            platform.width = platform.x + 240;
            break;
        case LARGE:
            bitmap_name += "-l";
            platform.width = platform.x + 350;
            break;
        case EXTRA_LARGE:
            bitmap_name += "-xl";
            platform.width = platform.x + 425;
            break;
        case SMALL:
        default:
            bitmap_name += "-s";
            platform.width = platform.x + 120;
    }

    return bitmap_named(bitmap_name);
}
