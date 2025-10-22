// Definition of system function already present in firmware
// Can probably contain some typos in addresses.


#define TX_THREAD_STRUCTURE_SIZE 167

#define KEY_POWER 0x109
#define KEY_VIEWMODE 0x127
#define KEY_UP 0x101
#define KEY_DOWN 0x102
#define KEY_LEFT 0x103
#define KEY_RIGHT 0x104
#define KEY_CENTRE 0x105
#define KEY_BACK 0x106
#define KEY_MENU 0x107
#define KEY_NONE 0x4FF

typedef unsigned int UINT;

static void* gui_thread_p = (void*)0x802478D0UL;

// print to UART
static int (*con_printf)(const char* fmt, ...) = (int (*)(const char*, ...))0x801B91FCUL;

// sprintf
static int (*sprintf)(char* dst, const char* fmt, ...) = (int (*)(char*, const char*, ...))0x801B9070UL;

// memory operation functions
static int (*memcpy)(void* dst, void* src, UINT len) = (int (*)(void*, void*, UINT))0x801C1B40UL;
static int (*memset)(void* dst, char val, UINT len) = (int (*)(void*, char, UINT))0x801F7FB0UL;
static void* (*malloc)(UINT sz) = (void* (*)(UINT))0x801ED62CUL;
static void (*free)(void* ptr) = (void (*)(void*))0x801ED1F0UL;

// keys
// key(0) is power key
// key(2) is viewmode key
static int (*key_read_key)(int n) = (int (*)(int))0x8001ADF4UL;
static int (*key_read_adc)(int group) = (int (*)(int))0x8001AD18UL;


// ThreadX functions
// tx_thread_create
static UINT (*tx_thread_create)(void* thread_ptr, char* name_ptr, void (*entry)(UINT), \
    UINT entry_input, void* stack_start, UINT stack_size, UINT priority, \
    UINT preempt_threshold, UINT time_slice, UINT auto_start) = 0x801BB96CUL;

// tx_thread_delete
static UINT (*tx_thread_delete)(void* thread_ptr) = (UINT (*)(void*))0x801BC2BCUL;
// tx_thread_suspend
static UINT (*tx_thread_suspend)(void* thread_ptr) = (UINT (*)(void*))0x801BB7B8UL;
// tx_thread_sleep
static UINT (*tx_thread_sleep)(UINT milliseconds) = (UINT (*)(UINT))0x80198E0CUL;

static UINT (*current_tick)(void) = (UINT (*)(void))0x801BCB0CUL;

// graphics
#include "gfx.h"

// create gc from bitmap
static struct gc_s* (*gc_create_from_bitmap)(struct bitmap_s* p_bitmap) = (struct gc_s* (*)(struct bitmap_s*))0x800423A0UL;

// destroy gc
static void (*gc_destroy)(struct gc_s* gc) = (void (*)(struct gc_s*))0x8004251CUL;

// translate draw region
static void (*gc_translate)(struct gc_s *gc, WORD dx, WORD dy) = (void (*)(struct gc_s*, WORD, WORD))0x8004267CUL;

// save gc state
static void (*gc_save_state)(struct gc_s *gc) = (void (*)(struct gc_s*))0x800426C4UL;
// restore gc state
static void (*gc_restore_state)(struct gc_s *gc) = (void (*)(struct gc_s*))0x8004275CUL;

static void (*gc_set_color)(struct gc_s* gc, color_t color) = \
                    (void (*)(struct gc_s*, color_t))0x80042588UL;

static void (*draw_clear)(struct gc_s* gc, color_t color) = \
                    (void (*)(struct gc_s*, color_t))0x80042DF4UL;

static void (*draw_line)(struct gc_s* gc, point_t p1, point_t p2) = \
                (void (*)(struct gc_s*, point_t, point_t))0x80042978UL;

static void (*draw_rectangle)(struct gc_s* gc, point_t pos, point_t sizes) = \
                        (void (*)(struct gc_s*, point_t, point_t))0x80042BBCUL;

static void (*draw_fill_rect)(struct gc_s *gc, point_t pos, point_t sizes) = \
                        (void (*)(struct gc_s*, point_t, point_t))0x80042CD8UL;

static void (*draw_ellipse)(struct gc_s* gc, point_t pos, point_t sizes) =   \
                        (void (*)(struct gc_s*, point_t, point_t))0x80042E68UL;

static void (*draw_fill_ellipse)(struct gc_s* gc, point_t pos, point_t sizes) = \
                        (void (*)(struct gc_s*, point_t, point_t))0x80042F84UL;

// draw polygon using lines
static void (*draw_polygon)(struct gc_s* gc, point_t* points, int cnt) = \
                        (void (*)(struct gc_s*, point_t*, int))0x80044444UL;

static void (*draw_fill_polygon)(struct gc_s* gc, point_t* points, int cnt) = \
                        (void (*)(struct gc_s*, point_t*, int))0x80044510UL;

// set amt to -1 for automatic symbol count
static void (*draw_text)(struct gc_s* gc, WORD x, WORD y, char* text, int amt) = \
 (void (*)(struct gc_s*, WORD, WORD, char*, int))0x80043B88UL;

static void (*draw_bitmap)(struct gc_s* gc, point_t loc, point_t sizes, \
          struct bitmap_s* p_bitmap, point_t second_loc, point_t second_sizes) = 0x800431B8UL;

// display stuff prob

static struct bitmap_s* (*get_osd_bitmap)(void) = (struct bitmap_s* (*)(void))0x80015A6CUL;
static struct bitmap_s* (*get_yuv_bitmap)(void) = (struct bitmap_s* (*)(void))0x800158B4UL;










