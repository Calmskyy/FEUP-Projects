#include "dispatcher.h"
#include "fantale.h"
#include "keyboard.h"
#include "mouse.h"
#include "proj.h"
#include "rtc.h"
#include <lcom/lcf.h>
#include <stdbool.h>

StateMachine *create_state_machine() {
  StateMachine *sm = (StateMachine *) malloc(sizeof(StateMachine));

  if (sm == NULL)
    return STATE_MACHINE_ERROR;

  sm->state = MAIN_MENU;
  sm->events_to_process = 0;

  return sm;
}

void destroy_state_machine(StateMachine *sm) {
  if (sm == NULL)
    return;

  free(sm);

  sm = NULL;
}

void event_found(StateMachine *sm, event_t evt) {

  sm->events[sm->events_to_process] = evt;
  sm->events_to_process++;
}

void event_handler() {

  FanTale *game = get_game();
  if (game->sm->events_to_process == 0)
    return;

  for (unsigned int i = 0; i < game->sm->events_to_process; i++) {
    if (game->end == 1)
      break;
    switch (game->sm->events[i]) {
      case MOUSE_LB_PRESSED:
        mouse_lb_pressed_handler();
        break;
      case MOUSE_LB_RELEASED:
        mouse_lb_released_handler();
        break;
      case MOUSE_MOVEMENT:
        mouse_movement_handler();
        break;
      case TIMER_TICK:
        timer_frame_handler();
        break;
      case RTC_PERIODIC:
        rtc_handler();
        break;
      case W_PRESS:
        w_press_handler();
        break;
      case A_PRESS:
        a_press_handler();
        break;
      case S_PRESS:
        s_press_handler();
        break;
      case D_PRESS:
        d_press_handler();
        break;
      case Z_PRESS:
        z_press_handler();
        break;
      case X_PRESS:
        x_press_handler();
        break;
      case W_RELEASE:
        w_release_handler();
        break;
      case A_RELEASE:
        a_release_handler();
        break;
      case S_RELEASE:
        s_release_handler();
        break;
      case D_RELEASE:
        d_release_handler();
        break;
    }
  }
  game->sm->events_to_process = 0;
}

