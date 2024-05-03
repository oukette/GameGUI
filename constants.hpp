#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>
#include <vector>


// Supported resolutions
std::vector<std::pair<uint16_t, uint16_t>> RESOLUTIONS = {
    {640, 480},
    {800, 600},
    {1280, 720},
    {1920, 1080},
    {2560, 1080},
    {2560, 1440},
    {3840, 2160}
};

constexpr uint16_t SUPPORTED_RESOLUTION_COUNT = sizeof(RESOLUTIONS) / sizeof(RESOLUTIONS[0]);


// Define constants for color values
const unsigned int BACKGROUND_COLOR(0x181818FF);
const unsigned int UI_TEXT_COLOR_GENERAL(0xF48757FF);
const unsigned int UI_TEXT_COLOR_AUXILIARY(0x409CD6FF);
const unsigned int UI_BUTTON_FILL_COLOR_NORMAL(0xABABABFF);
const unsigned int UI_BUTTON_FILL_COLOR_HOVER(0xEEE69E88);
const unsigned int UI_BUTTON_FILL_COLOR_CLICK(0x9988BBAA);
const unsigned int UI_BUTTON_OUTLINE_COLOR(0x832B2BFF);

// Define constants for text sizes
const uint16_t UI_TEXT_SIZE_GENERAL = 20;
const uint16_t UI_TEXT_SIZE_AUXILIARY = 15;


#endif // CONSTANTS_HPP