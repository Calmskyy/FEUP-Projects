#include "mouse.h"
#include "dispatcher.h"
#include "fantale.h"
#include "keyboard.h"
#include "proj.h"
#include <lcom/lcf.h>
#include <minix/sysutil.h>

int mouse_id = 12;

extern int bytecode;
static uint8_t byte1, byte2, byte3;
static int bytecount = 0;

int mouse_subscribe_int(uint8_t *bit_no) {

  if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_id) != OK)
    return -1;
  return BIT(*bit_no);
}

int mouse_unsubscribe_int() {

  if (sys_irqrmpolicy(&mouse_id) != OK)
    return -1;
  return 0;
}

void(mouse_ih)() {

  (kbc_ih)();

  if (bytecode == -1 || bytecode == -2)
    return;

  FanTale *game = get_game();

  if (read_mouse_data() == PACKET_READY) {
    event_found(game->sm, MOUSE_MOVEMENT);

    if (byte1 & LB) {
      event_found(game->sm, MOUSE_LB_PRESSED);
    }
    else {
      event_found(game->sm, MOUSE_LB_RELEASED);
    }
  }
}

unsigned int read_mouse_ack() {
  unsigned int stat;
  unsigned int data;
  int a = 0;

  while (a < 10) {
    sys_inb(STAT_REG, &stat);
    if (stat & OBF) {
      sys_inb(OUT_BUF, &data);
      if ((stat & (PAR_ERR | TO_ERR)) == 0) {
        return data;
      }
    }
    tickdelay(micros_to_ticks(DELAY_KBC));
    a++;
  }
  if (a == 10) {
    return 1;
  }
  return 0;
}

int mouse_command(unsigned int cmd_args) {
  unsigned int ack;

  if (write_command(cmd_args, IN_BUF) != 0)
    return -1;

  ack = read_mouse_ack();

  while (ack == PS2_NACK) {
    if (write_command(cmd_args, IN_BUF) != 0)
      return -1;

    ack = read_mouse_ack();
    if (ack == PS2_ERROR)
      return 1;
  }
  return 0;
}

int read_mouse_data() {

  if (bytecount == 0) {
    byte1 = bytecode;
    if (byte1 & MOUSETEST) {
      bytecount = 1;
      return PACKET_NOT_READY;
    }
    else
      return PACKET_OUT_OF_SYNC;
  }
  else if (bytecount == 1) {
    byte2 = bytecode;
    bytecount = 2;
    return PACKET_NOT_READY;
  }
  else {
    byte3 = bytecode;
    bytecount = 0;
    return PACKET_READY;
  }
}

uint8_t get_byte1() {
  return byte1;
}

uint8_t get_byte2() {
  return byte2;
}

uint8_t get_byte3() {
  return byte3;
}