void timer_frame_handler() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU) {
    draw_main_menu();
  }
  if (game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2 || game->sm->state == HOW_PAGE3)
    draw_how_menu();
  if (game->sm->state == OVERWORLD) {
    if (draw_overworld(game) == RIGHT_REACHED) {
      unsigned int *count = get_frame_counter();
      *count = 0;
      load_combat();
      game->sm->state = COMBAT;
      handle_character_movement(RESET);
      destroy_overworld(game);
      return;
    }
  }
  if (game->sm->state == COMBAT || game->sm->state == ATTACK_PICK || game->sm->state == ACTION_PICK || game->sm->state == GIVE_UP_PICK)
    draw_combat();
  if (game->sm->state == FIGHT_ANIMATION) {
    if (draw_fight_animation() == ANIMATION_FINISHED) {
      unsigned int *count = get_frame_counter();
      *count = 0;
      destroy_player_attack();
      if (game->enemy->hp <= 0) {
        load_end_screen(game);
        game->sm->state = END_SCREEN;
        return;
      }
      if (game->enemy->turn > 20) {
        load_end_screen(game);
        game->sm->state = END_SCREEN;
        return;
      }
      switch (game->enemy->turn) {
        case 1:
          load_attack1(game);
          game->sm->state = ATTACK_1;
          break;
        case 2:
          load_attack2(game);
          game->sm->state = ATTACK_2;
          break;
        case 3:
          load_attack3(game);
          game->sm->state = ATTACK_3;
          break;
        case 4:
          load_attack5(game);
          game->sm->state = ATTACK_5;
          break;
        case 5:
          load_attack4(game);
          game->sm->state = ATTACK_4;
          break;
        case 6:
          load_attack2(game);
          game->sm->state = ATTACK_2;
          break;
        case 7:
          load_attack6(game);
          game->sm->state = ATTACK_6;
          break;
        case 8:
          load_attack7(game);
          game->sm->state = ATTACK_7;
          break;
        case 9:
          load_attack5(game);
          game->sm->state = ATTACK_5;
          break;
        case 10:
          load_attack8(game);
          game->sm->state = ATTACK_8;
          break;
        case 11:
          load_attack1(game);
          game->sm->state = ATTACK_1;
          break;
        case 12:
          load_attack7(game);
          game->sm->state = ATTACK_7;
          break;
        case 13:
          load_attack3(game);
          game->sm->state = ATTACK_3;
          break;
        case 14:
          load_attack6(game);
          game->sm->state = ATTACK_6;
          break;
        case 15:
          load_attack4(game);
          game->sm->state = ATTACK_4;
          break;
        case 16:
          load_attack2(game);
          game->sm->state = ATTACK_2;
          break;
        case 17:
          load_attack7(game);
          game->sm->state = ATTACK_7;
          break;
        case 18:
          load_attack5(game);
          game->sm->state = ATTACK_5;
          break;
        case 19:
          load_attack3(game);
          game->sm->state = ATTACK_3;
          break;
        case 20:
          load_attack8(game);
          game->sm->state = ATTACK_8;
          break;
      }
      return;
    }
  }
  if (game->sm->state == ATTACK_1) {
    if (draw_attack1() == ANIMATION_FINISHED) {
      reset_attack(1);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_2) {
    if (draw_attack2() == ANIMATION_FINISHED) {
      reset_attack(2);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_3) {
    if (draw_attack3() == ANIMATION_FINISHED) {
      reset_attack(3);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_4) {
    if (draw_attack4() == ANIMATION_FINISHED) {
      reset_attack(4);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_5) {
    if (draw_attack5() == ANIMATION_FINISHED) {
      reset_attack(5);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_6) {
    if (draw_attack6() == ANIMATION_FINISHED) {
      reset_attack(6);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_7) {
    if (draw_attack7() == ANIMATION_FINISHED) {
      reset_attack(7);
    }
    move_player();
  }
  if (game->sm->state == ATTACK_8) {
    if (draw_attack8() == ANIMATION_FINISHED) {
      reset_attack(8);
    }
    move_player_final();
  }

  if (game->sm->state == CHECK_HP)
    draw_check_hp();

  if (game->sm->state == END_SCREEN)
    draw_end_screen();

  if (game->sm->state == BOOST_MESSAGE)
    draw_boost_message();
}

void rtc_handler() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU) {
    uint8_t time = 0;
    rtc_get_time(&time);

    uint8_t unidades = (time & 0x0F);
    uint8_t dezenas = (time & 0xF0) >> 4;
    int decimaltime = unidades + (dezenas * 10);
    game->time = decimaltime;
  }
}

void mouse_lb_pressed_handler() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU || game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2 || game->sm->state == HOW_PAGE3) {
    if (game->cursor->lb == true)
      return;
    else
      update_cursor(game->cursor, 0, 0, true);
  }

  if (game->sm->state == MAIN_MENU) {
    if (check_all_collision(game) == EXIT_BUTTON_CLICK)
      game->end = 1;
    if (check_all_collision(game) == HOW_BUTTON_CLICK) {
      load_how_menu();
      game->sm->state = HOW_MENU;
      destroy_main_menu();
    }
    if (check_all_collision(game) == PLAY_BUTTON_CLICK) {
      load_overworld(game);
      game->sm->state = OVERWORLD;
      destroy_main_menu();
    }
    return;
  }

  if (game->sm->state == HOW_MENU) {
    if (check_all_collision(game) == BACK_BUTTON_CLICK) {
      load_main_menu();
      game->sm->state = MAIN_MENU;
      destroy_how_menu();
      return;
    }
    if (check_all_collision(game) == NEXT_BUTTON_CLICK) {
      game->sm->state = HOW_PAGE2;
      return;
    }
  }
  if (game->sm->state == HOW_PAGE2) {
    if (check_all_collision(game) == BACK_BUTTON_CLICK) {
      game->sm->state = HOW_MENU;
      return;
    }
    if (check_all_collision(game) == NEXT_BUTTON_CLICK) {
      game->sm->state = HOW_PAGE3;
      return;
    }
  }
  if (game->sm->state == HOW_PAGE3) {
    if (check_all_collision(game) == BACK_BUTTON_CLICK) {
      game->sm->state = HOW_PAGE2;
      return;
    }
  }
}

void mouse_lb_released_handler() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU || game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2 || game->sm->state == HOW_PAGE3) {

    if (game->cursor->lb == false)
      return;
    else
      update_cursor(game->cursor, 0, 0, false);
  }
}

void mouse_movement_handler() {
  FanTale *game = get_game();

  if (game->sm->state == MAIN_MENU || game->sm->state == HOW_MENU || game->sm->state == HOW_PAGE2 || game->sm->state == HOW_PAGE3) {

    bool x_negative, y_negative;
    int16_t delta_x, delta_y;

    uint8_t byte1 = get_byte1();
    uint8_t byte2 = get_byte2();
    uint8_t byte3 = get_byte3();

    if ((byte1 & XOVF) || (byte1 & YOVF))
      return;
    if (byte1 & YSIGN)
      y_negative = true;
    else
      y_negative = false;
    if (byte1 & XSIGN)
      x_negative = true;
    else
      x_negative = false;
    if (x_negative == true)
      delta_x = byte2 - 256;
    else
      delta_x = byte2;
    if (y_negative == true)
      delta_y = byte3 - 256;
    else
      delta_y = byte3;

    update_cursor(game->cursor, delta_x / 2, -delta_y / 2, game->cursor->lb);
    check_all_collision(game);
  }
}

void w_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == ACTION_PICK) {
    if (game->little_select->x == 200 && game->little_select->y == 585)
      game->little_select->y = 500;
  }
  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(UP_PRESS);
  }
}

