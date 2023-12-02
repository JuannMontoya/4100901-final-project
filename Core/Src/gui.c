#include "gui.h"

#include "ssd1306.h"
#include "ssd1306_fonts.h"

extern const uint8_t locked[];//external constant

/**

  * @note   This function is typically called during the system initialization to set up the graphical
  *         user interface for the lock system.
*/
void GUI_init(void)
{
    ssd1306_Init();  // Initialize the SSD1306 OLED display
    GUI_locked();    // Display the locked state on the OLED screen
}

/**
  * @brief  Updates the GUI to display the locked state.
  *
  * @note   This function fills the OLED screen with a black background, displays a "Locked" message,
  *         and shows a graphical representation of the locked state, such as a padlock icon.

  */
void GUI_locked(void)
{
    ssd1306_Fill(Black);                   // Fill the screen with a black background
    ssd1306_SetCursor(20, 5);              // Set the cursor position for the "Locked" message
    ssd1306_WriteString("Locked", Font_16x26, White);  // Display the "Locked" message
    ssd1306_DrawBitmap(50, 35, locked, 30, 30, White);  // Display a graphical representation of the locked state
    ssd1306_UpdateScreen();                // Update the OLED screen with the changes
}
/**
  * @brief  Updates the GUI to display the unlocked state.
  * @note   This function fills the OLED screen with a black background, displays an "Unlocked" message,
  *         and updates the OLED screen accordingly to represent the unlocked state.
  */
void GUI_unlocked(void)
{
    ssd1306_Fill(Black);                   // Fill the screen with a black background
    ssd1306_SetCursor(5, 5);               // Set the cursor position for the "Unlocked" message
    ssd1306_WriteString("Unlocked", Font_16x26, White);  // Display the "Unlocked" message
    ssd1306_UpdateScreen();                // Update the OLED screen with the changes
}

/**
  * @brief  Initializes the GUI for the password update process.
  * @note   This function fills the OLED screen with a black background, displays a "New PW:" message,
  *         and updates the OLED screen accordingly to represent the initiation of the password update process.
  */
void GUI_update_password_init(void)
{
    ssd1306_Fill(Black);                   // Fill the screen with a black background
    ssd1306_SetCursor(5, 5);               // Set the cursor position for the "New PW:" message
    ssd1306_WriteString("New PW:", Font_16x26, White);  // Display the "New PW:" message
    ssd1306_UpdateScreen();                // Update the OLED screen with the changes
}

/**
  * @brief  Updates the GUI to display the current password.
  *
  * @param  password: Pointer to the array containing the current password.
  *
  * @note   This function sets the cursor position on the OLED screen and writes the current password
  *         using a specified font and color. It then updates the OLED screen with the changes.
  */
void GUI_update_password(uint8_t *password)
{
    ssd1306_SetCursor(10, 35);                         // Set the cursor position for displaying the password
    ssd1306_WriteString((char *)password, Font_7x10, White);  // Display the password using a 7x10 font in white color
    ssd1306_UpdateScreen();                            // Update the OLED screen with the changes
}

/**
  * @brief  Updates the GUI to indicate a successful password update.
  * @note   This function sets the cursor position on the OLED screen, writes a "Success!" message
  *         using a specified font and color, and updates the OLED screen accordingly.
  */
void GUI_update_password_success(void)
{
    ssd1306_SetCursor(5, 35);                         // Set the cursor position for displaying the success message
    ssd1306_WriteString("Success!", Font_16x26, White);  // Display the success message using a 16x26 font in white color
    ssd1306_UpdateScreen();                            // Update the OLED screen with the changes
}

