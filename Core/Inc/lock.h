/*
 * lock.h
 *
 *  Created on: Nov 20, 2023
 *      Author: saaci
 */


#ifndef INC_LOCK_H_
#define INC_LOCK_H_

#include <stdint.h>

/**
  * @brief  Initializes the lock system.
  *
  * @note   This function sets up the initial state of the lock system, including any necessary
  *         components and modules. It is typically called during the system initialization phase.
  */
void lock_init(void);

/**
  * @brief  Handles a key in the context of the lock system.
  *
  * @param  key: The key entered by the user.
  *
  * @note   This function interprets the input key and takes appropriate actions within the lock system.
  *         It may involve password validation, GUI updates, and other related functionalities based on
  *         the entered key.
  */
void lock_sequence_handler(uint8_t key);

/**
  * @brief  Gets the current status of the lock system.
  *
  * @note   This function returns the current status of the lock system, which may be used for
  *         monitoring or controlling external processes based on the lock state.
  *
  * @retval The current status of the lock system.
  */
int statusl(void);

#endif /* INC_LOCK_H_ */