void a_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == COMBAT) {
    if (game->attack->hover == true)
      return;
    if (game->action->hover == true) {
      update_button(game->action, false);
      move_sprite(game->select, -300, 0);
      update_button(game->attack, true);
      return;
    }
    if (game->give_up->hover == true) {
      update_button(game->give_up, false);
      move_sprite(game->select, -300, 0);
      update_button(game->action, true);
      return;
    }
  }
  if (game->sm->state == ACTION_PICK) {
    if (game->little_select->x == 500 && game->little_select->y == 500)
      game->little_select->x = 200;
  }
  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(LEFT_PRESS);
  }
}

void s_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == ACTION_PICK) {
    if (game->little_select->x == 200 && game->little_select->y == 500)
      game->little_select->y = 585;
  }
  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(DOWN_PRESS);
  }
}

void d_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == COMBAT) {
    if (game->attack->hover == true) {
      update_button(game->attack, false);
      move_sprite(game->select, 300, 0);
      update_button(game->action, true);
      return;
    }
    if (game->action->hover == true) {
      update_button(game->action, false);
      move_sprite(game->select, 300, 0);
      update_button(game->give_up, true);
      return;
    }
    if (game->give_up->hover == true) {
      return;
    }
  }
  if (game->sm->state == ACTION_PICK) {
    if (game->little_select->x == 200 && game->little_select->y == 500)
      game->little_select->x = 500;
  }
  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(RIGHT_PRESS);
  }
}

void z_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == COMBAT) {
    if (game->attack->hover == true) {
      game->sm->state = ATTACK_PICK;
      game->little_select->x = 200;
      game->little_select->y = 500;
      return;
    }
    if (game->action->hover == true) {
      game->sm->state = ACTION_PICK;
      game->little_select->x = 200;
      game->little_select->y = 500;
      return;
    }
    if (game->give_up->hover == true) {
      game->sm->state = GIVE_UP_PICK;
      game->little_select->x = 200;
      game->little_select->y = 500;
      return;
    }
  }
  if (game->sm->state == GIVE_UP_PICK) {
    load_end_screen(game);
    game->sm->state = END_SCREEN;
    return;
  }
  if (game->sm->state == ATTACK_PICK) {
    load_player_attack();
    game->sm->state = FIGHT_ANIMATION;
    return;
  }
  if (game->sm->state == FIGHT_ANIMATION) {
    unsigned int *count = get_frame_counter();
    if (*count < 100)
      *count = 100;
    return;
  }
  if (game->sm->state == ACTION_PICK) {
    if (game->little_select->x == 200 && game->little_select->y == 500) {
      game->sm->state = CHECK_HP;
    }
    if (game->little_select->x == 500 && game->little_select->y == 500) {
      load_player_attack();
      unsigned int *count = get_frame_counter();
      *count = 300;
      update_character(game->player, 0, 0, 30, 0, 0);
      if (game->player->hp > 90)
        game->player->hp = 90;
      game->sm->state = FIGHT_ANIMATION;
    }
    if (game->little_select->x == 200 && game->little_select->y == 585) {
      game->sm->state = BOOST_MESSAGE;
    }
    return;
  }
  if (game->sm->state == CHECK_HP) {
    game->sm->state = COMBAT;
    return;
  }
  if (game->sm->state == BOOST_MESSAGE) {
    load_player_attack();
    game->boost = 1;
    unsigned int *count = get_frame_counter();
    *count = 300;
    game->sm->state = FIGHT_ANIMATION;
    return;
  }
  if (game->sm->state == END_SCREEN) {
    load_main_menu();
    destroy_end_screen();
    destroy_combat();
    game->sm->state = MAIN_MENU;
    return;
  }
}

void x_press_handler() {
  FanTale *game = get_game();

  if (game->sm->state == ATTACK_PICK)
    game->sm->state = COMBAT;
  if (game->sm->state == ACTION_PICK)
    game->sm->state = COMBAT;
  if (game->sm->state == GIVE_UP_PICK)
    game->sm->state = COMBAT;
}

void w_release_handler() {
  FanTale *game = get_game();

  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(UP_RELEASE);
  }
}

void a_release_handler() {
  FanTale *game = get_game();

  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(LEFT_RELEASE);
  }
}

void s_release_handler() {
  FanTale *game = get_game();

  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(DOWN_RELEASE);
  }
}

void d_release_handler() {
  FanTale *game = get_game();

  if (game->sm->state == OVERWORLD || game->sm->state == ATTACK_1 || game->sm->state == ATTACK_2 || game->sm->state == ATTACK_3 || game->sm->state == ATTACK_4 || game->sm->state == ATTACK_5 || game->sm->state == ATTACK_6 || game->sm->state == ATTACK_7 || game->sm->state == ATTACK_8) {
    handle_character_movement(RIGHT_RELEASE);
  }
}
