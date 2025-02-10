// Standard includes
#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"

// Common interface includes
#include "uart_if.h"
#include "oled_test.h"
#include "pin_mux_config.h"


#define APPLICATION_VERSION     "1.4.0"

#define SPI_IF_BIT_RATE  100000
#define TR_BUFF_SIZE     100

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************



//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}
//*****************************************************************************
// drawHeart()
// Draws a heart shape by drawing two filled circles for the top lobes and a
// filled triangle for the bottom portion. Adjust the coordinates as needed.
//*****************************************************************************
void drawHeart(unsigned int color)
{
    // Center the heart horizontally
    int centerX = SSD1351WIDTH / 2;
    // Choose a vertical position for the top of the heart
    int centerY = 40;
    // Choose a radius that suits your design
    int radius  = 12;

    // Draw the left lobe of the heart.
    // The center of this circle is shifted left by 'radius'
    fillCircle(centerX - radius, centerY, radius, color);

    // Draw the right lobe of the heart.
    // The center of this circle is shifted right by 'radius'
    fillCircle(centerX + radius, centerY, radius, color);

    // Draw the bottom triangle that forms the point of the heart
    // The triangle is drawn between:
    //   - left point: (centerX - 2*radius, centerY)
    //   - right point: (centerX + 2*radius, centerY)
    //   - bottom point: (centerX, centerY + 2*radius)
    fillTriangle(centerX - 2 * radius, centerY,
                 centerX + 2 * radius, centerY,
                 centerX, centerY + 2 * radius, color);
}
//*****************************************************************************
// testWillYouBeMyValentine(unsigned int color)
// Displays a text message to the OLED display below the drawn heart
//*****************************************************************************
void testWillYouBeMyValentine(unsigned int color)
{
    char* line1 = "Will you be my";
    char* line2 = "Valentine?";

    // Calculate the length of each string
    int len1 = strlen(line1);
    int len2 = strlen(line2);

    // Calculate horizontal starting positions to center the text
    int x1 = (SSD1351WIDTH - (len1 * 6)) / 2;
    int x2 = (SSD1351WIDTH - (len2 * 6)) / 2;

    // Set the vertical positions. Adjust these values as needed
    int y1 = 90;      // First line Y coordinate
    int y2 = y1 + 8;  // Second line 8 pixels below the first line

    int i;
    for (i = 0; i < len1; i++)
    {
        drawChar(x1 + i * 6, y1, line1[i], color, BLACK, 1);
    }

    for (i = 0; i < len2; i++)
    {
        drawChar(x2 + i * 6, y2, line2[i], color, BLACK, 1);
    }
}


//*****************************************************************************
//
//! Main function
//!
//! \param none
//!
//! \return None.
//
//*****************************************************************************
void main()
{
    //
    // Initialize Board configurations
    //
    BoardInit();

    //
    // Muxing UART and SPI lines.
    //
    PinMuxConfig();

    //
    // Enable the SPI module clock
    //
    MAP_PRCMPeripheralClkEnable(PRCM_GSPI,PRCM_RUN_MODE_CLK);

    //
    // Initialising the Terminal.
    //
    InitTerm();

    //
    // Clearing the Terminal.
    //
    ClearTerm();

    //
    // Display the Banner
    //
    Message("\n\n\n\r");
    Message("\t\t   ********************************************\n\r");
    Message("\t\t        To my triny trin trin  \n\r");
    Message("\t\t   ********************************************\n\r");
    Message("\n\n\n\r");

    //
    // Reset the peripheral
    //
    MAP_PRCMPeripheralReset(PRCM_GSPI);

    MAP_SPIReset(GSPI_BASE);

    //
    // Configure SPI interface
    //
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                     (SPI_SW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVEHIGH |
                     SPI_WL_8));

    //
    // Enable SPI for communication
    //
    MAP_SPIEnable(GSPI_BASE);

    Adafruit_Init();
    // Clear the screen to black.
    fillScreen(BLACK);

    // Draw a heart in red.
    drawHeart(RED);

    // Configure text properties and position.
    setTextColor(WHITE, BLACK);
    // Position the text below the heart.
    setCursor(10, 90);
    testWillYouBeMyValentine(WHITE);
}
