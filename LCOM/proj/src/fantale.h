#pragma once

#include "bitmap.h"
#include "button.h"
#include "character.h"
#include "cursor.h"
#include "dispatcher.h"

#define LOAD_SUCCESS 0
#define FANTALE_ERROR 1
#define BMP_LOAD_ERROR 2
#define OBJECT_CREATION_ERROR 3
#define LOAD_FAILED NULL
#define GAME_CREATION_ERROR NULL
#define STATE_MACHINE_CREATION_ERROR NULL
#define TIMER_BIT 0
#define MOUSE_BIT 12
#define KEYBOARD_BIT 10
#define RTC_BIT 8
#define SUBSCRIPTION_ERROR -1
#define FAILED_SUBSCRIPTION 1

#define CURSOR_PATH "/home/lcom/labs/proj/images/cursor.bmp"
#define TITLE_PATH "/home/lcom/labs/proj/images/title.bmp"
#define PLAY_HOVER_PATH "/home/lcom/labs/proj/images/play_hover.bmp"
#define PLAY_DEFAULT_PATH "/home/lcom/labs/proj/images/play.bmp"
#define EXIT_HOVER_PATH "/home/lcom/labs/proj/images/exit_hover.bmp"
#define EXIT_DEFAULT_PATH "/home/lcom/labs/proj/images/exit.bmp"
#define HOW_HOVER_PATH "/home/lcom/labs/proj/images/how_hover.bmp"
#define HOW_DEFAULT_PATH "/home/lcom/labs/proj/images/how.bmp"
#define BACK_HOVER_PATH "/home/lcom/labs/proj/images/back_hover.bmp"
#define BACK_DEFAULT_PATH "/home/lcom/labs/proj/images/back.bmp"
#define NEXT_HOVER_PATH "/home/lcom/labs/proj/images/next_hover.bmp"
#define NEXT_DEFAULT_PATH "/home/lcom/labs/proj/images/next.bmp"
#define HOW_PAGE1_PATH "/home/lcom/labs/proj/images/how_page1.bmp"
#define HOW_PAGE2_PATH "/home/lcom/labs/proj/images/how_page2.bmp"
#define HOW_PAGE3_PATH "/home/lcom/labs/proj/images/how_page3.bmp"
#define OVERWORLD_DAY_PATH "/home/lcom/labs/proj/images/overworld_day.bmp"
#define OVERWORLD_NIGHT_PATH "/home/lcom/labs/proj/images/overworld_night.bmp"
#define OVERWORLD_CHARACTER_PATH "/home/lcom/labs/proj/images/overworld_character.bmp"
#define OVERWORLD_CHARACTER_LEFT_PATH "/home/lcom/labs/proj/images/overworld_character_left.bmp"
#define OVERWORLD_WALK1_PATH "/home/lcom/labs/proj/images/overworld_walk1.bmp"
#define OVERWORLD_WALK1_LEFT_PATH "/home/lcom/labs/proj/images/overworld_walk1_left.bmp"
#define OVERWORLD_WALK2_PATH "/home/lcom/labs/proj/images/overworld_walk2.bmp"
#define OVERWORLD_WALK2_LEFT_PATH "/home/lcom/labs/proj/images/overworld_walk2_left.bmp"
#define OVERWORLD_ROAD_PATH "/home/lcom/labs/proj/images/overworld_road.bmp"
#define OVERWORLD_FENCE_PATH "/home/lcom/labs/proj/images/overworld_fence.bmp"
#define ATTACK_DEFAULT_PATH "/home/lcom/labs/proj/images/attack.bmp"
#define ATTACK_HOVER_PATH "/home/lcom/labs/proj/images/attack_hover.bmp"
#define ACTION_DEFAULT_PATH "/home/lcom/labs/proj/images/action.bmp"
#define ACTION_HOVER_PATH "/home/lcom/labs/proj/images/action_hover.bmp"
#define GIVE_UP_DEFAULT_PATH "/home/lcom/labs/proj/images/give_up.bmp"
#define GIVE_UP_HOVER_PATH "/home/lcom/labs/proj/images/give_up_hover.bmp"
#define SELECT_PATH "/home/lcom/labs/proj/images/select.bmp"
#define HP_BAR_PATH "/home/lcom/labs/proj/images/hp_bar.bmp"
#define GREEN_HP_PATH "/home/lcom/labs/proj/images/green_hp.bmp"
#define PLAYER_NAME_PATH "/home/lcom/labs/proj/images/player_name.bmp"
#define ENEMY_PATH "/home/lcom/labs/proj/images/enemy.bmp"
#define LITTLE_SELECT_PATH "/home/lcom/labs/proj/images/little_select.bmp"
#define BOOST_CHAT_PATH "/home/lcom/labs/proj/images/boost_chat.bmp"
#define BOOST_SUCCESS_PATH "/home/lcom/labs/proj/images/boost_success.bmp"
#define BOOST_FAILED_PATH "/home/lcom/labs/proj/images/boost_failed.bmp"
#define HEAL_CHAT_PATH "/home/lcom/labs/proj/images/heal_chat.bmp"
#define CHECK_CHAT_PATH "/home/lcom/labs/proj/images/check_chat.bmp"
#define CONFIRM_CHAT_PATH "/home/lcom/labs/proj/images/confirm_chat.bmp"
#define ENEMY_CHAT_PATH "/home/lcom/labs/proj/images/enemy_chat.bmp"
#define ATTACK_BAR_PATH "/home/lcom/labs/proj/images/attack_bar.bmp"
#define CHATBOX_TILE_PATH "/home/lcom/labs/proj/images/chatbox_tile.bmp"
#define SLASH_PATH "/home/lcom/labs/proj/images/slash.bmp"
#define DAMAGE_TEN_PATH "/home/lcom/labs/proj/images/damage_ten.bmp"
#define DAMAGE_EIGHT_PATH "/home/lcom/labs/proj/images/damage_eight.bmp"
#define DAMAGE_SIX_PATH "/home/lcom/labs/proj/images/damage_six.bmp"
#define DAMAGE_TWELVE_PATH "/home/lcom/labs/proj/images/damage_twelve.bmp"
#define TARGET_PATH "/home/lcom/labs/proj/images/target.bmp"
#define GOOD_BAR_PATH "/home/lcom/labs/proj/images/good_bar.bmp"
#define NUMBER_ZERO_PATH "/home/lcom/labs/proj/images/number_zero.bmp"
#define NUMBER_ONE_PATH "/home/lcom/labs/proj/images/number_one.bmp"
#define NUMBER_TWO_PATH "/home/lcom/labs/proj/images/number_two.bmp"
#define NUMBER_THREE_PATH "/home/lcom/labs/proj/images/number_three.bmp"
#define NUMBER_FOUR_PATH "/home/lcom/labs/proj/images/number_four.bmp"
#define NUMBER_FIVE_PATH "/home/lcom/labs/proj/images/number_five.bmp"
#define NUMBER_SIX_PATH "/home/lcom/labs/proj/images/number_six.bmp"
#define NUMBER_SEVEN_PATH "/home/lcom/labs/proj/images/number_seven.bmp"
#define NUMBER_EIGHT_PATH "/home/lcom/labs/proj/images/number_eight.bmp"
#define NUMBER_NINE_PATH "/home/lcom/labs/proj/images/number_nine.bmp"
#define NUMBER_BAR_PATH "/home/lcom/labs/proj/images/number_bar.bmp"
#define PLAYER_PATH "/home/lcom/labs/proj/images/player.bmp"
#define A1_VERTICAL_PATH "/home/lcom/labs/proj/images/a1_vertical.bmp"
#define A1_VERTICAL_RED_PATH "/home/lcom/labs/proj/images/a1_vertical_red.bmp"
#define A1_HORIZONTAL_PATH "/home/lcom/labs/proj/images/a1_horizontal.bmp"
#define A1_HORIZONTAL_RED_PATH "/home/lcom/labs/proj/images/a1_horizontal_red.bmp"
#define A2_METEOR_PATH "/home/lcom/labs/proj/images/a2_meteor.bmp"
#define A2_METEOR_RIGHT_PATH "/home/lcom/labs/proj/images/a2_meteor_right.bmp"
#define A3_SNAKE_PATH "/home/lcom/labs/proj/images/a3_snake.bmp"
#define A3_SNAKE_RED_PATH "/home/lcom/labs/proj/images/a3_snake_red.bmp"
#define A4_COG_PATH "/home/lcom/labs/proj/images/a4_cog.bmp"
#define A4_COG_RED_PATH "/home/lcom/labs/proj/images/a4_cog_red.bmp"
#define A5_LOADING_PATH "/home/lcom/labs/proj/images/a5_loading.bmp"
#define A5_LASER_PATH "/home/lcom/labs/proj/images/a5_laser.bmp"
#define A6_HBAR_PATH "/home/lcom/labs/proj/images/a6_hbar.bmp"
#define A6_VBAR_PATH "/home/lcom/labs/proj/images/a6_vbar.bmp"
#define A7_SPIKE_DOWN_PATH "/home/lcom/labs/proj/images/a7_spike_down.bmp"
#define A7_SPIKE_DOWN_RED_PATH "/home/lcom/labs/proj/images/a7_spike_down_red.bmp"
#define A7_SPIKE_LEFT_PATH "/home/lcom/labs/proj/images/a7_spike_left.bmp"
#define A7_SPIKE_LEFT_RED_PATH "/home/lcom/labs/proj/images/a7_spike_left_red.bmp"
#define A7_SPIKE_UP_PATH "/home/lcom/labs/proj/images/a7_spike_up.bmp"
#define A7_SPIKE_UP_RED_PATH "/home/lcom/labs/proj/images/a7_spike_up_red.bmp"
#define A7_SPIKE_RIGHT_PATH "/home/lcom/labs/proj/images/a7_spike_right.bmp"
#define A7_SPIKE_RIGHT_RED_PATH "/home/lcom/labs/proj/images/a7_spike_right_red.bmp"
#define A8_METEOR_PATH "/home/lcom/labs/proj/images/a8_meteor.bmp"
#define A8_METEOR_RIGHT_PATH "/home/lcom/labs/proj/images/a8_meteor_right.bmp"
#define A8_LOADING_PATH "/home/lcom/labs/proj/images/a8_loading.bmp"
#define A8_LASER_PATH "/home/lcom/labs/proj/images/a8_laser.bmp"
#define CONTINUE_BUTTON_PATH "/home/lcom/labs/proj/images/continue_button.bmp"
#define DEATH_MESSAGE_PATH "/home/lcom/labs/proj/images/death_message.bmp"
#define VICTORY_MESSAGE_PATH "/home/lcom/labs/proj/images/victory_message.bmp"

