/*
 * gui.h
 *
 *  Created on: Nov 20, 2023
 *      Author: saaci
 */


#ifndef INC_GUI_H_
#define INC_GUI_H_

#include <stdint.h>

/**
  * @brief  Initializes the Graphical User Interface (GUI).
  *
  * @note   This function is responsible for setting up the initial state of the GUI, typically
  *         during the system initialization phase.
  */
void GUI_init(void);

/**
  * @brief  Updates the GUI to display the locked state.
  *
  * @note   This function fills the OLED screen with a black background, displays a "Locked" message,
  *         and shows a graphical representation of the locked state, such as a padlock icon.
  */
void GUI_locked(void);

/**
  * @brief  Updates the GUI to display the unlocked state.
  *
  * @note   This function fills the OLED screen with a black background, displays an "Unlocked" message,
  *         and updates the OLED screen accordingly to represent the unlocked state.
  */
void GUI_unlocked(void);

/**
  * @brief  Initializes the GUI for the password update process.
  *
  * @note   This function fills the OLED screen with a black background, displays a "New PW:" message,
  *         and updates the OLED screen accordingly to represent the initiation of the password update process.
  */
void GUI_update_password_init(void);

/**
  * @brief  Updates the GUI to display the current password.
  *
  * @param  password: Pointer to the array containing the current password.
  *
  * @note   This function sets the cursor position on the OLED screen and writes the current password
  *         using a specified font and color. It then updates the OLED screen with the changes.
  */
void GUI_update_password(uint8_t *password);

/**
  * @brief  Updates the GUI to indicate a successful password update.
  *
  * @note   This function sets the cursor position on the OLED screen, writes a "Success!" message
  *         using a specified font and color, and updates the OLED screen accordingly.
  */
void GUI_update_password_success(void);

#endif /* INC_GUI_H_ */
