// graphics API

#define SCREEN_WIDTH  768 
#define SCREEN_HEIGHT 480

typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct {
    char b;
    char g;
    char r;
    char a;
} color_t;

typedef struct {
    short int x;
    short int y;
} point_t;

typedef struct {
  short int x;
  short int y;
  short int width;
  short int height;
} rect_t;

// bitmap structure
struct bitmap_s {
  short int width;
  short int height;
  WORD bpl;
  WORD type;
  DWORD dataAddr;
  DWORD magic;
  int dw4;
  void* p_some;
  rect_t valid_rect;
};

// graphic context impl

struct gc_impl {
    color_t current_color;
    DWORD dw1;
    struct bitmap_s* bitmap; // canvas pointer
    rect_t* p_draw_region;
    int orientation;
    void (*convert_color_to_format)(color_t);
    void (*draw_vertical_line)(struct gc_impl *, int, int, int);
    void (*draw_horizontal_line)(struct gc_impl *, int, int, int);
    void (*setup_draw_roi)(struct gc_impl *, rect_t *);
    void (*draw_point)(struct gc_impl *, point_t point);
    void (*draw_line)(struct gc_impl *, point_t, point_t);
    void (*draw_rectangle)(struct gc_impl *, rect_t *);
    void (*draw_fill_rect)(struct gc_impl *, rect_t *);
    void (*draw_ellipse)(struct gc_impl *, rect_t *);
    void (*draw_fill_ellipse)(struct gc_impl *, rect_t *);
    void (*draw_polygon)(struct gc_impl *, point_t * point_list, int);
    void (*draw_polygon_fixed_point)(struct gc_impl *, point_t * point_list, int);
    void (*pfunc17)(void); // unknown usage
    void (*draw_bitmap)(struct gc_impl *, point_t, point_t, struct bitmap_s* p_bitmap, int, int);
    void (*draw_blend)(struct gc_impl *,  point_t pos, struct bitmap_s* p_bitmap1, point_t, point_t, int, struct bitmap_s* p_bitmap2, point_t, point_t, int);
    void (*draw_perspective)(void);
};

// graphic context structure

struct gc_s {
    struct gc_impl *impl;
    DWORD font;
    point_t pos;
    short int width;
    short int height;
    DWORD dw4;
    void* p_list_rois;
    DWORD dw6;
    rect_t clip_rect;
    rect_t draw_rect_prob;
    point_t point_2;
    void* p_list_saved_states;
};

color_t set_color(char r, char g, char b, char a) {
    color_t clr = {b, g, r, a};
    return clr;
}






