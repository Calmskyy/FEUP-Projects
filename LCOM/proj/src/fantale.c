#include "fantale.h"
#include "keyboard.h"
#include "mouse.h"
#include "proj.h"
#include "rtc.h"
#include "timer.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <math.h>

#define PI 3.14159265
static unsigned int framecounter = 0;

int load_cursor(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *cursor_image = load_bitmap_file(CURSOR_PATH);
  if (cursor_image == NULL) {
    printf("Cursor BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->cursor = create_cursor(cursor_image, 100, 100);
  if (game->cursor == NULL) {
    printf("Cursor creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_title(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *title = load_bitmap_file(TITLE_PATH);
  if (title == NULL) {
    printf("Title BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->title = create_sprite(title, 326, 150);
  if (game->title == NULL) {
    printf("Cursor creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_play_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *play_default = load_bitmap_file(PLAY_DEFAULT_PATH);
  BitmapImage *play_hover = load_bitmap_file(PLAY_HOVER_PATH);
  if (play_default == NULL || play_hover == NULL) {
    printf("Play button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->play = create_button(play_default, play_hover, 176, 350);
  if (game->play == NULL) {
    printf("Play button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_how_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *how_default = load_bitmap_file(HOW_DEFAULT_PATH);
  BitmapImage *how_hover = load_bitmap_file(HOW_HOVER_PATH);
  if (how_default == NULL || how_hover == NULL) {
    printf("How to play button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->how = create_button(how_default, how_hover, 626, 350);
  if (game->how == NULL) {
    printf("How to play button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_exit_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *exit_default = load_bitmap_file(EXIT_DEFAULT_PATH);
  BitmapImage *exit_hover = load_bitmap_file(EXIT_HOVER_PATH);
  if (exit_default == NULL || exit_hover == NULL) {
    printf("Exit button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->exit = create_button(exit_default, exit_hover, 401, 600);
  if (game->exit == NULL) {
    printf("Exit button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_back_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *back_default = load_bitmap_file(BACK_DEFAULT_PATH);
  BitmapImage *back_hover = load_bitmap_file(BACK_HOVER_PATH);
  if (back_default == NULL || back_hover == NULL) {
    printf("Back button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->back = create_button(back_default, back_hover, 50, 750);
  if (game->back == NULL) {
    printf("Back button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_next_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *next_default = load_bitmap_file(NEXT_DEFAULT_PATH);
  BitmapImage *next_hover = load_bitmap_file(NEXT_HOVER_PATH);
  if (next_default == NULL || next_hover == NULL) {
    printf("Next button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->next = create_button(next_default, next_hover, 1002, 750);
  if (game->next == NULL) {
    printf("Next button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_how_page1(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *how_page1 = load_bitmap_file(HOW_PAGE1_PATH);
  if (how_page1 == NULL) {
    printf("Instructions BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->how_page1 = create_sprite(how_page1, 300, 100);
  if (game->how_page1 == NULL) {
    printf("Instructions creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_how_page2(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *how_page2 = load_bitmap_file(HOW_PAGE2_PATH);
  if (how_page2 == NULL) {
    printf("Instructions BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->how_page2 = create_sprite(how_page2, 50, 10);
  if (game->how_page2 == NULL) {
    printf("Instructions creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_how_page3(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *how_page3 = load_bitmap_file(HOW_PAGE3_PATH);
  if (how_page3 == NULL) {
    printf("Instructions BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->how_page3 = create_sprite(how_page3, 20, 10);
  if (game->how_page3 == NULL) {
    printf("Instructions creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_overworld(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  if (game->time > 7 && game->time < 20) {
    BitmapImage *overworld_day = load_bitmap_file(OVERWORLD_DAY_PATH);
    if (overworld_day == NULL) {
      printf("Overworld BMP not found.\n");
      return BMP_LOAD_ERROR;
    }
    game->overworld = create_sprite(overworld_day, 0, 0);
    if (game->overworld == NULL) {
      printf("Overworld creation failed.\n");
      return OBJECT_CREATION_ERROR;
    }
  }
  else {
    BitmapImage *overworld_night = load_bitmap_file(OVERWORLD_NIGHT_PATH);
    if (overworld_night == NULL) {
      printf("Overworld BMP not found.\n");
      return BMP_LOAD_ERROR;
    }
    game->overworld = create_sprite(overworld_night, 0, 0);
    if (game->overworld == NULL) {
      printf("Overworld creation failed.\n");
      return OBJECT_CREATION_ERROR;
    }
  }

  BitmapImage *overworld_character = load_bitmap_file(OVERWORLD_CHARACTER_PATH);
  if (overworld_character == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_character_left = load_bitmap_file(OVERWORLD_CHARACTER_LEFT_PATH);
  if (overworld_character_left == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_walk1 = load_bitmap_file(OVERWORLD_WALK1_PATH);
  if (overworld_walk1 == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_walk1_left = load_bitmap_file(OVERWORLD_WALK1_LEFT_PATH);
  if (overworld_walk1_left == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_walk2 = load_bitmap_file(OVERWORLD_WALK2_PATH);
  if (overworld_walk2 == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_walk2_left = load_bitmap_file(OVERWORLD_WALK2_LEFT_PATH);
  if (overworld_walk2_left == NULL) {
    printf("Overworld character BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_fence = load_bitmap_file(OVERWORLD_FENCE_PATH);
  if (overworld_fence == NULL) {
    printf("Overworld fence BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *overworld_road = load_bitmap_file(OVERWORLD_ROAD_PATH);
  if (overworld_road == NULL) {
    printf("Overworld road BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->overworld_character = create_character(overworld_character, 100, 485, 2);
  if (game->overworld_character == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_character_left = create_sprite(overworld_character_left, 100, 485);
  if (game->overworld_character_left == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_walk1 = create_sprite(overworld_walk1, 100, 485);
  if (game->overworld_walk1 == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_walk1_left = create_sprite(overworld_walk1_left, 100, 485);
  if (game->overworld_walk1_left == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_walk2 = create_sprite(overworld_walk2, 100, 485);
  if (game->overworld_walk2 == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_walk2_left = create_sprite(overworld_walk2_left, 100, 485);
  if (game->overworld_walk2_left == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_fence = create_sprite(overworld_fence, 0, 624);
  if (game->overworld_fence == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->overworld_road = create_sprite(overworld_road, 0, 479);
  if (game->overworld_road == NULL) {
    printf("Overworld creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }

  return LOAD_SUCCESS;
}

int load_attack_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *attack_default = load_bitmap_file(ATTACK_DEFAULT_PATH);
  BitmapImage *attack_hover = load_bitmap_file(ATTACK_HOVER_PATH);
  if (attack_default == NULL || attack_hover == NULL) {
    printf("Attack button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->attack = create_button(attack_default, attack_hover, 176, 750);
  if (game->attack == NULL) {
    printf("Attack button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  update_button(game->attack, true);
  return LOAD_SUCCESS;
}

int load_action_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *action_default = load_bitmap_file(ACTION_DEFAULT_PATH);
  BitmapImage *action_hover = load_bitmap_file(ACTION_HOVER_PATH);
  if (action_default == NULL || action_hover == NULL) {
    printf("Action button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->action = create_button(action_default, action_hover, 476, 750);
  if (game->action == NULL) {
    printf("Action button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_give_up_button(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *give_up_default = load_bitmap_file(GIVE_UP_DEFAULT_PATH);
  BitmapImage *give_up_hover = load_bitmap_file(GIVE_UP_HOVER_PATH);
  if (give_up_default == NULL || give_up_hover == NULL) {
    printf("Give up button BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->give_up = create_button(give_up_default, give_up_hover, 776, 750);
  if (game->give_up == NULL) {
    printf("Give up button creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_select(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *select = load_bitmap_file(SELECT_PATH);
  if (select == NULL) {
    printf("Select BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->select = create_sprite(select, 106, 750);
  if (game->select == NULL) {
    printf("Select creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_hp_bar(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *hp_bar = load_bitmap_file(HP_BAR_PATH);
  if (hp_bar == NULL) {
    printf("HP bar BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->hp_bar = create_sprite(hp_bar, 426, 680);
  if (game->hp_bar == NULL) {
    printf("HP bar creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_player_name(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *player_name = load_bitmap_file(PLAYER_NAME_PATH);
  if (player_name == NULL) {
    printf("Player name BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->player_name = create_sprite(player_name, 176, 687);
  if (game->player_name == NULL) {
    printf("Player name creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_green_hp(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *green_hp = load_bitmap_file(GREEN_HP_PATH);
  if (green_hp == NULL) {
    printf("Green HP bar BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->green_hp = create_sprite(green_hp, 428, 682);
  if (game->green_hp == NULL) {
    printf("Green HP bar creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_enemy(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *enemy = load_bitmap_file(ENEMY_PATH);
  if (enemy == NULL) {
    printf("Enemy BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->enemy = create_character(enemy, 496, 140, 150);
  if (game->enemy == NULL) {
    printf("Enemy creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_little_select(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *little_select = load_bitmap_file(LITTLE_SELECT_PATH);
  if (little_select == NULL) {
    printf("Little select BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->little_select = create_sprite(little_select, 200, 500);
  if (game->little_select == NULL) {
    printf("Little select creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_boost_chat(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *boost_chat = load_bitmap_file(BOOST_CHAT_PATH);
  if (boost_chat == NULL) {
    printf("Boost chat BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *boost_success = load_bitmap_file(BOOST_SUCCESS_PATH);
  if (boost_success == NULL) {
    printf("Boost success BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *boost_failed = load_bitmap_file(BOOST_FAILED_PATH);
  if (boost_failed == NULL) {
    printf("Boost failed BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->boost_chat = create_sprite(boost_chat, 235, 585);
  if (game->boost_chat == NULL) {
    printf("Boost chat creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->boost_success = create_sprite(boost_success, 235, 500);
  if (game->boost_success == NULL) {
    printf("Boost success creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->boost_failed = create_sprite(boost_failed, 235, 500);
  if (game->boost_failed == NULL) {
    printf("Boost failed creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_heal_chat(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *heal_chat = load_bitmap_file(HEAL_CHAT_PATH);
  if (heal_chat == NULL) {
    printf("Heal chat BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->heal_chat = create_sprite(heal_chat, 535, 500);
  if (game->heal_chat == NULL) {
    printf("Heal chat creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_enemy_chat(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *enemy_chat = load_bitmap_file(ENEMY_CHAT_PATH);
  if (enemy_chat == NULL) {
    printf("Enemy chat BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->enemy_chat = create_sprite(enemy_chat, 235, 500);
  if (game->enemy_chat == NULL) {
    printf("Enemy chat creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_check_chat(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *check_chat = load_bitmap_file(CHECK_CHAT_PATH);
  if (check_chat == NULL) {
    printf("Check chat BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->check_chat = create_sprite(check_chat, 235, 500);
  if (game->check_chat == NULL) {
    printf("Check chat creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_confirm_chat(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *confirm_chat = load_bitmap_file(CONFIRM_CHAT_PATH);
  if (confirm_chat == NULL) {
    printf("Confirm chat BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->confirm_chat = create_sprite(confirm_chat, 235, 500);
  if (game->confirm_chat == NULL) {
    printf("Confirm chat creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack_bar(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *attack_bar = load_bitmap_file(ATTACK_BAR_PATH);
  if (attack_bar == NULL) {
    printf("Attack bar BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->attack_bar = create_sprite(attack_bar, 176, 460);
  if (game->attack_bar == NULL) {
    printf("Attack bar creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_chatbox_tile(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *chatbox_tile = load_bitmap_file(CHATBOX_TILE_PATH);
  if (chatbox_tile == NULL) {
    printf("Chatbox tile BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->chatbox_tile = create_sprite(chatbox_tile, 172, 460);
  if (game->chatbox_tile == NULL) {
    printf("Chatbox tile creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_slash(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *slash = load_bitmap_file(SLASH_PATH);
  if (slash == NULL) {
    printf("Slash BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->slash = create_sprite(slash, 600, 200);
  if (game->slash == NULL) {
    printf("Slash creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_damage_numbers(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *damage_six = load_bitmap_file(DAMAGE_SIX_PATH);
  if (damage_six == NULL) {
    printf("Six damage BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *damage_eight = load_bitmap_file(DAMAGE_EIGHT_PATH);
  if (damage_eight == NULL) {
    printf("Eight damage BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *damage_ten = load_bitmap_file(DAMAGE_TEN_PATH);
  if (damage_ten == NULL) {
    printf("Ten damage BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *damage_twelve = load_bitmap_file(DAMAGE_TWELVE_PATH);
  if (damage_twelve == NULL) {
    printf("Twelve damage BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->damage_six = create_sprite(damage_six, 680, 200);
  if (game->damage_six == NULL) {
    printf("Six damage creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->damage_eight = create_sprite(damage_eight, 680, 200);
  if (game->damage_eight == NULL) {
    printf("Eight damage creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->damage_ten = create_sprite(damage_ten, 680, 200);
  if (game->damage_ten == NULL) {
    printf("Ten damage creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->damage_twelve = create_sprite(damage_twelve, 680, 200);
  if (game->damage_twelve == NULL) {
    printf("Twelve damage creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_target(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *target = load_bitmap_file(TARGET_PATH);
  if (target == NULL) {
    printf("Target BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->target = create_sprite(target, 526, 460);
  if (game->target == NULL) {
    printf("Target creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_good_bar(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *good_bar = load_bitmap_file(GOOD_BAR_PATH);
  if (good_bar == NULL) {
    printf("Good bar BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->good_bar = create_sprite(good_bar, 422, 460);
  if (game->good_bar == NULL) {
    printf("Good bar creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_numbers(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *number_zero = load_bitmap_file(NUMBER_ZERO_PATH);
  if (number_zero == NULL) {
    printf("Number zero BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_one = load_bitmap_file(NUMBER_ONE_PATH);
  if (number_one == NULL) {
    printf("Number one BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_two = load_bitmap_file(NUMBER_TWO_PATH);
  if (number_two == NULL) {
    printf("Number two BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_three = load_bitmap_file(NUMBER_THREE_PATH);
  if (number_three == NULL) {
    printf("Number three BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_four = load_bitmap_file(NUMBER_FOUR_PATH);
  if (number_four == NULL) {
    printf("Number four BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_five = load_bitmap_file(NUMBER_FIVE_PATH);
  if (number_five == NULL) {
    printf("Number five BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_six = load_bitmap_file(NUMBER_SIX_PATH);
  if (number_six == NULL) {
    printf("Number six BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_seven = load_bitmap_file(NUMBER_SEVEN_PATH);
  if (number_seven == NULL) {
    printf("Number seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_eight = load_bitmap_file(NUMBER_EIGHT_PATH);
  if (number_eight == NULL) {
    printf("Number eight BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_nine = load_bitmap_file(NUMBER_NINE_PATH);
  if (number_nine == NULL) {
    printf("Number nine BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *number_bar = load_bitmap_file(NUMBER_BAR_PATH);
  if (number_bar == NULL) {
    printf("Number bar BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->number_zero = create_sprite(number_zero, 235, 485);
  if (game->number_zero == NULL) {
    printf("Number zero creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_one = create_sprite(number_one, 235, 485);
  if (game->number_one == NULL) {
    printf("Number one creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_two = create_sprite(number_two, 235, 485);
  if (game->number_two == NULL) {
    printf("Number two creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_three = create_sprite(number_three, 235, 485);
  if (game->number_three == NULL) {
    printf("Number three creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_four = create_sprite(number_four, 235, 485);
  if (game->number_four == NULL) {
    printf("Number four creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_five = create_sprite(number_five, 235, 485);
  if (game->number_five == NULL) {
    printf("Number five creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_six = create_sprite(number_six, 235, 485);
  if (game->number_six == NULL) {
    printf("Number six creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_seven = create_sprite(number_seven, 235, 485);
  if (game->number_seven == NULL) {
    printf("Number seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_eight = create_sprite(number_eight, 235, 485);
  if (game->number_eight == NULL) {
    printf("Number eight creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_nine = create_sprite(number_nine, 235, 485);
  if (game->number_nine == NULL) {
    printf("Number nine creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->number_bar = create_sprite(number_bar, 235, 485);
  if (game->number_bar == NULL) {
    printf("Number bar creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_player(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *player = load_bitmap_file(PLAYER_PATH);
  if (player == NULL) {
    printf("Player BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->player = create_character(player, 572, 500, 90);
  if (game->player == NULL) {
    printf("Player creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack1(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a1_vertical = load_bitmap_file(A1_VERTICAL_PATH);
  if (a1_vertical == NULL) {
    printf("Attack one BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a1_vertical_red = load_bitmap_file(A1_VERTICAL_RED_PATH);
  if (a1_vertical_red == NULL) {
    printf("Attack one BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a1_horizontal = load_bitmap_file(A1_HORIZONTAL_PATH);
  if (a1_horizontal == NULL) {
    printf("Attack one BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a1_horizontal_red = load_bitmap_file(A1_HORIZONTAL_RED_PATH);
  if (a1_horizontal_red == NULL) {
    printf("Attack one BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a1_vertical = create_sprite(a1_vertical, 456, 364);
  if (game->a1_vertical == NULL) {
    printf("Attack one creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a1_vertical_red = create_sprite(a1_vertical_red, 456, 364);
  if (game->a1_vertical_red == NULL) {
    printf("Attack one creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a1_horizontal = create_sprite(a1_horizontal, 376, 400);
  if (game->a1_horizontal == NULL) {
    printf("Attack one creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a1_horizontal_red = create_sprite(a1_horizontal_red, 376, 400);
  if (game->a1_horizontal_red == NULL) {
    printf("Attack one creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack2(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a2_meteor = load_bitmap_file(A2_METEOR_PATH);
  if (a2_meteor == NULL) {
    printf("Attack two BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a2_meteor_right = load_bitmap_file(A2_METEOR_RIGHT_PATH);
  if (a2_meteor_right == NULL) {
    printf("Attack two BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a2_meteor = create_sprite(a2_meteor, 456, 364);
  if (game->a2_meteor == NULL) {
    printf("Attack two creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a2_meteor_right = create_sprite(a2_meteor_right, 456, 364);
  if (game->a2_meteor_right == NULL) {
    printf("Attack two creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack3(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a3_snake = load_bitmap_file(A3_SNAKE_PATH);
  if (a3_snake == NULL) {
    printf("Attack three BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a3_snake_red = load_bitmap_file(A3_SNAKE_RED_PATH);
  if (a3_snake_red == NULL) {
    printf("Attack three BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a3_snake = create_sprite(a3_snake, 456, 364);
  if (game->a3_snake == NULL) {
    printf("Attack three creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a3_snake_red = create_sprite(a3_snake_red, 456, 364);
  if (game->a3_snake_red == NULL) {
    printf("Attack three creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack4(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a4_snake = load_bitmap_file(A3_SNAKE_PATH);
  if (a4_snake == NULL) {
    printf("Attack four BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a4_snake_red = load_bitmap_file(A3_SNAKE_RED_PATH);
  if (a4_snake_red == NULL) {
    printf("Attack four BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a4_cog = load_bitmap_file(A4_COG_PATH);
  if (a4_cog == NULL) {
    printf("Attack four BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a4_cog_red = load_bitmap_file(A4_COG_RED_PATH);
  if (a4_cog_red == NULL) {
    printf("Attack four BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a4_snake = create_sprite(a4_snake, 456, 364);
  if (game->a4_snake == NULL) {
    printf("Attack four creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a4_snake_red = create_sprite(a4_snake_red, 456, 364);
  if (game->a4_snake_red == NULL) {
    printf("Attack four creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a4_cog = create_sprite(a4_cog, 550, 488);
  if (game->a4_cog == NULL) {
    printf("Attack four creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a4_cog_red = create_sprite(a4_cog_red, 550, 488);
  if (game->a4_cog_red == NULL) {
    printf("Attack four creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack5(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a5_loading = load_bitmap_file(A5_LOADING_PATH);
  if (a5_loading == NULL) {
    printf("Attack five BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a5_laser = load_bitmap_file(A5_LASER_PATH);
  if (a5_laser == NULL) {
    printf("Attack five BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a5_loading = create_sprite(a5_loading, 456, 364);
  if (game->a5_loading == NULL) {
    printf("Attack five creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a5_laser = create_sprite(a5_laser, 456, 364);
  if (game->a5_laser == NULL) {
    printf("Attack five creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack6(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a6_hbar = load_bitmap_file(A6_HBAR_PATH);
  if (a6_hbar == NULL) {
    printf("Attack six BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a6_vbar = load_bitmap_file(A6_VBAR_PATH);
  if (a6_vbar == NULL) {
    printf("Attack six BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a6_hbar = create_sprite(a6_hbar, 456, 364);
  if (game->a6_hbar == NULL) {
    printf("Attack six creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a6_vbar = create_sprite(a6_vbar, 456, 364);
  if (game->a6_vbar == NULL) {
    printf("Attack six creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack7(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a7_spike_down = load_bitmap_file(A7_SPIKE_DOWN_PATH);
  if (a7_spike_down == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_down_red = load_bitmap_file(A7_SPIKE_DOWN_RED_PATH);
  if (a7_spike_down_red == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_left = load_bitmap_file(A7_SPIKE_LEFT_PATH);
  if (a7_spike_left == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_left_red = load_bitmap_file(A7_SPIKE_LEFT_RED_PATH);
  if (a7_spike_left_red == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_up = load_bitmap_file(A7_SPIKE_UP_PATH);
  if (a7_spike_up == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_up_red = load_bitmap_file(A7_SPIKE_UP_RED_PATH);
  if (a7_spike_up_red == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_right = load_bitmap_file(A7_SPIKE_RIGHT_PATH);
  if (a7_spike_right == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a7_spike_right_red = load_bitmap_file(A7_SPIKE_RIGHT_RED_PATH);
  if (a7_spike_right_red == NULL) {
    printf("Attack seven BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a7_spike_down = create_sprite(a7_spike_down, 376, 610);
  if (game->a7_spike_down == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_down_red = create_sprite(a7_spike_down_red, 376, 610);
  if (game->a7_spike_down_red == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_left = create_sprite(a7_spike_left, 376, 360);
  if (game->a7_spike_left == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_left_red = create_sprite(a7_spike_left_red, 376, 360);
  if (game->a7_spike_left_red == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_up = create_sprite(a7_spike_up, 376, 360);
  if (game->a7_spike_up == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_up_red = create_sprite(a7_spike_up_red, 376, 360);
  if (game->a7_spike_up_red == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_right = create_sprite(a7_spike_right, 726, 360);
  if (game->a7_spike_right == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a7_spike_right_red = create_sprite(a7_spike_right_red, 726, 360);
  if (game->a7_spike_right_red == NULL) {
    printf("Attack seven creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_attack8(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *a8_loading = load_bitmap_file(A8_LOADING_PATH);
  if (a8_loading == NULL) {
    printf("Attack eight BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a8_laser = load_bitmap_file(A8_LASER_PATH);
  if (a8_laser == NULL) {
    printf("Attack eight BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a8_meteor = load_bitmap_file(A8_METEOR_PATH);
  if (a8_meteor == NULL) {
    printf("Attack eight BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *a8_meteor_right = load_bitmap_file(A8_METEOR_RIGHT_PATH);
  if (a8_meteor_right == NULL) {
    printf("Attack eight BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->a8_loading = create_sprite(a8_loading, 456, 364);
  if (game->a8_loading == NULL) {
    printf("Attack eight creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a8_laser = create_sprite(a8_laser, 456, 364);
  if (game->a8_laser == NULL) {
    printf("Attack eight creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a8_meteor = create_sprite(a8_meteor, 456, 364);
  if (game->a8_meteor == NULL) {
    printf("Attack eight creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->a8_meteor_right = create_sprite(a8_meteor_right, 456, 364);
  if (game->a8_meteor_right == NULL) {
    printf("Attack eight creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

int load_end_screen(FanTale *game) {
  if (game == NULL)
    return FANTALE_ERROR;

  BitmapImage *continue_button = load_bitmap_file(CONTINUE_BUTTON_PATH);
  if (continue_button == NULL) {
    printf("End screen BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *death_message = load_bitmap_file(DEATH_MESSAGE_PATH);
  if (death_message == NULL) {
    printf("End screen BMP not found.\n");
    return BMP_LOAD_ERROR;
  }
  BitmapImage *victory_message = load_bitmap_file(VICTORY_MESSAGE_PATH);
  if (victory_message == NULL) {
    printf("End screen BMP not found.\n");
    return BMP_LOAD_ERROR;
  }

  game->continue_button = create_sprite(continue_button, 470, 700);
  if (game->continue_button == NULL) {
    printf("End screen creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->death_message = create_sprite(death_message, 430, 500);
  if (game->death_message == NULL) {
    printf("End screen creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  game->victory_message = create_sprite(victory_message, 430, 500);
  if (game->victory_message == NULL) {
    printf("End screen creation failed.\n");
    return OBJECT_CREATION_ERROR;
  }
  return LOAD_SUCCESS;
}

FanTale *create_game() {
  FanTale *game = (FanTale *) malloc(sizeof(FanTale));

  int loadingerror = 0;

  if (game == NULL)
    return GAME_CREATION_ERROR;

  game->sm = create_state_machine();
  if (game->sm == NULL) {
    printf("State machine creation failed.\n");
    return STATE_MACHINE_CREATION_ERROR;
  }

  if (load_cursor(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_cursor(game->cursor);

  if (load_title(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->title);

  if (load_play_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->play);

  if (load_how_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->how);

  if (load_exit_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->exit);

  if (load_back_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->back);

  if (load_next_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->next);

  if (load_how_page1(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->how_page1);

  if (load_how_page2(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->how_page2);

  if (load_how_page3(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->how_page3);

  if (load_overworld(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->overworld);
  destroy_character(game->overworld_character);
  destroy_sprite(game->overworld_fence);
  destroy_sprite(game->overworld_road);
  destroy_sprite(game->overworld_character_left);
  destroy_sprite(game->overworld_walk1);
  destroy_sprite(game->overworld_walk2);
  destroy_sprite(game->overworld_walk1_left);
  destroy_sprite(game->overworld_walk2_left);

  if (load_attack_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->attack);

  if (load_action_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->action);

  if (load_give_up_button(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_button(game->give_up);

  if (load_select(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->select);

  if (load_hp_bar(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->hp_bar);

  if (load_player_name(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->player_name);

  if (load_green_hp(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->green_hp);

  if (load_enemy(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_character(game->enemy);

  if (load_boost_chat(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->boost_chat);
  destroy_sprite(game->boost_success);
  destroy_sprite(game->boost_failed);

  if (load_heal_chat(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->heal_chat);

  if (load_enemy_chat(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->enemy_chat);

  if (load_check_chat(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->check_chat);

  if (load_confirm_chat(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->confirm_chat);

  if (load_little_select(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->little_select);

  if (load_attack_bar(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->attack_bar);

  if (load_slash(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->slash);

  if (load_damage_numbers(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->damage_six);
  destroy_sprite(game->damage_eight);
  destroy_sprite(game->damage_ten);
  destroy_sprite(game->damage_twelve);

  if (load_target(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->target);

  if (load_good_bar(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->good_bar);

  if (load_numbers(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->number_bar);
  destroy_sprite(game->number_zero);
  destroy_sprite(game->number_one);
  destroy_sprite(game->number_two);
  destroy_sprite(game->number_three);
  destroy_sprite(game->number_four);
  destroy_sprite(game->number_five);
  destroy_sprite(game->number_six);
  destroy_sprite(game->number_seven);
  destroy_sprite(game->number_eight);
  destroy_sprite(game->number_nine);

  if (load_player(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_character(game->player);

  if (load_attack1(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a1_horizontal);
  destroy_sprite(game->a1_horizontal_red);
  destroy_sprite(game->a1_vertical);
  destroy_sprite(game->a1_vertical_red);

  if (load_attack2(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a2_meteor);
  destroy_sprite(game->a2_meteor_right);

  if (load_attack3(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a3_snake);
  destroy_sprite(game->a3_snake_red);

  if (load_attack4(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a4_snake);
  destroy_sprite(game->a4_snake_red);
  destroy_sprite(game->a4_cog);
  destroy_sprite(game->a4_cog_red);

  if (load_attack5(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a5_loading);
  destroy_sprite(game->a5_laser);

  if (load_attack6(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a6_hbar);
  destroy_sprite(game->a6_vbar);

  if (load_attack7(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a7_spike_down);
  destroy_sprite(game->a7_spike_down_red);
  destroy_sprite(game->a7_spike_left);
  destroy_sprite(game->a7_spike_left_red);
  destroy_sprite(game->a7_spike_right);
  destroy_sprite(game->a7_spike_right_red);
  destroy_sprite(game->a7_spike_up);
  destroy_sprite(game->a7_spike_up_red);

  if (load_attack8(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->a8_loading);
  destroy_sprite(game->a8_laser);
  destroy_sprite(game->a8_meteor);
  destroy_sprite(game->a8_meteor_right);

  if (load_end_screen(game) != LOAD_SUCCESS)
    loadingerror = 1;
  destroy_sprite(game->continue_button);
  destroy_sprite(game->death_message);
  destroy_sprite(game->victory_message);

  game->end = 0;
  game->boost = 0;
  game->time = 0;

  if (loadingerror == 1)
    return GAME_CREATION_ERROR;

  return game;
}

void finish_game(FanTale *game) {
  if (game == NULL)
    return;

  vg_exit();
  printf("terminating.\n");
  destroy_button(game->play);
  destroy_cursor(game->cursor);
  destroy_button(game->how);
  destroy_button(game->exit);
  destroy_state_machine(game->sm);
  free_mem(get_buffer());

  if (mouse_unsubscribe_int() == SUBSCRIPTION_ERROR)
    printf("Mouse unsubscription failed.\n");

  unsigned int cmd_byte = DISABLE_DATA;
  issue_command(MOUSE_WRITE_CMD, cmd_byte);
  read_mouse_ack();

  if (timer_unsubscribe_int() == SUBSCRIPTION_ERROR)
    printf("Timer unsubscription failed.\n");

  if (kbc_unsubscribe_int() == SUBSCRIPTION_ERROR)
    printf("Keyboard unsubscription failed.\n");

  if (rtc_unsubscribe_int() == SUBSCRIPTION_ERROR)
    printf("RTC unsubscription failed.\n");

  if (rtc_command(DISABLE_INTERRUPT) != RTC_SUCCESS)
    printf("Disabling RTC interrupts failed.\n");

  free(game);
  game = NULL;
}

int fantale_loop(FanTale *game) {

  int ipc_status, r;
  message msg;

  uint8_t bit_timer = TIMER_BIT;
  uint8_t bit_mouse = MOUSE_BIT;
  uint8_t bit_keyboard = KEYBOARD_BIT;
  uint8_t bit_rtc = RTC_BIT;

  int timer_irq = timer_subscribe_int(&bit_timer);
  if (timer_irq == SUBSCRIPTION_ERROR) {
    printf("Timer subscription failed.\n");
    return FAILED_SUBSCRIPTION;
  }

  unsigned int cmd_byte = ENABLE_DATA;
  issue_command(MOUSE_WRITE_CMD, cmd_byte);
  read_mouse_ack();

  if (rtc_command(ENABLE_INTERRUPT) != RTC_SUCCESS)
    printf("Enabling RTC interrupts failed.\n");

  if (rtc_command(SET_INTERRUPT_RATE) != RTC_SUCCESS)
    printf("Enabling RTC interrupts failed.\n");

  int mouse_irq = mouse_subscribe_int(&bit_mouse);
  if (mouse_irq == SUBSCRIPTION_ERROR) {
    printf("Mouse subscription failed.\n");
    return FAILED_SUBSCRIPTION;
  }

  int keyboard_irq = kbc_subscribe_int(&bit_keyboard);
  if (keyboard_irq == SUBSCRIPTION_ERROR) {
    printf("Keyboard subscription failed.\n");
    return FAILED_SUBSCRIPTION;
  }

  int rtc_irq = rtc_subscribe_int(&bit_rtc);
  if (rtc_irq == SUBSCRIPTION_ERROR) {
    printf("RTC subscription failed.\n");
    return FAILED_SUBSCRIPTION;
  }

  load_main_menu();

  rtc_int_handler();

  while (game->end == 0) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & mouse_irq) {
            mouse_ih();
          }
          if (msg.m_notify.interrupts & keyboard_irq) {
            keyboard_int_handler();
          }
          if (msg.m_notify.interrupts & timer_irq) {
            timer_int_handler();
          }
          if (msg.m_notify.interrupts & rtc_irq) {
            rtc_int_handler();
          }
          break;
        default:
          break;
      }
    }
    event_handler();
  }
  return SUCCESS;
}

void load_main_menu() {
  FanTale *game = get_game();

  if (game->sm->state != (HOW_MENU || MAIN_MENU)) {
    load_cursor(game);
  }

  load_play_button(game);
  game->boost = 0;
  load_how_button(game);
  load_exit_button(game);
  load_title(game);
}

void draw_background() {
  char *buffer = get_buffer();
  unsigned int hres = get_h_res();
  unsigned int vres = get_v_res();

  for (unsigned int i = 0; i < hres * vres * 4; i += 4) {
    *(buffer + i) = BACKGROUND_FIRST_BYTE;
    *(buffer + i + 1) = BACKGROUND_SECOND_BYTE;
    *(buffer + i + 2) = BACKGROUND_THIRD_BYTE;
    *(buffer + i + 3) = BACKGROUND_FOURTH_BYTE;
  }
}

void destroy_main_menu() {
  FanTale *game = get_game();

  if (game->sm->state == OVERWORLD) {
    destroy_cursor(game->cursor);
  }
  destroy_button(game->play);
  destroy_button(game->how);
  destroy_button(game->exit);
  destroy_sprite(game->title);
}

void destroy_overworld() {
  FanTale *game = get_game();

  destroy_character(game->overworld_character);
  destroy_sprite(game->overworld);
  destroy_sprite(game->overworld_fence);
  destroy_sprite(game->overworld_road);
  destroy_sprite(game->overworld_character_left);
  destroy_sprite(game->overworld_walk1);
  destroy_sprite(game->overworld_walk2);
  destroy_sprite(game->overworld_walk1_left);
  destroy_sprite(game->overworld_walk2_left);
}

void load_how_menu() {
  FanTale *game = get_game();

  load_back_button(game);
  load_next_button(game);
  load_how_page1(game);
  load_how_page2(game);
  load_how_page3(game);
}

void destroy_how_menu() {
  FanTale *game = get_game();

  destroy_button(game->back);
  destroy_button(game->next);
  destroy_sprite(game->how_page1);
  destroy_sprite(game->how_page2);
  destroy_sprite(game->how_page3);
}

void load_combat() {
  FanTale *game = get_game();

  load_attack_button(game);
  load_action_button(game);
  load_give_up_button(game);
  load_player_name(game);
  load_hp_bar(game);
  load_green_hp(game);
  load_enemy(game);
  load_select(game);
  load_little_select(game);
  load_enemy_chat(game);
  load_check_chat(game);
  load_heal_chat(game);
  load_boost_chat(game);
  load_confirm_chat(game);
  load_chatbox_tile(game);
  load_player(game);
  load_numbers(game);
}

void load_player_attack() {
  FanTale *game = get_game();

  load_attack_bar(game);
  load_slash(game);
  load_damage_numbers(game);
  load_target(game);
  load_good_bar(game);
}

void destroy_player_attack() {
  FanTale *game = get_game();

  destroy_sprite(game->attack_bar);
  destroy_sprite(game->slash);
  destroy_damage_numbers();
  destroy_sprite(game->target);
  destroy_sprite(game->good_bar);
}

void destroy_combat() {
  FanTale *game = get_game();

  destroy_button(game->attack);
  destroy_button(game->action);
  destroy_button(game->give_up);
  destroy_sprite(game->player_name);
  destroy_sprite(game->hp_bar);
  destroy_sprite(game->green_hp);
  destroy_character(game->enemy);
  destroy_character(game->player);
  destroy_sprite(game->little_select);
  destroy_sprite(game->select);
  destroy_sprite(game->enemy_chat);
  destroy_sprite(game->check_chat);
  destroy_sprite(game->heal_chat);
  destroy_sprite(game->boost_chat);
  destroy_sprite(game->boost_success);
  destroy_sprite(game->boost_failed);
  destroy_sprite(game->confirm_chat);
  destroy_sprite(game->chatbox_tile);
  destroy_numbers();
}

void destroy_numbers() {
  FanTale *game = get_game();

  destroy_sprite(game->number_zero);
  destroy_sprite(game->number_one);
  destroy_sprite(game->number_two);
  destroy_sprite(game->number_three);
  destroy_sprite(game->number_four);
  destroy_sprite(game->number_five);
  destroy_sprite(game->number_six);
  destroy_sprite(game->number_seven);
  destroy_sprite(game->number_eight);
  destroy_sprite(game->number_nine);
  destroy_sprite(game->number_bar);
}

void destroy_damage_numbers() {
  FanTale *game = get_game();

  destroy_sprite(game->damage_six);
  destroy_sprite(game->damage_eight);
  destroy_sprite(game->damage_ten);
  destroy_sprite(game->damage_twelve);
}

void destroy_attack1() {
  FanTale *game = get_game();

  destroy_sprite(game->a1_horizontal);
  destroy_sprite(game->a1_horizontal_red);
  destroy_sprite(game->a1_vertical);
  destroy_sprite(game->a1_vertical_red);
}

void destroy_attack2() {
  FanTale *game = get_game();

  destroy_sprite(game->a2_meteor);
  destroy_sprite(game->a2_meteor_right);
}

void destroy_attack3() {
  FanTale *game = get_game();

  destroy_sprite(game->a3_snake);
  destroy_sprite(game->a3_snake_red);
}

void destroy_attack4() {
  FanTale *game = get_game();

  destroy_sprite(game->a4_snake);
  destroy_sprite(game->a4_snake_red);
  destroy_sprite(game->a4_cog);
  destroy_sprite(game->a4_cog_red);
}

void destroy_attack5() {
  FanTale *game = get_game();

  destroy_sprite(game->a5_loading);
  destroy_sprite(game->a5_laser);
}

void destroy_attack6() {
  FanTale *game = get_game();

  destroy_sprite(game->a6_hbar);
  destroy_sprite(game->a6_vbar);
}

void destroy_attack7() {
  FanTale *game = get_game();

  destroy_sprite(game->a7_spike_down);
  destroy_sprite(game->a7_spike_down_red);
  destroy_sprite(game->a7_spike_left);
  destroy_sprite(game->a7_spike_left_red);
  destroy_sprite(game->a7_spike_right);
  destroy_sprite(game->a7_spike_right_red);
  destroy_sprite(game->a7_spike_up);
  destroy_sprite(game->a7_spike_up_red);
}

void destroy_attack8() {
  FanTale *game = get_game();

  destroy_sprite(game->a8_loading);
  destroy_sprite(game->a8_laser);
  destroy_sprite(game->a8_meteor);
  destroy_sprite(game->a8_meteor_right);
}

void destroy_end_screen() {
  FanTale *game = get_game();

  destroy_sprite(game->continue_button);
  destroy_sprite(game->death_message);
  destroy_sprite(game->victory_message);
}

void draw_main_menu() {
  FanTale *game = get_game();

  draw_background();
  draw_button(game->play);
  draw_button(game->how);
  draw_button(game->exit);
  draw_sprite(game->title);
  draw_cursor(game->cursor);
  buffercopy();
}

void draw_how_menu() {
  FanTale *game = get_game();

  draw_background();

  if (game->sm->state == HOW_MENU)
    draw_sprite(game->how_page1);
  if (game->sm->state == HOW_PAGE2)
    draw_sprite(game->how_page2);
  if (game->sm->state == HOW_PAGE3)
    draw_sprite(game->how_page3);
  draw_button(game->back);
  if (game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2)
    draw_button(game->next);
  draw_cursor(game->cursor);
  buffercopy();
}

int draw_overworld() {
  FanTale *game = get_game();

  static int cyclecount;
  static int direction;
  int movement;

  if (framecounter == 0)
    draw_sprite(game->overworld);
  draw_sprite(game->overworld_road);

  movement = move_overworld();

  if (movement == RIGHT_MOVEMENT || movement == UP_AND_RIGHT_MOVEMENT || movement == DOWN_AND_RIGHT_MOVEMENT) {
    if (direction == 0)
      cyclecount++;
    else if (direction == 1) {
      direction = 0;
      cyclecount = 0;
    }
  }
  else if (movement == LEFT_MOVEMENT || movement == UP_AND_LEFT_MOVEMENT || movement == DOWN_AND_LEFT_MOVEMENT) {
    if (direction == 0) {
      direction = 1;
      cyclecount = 0;
    }
    else if (direction == 1) {
      cyclecount++;
    }
  }
  else if (movement == NOTHING_HAPPENED)
    cyclecount = 0;

  if (cyclecount == 80)
    cyclecount = 0;

  if (direction == 0) {
    if (cyclecount < 20) {
      draw_character(game->overworld_character);
    }
    else if (cyclecount < 40) {
      game->overworld_walk1->x = game->overworld_character->sprite->x;
      game->overworld_walk1->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_walk1);
    }
    else if (cyclecount < 60) {
      draw_character(game->overworld_character);
    }
    else if (cyclecount < 80) {
      game->overworld_walk2->x = game->overworld_character->sprite->x;
      game->overworld_walk2->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_walk2);
    }
  }
  else if (direction == 1) {
    if (cyclecount < 20) {
      game->overworld_character_left->x = game->overworld_character->sprite->x;
      game->overworld_character_left->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_character_left);
    }
    else if (cyclecount < 40) {
      game->overworld_walk1_left->x = game->overworld_character->sprite->x - 20;
      game->overworld_walk1_left->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_walk1_left);
    }
    else if (cyclecount < 60) {
      game->overworld_character_left->x = game->overworld_character->sprite->x;
      game->overworld_character_left->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_character_left);
    }
    else if (cyclecount < 80) {
      game->overworld_walk2_left->x = game->overworld_character->sprite->x - 20;
      game->overworld_walk2_left->y = game->overworld_character->sprite->y;
      draw_sprite(game->overworld_walk2_left);
    }
  }

  draw_sprite(game->overworld_fence);
  buffercopy();
  framecounter++;

  if (game->overworld_character->sprite->x > 1040) {
    direction = 0;
    cyclecount = 0;
    return RIGHT_REACHED;
  }
  else
    return ANIMATION_NOT_FINISHED;
}

void draw_combat() {
  FanTale *game = get_game();

  clear_buffer();
  draw_button(game->attack);
  draw_button(game->action);
  draw_button(game->give_up);
  draw_sprite(game->select);
  draw_sprite(game->player_name);
  draw_character(game->enemy);
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);
  draw_chatbox(200, 50, 172, 460);
  if (game->sm->state == ACTION_PICK || game->sm->state == ATTACK_PICK || game->sm->state == GIVE_UP_PICK)
    draw_sprite(game->little_select);
  if (game->attack->hover == true && game->sm->state != FIGHT_ANIMATION) {
    draw_sprite(game->enemy_chat);
  }
  if (game->action->hover == true) {
    draw_sprite(game->heal_chat);
    draw_sprite(game->check_chat);
    draw_sprite(game->boost_chat);
  }
  if (game->give_up->hover == true) {
    draw_sprite(game->confirm_chat);
  }
  buffercopy();
}

void draw_check_hp() {
  FanTale *game = get_game();

  clear_buffer();
  draw_sprite(game->player_name);
  draw_character(game->enemy);
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);
  draw_chatbox(200, 50, 172, 460);
  draw_hp_amount(game->enemy->hp, 1);
  buffercopy();
}

void draw_boost_message() {
  FanTale *game = get_game();

  clear_buffer();
  draw_sprite(game->player_name);
  draw_character(game->enemy);
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);
  if (game->boost == 0)
    draw_sprite(game->boost_success);
  else if (game->boost == 1)
    draw_sprite(game->boost_failed);

  draw_chatbox(200, 50, 172, 460);
  buffercopy();
}

void draw_chatbox(unsigned int width, unsigned int height, int x, int y) {
  FanTale *game = get_game();

  game->chatbox_tile->x = x;
  game->chatbox_tile->y = y;

  for (unsigned int i = 0; i < width; i++) {
    move_sprite(game->chatbox_tile, 4, 0);
    draw_sprite(game->chatbox_tile);
  }

  for (unsigned int i = 0; i < height; i++) {
    move_sprite(game->chatbox_tile, 0, 4);
    draw_sprite(game->chatbox_tile);
  }

  game->chatbox_tile->x = x + 4;
  game->chatbox_tile->y = y;

  for (unsigned int i = 0; i < height; i++) {
    move_sprite(game->chatbox_tile, 0, 4);
    draw_sprite(game->chatbox_tile);
  }

  for (unsigned int i = 0; i < (width - 1); i++) {
    move_sprite(game->chatbox_tile, 4, 0);
    draw_sprite(game->chatbox_tile);
  }
}

int draw_fight_animation() {
  FanTale *game = get_game();

  clear_buffer();
  draw_sprite(game->player_name);
  draw_character(game->enemy);
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);
  if (framecounter < 300) {
    draw_sprite(game->target);
    draw_sprite(game->good_bar);
    move_sprite(game->good_bar, 300, 0);
    draw_sprite(game->good_bar);
    move_sprite(game->good_bar, -300, 0);
  }

  int xattack = game->attack_bar->x;
  int xitarget = game->target->x;
  int xftarget = game->target->bitmap->width + xitarget;
  int xigoodbar = game->good_bar->x;
  int xfgoodbar = xigoodbar + 300;
  int spritedrawn = 0;
  static int attackdone;

  if (framecounter < 100) {
    draw_sprite(game->attack_bar);
    move_sprite(game->attack_bar, 8, 0);
  }

  if (framecounter >= 100) {
    if (framecounter < 150) {

      for (unsigned int i = 100; i <= framecounter; i++) {
        draw_sprite(game->slash);
        move_sprite(game->slash, -2, 2);
      }
      game->slash->x = 600;
      game->slash->y = 200;
    }
    else if (framecounter < 200) {

      for (unsigned int i = 150; i <= framecounter; i++) {
        draw_sprite(game->slash);
        move_sprite(game->slash, 2, 2);
      }
      game->slash->x = 500;
      game->slash->y = 200;
    }
    else if (framecounter < 300) {
      if ((xattack > xitarget) && (xattack < xftarget)) {
        if (game->boost == 0)
          draw_sprite(game->damage_ten);
        else if (game->boost == 1)
          draw_sprite(game->damage_twelve);
        if (attackdone == 0) {
          attackdone = 1;
          if (game->boost == 0)
            update_character(game->enemy, 0, 0, -10, 0, 1);
          else if (game->boost == 1)
            update_character(game->enemy, 0, 0, -12, 0, 1);
        }
        spritedrawn = 1;
      }
      else if ((xattack > xftarget) && (xattack < xfgoodbar)) {
        if (game->boost == 0)
          draw_sprite(game->damage_eight);
        else if (game->boost == 1)
          draw_sprite(game->damage_ten);
        if (attackdone == 0) {
          attackdone = 1;
          if (game->boost == 0)
            update_character(game->enemy, 0, 0, -8, 0, 1);
          else if (game->boost == 1)
            update_character(game->enemy, 0, 0, -10, 0, 1);
        }
        spritedrawn = 1;
      }
      else if ((xattack < xitarget) && (xattack > xigoodbar)) {
        if (game->boost == 0)
          draw_sprite(game->damage_eight);
        else if (game->boost == 1)
          draw_sprite(game->damage_ten);
        if (attackdone == 0) {
          attackdone = 1;
          if (game->boost == 0)
            update_character(game->enemy, 0, 0, -8, 0, 1);
          else if (game->boost == 1)
            update_character(game->enemy, 0, 0, -10, 0, 1);
        }
        spritedrawn = 1;
      }

      if (spritedrawn == 0) {
        if (game->boost == 0)
          draw_sprite(game->damage_six);
        else if (game->boost == 1)
          draw_sprite(game->damage_eight);
        if (attackdone == 0) {
          attackdone = 1;
          if (game->boost == 0)
            update_character(game->enemy, 0, 0, -6, 0, 1);
          else if (game->boost == 1)
            update_character(game->enemy, 0, 0, -8, 0, 1);
        }
      }
    }
  }

  if (framecounter == 150) {
    game->slash->x = 500;
    game->slash->y = 200;
  }

  if (framecounter == 200) {
    game->slash->x = 600;
    game->slash->y = 200;
  }

  if (framecounter == 300)
    if (game->enemy->hp <= 0) {
      attackdone = 0;
      return ANIMATION_FINISHED;
    }

  if (framecounter >= 300) {
    int drawing_frame = (framecounter - 300);
    if (drawing_frame < 25)
      draw_chatbox(200 - (drawing_frame * 4), 50 + drawing_frame, 172 + (drawing_frame * 8), 460 - drawing_frame * 4);
    else
      draw_chatbox(100, 75, 372, 360);
  }
  else
    draw_chatbox(200, 50, 172, 460);

  framecounter++;

  buffercopy();

  if (framecounter == 325) {
    attackdone = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack1() {
  FanTale *game = get_game();

  static int invulnframe;
  static int barmovement;
  static int xbar;
  static int ybar;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if (framecounter < 30) {
    game->a1_vertical->x = 500;
  }
  else if (framecounter < 90) {
    game->a1_vertical->x = 500;
    game->a1_horizontal->y = 400;
    draw_sprite(game->a1_vertical);
    move_sprite(game->a1_vertical, 90, 0);
    draw_sprite(game->a1_vertical);
    draw_sprite(game->a1_horizontal);
    move_sprite(game->a1_horizontal, 0, 150);
    draw_sprite(game->a1_horizontal);
  }
  else if (framecounter < 150) {
    game->a1_vertical_red->x = 500;
    game->a1_horizontal_red->y = 400;
    draw_sprite(game->a1_vertical_red);
    move_sprite(game->a1_vertical_red, 90, 0);
    draw_sprite(game->a1_vertical_red);
    draw_sprite(game->a1_horizontal_red);
    move_sprite(game->a1_horizontal_red, 0, 150);
    draw_sprite(game->a1_horizontal_red);
  }
  else if (framecounter < 180) {
  }
  else if (framecounter < 240) {
    game->a1_vertical->x = 456;
    game->a1_horizontal->y = 430;
    draw_sprite(game->a1_vertical);
    move_sprite(game->a1_vertical, 168, 0);
    draw_sprite(game->a1_vertical);
    draw_sprite(game->a1_horizontal);
    move_sprite(game->a1_horizontal, 0, 90);
    draw_sprite(game->a1_horizontal);
  }
  else if (framecounter < 300) {
    game->a1_vertical_red->x = 456;
    game->a1_horizontal_red->y = 430;
    draw_sprite(game->a1_vertical_red);
    move_sprite(game->a1_vertical_red, 168, 0);
    draw_sprite(game->a1_vertical_red);
    draw_sprite(game->a1_horizontal_red);
    move_sprite(game->a1_horizontal_red, 0, 90);
    draw_sprite(game->a1_horizontal_red);
  }
  else if (framecounter < 330) {
  }
  else if (framecounter < 390) {
    game->a1_vertical->x = 376;
    game->a1_horizontal->y = 364;
    draw_sprite(game->a1_vertical);
    move_sprite(game->a1_vertical, 330, 0);
    draw_sprite(game->a1_vertical);
    draw_sprite(game->a1_horizontal);
    move_sprite(game->a1_horizontal, 0, 230);
    draw_sprite(game->a1_horizontal);
  }
  else if (framecounter < 480) {
    if (framecounter == 390) {
      xbar = 376;
      ybar = 364;
    }
    game->a1_vertical_red->x = 376;
    game->a1_horizontal_red->y = 364;
    draw_sprite(game->a1_vertical_red);
    move_sprite(game->a1_vertical_red, 330, 0);
    draw_sprite(game->a1_vertical_red);
    draw_sprite(game->a1_horizontal_red);
    move_sprite(game->a1_horizontal_red, 0, 230);
    draw_sprite(game->a1_horizontal_red);
    if (barmovement % 2 == 0) {
      xbar += 1;
      ybar += 1;
    }
    else {
      xbar += 2;
      ybar += 2;
    }
    game->a1_vertical->x = xbar;
    game->a1_horizontal->y = ybar;
    draw_sprite(game->a1_vertical);
    draw_sprite(game->a1_horizontal);
    barmovement++;
  }
  else if (framecounter < 560) {
    if (framecounter == 480) {
      game->a1_vertical->x = game->a1_vertical_red->x;
      game->a1_horizontal->y = game->a1_horizontal_red->y;
    }
    game->a1_vertical_red->x = 376;
    game->a1_horizontal_red->y = 364;
    draw_sprite(game->a1_vertical_red);
    move_sprite(game->a1_vertical_red, 330, 0);
    draw_sprite(game->a1_vertical_red);
    draw_sprite(game->a1_horizontal_red);
    move_sprite(game->a1_horizontal_red, 0, 230);
    draw_sprite(game->a1_horizontal_red);
    if (barmovement % 2 == 0) {
      xbar += 1;
      ybar += 1;
    }
    else {
      xbar += 2;
      ybar += 2;
    }
    if (ybar > 590)
      ybar = 590;
    game->a1_vertical_red->x = xbar;
    game->a1_horizontal_red->y = ybar;
    draw_sprite(game->a1_vertical_red);
    draw_sprite(game->a1_horizontal_red);
    barmovement++;
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 560) {
    barmovement = 0;
    xbar = 0;
    ybar = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack2() {
  FanTale *game = get_game();

  static int meteor1, meteor2, meteor3, meteor4, meteor5;
  static int x1, x2, x3, x4, x5, y1, y2, y3, y4, y5;
  static int invulnframe;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if ((framecounter % 15) == 0) {
    if (meteor1 == 0) {
      if (rand() % 2 == 0) {
        x1 = rand() % 170 + 402;
        y1 = 360;
        meteor1 = 1;
      }
      else {
        y1 = 360;
        x1 = 742 - game->a2_meteor_right->bitmap->width - (rand() % 170);
        meteor1 = 2;
      }
    }
    else if (meteor2 == 0) {
      if (rand() % 2 == 0) {
        x2 = rand() % 170 + 402;
        y2 = 360;
        meteor2 = 1;
      }
      else {
        y2 = 360;
        x2 = 742 - game->a2_meteor_right->bitmap->width - (rand() % 170);
        meteor2 = 2;
      }
    }
    else if (meteor3 == 0) {
      if (rand() % 2 == 0) {
        x3 = rand() % 170 + 402;
        y3 = 360;
        meteor3 = 1;
      }
      else {
        y3 = 360;
        x3 = 742 - game->a2_meteor_right->bitmap->width - (rand() % 170);
        meteor3 = 2;
      }
    }
    else if (meteor4 == 0) {
      if (rand() % 2 == 0) {
        x4 = rand() % 170 + 402;
        y4 = 360;
        meteor4 = 1;
      }
      else {
        y4 = 360;
        x4 = 742 - game->a2_meteor_right->bitmap->width - (rand() % 170);
        meteor4 = 2;
      }
    }
    else if (meteor5 == 0) {
      if (rand() % 2 == 0) {
        x5 = rand() % 170 + 402;
        y5 = 360;
        meteor5 = 1;
      }
      else {
        y5 = 360;
        x5 = 742 - game->a2_meteor_right->bitmap->width - (rand() % 170);
        meteor5 = 2;
      }
    }
  }

  if (framecounter < 420) {
    if (meteor1 == 1) {
      game->a2_meteor->x = x1;
      game->a2_meteor->y = y1;
      draw_sprite(game->a2_meteor);
      x1 += 5;
      y1 += 6;
    }
    else if (meteor1 == 2) {
      game->a2_meteor_right->x = x1;
      game->a2_meteor_right->y = y1;
      draw_sprite(game->a2_meteor_right);
      x1 -= 5;
      y1 += 6;
    }
    if (meteor2 == 1) {
      game->a2_meteor->x = x2;
      game->a2_meteor->y = y2;
      draw_sprite(game->a2_meteor);
      x2 += 2;
      y2 += 4;
    }
    else if (meteor2 == 2) {
      game->a2_meteor_right->x = x2;
      game->a2_meteor_right->y = y2;
      draw_sprite(game->a2_meteor_right);
      x2 -= 2;
      y2 += 4;
    }
    if (meteor3 == 1) {
      game->a2_meteor->x = x3;
      game->a2_meteor->y = y3;
      draw_sprite(game->a2_meteor);
      x3 += 3;
      y3 += 5;
    }
    else if (meteor3 == 2) {
      game->a2_meteor_right->x = x3;
      game->a2_meteor_right->y = y3;
      draw_sprite(game->a2_meteor_right);
      x3 -= 3;
      y3 += 5;
    }
    if (meteor4 == 1) {
      game->a2_meteor->x = x4;
      game->a2_meteor->y = y4;
      draw_sprite(game->a2_meteor);
      x4 += 5;
      y4 += 3;
    }
    else if (meteor4 == 2) {
      game->a2_meteor_right->x = x4;
      game->a2_meteor_right->y = y4;
      draw_sprite(game->a2_meteor_right);
      x4 -= 5;
      y4 += 3;
    }
    if (meteor5 == 1) {
      game->a2_meteor->x = x5;
      game->a2_meteor->y = y5;
      draw_sprite(game->a2_meteor);
      x5 += 4;
      y5 += 2;
    }
    else if (meteor5 == 2) {
      game->a2_meteor_right->x = x5;
      game->a2_meteor_right->y = y5;
      draw_sprite(game->a2_meteor_right);
      x5 -= 4;
      y5 += 2;
    }
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  if (meteor1 == 1) {
    if ((game->a2_meteor->bitmap->width + x1) > 776 || (game->a2_meteor->bitmap->height + y1) > 664)
      meteor1 = 0;
  }
  else if (meteor1 == 2)
    if (x1 < 376 || (game->a2_meteor_right->bitmap->height + y1) > 664)
      meteor1 = 0;

  if (meteor2 == 1) {
    if ((game->a2_meteor->bitmap->width + x2) > 776 || (game->a2_meteor->bitmap->height + y2) > 664)
      meteor2 = 0;
  }
  else if (meteor2 == 2)
    if (x2 < 376 || (game->a2_meteor_right->bitmap->height + y2) > 664)
      meteor2 = 0;

  if (meteor3 == 1) {
    if ((game->a2_meteor->bitmap->width + x3) > 776 || (game->a2_meteor->bitmap->height + y3) > 664)
      meteor3 = 0;
  }
  else if (meteor3 == 2)
    if (x3 < 376 || (game->a2_meteor_right->bitmap->height + y3) > 664)
      meteor3 = 0;

  if (meteor4 == 1) {
    if ((game->a2_meteor->bitmap->width + x4) > 776 || (game->a2_meteor->bitmap->height + y4) > 664)
      meteor4 = 0;
  }
  else if (meteor4 == 2)
    if (x4 < 376 || (game->a2_meteor_right->bitmap->height + y4) > 664)
      meteor4 = 0;

  if (meteor5 == 1) {
    if ((game->a2_meteor->bitmap->width + x5) > 776 || (game->a2_meteor->bitmap->height + y5) > 664)
      meteor5 = 0;
  }
  else if (meteor5 == 2)
    if (x5 < 376 || (game->a2_meteor_right->bitmap->height + y5) > 664)
      meteor5 = 0;

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 420) {
    meteor1 = 0;
    meteor2 = 0;
    meteor3 = 0;
    meteor4 = 0;
    meteor5 = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack3() {
  FanTale *game = get_game();

  static int snake1, snake2, snake3, snake4;
  static int x1, x2, x3, x4, y1, y2, y3, y4;
  static int xplayer1, xplayer2, xplayer3, xplayer4, yplayer1, yplayer2, yplayer3, yplayer4;
  static int snake1cnt, snake2cnt, snake3cnt, snake4cnt;
  double xleftover1, xleftover2, xleftover3, xleftover4;
  double yleftover1, yleftover2, yleftover3, yleftover4;
  static int invulnframe;
  double slopex, slopey;
  double xincrease, yincrease;
  int unitleftover = 0;
  xleftover1 = 0;
  xleftover2 = 0;
  xleftover3 = 0;
  xleftover4 = 0;
  yleftover1 = 0;
  yleftover2 = 0;
  yleftover3 = 0;
  yleftover4 = 0;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if (framecounter == 400) {
    snake1 = 0;
    snake1cnt = 0;
  }
  else if (framecounter == 500) {
    snake2 = 0;
    snake2cnt = 0;
  }
  else if (framecounter == 600) {
    snake3 = 0;
    snake3cnt = 0;
  }
  else if (framecounter == 700) {
    snake4 = 0;
    snake4cnt = 0;
  }

  if ((framecounter % 100) == 0) {
    if (snake1 == 0) {
      x1 = rand() % 340 + 402;
      y1 = 360;
      snake1 = 1;
    }
    else if (snake2 == 0) {
      x2 = 776 - game->a3_snake->bitmap->width;
      y2 = rand() % 236 + 390;
      snake2 = 1;
    }
    else if (snake3 == 0) {
      x3 = rand() % 340 + 402;
      y3 = 664 - game->a3_snake->bitmap->height;
      snake3 = 1;
    }
    else if (snake4 == 0) {
      x4 = 380;
      y4 = rand() % 236 + 390;
      snake4 = 1;
    }
  }

  if (framecounter < 800) {
    if (snake1 == 1) {
      game->a3_snake->x = x1;
      game->a3_snake->y = y1;
      xplayer1 = game->player->sprite->x;
      yplayer1 = game->player->sprite->y;
      slopex = (xplayer1 - x1);
      slopey = (yplayer1 - y1);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 0;
          yincrease = 8;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a3_snake->bitmap->width + game->a3_snake->x) > 776 || game->a3_snake->x < 376 || game->a3_snake->y < 360 || (game->a3_snake->bitmap->height + game->a3_snake->y) > 664)
          break;
        draw_sprite(game->a3_snake);
        xleftover1 += xincrease;
        yleftover1 += yincrease;
        if (xleftover1 >= 1) {
          unitleftover = (int) xleftover1;
          game->a3_snake->x += unitleftover;
          xleftover1 -= unitleftover;
        }
        else if (xleftover1 <= -1) {
          unitleftover = (int) xleftover1;
          game->a3_snake->x += unitleftover;
          xleftover1 -= unitleftover;
        }
        if (yleftover1 >= 1) {
          unitleftover = (int) yleftover1;
          game->a3_snake->y += unitleftover;
          yleftover1 -= unitleftover;
        }
        else if (yleftover1 <= -1) {
          unitleftover = (int) yleftover1;
          game->a3_snake->y += unitleftover;
          yleftover1 -= unitleftover;
        }
      }

      if (framecounter == 50 || framecounter == 450)
        snake1 = 2;
    }
    else if (snake1 == 2) {
      game->a3_snake_red->x = x1;
      game->a3_snake_red->y = y1;
      slopex = (xplayer1 - x1);
      slopey = (yplayer1 - y1);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 0;
          yincrease = 8;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < snake1cnt; i++) {
        if ((game->a3_snake_red->bitmap->width + game->a3_snake_red->x) > 776 || game->a3_snake_red->x < 376 || game->a3_snake_red->y < 360 || (game->a3_snake_red->bitmap->height + game->a3_snake_red->y) > 664)
          break;
        draw_sprite(game->a3_snake_red);
        xleftover1 += xincrease;
        yleftover1 += yincrease;
        if (xleftover1 >= 1) {
          unitleftover = (int) xleftover1;
          game->a3_snake_red->x += unitleftover;
          xleftover1 -= unitleftover;
        }
        else if (xleftover1 <= -1) {
          unitleftover = (int) xleftover1;
          game->a3_snake_red->x += unitleftover;
          xleftover1 -= unitleftover;
        }
        if (yleftover1 >= 1) {
          unitleftover = (int) yleftover1;
          game->a3_snake_red->y += unitleftover;
          yleftover1 -= unitleftover;
        }
        else if (yleftover1 <= -1) {
          unitleftover = (int) yleftover1;
          game->a3_snake_red->y += unitleftover;
          yleftover1 -= unitleftover;
        }
      }
      snake1cnt++;
    }

    if (snake2 == 1) {
      game->a3_snake->x = x2;
      game->a3_snake->y = y2;
      xplayer2 = game->player->sprite->x;
      yplayer2 = game->player->sprite->y;
      slopex = (xplayer2 - x2);
      slopey = (yplayer2 - y2);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = -8;
          yincrease = 0;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a3_snake->bitmap->width + game->a3_snake->x) > 776 || game->a3_snake->x < 376 || game->a3_snake->y < 360 || (game->a3_snake->bitmap->height + game->a3_snake->y) > 664)
          break;
        draw_sprite(game->a3_snake);
        xleftover2 += xincrease;
        yleftover2 += yincrease;
        if (xleftover2 >= 1) {
          unitleftover = (int) xleftover2;
          game->a3_snake->x += unitleftover;
          xleftover2 -= unitleftover;
        }
        else if (xleftover2 <= -1) {
          unitleftover = (int) xleftover2;
          game->a3_snake->x += unitleftover;
          xleftover2 -= unitleftover;
        }
        if (yleftover2 >= 1) {
          unitleftover = (int) yleftover2;
          game->a3_snake->y += unitleftover;
          yleftover2 -= unitleftover;
        }
        else if (yleftover2 <= -1) {
          unitleftover = (int) yleftover2;
          game->a3_snake->y += unitleftover;
          yleftover2 -= unitleftover;
        }
      }

      if (framecounter == 150 || framecounter == 550)
        snake2 = 2;
    }
    else if (snake2 == 2) {
      game->a3_snake_red->x = x2;
      game->a3_snake_red->y = y2;
      slopex = (xplayer2 - x2);
      slopey = (yplayer2 - y2);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = -8;
          yincrease = 0;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < snake2cnt; i++) {
        if ((game->a3_snake_red->bitmap->width + game->a3_snake_red->x) > 776 || game->a3_snake_red->x < 376 || game->a3_snake_red->y < 360 || (game->a3_snake_red->bitmap->height + game->a3_snake_red->y) > 664)
          break;
        draw_sprite(game->a3_snake_red);
        xleftover2 += xincrease;
        yleftover2 += yincrease;
        if (xleftover2 >= 1) {
          unitleftover = (int) xleftover2;
          game->a3_snake_red->x += unitleftover;
          xleftover2 -= unitleftover;
        }
        else if (xleftover2 <= -1) {
          unitleftover = (int) xleftover2;
          game->a3_snake_red->x += unitleftover;
          xleftover2 -= unitleftover;
        }
        if (yleftover2 >= 1) {
          unitleftover = (int) yleftover2;
          game->a3_snake_red->y += unitleftover;
          yleftover2 -= unitleftover;
        }
        else if (yleftover2 <= -1) {
          unitleftover = (int) yleftover2;
          game->a3_snake_red->y += unitleftover;
          yleftover2 -= unitleftover;
        }
      }
      snake2cnt++;
    }

    if (snake3 == 1) {
      game->a3_snake->x = x3;
      game->a3_snake->y = y3;
      xplayer3 = game->player->sprite->x;
      yplayer3 = game->player->sprite->y;
      slopex = (xplayer3 - x3);
      slopey = (yplayer3 - y3);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 0;
          yincrease = -8;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a3_snake->bitmap->width + game->a3_snake->x) > 776 || game->a3_snake->x < 376 || game->a3_snake->y < 360 || (game->a3_snake->bitmap->height + game->a3_snake->y) > 664)
          break;
        draw_sprite(game->a3_snake);
        xleftover3 += xincrease;
        yleftover3 += yincrease;
        if (xleftover3 >= 1) {
          unitleftover = (int) xleftover3;
          game->a3_snake->x += unitleftover;
          xleftover3 -= unitleftover;
        }
        else if (xleftover3 <= -1) {
          unitleftover = (int) xleftover3;
          game->a3_snake->x += unitleftover;
          xleftover3 -= unitleftover;
        }
        if (yleftover3 >= 1) {
          unitleftover = (int) yleftover3;
          game->a3_snake->y += unitleftover;
          yleftover3 -= unitleftover;
        }
        else if (yleftover3 <= -1) {
          unitleftover = (int) yleftover3;
          game->a3_snake->y += unitleftover;
          yleftover3 -= unitleftover;
        }
      }

      if (framecounter == 250 || framecounter == 650)
        snake3 = 2;
    }
    else if (snake3 == 2) {
      game->a3_snake_red->x = x3;
      game->a3_snake_red->y = y3;
      slopex = (xplayer3 - x3);
      slopey = (yplayer3 - y3);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 0;
          yincrease = -8;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < snake3cnt; i++) {
        if ((game->a3_snake_red->bitmap->width + game->a3_snake_red->x) > 776 || game->a3_snake_red->x < 376 || game->a3_snake_red->y < 360 || (game->a3_snake_red->bitmap->height + game->a3_snake_red->y) > 664)
          break;
        draw_sprite(game->a3_snake_red);
        xleftover3 += xincrease;
        yleftover3 += yincrease;
        if (xleftover3 >= 1) {
          unitleftover = (int) xleftover3;
          game->a3_snake_red->x += unitleftover;
          xleftover3 -= unitleftover;
        }
        else if (xleftover3 <= -1) {
          unitleftover = (int) xleftover3;
          game->a3_snake_red->x += unitleftover;
          xleftover3 -= unitleftover;
        }
        if (yleftover3 >= 1) {
          unitleftover = (int) yleftover3;
          game->a3_snake_red->y += unitleftover;
          yleftover3 -= unitleftover;
        }
        else if (yleftover3 <= -1) {
          unitleftover = (int) yleftover3;
          game->a3_snake_red->y += unitleftover;
          yleftover3 -= unitleftover;
        }
      }
      snake3cnt++;
    }

    if (snake4 == 1) {
      game->a3_snake->x = x4;
      game->a3_snake->y = y4;
      xplayer4 = game->player->sprite->x;
      yplayer4 = game->player->sprite->y;
      slopex = (xplayer4 - x4);
      slopey = (yplayer4 - y4);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 8;
          yincrease = 0;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a3_snake->bitmap->width + game->a3_snake->x) > 776 || game->a3_snake->x < 376 || game->a3_snake->y < 360 || (game->a3_snake->bitmap->height + game->a3_snake->y) > 664)
          break;
        draw_sprite(game->a3_snake);
        xleftover4 += xincrease;
        yleftover4 += yincrease;
        if (xleftover4 >= 1) {
          unitleftover = (int) xleftover4;
          game->a3_snake->x += unitleftover;
          xleftover4 -= unitleftover;
        }
        else if (xleftover4 <= -1) {
          unitleftover = (int) xleftover4;
          game->a3_snake->x += unitleftover;
          xleftover4 -= unitleftover;
        }
        if (yleftover4 >= 1) {
          unitleftover = (int) yleftover4;
          game->a3_snake->y += unitleftover;
          yleftover4 -= unitleftover;
        }
        else if (yleftover4 <= -1) {
          unitleftover = (int) yleftover4;
          game->a3_snake->y += unitleftover;
          yleftover4 -= unitleftover;
        }
      }

      if (framecounter == 350 || framecounter == 750)
        snake4 = 2;
    }
    else if (snake4 == 2) {
      game->a3_snake_red->x = x4;
      game->a3_snake_red->y = y4;
      slopex = (xplayer4 - x4);
      slopey = (yplayer4 - y4);
      if (abs(slopex) >= abs(slopey)) {
        if (abs(slopex) == 0) {
          xincrease = 8;
          yincrease = 0;
        }
        else {
          xincrease = (slopex / abs(slopex)) * 8;
          yincrease = (slopey / abs(slopex)) * 8;
        }
      }
      else if (abs(slopey) > abs(slopex)) {
        yincrease = (slopey / abs(slopey)) * 8;
        xincrease = (slopex / abs(slopey)) * 8;
      }

      for (int i = 0; i < snake4cnt; i++) {
        if ((game->a3_snake_red->bitmap->width + game->a3_snake_red->x) > 776 || game->a3_snake_red->x < 376 || game->a3_snake_red->y < 360 || (game->a3_snake_red->bitmap->height + game->a3_snake_red->y) > 664)
          break;
        draw_sprite(game->a3_snake_red);
        xleftover4 += xincrease;
        yleftover4 += yincrease;
        if (xleftover4 >= 1) {
          unitleftover = (int) xleftover4;
          game->a3_snake_red->x += unitleftover;
          xleftover4 -= unitleftover;
        }
        else if (xleftover4 <= -1) {
          unitleftover = (int) xleftover4;
          game->a3_snake_red->x += unitleftover;
          xleftover4 -= unitleftover;
        }
        if (yleftover4 >= 1) {
          unitleftover = (int) yleftover4;
          game->a3_snake_red->y += unitleftover;
          yleftover4 -= unitleftover;
        }
        else if (yleftover4 <= -1) {
          unitleftover = (int) yleftover4;
          game->a3_snake_red->y += unitleftover;
          yleftover4 -= unitleftover;
        }
      }
      snake4cnt++;
    }
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 800) {
    snake1 = 0;
    snake2 = 0;
    snake3 = 0;
    snake4 = 0;
    snake1cnt = 0;
    snake2cnt = 0;
    snake3cnt = 0;
    snake4cnt = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack4() {
  FanTale *game = get_game();

  static int invulnframe;
  double xincrease, yincrease;
  double totalx, totaly;
  static double angle;
  int distance = 200;
  int xi = 562;
  int yi = 500;
  double xleftover = 0;
  double yleftover = 0;
  int unitleftover = 0;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if (framecounter < 100) {
    for (unsigned int i = 0; i < 4; i++) {
      game->a4_snake->x = xi;
      game->a4_snake->y = yi;
      totalx = distance * cos((angle + (i * 90)) * (PI / 180.0));
      totaly = distance * sin((angle + (i * 90)) * (PI / 180.0));
      if (abs(totalx) >= abs(totaly)) {
        if (abs(totalx) == 0) {
          if (i == 1 || i == 3) {
            xincrease = 4;
            yincrease = 0;
          }
          else {
            xincrease = 0;
            yincrease = 4;
          }
        }
        else {
          xincrease = (totalx / abs(totalx)) * 4;
          yincrease = (totaly / abs(totalx)) * 4;
        }
      }
      else if (abs(totaly) > abs(totalx)) {
        yincrease = (totaly / abs(totaly)) * 4;
        xincrease = (totalx / abs(totaly)) * 4;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a4_snake->bitmap->width + game->a4_snake->x) > 776 || game->a4_snake->x < 376 || game->a4_snake->y < 360 || (game->a4_snake->bitmap->height + game->a4_snake->y) > 664)
          break;
        draw_sprite(game->a4_snake);
        xleftover += xincrease;
        yleftover += yincrease;
        if (xleftover >= 1) {
          unitleftover = (int) xleftover;
          game->a4_snake->x += unitleftover;
          xleftover -= unitleftover;
        }
        else if (xleftover <= -1) {
          unitleftover = (int) xleftover;
          game->a4_snake->x += unitleftover;
          xleftover -= unitleftover;
        }
        if (yleftover >= 1) {
          unitleftover = (int) yleftover;
          game->a4_snake->y += unitleftover;
          yleftover -= unitleftover;
        }
        else if (yleftover <= -1) {
          unitleftover = (int) yleftover;
          game->a4_snake->y += unitleftover;
          yleftover -= unitleftover;
        }
      }
      xleftover = 0;
      yleftover = 0;
    }
    draw_sprite(game->a4_cog);
  }
  else {
    for (unsigned int i = 0; i < 4; i++) {
      game->a4_snake_red->x = xi;
      game->a4_snake_red->y = yi;
      totalx = distance * cos((angle + (i * 90)) * (PI / 180.0));
      totaly = distance * sin((angle + (i * 90)) * (PI / 180.0));
      if (abs(totalx) >= abs(totaly)) {
        if (abs(totalx) == 0) {
          if (i == 1 || i == 3) {
            xincrease = 4;
            yincrease = 0;
          }
          else {
            xincrease = 0;
            yincrease = 4;
          }
        }
        else {
          xincrease = (totalx / abs(totalx)) * 4;
          yincrease = (totaly / abs(totalx)) * 4;
        }
      }
      else if (abs(totaly) > abs(totalx)) {
        yincrease = (totaly / abs(totaly)) * 4;
        xincrease = (totalx / abs(totaly)) * 4;
      }

      for (int i = 0; i < 50; i++) {
        if ((game->a4_snake_red->bitmap->width + game->a4_snake_red->x) > 776 || game->a4_snake_red->x < 376 || game->a4_snake_red->y < 360 || (game->a4_snake_red->bitmap->height + game->a4_snake_red->y) > 664)
          break;
        draw_sprite(game->a4_snake_red);
        xleftover += xincrease;
        yleftover += yincrease;
        if (xleftover >= 1) {
          unitleftover = (int) xleftover;
          game->a4_snake_red->x += unitleftover;
          xleftover -= unitleftover;
        }
        else if (xleftover <= -1) {
          unitleftover = (int) xleftover;
          game->a4_snake_red->x += unitleftover;
          xleftover -= unitleftover;
        }
        if (yleftover >= 1) {
          unitleftover = (int) yleftover;
          game->a4_snake_red->y += unitleftover;
          yleftover -= unitleftover;
        }
        else if (yleftover <= -1) {
          unitleftover = (int) yleftover;
          game->a4_snake_red->y += unitleftover;
          yleftover -= unitleftover;
        }
      }
      xleftover = 0;
      yleftover = 0;
    }
    draw_sprite(game->a4_cog_red);
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  if (framecounter < 50) {
    angle = 0;
  }
  else if (framecounter < 175) {
    angle = angle + 1;
  }
  else if (framecounter < 190) {
    angle = angle + 0;
  }
  else if (framecounter < 250) {
    angle = angle - 1;
  }
  else if (framecounter < 300) {
    angle = angle - 1.5;
  }
  else if (framecounter < 400) {
    angle = angle - 2;
  }
  else if (framecounter < 425) {
    angle = angle - 1;
  }
  else if (framecounter < 440) {
    angle = angle + 0;
  }
  else if (framecounter < 475) {
    angle = angle - 1;
  }
  else if (framecounter < 490) {
    angle = angle + 0;
  }
  else if (framecounter < 540) {
    angle = angle + 1.5;
  }
  else if (framecounter < 550) {
    angle = angle + 0;
  }
  else if (framecounter < 600) {
    angle = angle - 1.5;
  }
  else if (framecounter < 610) {
    angle = angle + 0;
  }
  else if (framecounter < 660) {
    angle = angle + 1.5;
  }
  else if (framecounter < 670) {
    angle = angle + 0;
  }
  else if (framecounter < 720) {
    angle = angle - 1.5;
  }
  else if (framecounter < 740) {
    angle = angle + 0;
  }
  else if (framecounter < 760) {
    angle = angle + 3;
  }
  else if (framecounter < 770) {
    angle = angle + 0;
  }
  else if (framecounter < 790) {
    angle = angle - 3;
  }
  else if (framecounter < 800) {
    angle = angle + 0;
  }
  else if (framecounter < 820) {
    angle = angle + 3;
  }
  else if (framecounter < 830) {
    angle = angle + 0;
  }
  else if (framecounter < 850) {
    angle = angle - 3;
  }
  else if (framecounter < 860) {
    angle = angle + 0;
  }
  else if (framecounter < 880) {
    angle = angle + 3;
  }
  else if (framecounter < 890) {
    angle = angle + 0;
  }
  else if (framecounter < 910) {
    angle = angle - 3;
  }
  else if (framecounter < 920) {
    angle = angle + 0;
  }
  else if (framecounter < 940) {
    angle = angle + 3;
  }
  else if (framecounter < 950) {
    angle = angle + 0;
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 950) {
    angle = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack5() {
  FanTale *game = get_game();

  static int laser1, laser2, laser3, laser4, laser5, laser6, laser7, laser8;
  static int invulnframe;
  static int laser1cnt, laser2cnt, laser3cnt, laser4cnt, laser5cnt, laser6cnt, laser7cnt, laser8cnt;
  int randomnumber = rand() % 8;
  int laser[8] = {laser1, laser2, laser3, laser4, laser5, laser6, laser7, laser8};

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if ((framecounter % 25) == 0) {
    while (laser[randomnumber] != 0) {
      randomnumber = rand() % 8;
    }
    if (randomnumber == 0) {
      laser1 = 1;
      laser1cnt = 0;
    }
    else if (randomnumber == 1) {
      laser2 = 1;
      laser2cnt = 0;
    }
    else if (randomnumber == 2) {
      laser3 = 1;
      laser3cnt = 0;
    }
    else if (randomnumber == 3) {
      laser4 = 1;
      laser4cnt = 0;
    }
    else if (randomnumber == 4) {
      laser5 = 1;
      laser5cnt = 0;
    }
    else if (randomnumber == 5) {
      laser6 = 1;
      laser6cnt = 0;
    }
    else if (randomnumber == 6) {
      laser7 = 1;
      laser7cnt = 0;
    }
    else if (randomnumber == 7) {
      laser8 = 1;
      laser8cnt = 0;
    }
  }

  if (laser1 == 1) {
    game->a5_loading->x = 376;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser1cnt++;
    if (laser1cnt == 20)
      laser1 = 2;
  }
  else if (laser1 == 2) {
    game->a5_loading->x = 376;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser1cnt++;
    if (laser1cnt == 40)
      laser1 = 3;
  }
  else if (laser1 == 3) {
    game->a5_loading->x = 376;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser1cnt++;
    if (laser1cnt == 60)
      laser1 = 4;
  }
  else if (laser1 == 4) {
    game->a5_laser->x = 376;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser1cnt++;
    if (laser1cnt == 90)
      laser1 = 0;
  }

  if (laser2 == 1) {
    game->a5_loading->x = 426;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser2cnt++;
    if (laser2cnt == 20)
      laser2 = 2;
  }
  else if (laser2 == 2) {
    game->a5_loading->x = 426;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser2cnt++;
    if (laser2cnt == 40)
      laser2 = 3;
  }
  else if (laser2 == 3) {
    game->a5_loading->x = 426;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser2cnt++;
    if (laser2cnt == 60)
      laser2 = 4;
  }
  else if (laser2 == 4) {
    game->a5_laser->x = 426;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser2cnt++;
    if (laser2cnt == 90)
      laser2 = 0;
  }

  if (laser3 == 1) {
    game->a5_loading->x = 476;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser3cnt++;
    if (laser3cnt == 20)
      laser3 = 2;
  }
  else if (laser3 == 2) {
    game->a5_loading->x = 476;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser3cnt++;
    if (laser3cnt == 40)
      laser3 = 3;
  }
  else if (laser3 == 3) {
    game->a5_loading->x = 476;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser3cnt++;
    if (laser3cnt == 60)
      laser3 = 4;
  }
  else if (laser3 == 4) {
    game->a5_laser->x = 476;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser3cnt++;
    if (laser3cnt == 90)
      laser3 = 0;
  }

  if (laser4 == 1) {
    game->a5_loading->x = 526;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser4cnt++;
    if (laser4cnt == 20)
      laser4 = 2;
  }
  else if (laser4 == 2) {
    game->a5_loading->x = 526;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser4cnt++;
    if (laser4cnt == 40)
      laser4 = 3;
  }
  else if (laser4 == 3) {
    game->a5_loading->x = 526;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser4cnt++;
    if (laser4cnt == 60)
      laser4 = 4;
  }
  else if (laser4 == 4) {
    game->a5_laser->x = 526;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser4cnt++;
    if (laser4cnt == 90)
      laser4 = 0;
  }

  if (laser5 == 1) {
    game->a5_loading->x = 576;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser5cnt++;
    if (laser5cnt == 20)
      laser5 = 2;
  }
  else if (laser5 == 2) {
    game->a5_loading->x = 576;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser5cnt++;
    if (laser5cnt == 40)
      laser5 = 3;
  }
  else if (laser5 == 3) {
    game->a5_loading->x = 576;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser5cnt++;
    if (laser5cnt == 60)
      laser5 = 4;
  }
  else if (laser5 == 4) {
    game->a5_laser->x = 576;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser5cnt++;
    if (laser5cnt == 90)
      laser5 = 0;
  }

  if (laser6 == 1) {
    game->a5_loading->x = 626;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser6cnt++;
    if (laser6cnt == 20)
      laser6 = 2;
  }
  else if (laser6 == 2) {
    game->a5_loading->x = 626;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser6cnt++;
    if (laser6cnt == 40)
      laser6 = 3;
  }
  else if (laser6 == 3) {
    game->a5_loading->x = 626;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser6cnt++;
    if (laser6cnt == 60)
      laser6 = 4;
  }
  else if (laser6 == 4) {
    game->a5_laser->x = 626;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser6cnt++;
    if (laser6cnt == 90)
      laser6 = 0;
  }

  if (laser7 == 1) {
    game->a5_loading->x = 676;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser7cnt++;
    if (laser7cnt == 20)
      laser7 = 2;
  }
  else if (laser7 == 2) {
    game->a5_loading->x = 676;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser7cnt++;
    if (laser7cnt == 40)
      laser7 = 3;
  }
  else if (laser7 == 3) {
    game->a5_loading->x = 676;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser7cnt++;
    if (laser7cnt == 60)
      laser7 = 4;
  }
  else if (laser7 == 4) {
    game->a5_laser->x = 676;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser7cnt++;
    if (laser7cnt == 90)
      laser7 = 0;
  }

  if (laser8 == 1) {
    game->a5_loading->x = 726;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    laser8cnt++;
    if (laser8cnt == 20)
      laser8 = 2;
  }
  else if (laser8 == 2) {
    game->a5_loading->x = 726;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser8cnt++;
    if (laser8cnt == 40)
      laser8 = 3;
  }
  else if (laser8 == 3) {
    game->a5_loading->x = 726;
    game->a5_loading->y = 360;
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    move_sprite(game->a5_loading, 0, 30);
    draw_sprite(game->a5_loading);
    laser8cnt++;
    if (laser8cnt == 60)
      laser8 = 4;
  }
  else if (laser8 == 4) {
    game->a5_laser->x = 726;
    game->a5_laser->y = 360;
    draw_sprite(game->a5_laser);
    laser8cnt++;
    if (laser8cnt == 90)
      laser8 = 0;
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 950) {
    laser1 = 0;
    laser2 = 0;
    laser3 = 0;
    laser4 = 0;
    laser5 = 0;
    laser6 = 0;
    laser7 = 0;
    laser8 = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack6() {
  FanTale *game = get_game();

  static int invulnframe;
  static int ybar1, ybar2;
  static int xbar1, xbar2;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if (framecounter == 0) {
    ybar1 = 360;
    ybar2 = 640;
  }

  if (framecounter == 300) {
    xbar1 = 376;
    xbar2 = 756;
  }

  if (framecounter < 340) {
    game->a6_hbar->x = 376;
    game->a6_hbar->y = ybar1;
    draw_sprite(game->a6_hbar);
    ybar1 += 5;
    if (game->a6_hbar->bitmap->height + ybar1 > 660)
      ybar1 = 360;

    game->a6_hbar->x = 576;
    game->a6_hbar->y = ybar2;
    draw_sprite(game->a6_hbar);
    ybar2 -= 5;
    if (ybar2 < 360)
      ybar2 = 640;
  }
  else if (framecounter > 400 && framecounter < 700) {
    game->a6_vbar->x = xbar1;
    game->a6_vbar->y = 360;
    draw_sprite(game->a6_vbar);
    xbar1 += 5;
    if (game->a6_vbar->bitmap->width + xbar1 > 776)
      xbar1 = 376;

    game->a6_vbar->x = xbar2;
    game->a6_vbar->y = 510;
    draw_sprite(game->a6_vbar);
    xbar2 -= 5;
    if (xbar2 < 376)
      xbar2 = 756;
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 700) {
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack7() {
  FanTale *game = get_game();

  static int invulnframe;
  static int lastrand;
  int randomnum;
  static int attackcnt;
  static int spike1, spike2, spike3, spike4;

  if (framecounter == 0)
    lastrand = 6;

  if (framecounter < 3)
    clear_buffer();
  else
    clear_combat_buffer();
  if (framecounter < 3) {
    draw_sprite(game->player_name);
    draw_character(game->enemy);
  }
  draw_sprite(game->hp_bar);
  draw_hp_bar();
  draw_hp_amount(game->player->hp, 0);

  if ((framecounter % 90) == 0) {
    randomnum = rand() % 4;
    while (randomnum == lastrand) {
      randomnum = rand() % 4;
    }
    lastrand = randomnum;
    if (randomnum == 0) {
      spike1 = 1;
      attackcnt = 0;
    }
    if (randomnum == 1) {
      spike2 = 1;
      attackcnt = 0;
    }
    if (randomnum == 2) {
      spike3 = 1;
      attackcnt = 0;
    }
    if (randomnum == 3) {
      spike4 = 1;
      attackcnt = 0;
    }
  }

  if (spike1 == 1) {
    if (attackcnt < 5)
      attackcnt++;
    else {
      draw_sprite(game->a7_spike_down);
      if (attackcnt < 35)
        update_character(game->player, 0, 16, 0, 0, 0);
      attackcnt++;
      if (attackcnt == 55)
        spike1 = 2;
    }
  }
  else if (spike2 == 1) {
    if (attackcnt < 5)
      attackcnt++;
    else {
      draw_sprite(game->a7_spike_left);
      if (attackcnt < 35)
        update_character(game->player, -16, 0, 0, 0, 0);
      attackcnt++;
      if (attackcnt == 55)
        spike2 = 2;
    }
  }
  else if (spike3 == 1) {
    if (attackcnt < 5)
      attackcnt++;
    else {
      draw_sprite(game->a7_spike_up);
      if (attackcnt < 35)
        update_character(game->player, 0, -16, 0, 0, 0);
      attackcnt++;
      if (attackcnt == 55)
        spike3 = 2;
    }
  }
  else if (spike4 == 1) {
    if (attackcnt < 5)
      attackcnt++;
    else {
      draw_sprite(game->a7_spike_right);
      if (attackcnt < 35)
        update_character(game->player, 16, 0, 0, 0, 0);
      attackcnt++;
      if (attackcnt == 55)
        spike4 = 2;
    }
  }

  if (spike1 == 2) {
    draw_sprite(game->a7_spike_down_red);
    attackcnt++;
    if (attackcnt == 90)
      spike1 = 0;
  }
  else if (spike2 == 2) {
    draw_sprite(game->a7_spike_left_red);
    attackcnt++;
    if (attackcnt == 90)
      spike2 = 0;
  }
  else if (spike3 == 2) {
    draw_sprite(game->a7_spike_up_red);
    attackcnt++;
    if (attackcnt == 90)
      spike3 = 0;
  }
  else if (spike4 == 2) {
    draw_sprite(game->a7_spike_right_red);
    attackcnt++;
    if (attackcnt == 90)
      spike4 = 0;
  }

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 0);
      invulnframe = 30;
    }
  }

  draw_chatbox(100, 75, 372, 360);
  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 810) {
    spike1 = 0;
    spike2 = 0;
    spike3 = 0;
    spike4 = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

int draw_attack8() {
  FanTale *game = get_game();

  static int invulnframe;
  static int laser1, laser2, laser3, laser4, laser5, laser6, laser7, laser8;
  static int laser1cnt, laser2cnt, laser3cnt, laser4cnt, laser5cnt, laser6cnt, laser7cnt, laser8cnt;
  int randomnumber = rand() % 8;
  int laser[8] = {laser1, laser2, laser3, laser4, laser5, laser6, laser7, laser8};

  clear_buffer();
  if (framecounter < 50) {
    draw_chatbox(200 + (framecounter * 8), 50 + (framecounter * 16), 172 - (framecounter * 16), 460 - framecounter * 32);
  }
  else {
    if ((framecounter % 50) == 0) {
      while (laser[randomnumber] != 0) {
        randomnumber = rand() % 8;
      }
      if (randomnumber == 0) {
        laser1 = 1;
        laser1cnt = 0;
      }
      else if (randomnumber == 1) {
        laser2 = 1;
        laser2cnt = 0;
      }
      else if (randomnumber == 2) {
        laser3 = 1;
        laser3cnt = 0;
      }
      else if (randomnumber == 3) {
        laser4 = 1;
        laser4cnt = 0;
      }
      else if (randomnumber == 4) {
        laser5 = 1;
        laser5cnt = 0;
      }
      else if (randomnumber == 5) {
        laser6 = 1;
        laser6cnt = 0;
      }
      else if (randomnumber == 6) {
        laser7 = 1;
        laser7cnt = 0;
      }
      else if (randomnumber == 7) {
        laser8 = 1;
        laser8cnt = 0;
      }
    }

    if (laser1 == 1) {
      game->a8_loading->x = 0;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser1cnt++;
      if (laser1cnt == 20)
        laser1 = 2;
    }
    else if (laser1 == 2) {
      game->a8_loading->x = 0;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser1cnt++;
      if (laser1cnt == 40)
        laser1 = 3;
    }
    else if (laser1 == 3) {
      game->a8_loading->x = 0;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser1cnt++;
      if (laser1cnt == 60)
        laser1 = 4;
    }
    else if (laser1 == 4) {
      game->a8_laser->x = 0;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser1cnt++;
      if (laser1cnt == 90)
        laser1 = 0;
    }

    if (laser2 == 1) {
      game->a8_loading->x = 144;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser2cnt++;
      if (laser2cnt == 20)
        laser2 = 2;
    }
    else if (laser2 == 2) {
      game->a8_loading->x = 144;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser2cnt++;
      if (laser2cnt == 40)
        laser2 = 3;
    }
    else if (laser2 == 3) {
      game->a8_loading->x = 144;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser2cnt++;
      if (laser2cnt == 60)
        laser2 = 4;
    }
    else if (laser2 == 4) {
      game->a8_laser->x = 144;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser2cnt++;
      if (laser2cnt == 90)
        laser2 = 0;
    }

    if (laser3 == 1) {
      game->a8_loading->x = 288;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser3cnt++;
      if (laser3cnt == 20)
        laser3 = 2;
    }
    else if (laser3 == 2) {
      game->a8_loading->x = 288;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser3cnt++;
      if (laser3cnt == 40)
        laser3 = 3;
    }
    else if (laser3 == 3) {
      game->a8_loading->x = 288;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser3cnt++;
      if (laser3cnt == 60)
        laser3 = 4;
    }
    else if (laser3 == 4) {
      game->a8_laser->x = 288;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser3cnt++;
      if (laser3cnt == 90)
        laser3 = 0;
    }

    if (laser4 == 1) {
      game->a8_loading->x = 432;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser4cnt++;
      if (laser4cnt == 20)
        laser4 = 2;
    }
    else if (laser4 == 2) {
      game->a8_loading->x = 432;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser4cnt++;
      if (laser4cnt == 40)
        laser4 = 3;
    }
    else if (laser4 == 3) {
      game->a8_loading->x = 432;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser4cnt++;
      if (laser4cnt == 60)
        laser4 = 4;
    }
    else if (laser4 == 4) {
      game->a8_laser->x = 432;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser4cnt++;
      if (laser4cnt == 90)
        laser4 = 0;
    }

    if (laser5 == 1) {
      game->a8_loading->x = 576;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser5cnt++;
      if (laser5cnt == 20)
        laser5 = 2;
    }
    else if (laser5 == 2) {
      game->a8_loading->x = 576;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser5cnt++;
      if (laser5cnt == 40)
        laser5 = 3;
    }
    else if (laser5 == 3) {
      game->a8_loading->x = 576;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser5cnt++;
      if (laser5cnt == 60)
        laser5 = 4;
    }
    else if (laser5 == 4) {
      game->a8_laser->x = 576;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser5cnt++;
      if (laser5cnt == 90)
        laser5 = 0;
    }

    if (laser6 == 1) {
      game->a8_loading->x = 720;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser6cnt++;
      if (laser6cnt == 20)
        laser6 = 2;
    }
    else if (laser6 == 2) {
      game->a8_loading->x = 720;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser6cnt++;
      if (laser6cnt == 40)
        laser6 = 3;
    }
    else if (laser6 == 3) {
      game->a8_loading->x = 720;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser6cnt++;
      if (laser6cnt == 60)
        laser6 = 4;
    }
    else if (laser6 == 4) {
      game->a8_laser->x = 720;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser6cnt++;
      if (laser6cnt == 90)
        laser6 = 0;
    }

    if (laser7 == 1) {
      game->a8_loading->x = 864;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser7cnt++;
      if (laser7cnt == 20)
        laser7 = 2;
    }
    else if (laser7 == 2) {
      game->a8_loading->x = 864;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser7cnt++;
      if (laser7cnt == 40)
        laser7 = 3;
    }
    else if (laser7 == 3) {
      game->a8_loading->x = 864;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser7cnt++;
      if (laser7cnt == 60)
        laser7 = 4;
    }
    else if (laser7 == 4) {
      game->a8_laser->x = 864;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser7cnt++;
      if (laser7cnt == 90)
        laser7 = 0;
    }

    if (laser8 == 1) {
      game->a8_loading->x = 1008;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      laser8cnt++;
      if (laser8cnt == 20)
        laser8 = 2;
    }
    else if (laser8 == 2) {
      game->a8_loading->x = 1008;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser8cnt++;
      if (laser8cnt == 40)
        laser8 = 3;
    }
    else if (laser8 == 3) {
      game->a8_loading->x = 1008;
      game->a8_loading->y = 0;
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      move_sprite(game->a8_loading, 0, 70);
      draw_sprite(game->a8_loading);
      laser8cnt++;
      if (laser8cnt == 60)
        laser8 = 4;
    }
    else if (laser8 == 4) {
      game->a8_laser->x = 1008;
      game->a8_laser->y = 0;
      draw_sprite(game->a8_laser);
      laser8cnt++;
      if (laser8cnt == 90)
        laser8 = 0;
    }
  }

  static int meteor1, meteor2, meteor3, meteor4, meteor5;
  static int x1, x2, x3, x4, x5, y1, y2, y3, y4, y5;

  if ((framecounter % 25) == 0) {
    if (meteor1 == 0) {
      if (rand() % 2 == 0) {
        x1 = rand() % 501 + 82;
        y1 = 0;
        meteor1 = 1;
      }
      else {
        y1 = 0;
        x1 = 1152 - game->a8_meteor_right->bitmap->width - (rand() % 501);
        meteor1 = 2;
      }
    }
    else if (meteor2 == 0) {
      if (rand() % 2 == 0) {
        x2 = rand() % 501 + 82;
        y2 = 0;
        meteor2 = 1;
      }
      else {
        y2 = 0;
        x2 = 1152 - game->a8_meteor_right->bitmap->width - (rand() % 501);
        meteor2 = 2;
      }
    }
    else if (meteor3 == 0) {
      if (rand() % 2 == 0) {
        x3 = rand() % 501 + 82;
        y3 = 0;
        meteor3 = 1;
      }
      else {
        y3 = 0;
        x3 = 1152 - game->a8_meteor_right->bitmap->width - (rand() % 501);
        meteor3 = 2;
      }
    }
    else if (meteor4 == 0) {
      if (rand() % 2 == 0) {
        x4 = rand() % 501 + 82;
        y4 = 0;
        meteor4 = 1;
      }
      else {
        y4 = 0;
        x4 = 1152 - game->a8_meteor_right->bitmap->width - (rand() % 501);
        meteor4 = 2;
      }
    }
    else if (meteor5 == 0) {
      if (rand() % 2 == 0) {
        x5 = rand() % 501 + 82;
        y5 = 0;
        meteor5 = 1;
      }
      else {
        y5 = 0;
        x5 = 1152 - game->a8_meteor_right->bitmap->width - (rand() % 501);
        meteor5 = 2;
      }
    }
  }

  if (meteor1 == 1) {
    game->a8_meteor->x = x1;
    game->a8_meteor->y = y1;
    draw_sprite(game->a8_meteor);
    x1 += 15;
    y1 += 18;
  }
  else if (meteor1 == 2) {
    game->a8_meteor_right->x = x1;
    game->a8_meteor_right->y = y1;
    draw_sprite(game->a8_meteor_right);
    x1 -= 15;
    y1 += 18;
  }
  if (meteor2 == 1) {
    game->a8_meteor->x = x2;
    game->a8_meteor->y = y2;
    draw_sprite(game->a8_meteor);
    x2 += 6;
    y2 += 12;
  }
  else if (meteor2 == 2) {
    game->a8_meteor_right->x = x2;
    game->a8_meteor_right->y = y2;
    draw_sprite(game->a8_meteor_right);
    x2 -= 6;
    y2 += 12;
  }
  if (meteor3 == 1) {
    game->a8_meteor->x = x3;
    game->a8_meteor->y = y3;
    draw_sprite(game->a8_meteor);
    x3 += 9;
    y3 += 15;
  }
  else if (meteor3 == 2) {
    game->a8_meteor_right->x = x3;
    game->a8_meteor_right->y = y3;
    draw_sprite(game->a8_meteor_right);
    x3 -= 9;
    y3 += 15;
  }
  if (meteor4 == 1) {
    game->a8_meteor->x = x4;
    game->a8_meteor->y = y4;
    draw_sprite(game->a8_meteor);
    x4 += 15;
    y4 += 9;
  }
  else if (meteor4 == 2) {
    game->a8_meteor_right->x = x4;
    game->a8_meteor_right->y = y4;
    draw_sprite(game->a8_meteor_right);
    x4 -= 15;
    y4 += 9;
  }
  if (meteor5 == 1) {
    game->a8_meteor->x = x5;
    game->a8_meteor->y = y5;
    draw_sprite(game->a8_meteor);
    x5 += 12;
    y5 += 6;
  }
  else if (meteor5 == 2) {
    game->a8_meteor_right->x = x5;
    game->a8_meteor_right->y = y5;
    draw_sprite(game->a8_meteor_right);
    x5 -= 12;
    y5 += 6;
  }

  if (meteor1 == 1) {
    if ((game->a8_meteor->bitmap->width + x1) > 1152 || (game->a8_meteor->bitmap->height + y1) > 864)
      meteor1 = 0;
  }
  else if (meteor1 == 2)
    if (x1 < 0 || (game->a8_meteor_right->bitmap->height + y1) > 864)
      meteor1 = 0;

  if (meteor2 == 1) {
    if ((game->a8_meteor->bitmap->width + x2) > 1152 || (game->a8_meteor->bitmap->height + y2) > 864)
      meteor2 = 0;
  }
  else if (meteor2 == 2)
    if (x2 < 0 || (game->a8_meteor_right->bitmap->height + y2) > 864)
      meteor2 = 0;

  if (meteor3 == 1) {
    if ((game->a8_meteor->bitmap->width + x3) > 1152 || (game->a8_meteor->bitmap->height + y3) > 864)
      meteor3 = 0;
  }
  else if (meteor3 == 2)
    if (x3 < 0 || (game->a8_meteor_right->bitmap->height + y3) > 864)
      meteor3 = 0;

  if (meteor4 == 1) {
    if ((game->a8_meteor->bitmap->width + x4) > 1152 || (game->a8_meteor->bitmap->height + y4) > 864)
      meteor4 = 0;
  }
  else if (meteor4 == 2)
    if (x4 < 0 || (game->a8_meteor_right->bitmap->height + y4) > 864)
      meteor4 = 0;

  if (meteor5 == 1) {
    if ((game->a8_meteor->bitmap->width + x5) > 1152 || (game->a8_meteor->bitmap->height + y5) > 864)
      meteor5 = 0;
  }
  else if (meteor5 == 2)
    if (x5 < 0 || (game->a8_meteor_right->bitmap->height + y5) > 864)
      meteor5 = 0;

  if (draw_character(game->player) == CHARACTER_COLLISION) {
    if (invulnframe == 0) {
      update_character(game->player, 0, 0, -5, 0, 7);
      invulnframe = 30;
    }
  }

  buffercopy();
  framecounter++;
  if (invulnframe > 0)
    invulnframe--;

  if (framecounter == 700) {
    laser1 = 0;
    laser2 = 0;
    laser3 = 0;
    laser4 = 0;
    laser5 = 0;
    laser6 = 0;
    laser7 = 0;
    laser8 = 0;
    meteor1 = 0;
    meteor2 = 0;
    meteor3 = 0;
    meteor4 = 0;
    meteor5 = 0;
    return ANIMATION_FINISHED;
  }

  return ANIMATION_NOT_FINISHED;
}

void draw_end_screen() {
  FanTale *game = get_game();

  clear_buffer();
  draw_sprite(game->continue_button);
  if (game->enemy->hp <= 0)
    draw_sprite(game->victory_message);
  else
    draw_sprite(game->death_message);
  draw_character(game->enemy);

  game->select->x = 400;
  game->select->y = 700;
  draw_sprite(game->select);
  buffercopy();
}

void draw_hp_bar() {
  FanTale *game = get_game();
  int greenhp = game->player->hp;

  for (int i = 0; i < greenhp; i++) {
    draw_sprite(game->green_hp);
    move_sprite(game->green_hp, 2, 0);
  }

  game->green_hp->x = 428;
}

void draw_hp_amount(int hp, int which) {
  FanTale *game = get_game();

  if (which == 1) {
    game->number_zero->x = 235;
    game->number_one->x = 235;
    game->number_two->x = 235;
    game->number_three->x = 235;
    game->number_four->x = 235;
    game->number_five->x = 235;
    game->number_six->x = 235;
    game->number_seven->x = 235;
    game->number_eight->x = 235;
    game->number_nine->x = 235;
    game->number_bar->x = 235;
    game->number_zero->y = 510;
    game->number_one->y = 510;
    game->number_two->y = 510;
    game->number_three->y = 510;
    game->number_four->y = 510;
    game->number_five->y = 510;
    game->number_six->y = 510;
    game->number_seven->y = 510;
    game->number_eight->y = 510;
    game->number_nine->y = 510;
    game->number_bar->y = 510;
  }
  else if (which == 0) {
    game->number_zero->x = 620;
    game->number_one->x = 620;
    game->number_two->x = 620;
    game->number_three->x = 620;
    game->number_four->x = 620;
    game->number_five->x = 620;
    game->number_six->x = 620;
    game->number_seven->x = 620;
    game->number_eight->x = 620;
    game->number_nine->x = 620;
    game->number_bar->x = 620;
    game->number_zero->y = 685;
    game->number_one->y = 685;
    game->number_two->y = 685;
    game->number_three->y = 685;
    game->number_four->y = 685;
    game->number_five->y = 685;
    game->number_six->y = 685;
    game->number_seven->y = 685;
    game->number_eight->y = 685;
    game->number_nine->y = 685;
    game->number_bar->y = 685;
  }

  int char_hp = hp;
  int position = 1;

  int centena = char_hp / 100;
  int dezena, unidade;

  if (char_hp < 100)
    dezena = char_hp / 10;
  else if (char_hp == 100)
    dezena = 0;
  else
    dezena = (char_hp - 100) / 10;

  if (char_hp < 100)
    unidade = (char_hp % 10);
  else if (char_hp == 100)
    unidade = 0;
  else
    unidade = ((char_hp - 100) % 10);

  switch (centena) {
    case 0:
      break;
    case 1:
      draw_sprite(game->number_one);
      position = 2;
      break;
  }

  if (position == 2) {
    move_sprite(game->number_zero, 33, 0);
    move_sprite(game->number_one, 33, 0);
    move_sprite(game->number_two, 33, 0);
    move_sprite(game->number_three, 33, 0);
    move_sprite(game->number_four, 33, 0);
    move_sprite(game->number_five, 33, 0);
    move_sprite(game->number_six, 33, 0);
    move_sprite(game->number_seven, 33, 0);
    move_sprite(game->number_eight, 33, 0);
    move_sprite(game->number_nine, 33, 0);
    move_sprite(game->number_bar, 33, 0);
  }

  switch (dezena) {
    case 0:
      if (centena == 1) {
        draw_sprite(game->number_zero);
        position = 3;
      }
      break;
    case 1:
      draw_sprite(game->number_one);
      position = 3;
      break;
    case 2:
      draw_sprite(game->number_two);
      position = 3;
      break;
    case 3:
      draw_sprite(game->number_three);
      position = 3;
      break;
    case 4:
      draw_sprite(game->number_four);
      position = 3;
      break;
    case 5:
      draw_sprite(game->number_five);
      position = 3;
      break;
    case 6:
      draw_sprite(game->number_six);
      position = 3;
      break;
    case 7:
      draw_sprite(game->number_seven);
      position = 3;
      break;
    case 8:
      draw_sprite(game->number_eight);
      position = 3;
      break;
    case 9:
      draw_sprite(game->number_nine);
      position = 3;
      break;
  }

  if (position == 3) {
    move_sprite(game->number_zero, 33, 0);
    move_sprite(game->number_one, 33, 0);
    move_sprite(game->number_two, 33, 0);
    move_sprite(game->number_three, 33, 0);
    move_sprite(game->number_four, 33, 0);
    move_sprite(game->number_five, 33, 0);
    move_sprite(game->number_six, 33, 0);
    move_sprite(game->number_seven, 33, 0);
    move_sprite(game->number_eight, 33, 0);
    move_sprite(game->number_nine, 33, 0);
    move_sprite(game->number_bar, 33, 0);
  }

  switch (unidade) {
    case 0:
      draw_sprite(game->number_zero);
      break;
    case 1:
      draw_sprite(game->number_one);
      break;
    case 2:
      draw_sprite(game->number_two);
      break;
    case 3:
      draw_sprite(game->number_three);
      break;
    case 4:
      draw_sprite(game->number_four);
      break;
    case 5:
      draw_sprite(game->number_five);
      break;
    case 6:
      draw_sprite(game->number_six);
      break;
    case 7:
      draw_sprite(game->number_seven);
      break;
    case 8:
      draw_sprite(game->number_eight);
      break;
    case 9:
      draw_sprite(game->number_nine);
      break;
  }

  move_sprite(game->number_bar, 39, 0);
  draw_sprite(game->number_bar);

  if (which == 1) {
    move_sprite(game->number_zero, 132, 0);
    move_sprite(game->number_one, 66, 0);
    move_sprite(game->number_five, 99, 0);
    draw_sprite(game->number_one);
    draw_sprite(game->number_five);
    draw_sprite(game->number_zero);
  }
  else if (which == 0) {
    move_sprite(game->number_zero, 99, 0);
    move_sprite(game->number_nine, 66, 0);
    draw_sprite(game->number_nine);
    draw_sprite(game->number_zero);
  }
}

int check_collision(Button *but, Cursor *curs) {
  if (but == NULL || curs == NULL)
    return NULL_POINTERS;

  int xibut = but->sprite->x;
  int xfbut = xibut + but->sprite->bitmap->width;
  int xicurs = curs->sprite->x;
  int yibut = but->sprite->y;
  int yfbut = yibut + but->sprite->bitmap->height;
  int yicurs = curs->sprite->y;

  if ((xibut < xicurs) && (yibut < yicurs) && (xfbut > xicurs) && (yfbut > yicurs)) {
    if (curs->lb == true)
      return BUTTON_CLICK;
    else
      return COLLISION;
  }
  else
    return NO_COLLISION;
}

int check_all_collision() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU) {

    if (check_collision(game->play, game->cursor) == COLLISION)
      update_button(game->play, true);
    else if (check_collision(game->play, game->cursor) == NO_COLLISION)
      update_button(game->play, false);
    else if (check_collision(game->play, game->cursor) == BUTTON_CLICK)
      return PLAY_BUTTON_CLICK;
    if (check_collision(game->how, game->cursor) == COLLISION)
      update_button(game->how, true);
    else if (check_collision(game->how, game->cursor) == NO_COLLISION)
      update_button(game->how, false);
    else if (check_collision(game->how, game->cursor) == BUTTON_CLICK)
      return HOW_BUTTON_CLICK;
    if (check_collision(game->exit, game->cursor) == COLLISION)
      update_button(game->exit, true);
    else if (check_collision(game->exit, game->cursor) == NO_COLLISION)
      update_button(game->exit, false);
    else if (check_collision(game->exit, game->cursor) == BUTTON_CLICK)
      return EXIT_BUTTON_CLICK;
  }

  if (game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2) {
    if (check_collision(game->back, game->cursor) == COLLISION)
      update_button(game->back, true);
    else if (check_collision(game->back, game->cursor) == NO_COLLISION)
      update_button(game->back, false);
    else if (check_collision(game->back, game->cursor) == BUTTON_CLICK)
      return BACK_BUTTON_CLICK;
    if (check_collision(game->next, game->cursor) == COLLISION)
      update_button(game->next, true);
    else if (check_collision(game->next, game->cursor) == NO_COLLISION)
      update_button(game->next, false);
    else if (check_collision(game->next, game->cursor) == BUTTON_CLICK)
      return NEXT_BUTTON_CLICK;
  }

  if (game->sm->state == HOW_PAGE3) {
    if (check_collision(game->back, game->cursor) == COLLISION)
      update_button(game->back, true);
    else if (check_collision(game->back, game->cursor) == NO_COLLISION)
      update_button(game->back, false);
    else if (check_collision(game->back, game->cursor) == BUTTON_CLICK)
      return BACK_BUTTON_CLICK;
  }

  return NO_BUTTON_COLLISION;
}

int handle_character_movement(int key_press) {
  static int up_press;
  static int left_press;
  static int down_press;
  static int right_press;
  static int order[4];
  static int keys_pressed;
  int i = 0;
  int first_press = NO_PRESS;
  int second_press = NO_PRESS;

  switch (key_press) {
    case NO_PRESS:
      if (keys_pressed == 0)
        break;

      first_press = order[0];
      if (keys_pressed == 1) {
        if (first_press == UP_PRESS)
          return UP_MOVEMENT;
        else if (first_press == LEFT_PRESS)
          return LEFT_MOVEMENT;
        else if (first_press == RIGHT_PRESS)
          return RIGHT_MOVEMENT;
        else if (first_press == DOWN_PRESS)
          return DOWN_MOVEMENT;
      }

      if (first_press == UP_PRESS || first_press == DOWN_PRESS) {
        if (order[1] == LEFT_PRESS || order[1] == RIGHT_PRESS)
          second_press = order[1];
        else if (order[2] == LEFT_PRESS || order[2] == RIGHT_PRESS)
          second_press = order[2];
        else if (order[3] == LEFT_PRESS || order[3] == RIGHT_PRESS)
          second_press = order[3];
      }

      if (first_press == LEFT_PRESS || first_press == RIGHT_PRESS) {
        if (order[1] == UP_PRESS || order[1] == DOWN_PRESS)
          second_press = order[1];
        else if (order[2] == UP_PRESS || order[2] == DOWN_PRESS)
          second_press = order[2];
        else if (order[3] == UP_PRESS || order[3] == DOWN_PRESS)
          second_press = order[3];
      }

      if (first_press == UP_PRESS) {
        if (second_press == LEFT_PRESS)
          return UP_AND_LEFT_MOVEMENT;
        else if (second_press == RIGHT_PRESS)
          return UP_AND_RIGHT_MOVEMENT;
        else if (second_press == NO_PRESS)
          return UP_MOVEMENT;
      }
      else if (first_press == DOWN_PRESS) {
        if (second_press == LEFT_PRESS)
          return DOWN_AND_LEFT_MOVEMENT;
        else if (second_press == RIGHT_PRESS)
          return DOWN_AND_RIGHT_MOVEMENT;
        else if (second_press == NO_PRESS)
          return DOWN_MOVEMENT;
      }
      else if (first_press == LEFT_PRESS) {
        if (second_press == UP_PRESS)
          return UP_AND_LEFT_MOVEMENT;
        else if (second_press == DOWN_PRESS)
          return DOWN_AND_LEFT_MOVEMENT;
        else if (second_press == NO_PRESS)
          return LEFT_MOVEMENT;
      }
      else if (first_press == RIGHT_PRESS) {
        if (second_press == UP_PRESS)
          return UP_AND_RIGHT_MOVEMENT;
        else if (second_press == DOWN_PRESS)
          return DOWN_AND_RIGHT_MOVEMENT;
        else if (second_press == NO_PRESS)
          return RIGHT_MOVEMENT;
      }
      break;
    case UP_PRESS:
      if (up_press == 1)
        break;
      else {
        up_press = 1;
        order[keys_pressed] = UP_PRESS;
        keys_pressed++;
        break;
      }
    case LEFT_PRESS:
      if (left_press == 1)
        break;
      else {
        left_press = 1;
        order[keys_pressed] = LEFT_PRESS;
        keys_pressed++;
        break;
      }
    case DOWN_PRESS:
      if (down_press == 1)
        break;
      else {
        down_press = 1;
        order[keys_pressed] = DOWN_PRESS;
        keys_pressed++;
        break;
      }
    case RIGHT_PRESS:
      if (right_press == 1)
        break;
      else {
        right_press = 1;
        order[keys_pressed] = RIGHT_PRESS;
        keys_pressed++;
        break;
      }
    case UP_RELEASE:
      if (up_press == 0)
        break;
      else {
        up_press = 0;

        for (; i < 4; i++) {
          if (order[i] == UP_PRESS)
            break;
        }

        if (i == 0) {
          order[0] = order[1];
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 1) {
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 2) {
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 3) {
          order[3] = NO_PRESS;
        }
        keys_pressed--;
      }
      break;
    case LEFT_RELEASE:
      if (left_press == 0)
        break;
      else {
        left_press = 0;

        for (; i < 4; i++) {
          if (order[i] == LEFT_PRESS)
            break;
        }

        if (i == 0) {
          order[0] = order[1];
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 1) {
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 2) {
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 3) {
          order[3] = NO_PRESS;
        }
        keys_pressed--;
      }
      break;
    case DOWN_RELEASE:
      if (down_press == 0)
        break;
      else {
        down_press = 0;

        for (; i < 4; i++) {
          if (order[i] == DOWN_PRESS)
            break;
        }

        if (i == 0) {
          order[0] = order[1];
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 1) {
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 2) {
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 3) {
          order[3] = NO_PRESS;
        }
        keys_pressed--;
      }
      break;
    case RIGHT_RELEASE:
      if (right_press == 0)
        break;
      else {
        right_press = 0;

        for (; i < 4; i++) {
          if (order[i] == RIGHT_PRESS)
            break;
        }

        if (i == 0) {
          order[0] = order[1];
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 1) {
          order[1] = order[2];
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 2) {
          order[2] = order[3];
          order[3] = NO_PRESS;
        }
        else if (i == 3) {
          order[3] = NO_PRESS;
        }
        keys_pressed--;
      }
      break;
    case RESET:
      up_press = 0;
      down_press = 0;
      left_press = 0;
      right_press = 0;
      order[0] = NO_PRESS;
      order[1] = NO_PRESS;
      order[2] = NO_PRESS;
      order[3] = NO_PRESS;
      keys_pressed = 0;
      break;
    default:
      return INVALID_KEY;
      break;
  }

  return NOTHING_HAPPENED;
}

void move_player() {
  FanTale *game = get_game();

  int char_movement = handle_character_movement(NO_PRESS);

  if (char_movement == UP_MOVEMENT)
    update_character(game->player, 0, -4, 0, 0, 0);
  else if (char_movement == LEFT_MOVEMENT)
    update_character(game->player, -4, 0, 0, 0, 0);
  else if (char_movement == RIGHT_MOVEMENT)
    update_character(game->player, 4, 0, 0, 0, 0);
  else if (char_movement == DOWN_MOVEMENT)
    update_character(game->player, 0, 4, 0, 0, 0);
  else if (char_movement == UP_AND_LEFT_MOVEMENT)
    update_character(game->player, -4, -4, 0, 0, 0);
  else if (char_movement == UP_AND_RIGHT_MOVEMENT)
    update_character(game->player, 4, -4, 0, 0, 0);
  else if (char_movement == DOWN_AND_LEFT_MOVEMENT)
    update_character(game->player, -4, 4, 0, 0, 0);
  else if (char_movement == DOWN_AND_RIGHT_MOVEMENT)
    update_character(game->player, 4, 4, 0, 0, 0);
}

void move_player_final() {
  FanTale *game = get_game();

  int char_movement = handle_character_movement(NO_PRESS);

  if (char_movement == UP_MOVEMENT)
    update_character(game->player, 0, -12, 0, 0, 1);
  else if (char_movement == LEFT_MOVEMENT)
    update_character(game->player, -12, 0, 0, 0, 1);
  else if (char_movement == RIGHT_MOVEMENT)
    update_character(game->player, 12, 0, 0, 0, 1);
  else if (char_movement == DOWN_MOVEMENT)
    update_character(game->player, 0, 12, 0, 0, 1);
  else if (char_movement == UP_AND_LEFT_MOVEMENT)
    update_character(game->player, -12, -12, 0, 0, 1);
  else if (char_movement == UP_AND_RIGHT_MOVEMENT)
    update_character(game->player, 12, -12, 0, 0, 1);
  else if (char_movement == DOWN_AND_LEFT_MOVEMENT)
    update_character(game->player, -12, 12, 0, 0, 1);
  else if (char_movement == DOWN_AND_RIGHT_MOVEMENT)
    update_character(game->player, 12, 12, 0, 0, 1);
}

int move_overworld() {
  FanTale *game = get_game();

  int char_movement = handle_character_movement(NO_PRESS);

  if (char_movement == LEFT_MOVEMENT) {
    update_character(game->overworld_character, -4, 0, 0, 0, 2);
    return LEFT_MOVEMENT;
  }
  else if (char_movement == RIGHT_MOVEMENT) {
    update_character(game->overworld_character, 4, 0, 0, 0, 2);
    return RIGHT_MOVEMENT;
  }
  else if (char_movement == UP_AND_LEFT_MOVEMENT) {
    update_character(game->overworld_character, -4, 0, 0, 0, 2);
    return UP_AND_LEFT_MOVEMENT;
  }
  else if (char_movement == UP_AND_RIGHT_MOVEMENT) {
    update_character(game->overworld_character, 4, 0, 0, 0, 2);
    return UP_AND_RIGHT_MOVEMENT;
  }
  else if (char_movement == DOWN_AND_LEFT_MOVEMENT) {
    update_character(game->overworld_character, -4, 0, 0, 0, 2);
    return DOWN_AND_LEFT_MOVEMENT;
  }
  else if (char_movement == DOWN_AND_RIGHT_MOVEMENT) {
    update_character(game->overworld_character, 4, 0, 0, 0, 2);
    return DOWN_AND_RIGHT_MOVEMENT;
  }

  return NOTHING_HAPPENED;
}

void reset_attack(int attack) {
  FanTale *game = get_game();

  framecounter = 0;
  game->player->sprite->x = 572;
  game->player->sprite->y = 500;
  handle_character_movement(RESET);

  switch (attack) {
    case 1:
      destroy_attack1();
      update_character(game->enemy, 0, 0, 0, 1, 1);
      break;
    case 2:
      destroy_attack2();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 3:
      destroy_attack3();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 4:
      destroy_attack4();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 5:
      destroy_attack5();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 6:
      destroy_attack6();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 7:
      destroy_attack7();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
    case 8:
      destroy_attack8();
      update_character(game->enemy, 0, 0, 0, 1, 1); // mudar quarto parametro (turno)
      break;
  }

  if (game->player->hp <= 0) {
    load_end_screen(game);
    game->sm->state = END_SCREEN;
    return;
  }
  game->sm->state = COMBAT;
}

unsigned int *get_frame_counter() {
  return &framecounter;
}
