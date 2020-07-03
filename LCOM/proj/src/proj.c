#include "proj.h"
#include "macros.h"
#include "video_gr.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <time.h>

static FanTale *fantale;

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  // lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // lcf_log_output("/home/lcom/labs/proj/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {

  fantale = create_game();

  srand(time(0));

  if (fantale == NULL) {
    printf("game could not be created.\n");
    return GAME_INIT_ERROR;
  }

  void *video_mem = vg_init(VIDEO_MODE);
  if (video_mem == VG_INIT_FAILED) {
    printf("Video mode initialization failed.\n");
    finish_game(fantale);
    return VIDEO_MODE_INIT_ERROR;
  }

  if (fantale_loop(fantale) == FAILED_SUBSCRIPTION) {
    vg_exit();
    printf("subscription of one or more interrupts failed.\n");
    return 1;
  }

  finish_game(fantale);

  return SUCCESS;
  printf("%s(%d, %p): under construction\n", __func__, argc, argv);
}

FanTale *get_game() {
  return fantale;
}
