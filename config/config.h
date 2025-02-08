#ifndef CONFIG_H
#define CONFIG_H

// Filepaths
#define SOUNDFONT_DATA_PATH "/soundfonts"

// Color definitions (RGB format)
#define COLOR_RED    0xFF0000
#define COLOR_GREEN  0x00FF00
#define COLOR_BLUE   0x0000FF
#define COLOR_WHITE  0xFFFFFF
#define COLOR_BLACK  0x000000

// Struct for storing complex data
typedef struct {
    const char* name;
    uint32_t color; // Color in RGB format
} ColorEntry;

// Example array of color entries
const ColorEntry predefinedColors[] = {
    {"Red", COLOR_RED},
    {"Green", COLOR_GREEN},
    {"Blue", COLOR_BLUE},
    {"White", COLOR_WHITE},
    {"Black", COLOR_BLACK}
};

// Function prototypes (if needed for config-related tasks)
void printConfigInfo();

#endif // CONFIG_H