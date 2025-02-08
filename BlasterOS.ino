#include <SD.h>

// Pin for the SD card module
#define SD_CS_PIN 10

// Define input pins
const int trigger_pin = 42;
const int stun_pin = 41;
const int font_pin = 40;

// Other configuration
const int pixel_count = 16;
const int blast_size = 4;
const int stun_size = 6;
const int font_count = 3;
const int sounds_per_font = 8;

class FontHandler {
public:
    int currentFont;
    int totalFonts;
    String soundFiles[font_count + 1][sounds_per_font];
    String fontColors[font_count + 1];

    FontHandler(int total) : currentFont(0), totalFonts(total) {
        loadSoundsFromSD();
        loadFontColors();
    }

    void loadSoundsFromSD() {
        for (int i = 1; i < totalFonts + 1; i++) {
            soundFiles[i][0] = "font" + String(i) + "/font.wav";
            for (int j = 1; j <= 4; j++) {
                soundFiles[i][j] = "font" + String(i) + "/blst" + String(j) + ".wav";
            }
            soundFiles[i][5] = "font" + String(i) + "/rapid.wav";
            soundFiles[i][6] = "font" + String(i) + "/load.wav";
            soundFiles[i][7] = "font" + String(i) + "/stun.wav";
        }
    }

    void loadFontColors() {
        fontColors[1] = "\033[31m"; // Red
        fontColors[2] = "\033[32m"; // Green
        fontColors[3] = "\033[34m"; // Blue
    }

    void nextFont() {
        currentFont = (currentFont + 1) % totalFonts;
        Serial.print("Font changed to: ");
        Serial.println(currentFont);
    }

    String getSound(int soundIndex) {
        if (soundIndex >= 0 && soundIndex < sounds_per_font) {
            return soundFiles[currentFont][soundIndex];
        } else {
            return "";
        }
    }

    String getFontColor() {
        return fontColors[currentFont];
    }
};

FontHandler fontHandler(font_count);

bool isPlaying = false;
unsigned int playbackStartTime = 0;
const unsigned int soundDuration = 400;

void displayTube(int position, int segmentSize, String color) {
    String tube = "[";
    for (int i = 0; i < pixel_count; i++) {
        if (i >= position && i < position + segmentSize) {
            tube += color + "#" + "\033[0m";
        } else {
            tube += "-";
        }
    }
    tube += "]";
    Serial.println(tube);
}

void setup() {
    pinMode(trigger_pin, INPUT);
    pinMode(stun_pin, INPUT);
    pinMode(font_pin, INPUT);

    Serial.begin(9600);

    // Initialize SD Card
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD card initialization failed!");
        while (1); // Halt if SD card fails to initialize
    }
    Serial.println("SD card initialized.");
}

void loop() {
    int font_button = digitalRead(font_pin);
    int trigger_state = digitalRead(trigger_pin);
    int stun_state = digitalRead(stun_pin);
    static int soundIndex = 0;
    static int blastPosition = 0;
    
    if (trigger_state == HIGH && stun_state!=HIGH && !isPlaying) {
        isPlaying = true;
        playbackStartTime = millis();
        Serial.print("Trigger pulled");
        Serial.println(fontHandler.getSound(soundIndex));
        soundIndex = ((soundIndex + 1) % 4) + 1;


        for (int i = 0; i <= pixel_count - blast_size; i++) {
            displayTube(i, blast_size, fontHandler.getFontColor());
            delay(100);
        }
    }
    
    if (stun_state == HIGH && trigger_state && !isPlaying) {
        isPlaying = true;
        playbackStartTime = millis();
        Serial.println(fontHandler.getSound(7));
        Serial.println("Stun");
        
        for (int i = 0; i <= pixel_count - stun_size; i++) {
            displayTube(i, stun_size, "\033[34m"); // Stun blasts should always be blue
            delay(100);
        }
    }
    
    if (isPlaying && millis() - playbackStartTime >= soundDuration) {
        isPlaying = false;
        Serial.println("Sound playback finished.");
    }
    
    if (font_button == HIGH) {
        fontHandler.nextFont();
        soundIndex = 0;
        delay(300);
    }
}
