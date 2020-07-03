#include "video_gr.h"
#include "macros.h"
#include <machine/int86.h>
#include <stdio.h>

static unsigned char *video_mem;
static char *buffer;

static unsigned h_res;
static unsigned v_res;
static unsigned bits_per_pixel;

char *get_buffer() {
  return buffer;
}

unsigned get_h_res() {
  return h_res;
}

unsigned get_v_res() {
  return v_res;
}

unsigned get_bits_per_pixel() {
  return bits_per_pixel;
}

void free_mem(char *buffer) {
  if (buffer != NULL) {
    free(buffer);
  }
}

void clear_buffer() {
  for (unsigned int i = 0; i < h_res * v_res * 4; i++) {
    *(buffer + i) = 0;
  }
}

void clear_combat_buffer() {
  char *buffer = get_buffer();
  char *bufferposition;
  unsigned int hres = get_h_res();

  for (unsigned int y = 360; y < 664; y++) {
    for (unsigned int x = 372; x < 772; x++) {
      bufferposition = buffer;
      bufferposition = bufferposition + x * 4 + y * hres * 4;
      *bufferposition = 0;
      *(bufferposition + 1) = 0;
      *(bufferposition + 2) = 0;
      *(bufferposition + 3) = 0;
    }
  }

  for (unsigned int y = 680; y < 730; y++) {
    for (unsigned int x = 426; x < 900; x++) {
      bufferposition = buffer;
      bufferposition = bufferposition + x * 4 + y * hres * 4;
      *bufferposition = 0;
      *(bufferposition + 1) = 0;
      *(bufferposition + 2) = 0;
      *(bufferposition + 3) = 0;
    }
  }
}

void buffercopy() {
  unsigned int vram_size = h_res * v_res * 4;
  memcpy(video_mem, buffer, vram_size);
}

int vbe_get_info(uint16_t mode, vbe_mode_info_t *vbe_info) {
  struct reg86u r;
  phys_bytes buf;
  void *virt;
  mmap_t map;

  memset(&r, 0, sizeof(r));

  virt = lm_alloc(sizeof(vbe_mode_info_t), &map);
  if (virt == NULL) {
    return MEMORY_ALLOC_FAILED;
  }

  buf = map.phys;
  r.u.w.ax = RETURN_VBE_INFO;
  r.u.w.es = PB2BASE(buf);
  r.u.w.di = PB2OFF(buf);
  r.u.w.cx = mode;
  r.u.b.intno = BIOS_SERVICES;
  if (sys_int86(&r) != OK) {
    printf("sys_int86() failed.\n");
    return BIOS_CALL_FAILED;
  }

  *vbe_info = *(vbe_mode_info_t *) map.virt;
  lm_free(&map);

  return SUCCESS;
}

int set_video_mode(uint16_t mode) {
  struct reg86u reg86;

  memset(&reg86, 0, sizeof(reg86));

  reg86.u.b.intno = BIOS_SERVICES;
  reg86.u.w.ax = SET_VIDEO_MODE;
  reg86.u.w.bx = BIT(14) | mode;

  if (sys_int86(&reg86) != OK) {
    printf("sys_int86() failed.\n");
    return BIOS_CALL_FAILED;
  }
  return SUCCESS;
}

void *(vg_init)(uint16_t mode) {

  void *virt;
  virt = lm_init(false);
  if (virt == NULL)
    return LM_INIT_FAILED;

  vbe_mode_info_t vbe_info;
  if (vbe_get_info(mode, &vbe_info) != SUCCESS) {
    printf("vbe_get_mode_info failed.\n");
    return VG_INIT_FAILED;
  }

  int r;
  struct minix_mem_range mr;
  unsigned int vram_base = vbe_info.PhysBasePtr;
  unsigned int bytes_per_pixel;
  if (vbe_info.BitsPerPixel <= 8)
    bytes_per_pixel = 1;
  if ((vbe_info.BitsPerPixel > 8) && (vbe_info.BitsPerPixel <= 16))
    bytes_per_pixel = 2;
  if ((vbe_info.BitsPerPixel > 16) && (vbe_info.BitsPerPixel <= 24))
    bytes_per_pixel = 3;
  if ((vbe_info.BitsPerPixel > 24) && (vbe_info.BitsPerPixel <= 32))
    bytes_per_pixel = 4;
  unsigned int vram_size = vbe_info.XResolution * vbe_info.YResolution * bytes_per_pixel;

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    panic("couldn't map video memory.\n");
    return VG_INIT_FAILED;
  }

  if (set_video_mode(mode) != SUCCESS) {
    printf("vg_init failed.\n");
    return VG_INIT_FAILED;
  }

  h_res = vbe_info.XResolution;
  v_res = vbe_info.YResolution;
  bits_per_pixel = vbe_info.BitsPerPixel;

  buffer = (char *) malloc(vram_size);
  if (buffer == NULL)
    return VG_INIT_FAILED;

  return video_mem;
}