#define PLAY_BUTTON_CLICK 1
#define HOW_BUTTON_CLICK 2
#define EXIT_BUTTON_CLICK 3
#define BACK_BUTTON_CLICK 4
#define NEXT_BUTTON_CLICK 5
#define NULL_POINTERS 6
#define NO_BUTTON_COLLISION 8

#define BACKGROUND_FIRST_BYTE 0xff
#define BACKGROUND_SECOND_BYTE 0x12
#define BACKGROUND_THIRD_BYTE 0x6C
#define BACKGROUND_FOURTH_BYTE 0xBF

#define ANIMATION_FINISHED 0
#define ANIMATION_NOT_FINISHED 1

#define RIGHT_REACHED 5

#define NOTHING_HAPPENED 0
#define INVALID_KEY 1
#define UP_MOVEMENT 2
#define LEFT_MOVEMENT 3
#define DOWN_MOVEMENT 4
#define RIGHT_MOVEMENT 5
#define UP_AND_LEFT_MOVEMENT 6
#define UP_AND_RIGHT_MOVEMENT 7
#define DOWN_AND_LEFT_MOVEMENT 8
#define DOWN_AND_RIGHT_MOVEMENT 9

typedef struct {
  Sprite *title, *select, *green_hp, *hp_bar, *player_name, *chatbox_tile, *slash, *damage_ten, *damage_eight, *damage_six, *damage_twelve, *overworld, *overworld_fence, *overworld_road;
  Sprite *little_select, *boost_chat, *check_chat, *confirm_chat, *enemy_chat, *heal_chat, *attack_bar, *good_bar, *target, *boost_success, *boost_failed, *how_page1, *how_page2, *how_page3;
  Sprite *number_zero, *number_one, *number_two, *number_three, *number_four, *number_five, *number_six, *number_seven, *number_eight, *number_nine, *number_bar;
  Sprite *a1_vertical, *a1_vertical_red, *a1_horizontal, *a1_horizontal_red, *a2_meteor, *a2_meteor_right, *a3_snake, *a3_snake_red, *a4_snake, *a4_snake_red, *a4_cog, *a4_cog_red;
  Sprite *a5_loading, *a5_laser, *a6_hbar, *a6_vbar, *a7_spike_down, *a7_spike_down_red, *a7_spike_left, *a7_spike_left_red, *a7_spike_up, *a7_spike_up_red, *a7_spike_right, *a7_spike_right_red;
  Sprite *a8_loading, *a8_laser, *a8_meteor, *a8_meteor_right, *continue_button, *death_message, *victory_message, *overworld_character_left, *overworld_walk1, *overworld_walk2, *overworld_walk1_left, *overworld_walk2_left;
  Cursor *cursor;
  Button *exit, *play, *how, *back, *attack, *action, *give_up, *next;
  Character *enemy, *player, *overworld_character;
  StateMachine *sm;
  int end, boost, time;
} FanTale;

