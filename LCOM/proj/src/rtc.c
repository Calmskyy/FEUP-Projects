#include "rtc.h"
#include "fantale.h"
#include "proj.h"
#include <lcom/lcf.h>
#include <stdlib.h>
#include <string.h>

int rtc_id = 8;

int rtc_subscribe_int(uint8_t *bit_no) {

  if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &rtc_id) != OK)
    return -1;
  return BIT(*bit_no);
}

int rtc_unsubscribe_int() {

  if (sys_irqrmpolicy(&rtc_id) != OK)
    return -1;
  return 0;
}

int rtc_write_address(uint8_t reg) {

  if (sys_outb(ADDRESS_REG, reg) != OK)
    return RTC_ERROR;
  else
    return RTC_SUCCESS;
}

int read_rtc_data(uint8_t reg, uint8_t *regcontent) {

  unsigned int data;

  if (rtc_write_address(reg) != RTC_SUCCESS)
    return RTC_ERROR;

  if (sys_inb(DATA_REG, &data) != OK)
    return RTC_ERROR;

  *regcontent = (uint8_t) data;
  return RTC_SUCCESS;
}

int rtc_command(int command) {

  uint8_t data;

  if (command == SET_INTERRUPT_RATE) {
    if (read_rtc_data(REGISTER_A, &data) != RTC_SUCCESS)
      return RTC_ERROR;
    data = data | RATE_SET_BYTE;

    if (rtc_write_address(REGISTER_A) != RTC_SUCCESS)
      return RTC_ERROR;

    sys_outb(DATA_REG, data);
    return RTC_SUCCESS;
  }

  if (read_rtc_data(REGISTER_B, &data) != RTC_SUCCESS)
    return RTC_ERROR;

  if (command == ENABLE_INTERRUPT)
    data = data | INTERRUPT_ENABLE_BIT;

  if (command == DISABLE_INTERRUPT)
    data = data & INTERRUPT_DISABLE_BYTE;

  if (rtc_write_address(REGISTER_B) != RTC_SUCCESS)
    return RTC_ERROR;

  sys_outb(DATA_REG, data);

  return RTC_SUCCESS;
}

int rtc_get_time(uint8_t *time) {

  if (read_rtc_data(HOUR_ADDRESS, time) != RTC_SUCCESS)
    return RTC_ERROR;
  else
    return RTC_SUCCESS;
}

void rtc_int_handler() {

  uint8_t data;
  FanTale *game = get_game();

  read_rtc_data(REGISTER_C, &data);

  if (data & PERIODIC_INTERRUPT_BIT)
    event_found(game->sm, RTC_PERIODIC);
}
