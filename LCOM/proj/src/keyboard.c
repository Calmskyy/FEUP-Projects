#include "keyboard.h"
#include "dispatcher.h"
#include "fantale.h"
#include "macros.h"
#include "proj.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>
#include <stdbool.h>

int kbc_id = 10;
int bytecode = 0;
static int twobyte = 0;
static uint8_t byte1, byte2;

int kbc_subscribe_int(uint8_t *bit_no) {

  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_id) != OK)
    return -1;
  return BIT(*bit_no);
}

int kbc_unsubscribe_int() {

  if (sys_irqrmpolicy(&kbc_id) != OK)
    return -1;
  return 0;
}

void(kbc_ih)() {

  bytecode = read_scan_codes();
}

void keyboard_int_handler() {
  kbc_ih();

  if (bytecode == -1 || bytecode == -2)
    return;

  FanTale *game = get_game();

  if (read_keyboard_data() == COMPLETE_BYTE) {
    if (byte1 == W_KEY_MAKECODE)
      event_found(game->sm, W_PRESS);
    else if (byte1 == A_KEY_MAKECODE)
      event_found(game->sm, A_PRESS);
    else if (byte1 == S_KEY_MAKECODE)
      event_found(game->sm, S_PRESS);
    else if (byte1 == D_KEY_MAKECODE)
      event_found(game->sm, D_PRESS);
    else if (byte1 == Z_KEY_MAKECODE)
      event_found(game->sm, Z_PRESS);
    else if (byte1 == X_KEY_MAKECODE)
      event_found(game->sm, X_PRESS);
    else if (byte1 == W_KEY_BREAKCODE)
      event_found(game->sm, W_RELEASE);
    else if (byte1 == A_KEY_BREAKCODE)
      event_found(game->sm, A_RELEASE);
    else if (byte1 == S_KEY_BREAKCODE)
      event_found(game->sm, S_RELEASE);
    else if (byte1 == D_KEY_BREAKCODE)
      event_found(game->sm, D_RELEASE);
  }
}

int read_keyboard_data() {

  if (bytecode == 0xE0) {
    byte1 = bytecode;
    twobyte = 1;
    return INCOMPLETE_TWO_BYTE;
  }

  if (twobyte == 1) {
    byte2 = bytecode;
    twobyte = 0;
    return COMPLETE_TWO_BYTE;
  }

  else {
    byte1 = bytecode;
    return COMPLETE_BYTE;
  }
}

int read_scan_codes() {

  unsigned int data;
  unsigned int stat;

  while (1) {
    sys_inb(STAT_REG, &stat);
    if (stat & OBF) {
      sys_inb(OUT_BUF, &data);
      if ((stat & (PAR_ERR | TO_ERR)) == 0)
        return data;
      else
        return -1;
    }
    return -2;
  }
}

int write_command(unsigned int type, unsigned int port) {
  unsigned int stat, data;
  int a = 0;

  while (a < 10) {
    sys_inb(STAT_REG, &stat);
    if (stat & OBF)
      sys_inb(OUT_BUF, &data);
    if ((stat & IBF) == 0) {
      sys_outb(port, type);
      tickdelay(micros_to_ticks(DELAY_KBC));
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_KBC));
    a = a + 1;
  }
  printf("error on writing KBC command.\n");
  return 2;
}

unsigned int issue_command(unsigned int type, unsigned int cmd_byte) {

  unsigned int stat, data;
  int a = 0;

  if (type == WRITE_CMD) {
    while (a < 10) {
      sys_inb(STAT_REG, &stat);
      if ((stat & IBF) == 0) {
        sys_outb(KBC_CMD_REG, WRITE_CMD);
        sys_outb(IN_BUF, cmd_byte);
        return 0;
      }
      tickdelay(micros_to_ticks(DELAY_KBC));
      a = a + 1;
    }
    if (a == 10) {
      printf("error on issuing command byte.\n");
      return 1;
    }
  }

  if (type == MOUSE_WRITE_CMD) {
    while (a < 10) {
      sys_inb(STAT_REG, &stat);
      if (stat & OBF)
        sys_inb(OUT_BUF, &data);
      if ((stat & IBF) == 0) {
        sys_outb(KBC_CMD_REG, MOUSE_WRITE_CMD);
        break;
      }
      tickdelay(micros_to_ticks(DELAY_KBC));
      a = a + 1;
    }
    if (a == 10) {
      printf("error on issuing command byte.\n");
      return 1;
    }
    a = 0;

    while (a < 10) {
      sys_inb(STAT_REG, &stat);
      if (stat & OBF)
        sys_inb(OUT_BUF, &data);
      if ((stat & IBF) == 0) {
        sys_outb(IN_BUF, cmd_byte);
        return 0;
      }
      tickdelay(micros_to_ticks(DELAY_KBC));
      a = a + 1;
    }
    if (a == 10) {
      printf("error on issuing command arguments.\n");
      return 1;
    }
  }
  return 1;
}