typedef enum {
  NO_PRESS,
  UP_PRESS,
  LEFT_PRESS,
  DOWN_PRESS,
  RIGHT_PRESS,
  UP_RELEASE,
  LEFT_RELEASE,
  DOWN_RELEASE,
  RIGHT_RELEASE,
  RESET,
} keys;

/**
 * @brief Loads the cursor image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_cursor(FanTale *game);

/**
 * @brief Loads the title image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_title(FanTale *game);

/**
 * @brief Loads the play button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_play_button(FanTale *game);

/**
 * @brief Loads the how to play button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_how_button(FanTale *game);

/**
 * @brief Loads the exit button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_exit_button(FanTale *game);

/**
 * @brief Loads the back arrow button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_back_button(FanTale *game);

/**
 * @brief Loads the next arrow button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_next_button(FanTale *game);

/**
 * @brief Loads the first page of instructions image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_how_page1(FanTale *game);

/**
 * @brief Loads the second page of instructions image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_how_page2(FanTale *game);

/**
 * @brief Loads the third page of instructions image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_how_page3(FanTale *game);

/**
 * @brief Loads the overworld images and creates the corresponding objects.
 *
 * Checks the RTC's saved time to load different images depending on night/day. (8 AM to 8 PM is daytime, 8 PM to 8 AM is nighttime)
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_overworld(FanTale *game);

/**
 * @brief Loads the attack button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack_button(FanTale *game);

/**
 * @brief Loads the action button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_action_button(FanTale *game);

/**
 * @brief Loads the give up button images and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_give_up_button(FanTale *game);

/**
 * @brief Loads the selection arrow image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_select(FanTale *game);

/**
 * @brief Loads the health bar image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_hp_bar(FanTale *game);

/**
 * @brief Loads the player display name image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_player_name(FanTale *game);

/**
 * @brief Loads the health image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_green_hp(FanTale *game);

/**
 * @brief Loads the enemy image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_enemy(FanTale *game);

/**
 * @brief Loads the boost option image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_boost_chat(FanTale *game);

/**
 * @brief Loads the heal option image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_heal_chat(FanTale *game);

/**
 * @brief Loads the enemy option image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_enemy_chat(FanTale *game);

/**
 * @brief Loads the check option image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_check_chat(FanTale *game);

/**
 * @brief Loads the confirm option image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_confirm_chat(FanTale *game);

/**
 * @brief Loads the small selection arrow image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_little_select(FanTale *game);

/**
 * @brief Loads the moving attack animation bar image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack_bar(FanTale *game);

/**
 * @brief Loads the damage animation image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_slash(FanTale *game);

/**
 * @brief Loads the damage display numbers images and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_damage_numbers(FanTale *game);

/**
 * @brief Loads the middle target (in the attack animation) image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_target(FanTale *game);

/**
 * @brief Loads the marker for a 'good' attack (in the attack animation) image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_good_bar(FanTale *game);

/**
 * @brief Loads the health display numbers images and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_numbers(FanTale *game);

/**
 * @brief Loads the playable character image and creates the corresponding object.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_player(FanTale *game);

/**
 * @brief Loads the images for the first enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack1(FanTale *game);

/**
 * @brief Loads the images for the second enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack2(FanTale *game);

/**
 * @brief Loads the images for the third enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack3(FanTale *game);

/**
 * @brief Loads the images for the fourth enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack4(FanTale *game);

/**
 * @brief Loads the images for the fifth enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack5(FanTale *game);

/**
 * @brief Loads the images for the sixth enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack6(FanTale *game);

/**
 * @brief Loads the images for the seventh enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack7(FanTale *game);

/**
 * @brief Loads the images for the eighth enemy attack and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_attack8(FanTale *game);

/**
 * @brief Loads the images for the end of game screen and creates the corresponding objects.
 *
 * @param game Object that contains all game objects.
 * @return Returns a success/error value.
 */
