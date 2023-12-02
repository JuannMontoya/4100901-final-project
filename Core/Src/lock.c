//Import custom libraries
#include "lock.h"
#include "ring_buffer.h"
#include "keypad.h"
#include "main.h"
#include "gui.h"

#include <stdio.h>
#include <string.h>


#define MAX_PASSWORD 12 //Initializes macro with value 12 for maximum password length


uint8_t password[MAX_PASSWORD] = "1992";//Generates variable to store the password.
uint8_t status=0;
uint8_t keypad_buffer[MAX_PASSWORD];//This is a static array of uint8_t elements with a size of MAX_PASSWORD. It is used to store the keypad input characters.
ring_buffer_t keypad_rb;//This is a ring buffer object of type ring_buffer_t. It is used to manage the keypad input characters in a circular fashion.

extern volatile uint16_t keypad_event;//This is an externally declared volatile variable of type uint16_t. It represents the keypad event code indicating which keypad button has been pressed.


static uint8_t lock_get_passkey(void)
{
	while (ring_buffer_size(&keypad_rb) == 0) {//This loop iterates until there are key presses in the keypad buffer.
		/* wait for key press */
		uint8_t key_pressed = keypad_run(&keypad_event);//This line checks if a key has been pressed using the keypad_run() function.
		if (key_pressed != KEY_PRESSED_NONE) {//If a valid key has been pressed, the key code is added to the keypad buffer using the ring_buffer_put() function.

			ring_buffer_put(&keypad_rb, key_pressed);//
		}
	}
	uint8_t key_pressed;//This line declares a variable to store the retrieved key code.
	ring_buffer_get(&keypad_rb, &key_pressed);//This line retrieves the key code from the keypad buffer.
	if (key_pressed == '*' || key_pressed == '#') {//If the key code is '*' or '#', it indicates the end of the password entry.
		return 0xFF;//The function returns 0xFF to signal the end of password entry.
	}
	return key_pressed;//If the key code is not '*' or '#', the function returns the key code.
}




static uint8_t lock_get_password(void)
/*
* @note   This function prompts the user to enter a new password through some graphical user interface
*         (GUI) or input method. The password is displayed as an asterisk shadow while being entered.
*         The function updates both the password shadow and the new password as digits are entered.
*         The `GUI_update_password` function is expected to handle the visual update of the user interface.
*/
{
    uint8_t idx = 0;  // Current position in the password
    uint8_t passkey = 0;  // Temporary variable to store each digit of the password
    uint8_t new_password[MAX_PASSWORD];  // Variable to store the new password
    memset(new_password, 0, MAX_PASSWORD);  // Initialize the new password variable with zeros
    uint8_t password_shadow[MAX_PASSWORD + 1]  = {
        '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'
    };  // Password shadow used to display the length of the password

    // Loop to obtain password digits until a confirmation button is pressed (0xFF)
    while (passkey != 0xFF) {
        // Update the user interface with the password shadow
        GUI_update_password(password_shadow);

        // Get the next digit of the password
        passkey = lock_get_passkey();

        // Display the entered digit as an asterisk in the password shadow
        password_shadow[idx] = '*';

        // Store the digit in the new password and update the index
        new_password[idx++] = passkey;

        // Update the user interface with the new password
        GUI_update_password(new_password);

        // Wait for a brief period before the next iteration (adjust according to your needs)
        HAL_Delay(200);
    }

    // Check if enough digits were entered to set a new password
    if (idx > 1) {
        // Copy the new password to the location of the current password
        memcpy(password, new_password, MAX_PASSWORD);

        // Inform the user interface about the success in updating the password
        GUI_update_password_success();

        // The operation was successful
        return 1;
    } else {
        // Inform the user interface that not enough digits were entered
        GUI_locked();

        // The operation failed
        return 0;
    }
}

int statusl(void)
{
	if(status==1){
	return 1;
	}
	else if(status!=1)
	{
		return 0;
	}


}

static uint8_t lock_validate_password(void)
/*
* @note   This function retrieves the sequence of digits entered through a keypad from a ring buffer.
*         It then compares the entered sequence with the stored password. If the sequences match,
*         the function returns 1 indicating a successful validation; otherwise, it returns 0.
*/

{
    uint8_t sequence[MAX_PASSWORD];  // Array to store the entered password sequence
    uint8_t seq_len = ring_buffer_size(&keypad_rb);  // Length of the entered sequence

    // Retrieve the entered sequence from the keypad ring buffer
    for (uint8_t idx = 0; idx < seq_len; idx++) {
        ring_buffer_get(&keypad_rb, &sequence[idx]);
    }

    // Compare the entered sequence with the stored password (assuming a password length of 4 digits)
    if (memcmp(sequence, password, 4) == 0) {
        // The entered password is valid
        return 1;
    }

    // The entered password is not valid
    return 0;
}

static void lock_update_password(void)

/* @note   This function first validates the entered password using the `lock_validate_password` function.
*         If the validation is successful, it initializes the user interface for password updating using
*         the `GUI_update_password_init` function, and then proceeds to obtain a new password through
*         the `lock_get_password` function. If the validation fails, indicating an incorrect password,
*         it updates the user interface to indicate the locked state using the `GUI_locked` function.
*/

{
    // Validate the entered password
    if (lock_validate_password() != 0) {
        // If the validation is successful, initialize the password update UI
        GUI_update_password_init();

        // Obtain a new password from the user
        lock_get_password();
    } else {
        // If the validation fails, update the UI to indicate the locked state
        GUI_locked();
    }
}

static void lock_open_lock(void)


/* @note   This function first validates the entered password using the `lock_validate_password` function.
 *         If the validation is successful, indicating a correct password, it updates the user interface
 *         to indicate an unlocked state using the `GUI_unlocked` function. If the validation fails,
 *         indicating an incorrect password, it updates the user interface to indicate the locked state
 *         using the `GUI_locked` function.
*/

{
    // Validate the entered password
    if (lock_validate_password() != 0) {
        // If the validation is successful, update the UI to indicate an unlocked state
        GUI_unlocked();
    } else {
        // If the validation fails, update the UI to indicate the locked state
        GUI_locked();
    }
}
void lock_init(void)

/* @note   This function sets up the initial state of the lock system by initializing the keypad ring buffer,
*         the graphical user interface (GUI), and any other necessary components. It is typically called
*         during the system initialization to prepare the lock system for operation.
*/


{
    // Initialize the keypad ring buffer with a capacity of 12 elements
    ring_buffer_init(&keypad_rb, keypad_buffer, 12);

    // Initialize the graphical user interface (GUI)
    GUI_init();
}

void lock_sequence_handler(uint8_t key)

/* @note   This function interprets the input key and takes appropriate actions within the lock system.
*         If the key is '*', it triggers the password update process by calling the `lock_update_password`
*         function. If the key is '#', it attempts to open the lock by calling the `lock_open_lock` function
*         and sets a system status indicator to 1. For any other keys, the function adds the key to the
*         keypad ring buffer for further processing.
*/
{
    if (key == '*') {
        // If the key is '*', trigger the password update process
        lock_update_password();
    } else if (key == '#') {
        // If the key is '#', attempt to open the lock and set the system status to 1
        lock_open_lock();
        status = 1;
    } else {
        // For any other keys, add the key to the keypad ring buffer for further processing
        ring_buffer_put(&keypad_rb, key);
    }
}
