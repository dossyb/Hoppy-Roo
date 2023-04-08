#pragma once

enum platform_size
{
    EXTRA_SMALL,
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

struct platform_data
{
    double x;
    double y;
    platform_size size;
    double width;
    double height;
};

platform_data new_platform(double x, double y, platform_size size);
bitmap platform_bitmap( platform_data &platform);