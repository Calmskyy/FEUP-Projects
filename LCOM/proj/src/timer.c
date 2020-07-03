#include "timer.h"
#include <lcom/lcf.h>
#include "dispatcher.h"
#include "fantale.h"
#include "proj.h"

int count = 0;
int framecount = 1;
int hook_id = 0;

int(timer_subscribe_int)(uint8_t *bit_no) {
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
    return -1;
  return BIT(*bit_no);
}

int(timer_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id) != OK)
    return -1;
  return 0;
}

void(timer_int_handler)() {
  count++;

  FanTale *game = get_game();

  if (count % framecount == 0)
    event_found(game->sm, TIMER_TICK);
}