int load_end_screen(FanTale *game);

/**
 * @brief Creates the game object.
 *
 * Creates the main game object, then loads every single file/object contained in the main game object, and destroys them afterwards, to make sure that all files are present. An error is given if a file is not encountered.
 *
 * @return Returns the game object, or a null pointer in case of any error.
 */
FanTale *create_game();

/**
 * @brief Terminates the program.
 *
 * Returns to minix's default text mode, destroys the remaining game objects and unsubscribes all the interrupts used.
 *
 * @param game Object that contains all game objects.
 */
void finish_game(FanTale *game);

/**
 * @brief Function that contains the interrupt handler loop.
 *
 * Subscribes the necessary interrupts, loads the initial game objects, and starts the interrupt handler loop, calling the event handler based on the interrupts' contents.
 *
 * @param game Object that contains all game objects.
 * @return Returns an error value if there's an error subscribing interrupts, otherwise returns success when the game is about to terminate.
 */
int fantale_loop(FanTale *game);

/**
 * @brief Loads the objects necessary for the main menu.
 *
 */
void load_main_menu();

/**
 * @brief Loads the objects necessary for the how to play menu.
 *
 */
void load_how_menu();

/**
 * @brief Loads the objects necessary for the combat.
 *
 */
void load_combat();

/**
 * @brief Loads the objects necessary for the player's attack.
 *
 */
