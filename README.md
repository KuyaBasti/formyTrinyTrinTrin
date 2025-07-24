# 💕 Valentine's Day OLED Heart Display

A romantic embedded project that displays a beautiful heart animation with "Will you be my Valentine?" message on an OLED display using the CC3200 microcontroller.

![Project Banner](https://img.shields.io/badge/Platform-CC3200-blue) ![Language](https://img.shields.io/badge/Language-C-green) ![Display](https://img.shields.io/badge/Display-SSD1351_OLED-red) ![Purpose](https://img.shields.io/badge/Purpose-Valentine's_Day-pink)

## 🎯 Project Overview

This project creates a charming Valentine's Day display that shows:
- A red heart shape drawn using geometric primitives (circles and triangles)
- The romantic message "Will you be my Valentine?" displayed below the heart
- Beautiful color rendering on a 128x128 pixel OLED display
- Smooth graphics powered by Adafruit's graphics library

Perfect for creating a memorable Valentine's Day proposal or gift! 💝

## 🔧 Hardware Requirements

### Main Components
- **CC3200 LaunchPad** - Texas Instruments WiFi-enabled microcontroller
- **Adafruit SSD1351 OLED Display** - 1.5" or 1.27" 16-bit color OLED
  - Resolution: 128x128 pixels
  - Colors: 65K colors (16-bit)
  - Interface: SPI communication

### Connections
The OLED display connects to the CC3200 via SPI interface:
- **SCLK** → CC3200 SPI Clock Pin
- **MOSI** → CC3200 SPI Data Pin  
- **CS** → CC3200 Chip Select Pin
- **DC** → CC3200 Data/Command Pin
- **RST** → CC3200 Reset Pin
- **VCC** → 3.3V
- **GND** → Ground

## 🛠 Software Requirements

### Development Environment
- **Code Composer Studio (CCS)** - Texas Instruments IDE
- **CC3200 SDK** - Software Development Kit
- **SPI Driver Libraries** - For OLED communication

### Dependencies
- `Adafruit_GFX.c/.h` - Graphics library for drawing primitives
- `Adafruit_SSD1351.h` - OLED display driver
- `uart_if.c/.h` - UART interface for debugging
- `pin_mux_config.c/.h` - Pin configuration
- CC3200 peripheral drivers (SPI, UART, etc.)

## 📁 Project Structure

```
formyTrinyTrinTrin-main/
├── main.c                    # Main application entry point
├── oled_test.c              # OLED testing and graphics functions
├── oled_test.h              # OLED function declarations and color definitions
├── Adafruit_GFX.c           # Graphics library implementation
├── Adafruit_GFX.h           # Graphics library header
├── Adafruit_OLED.c          # OLED specific functions
├── Adafruit_SSD1351.h       # SSD1351 display driver header
├── glcdfont.h               # Font data for text rendering
├── uart_if.c                # UART interface implementation
├── pin_mux_config.c         # Pin multiplexing configuration
├── pin_mux_config.h         # Pin configuration header
├── i2c_if.c                 # I2C interface (if needed)
├── cc3200v1p32.cmd          # Linker script
├── .ccsproject              # CCS project file
├── .cproject                # Eclipse C project file
├── .project                 # Project configuration
├── Debug/                   # Build output directory
├── .settings/               # IDE settings
├── .launches/               # Debug configurations
└── targetConfigs/           # Target configuration files
```

## 🚀 Getting Started

### 1. Hardware Setup
1. Connect the SSD1351 OLED display to your CC3200 LaunchPad following the pinout
2. Ensure proper power supply (3.3V) to the OLED display
3. Connect your CC3200 to your computer via USB

### 2. Software Setup
1. Install Code Composer Studio (CCS)
2. Import this project into CCS:
   - File → Import → CCS Projects
   - Browse to project directory
   - Select the project
3. Configure the target device (CC3200)

### 3. Build and Flash
1. Clean and build the project in CCS
2. Connect your CC3200 LaunchPad
3. Flash the program to the microcontroller
4. Reset the device to start the Valentine's display

## 💻 How It Works

### Main Functionality (`main.c`)

The main application follows this sequence:

1. **System Initialization**
   ```c
   BoardInit();          // Initialize CC3200 board
   PinMuxConfig();       // Configure pin multiplexing
   ```

2. **SPI Configuration**
   ```c
   MAP_SPIConfigSetExpClk(GSPI_BASE, MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                          SPI_IF_BIT_RATE, SPI_MODE_MASTER, SPI_SUB_MODE_0, ...);
   ```

3. **Display Initialization**
   ```c
   Adafruit_Init();      // Initialize OLED display
   fillScreen(BLACK);    // Clear screen to black
   ```

4. **Heart Drawing**
   ```c
   drawHeart(RED);       // Draw red heart using geometric primitives
   ```

5. **Text Display**
   ```c
   testWillYouBeMyValentine(WHITE);  // Display Valentine's message
   ```

### Heart Drawing Algorithm

The heart is created using geometric primitives:

```c
void drawHeart(unsigned int color) {
    int centerX = SSD1351WIDTH / 2;     // Center horizontally
    int centerY = 40;                   // Vertical position
    int radius = 12;                    // Heart size
    
    // Left and right lobes (circles)
    fillCircle(centerX - radius, centerY, radius, color);
    fillCircle(centerX + radius, centerY, radius, color);
    
    // Bottom point (triangle)
    fillTriangle(centerX - 2*radius, centerY,
                 centerX + 2*radius, centerY,
                 centerX, centerY + 2*radius, color);
}
```

### Text Rendering

The Valentine's message is displayed using character-by-character rendering:

```c
void testWillYouBeMyValentine(unsigned int color) {
    char* line1 = "Will you be my";
    char* line2 = "Valentine?";
    
    // Center text horizontally
    int x1 = (SSD1351WIDTH - (strlen(line1) * 6)) / 2;
    int x2 = (SSD1351WIDTH - (strlen(line2) * 6)) / 2;
    
    // Render each character
    for (int i = 0; i < strlen(line1); i++) {
        drawChar(x1 + i * 6, 90, line1[i], color, BLACK, 1);
    }
    // ... similar for line2
}
```

## 🎨 Graphics Features

### Color Support
- **16-bit color depth** (65,536 colors)
- Predefined colors: `RED`, `WHITE`, `BLACK`, `BLUE`, `GREEN`, etc.
- Custom RGB565 color support

### Drawing Primitives
- **Lines**: `drawLine()`, `drawFastHLine()`, `drawFastVLine()`
- **Rectangles**: `drawRect()`, `fillRect()`, `drawRoundRect()`
- **Circles**: `drawCircle()`, `fillCircle()`
- **Triangles**: `drawTriangle()`, `fillTriangle()`
- **Text**: `drawChar()`, custom font support

### Test Functions (`oled_test.c`)
- `testlines()` - Line drawing tests
- `testfastlines()` - Fast line drawing
- `testdrawrects()` - Rectangle drawing
- `testfillcircles()` - Filled circle tests
- `testtriangles()` - Triangle drawing
- `testHelloWorld()` - Basic text display
- `lcdTestPattern()` - Color pattern test

## 🔧 Customization Options

### Modify the Heart
- **Size**: Change the `radius` parameter in `drawHeart()`
- **Position**: Adjust `centerX` and `centerY` coordinates
- **Color**: Pass different color values (e.g., `MAGENTA`, `PINK`)

### Change the Message
```c
char* line1 = "Your custom";
char* line2 = "message here!";
```

### Add Animations
- Implement blinking effects using delays
- Add color cycling for the heart
- Create scrolling text effects

### Additional Graphics
- Add decorative elements (stars, flowers)
- Create background patterns
- Implement heart beating animation

## 🐛 Troubleshooting

### Common Issues

1. **Blank Display**
   - Check SPI connections
   - Verify power supply (3.3V)
   - Ensure proper pin configuration

2. **Corrupted Graphics**
   - Check SPI clock speed (`SPI_IF_BIT_RATE`)
   - Verify data integrity
   - Check wire connections

3. **Build Errors**
   - Ensure all library files are included
   - Check include paths in CCS
   - Verify CC3200 SDK installation

4. **Text Not Displaying**
   - Check font file (`glcdfont.h`)
   - Verify text positioning coordinates
   - Ensure sufficient contrast (text color vs background)

### Debug Tips
- Use UART output for debugging: `Message("Debug info\n\r");`
- Test individual graphics functions
- Verify SPI communication with oscilloscope

## 📚 References

- [Adafruit SSD1351 Library](https://github.com/adafruit/Adafruit-SSD1351-library)
- [CC3200 SDK Documentation](http://www.ti.com/tool/CC3200SDK)
- [Code Composer Studio](http://www.ti.com/tool/CCSTUDIO)
- [Adafruit OLED Display Datasheet](https://www.adafruit.com/product/1431)

## 💝 Perfect For

- 💕 Valentine's Day proposals
- 🎁 Romantic gifts for electronics enthusiasts  
- 📚 Embedded systems learning projects
- 🎨 Graphics programming demonstrations
- 💑 Anniversary surprises

## 📄 License

This project uses libraries from Adafruit Industries under BSD license. Please support Adafruit and open-source hardware by purchasing products from Adafruit!

---

Made with ❤️ for someone special - **To my triny trin trin**

*"Will you be my Valentine?"* 💕
