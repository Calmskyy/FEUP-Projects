#pragma once

#include <stdint.h>

#define STATE_MACHINE_ERROR NULL

typedef enum {
  MAIN_MENU,
  HOW_MENU,
  HOW_PAGE2,
  HOW_PAGE3,
  OVERWORLD,
  COMBAT,
  ATTACK_PICK,
  ACTION_PICK,
  GIVE_UP_PICK,
  FIGHT_ANIMATION,
  CHECK_HP,
  BOOST_MESSAGE,
  ATTACK_1,
  ATTACK_2,
  ATTACK_3,
  ATTACK_4,
  ATTACK_5,
  ATTACK_6,
  ATTACK_7,
  ATTACK_8,
  END_SCREEN,
} state_t;

typedef enum {
  MOUSE_LB_PRESSED,
  MOUSE_LB_RELEASED,
  MOUSE_MOVEMENT,
  TIMER_TICK,
  RTC_PERIODIC,
  W_PRESS,
  A_PRESS,
  S_PRESS,
  D_PRESS,
  W_RELEASE,
  A_RELEASE,
  S_RELEASE,
  D_RELEASE,
  Z_PRESS,
  X_PRESS
} event_t;

typedef struct {
  state_t state;
  event_t events[40];
  unsigned int events_to_process;
} StateMachine;

/**
 * @brief Creates a state machine object.
 *
 * @return Returns the state machine object created.
 */
StateMachine *create_state_machine();

/**
 * @brief Destroys a state machine.
 *
 * @param sm State machine to be destroyed.
 */
void destroy_state_machine(StateMachine *sm);

/**
 * @brief Adds a detected event to the state machine buffer, for processing.
 *
 * @param sm State machine to be updated.
 * @param evt Event to be added to the state machine buffer.
 */
void event_found(StateMachine *sm, event_t evt);

/**
 * @brief Processes the events awaiting on the state machine buffer.
 *
 */
void event_handler();

/**
 * @brief Upon the detection of the TIMER_TICK event, execute commands depending on the current state machine's state.
 *
 */
void timer_frame_handler();

/**
 * @brief Upon the detection of the RTC_PERIODIC event, execute commands depending on the current state machine's state.
 *
 */
void rtc_handler();

/**
 * @brief Upon the detection of the MOUSE_LB_PRESSED event, execute commands depending on the current state machine's state.
 *
 */
void mouse_lb_pressed_handler();

/**
 * @brief Upon the detection of the MOUSE_LB_RELEASED event, execute commands depending on the current state machine's state.
 *
 */
void mouse_lb_released_handler();

/**
 * @brief Upon the detection of the MOUSE_MOVEMENT event, execute commands depending on the current state machine's state.
 *
 */
void mouse_movement_handler();

/**
 * @brief Upon the detection of the W_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void w_press_handler();

/**
 * @brief Upon the detection of the A_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void a_press_handler();

/**
 * @brief Upon the detection of the S_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void s_press_handler();

/**
 * @brief Upon the detection of the D_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void d_press_handler();

/**
 * @brief Upon the detection of the Z_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void z_press_handler();

/**
 * @brief Upon the detection of the X_PRESS event, execute commands depending on the current state machine's state.
 *
 */
void x_press_handler();

/**
 * @brief Upon the detection of the W_RELEASE event, execute commands depending on the current state machine's state.
 *
 */
void w_release_handler();

/**
 * @brief Upon the detection of the A_RELEASE event, execute commands depending on the current state machine's state.
 *
 */
void a_release_handler();

/**
 * @brief Upon the detection of the S_RELEASE event, execute commands depending on the current state machine's state.
 *
 */
void s_release_handler();

/**
 * @brief Upon the detection of the D_RELEASE event, execute commands depending on the current state machine's state.
 *
 */
void d_release_handler();