void load_player_attack();

/**
 * @brief Destroys the objects necessary for the player's attack.
 *
 */
void destroy_player_attack();

/**
 * @brief Destroys the objects necessary for the combat.
 *
 */
void destroy_combat();

/**
 * @brief Destroys the objects necessary for the main menu.
 *
 */
void destroy_main_menu();

/**
 * @brief Destroys the objects necessary for the how to play menu.
 *
 */
void destroy_how_menu();

/**
 * @brief Destroys the objects necessary for the overworld.
 *
 */
void destroy_overworld();

/**
 * @brief Destroys the objects necessary for the health numbers.
 *
 */
void destroy_numbers();

/**
 * @brief Destroys the objects necessary for the damage numbers.
 *
 */
void destroy_damage_numbers();

/**
 * @brief Destroys the objects necessary for the first attack.
 *
 */
void destroy_attack1();

/**
 * @brief Destroys the objects necessary for the second attack.
 *
 */
void destroy_attack2();

/**
 * @brief Destroys the objects necessary for the third attack.
 *
 */
void destroy_attack3();

/**
 * @brief Destroys the objects necessary for the fourth attack.
 *
 */
void destroy_attack4();

/**
 * @brief Destroys the objects necessary for the fifth attack.
 *
 */
void destroy_attack5();

/**
 * @brief Destroys the objects necessary for the sixth attack.
 *
 */
void destroy_attack6();

/**
 * @brief Destroys the objects necessary for the seventh attack.
 *
 */
void destroy_attack7();

/**
 * @brief Destroys the objects necessary for the eighth attack.
 *
 */
void destroy_attack8();

/**
 * @brief Destroys the objects necessary for the end of game screen.
 *
 */
void destroy_end_screen();

/**
 * @brief Draws the main menu's background on the screen.
 *
 */
void draw_background();

/**
 * @brief Draws the main menu objects on the screen.
 *
 */
void draw_main_menu();

/**
 * @brief Draws the how to play menu objects on the screen.
 *
 */
void draw_how_menu();

/**
 * @brief Draws the overworld objects on the screen, and handles the character's walk cycle (different sprites depending on how many frames spent walking).
 *
 * @return Returns an animation finished flag if the player reaches the right end of the screen, otherwise returns an animation incomplete flag.
 */
int draw_overworld();

/**
 * @brief Draws the combat objects on the screen. Different objects are drawn depending on which combat option is being hovered.
 *
 */
void draw_combat();

/**
 * @brief Draws the check command (displays the amount of HP that the enemy has).
 *
 */
void draw_check_hp();

/**
 * @brief Draws the appropriate boost command message (acknowledges the boost, or warns the player that boost was already used).
 *
 */
void draw_boost_message();

/**
 * @brief Draws the player's HP bar.
 *
 */
void draw_hp_bar();

/**
 * @brief Draws the HP amount (in numbers) of a character.
 *
 * @param hp Health number that needs to be displayed.
 * @param which Flag used to differentiate enemy and player's drawings (as they are drawn in different places).
 */
void draw_hp_amount(int hp, int which);

/**
 * @brief Draws the box that encapsulates combat options in the player's turn, and fighting area in the enemy's turn.
 *
 * @param width Width of the box to be drawn.
 * @param height Height of the box to be drawn.
 * @param x Starting x position of the box.
 * @param y Starting y position of the box.
 */
void draw_chatbox(unsigned int width, unsigned int height, int x, int y);

/**
 * @brief Draws the player's attack animation.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_fight_animation();

/**
 * @brief Handles the execution of and draws the enemy's first attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack1();

/**
 * @brief Handles the execution of and draws the enemy's second attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack2();

/**
 * @brief Handles the execution of and draws the enemy's third attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack3();

/**
 * @brief Handles the execution of and draws the enemy's fourth attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack4();

/**
 * @brief Handles the execution of and draws the enemy's fifth attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack5();

/**
 * @brief Handles the execution of and draws the enemy's sixth attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack6();

/**
 * @brief Handles the execution of and draws the enemy's seventh attack.
 *
 * @return Returns an animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack7();

/**
 * @brief Handles the execution of and draws the enemy's eighth attack.
 *
 * @return Animation finished flag if the animation is finished, otherwise returns an animation incomplete flag.
 */
int draw_attack8();

/**
 * @brief Draws the end of game screen, depending if the game was won or lost.
 *
 */
void draw_end_screen();

/**
 * @brief Checks if the cursor is in the area of the button, highlighting the button if hovered, and clicking the button if left click is pressed.
 *
 * @param but Button whose area will be checked.
 * @param curs Cursor object interacting with the button.
 * @return 3 possible flags: one for no collision, one for button hovering, and one for button clicking.
 */
int check_collision(Button *but, Cursor *curs);

/**
 * @brief Checks if the cursor is in the area of any button on the screen.
 *
 * @return Hover/click flag of a specific button, if one is being hovered over.
 */
int check_all_collision();

/**
 * @brief Keeps track of which keys are currently being held by the player, and handles the character's movement on a frame-by-frame basis depending on the keys registered.
 *
 * @param key_press Detected key event. Also has 2 extra values, one for no new key event being detected, and one for resetting the program's static variables.
 * @return Flag for each possible movement/no movement. 
 */
int handle_character_movement(int key_press);

/**
 * @brief Moves the player on the combat box, depending on the direction the character is currently travelling in.
 *
 */
void move_player();

/**
 * @brief Moves the player on the combat box's final attack, depending on the direction the character is currently travelling in.
 *
 */
void move_player_final();

/**
 * @brief Moves the player on the overworld, depending on the direction the character is currently travelling in.
 *
 * @return Movement the character made, to be used on changing sprites in the character's walk cycle.
 */
int move_overworld();

/**
 * @brief Function called at the end of each enemy attack, resets framecounter and character position, destroys the attack objects used, and checks if the player has died (under 0 HP).
 *
 * @param attack Attack that will be destroyed.
 */
void reset_attack(int attack);

/**
 * @brief Returns the memory address of the framecounter static variable.
 *
 * @return Memory address of the variable.
 */
unsigned int *get_frame_counter();
