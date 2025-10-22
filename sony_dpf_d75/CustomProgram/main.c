//

#include "sys.h"


#define THREAD_STACK_SIZE 0x1000

// our thread structure
char pThread_structure[TX_THREAD_STRUCTURE_SIZE];

int quit_game = 0;

// 0x80141C18

// game snake

#define BLOCK_SIZE 32
#define FIELD_H (SCREEN_HEIGHT / BLOCK_SIZE)
#define FIELD_W (SCREEN_WIDTH / BLOCK_SIZE)

#define SNAKE_EMPTY 0
#define SNAKE_BODY  1
#define SNAKE_HEAD  2
#define SNAKE_FOOD  3

// crnd
#define RND_A 7141
#define RND_C 54773
#define RND_M 259200

#define MAX_SNAKE_LEN 256

char* field_p = 0;

int prev_snake_dir = 3; // start moving right
unsigned int g_rnd_val;

color_t snake_colors[4];

// snake data
point_t* snake = 0;
int snake_len = 0;

void field_set(int x, int y, char v) {
    field_p[y * FIELD_W + x] = v;
}
char field_get(int x, int y) {
    return field_p[y * FIELD_W + x];
}

void Rnd_init(UINT seed)
{
    unsigned int r_seed = (seed & 3);
    unsigned int b_seed = ((seed << 17) & 3);
    seed ^= (r_seed >> 17);
    seed ^= b_seed;
    g_rnd_val = seed;
}
// linear congruental generator, most simple rnd generator
unsigned int rand() {
    g_rnd_val = (RND_A * g_rnd_val + RND_C);
    return g_rnd_val;
}

void spawn_food() {
    while (1) {
        int x = rand() % FIELD_W;
        int y = rand() % FIELD_H;
        if (field_get(x, y) == SNAKE_EMPTY) {
            field_set(x, y, SNAKE_FOOD);
            return;
        }
    }
}



void snake_init() {
    snake_len = 3;
    int start_x = FIELD_W / 2;
    int start_y = FIELD_H / 2;

    for(int i = 0; i < snake_len; i++) {
        snake[i] = (point_t){start_x - i, start_y};
        field_set(start_x - i, start_y, (i == 0) ? SNAKE_HEAD : SNAKE_BODY);
    }
}

void game_init() {

    field_p = malloc(FIELD_H * FIELD_W);

    if(!field_p) {
        con_printf("malloc field error!\n");
        return;
    }

    memset(field_p, 0, FIELD_H * FIELD_W);

    snake = malloc(MAX_SNAKE_LEN * sizeof(point_t));

    if(!snake) {
        con_printf("malloc snake error!\n");
        return;
    }

    memset(snake, 0, MAX_SNAKE_LEN * sizeof(point_t));


    snake_init();

    UINT tickval = current_tick();
    Rnd_init(tickval);

    snake_colors[SNAKE_BODY] = set_color(0, 200, 0, 0);
    snake_colors[SNAKE_HEAD] = set_color(200, 0, 0, 0);
    snake_colors[SNAKE_FOOD] = set_color(150, 150, 0, 0);

    spawn_food();
}

void game_render(struct gc_s* gc) {

    point_t pos;

    for (int y = 0; y < FIELD_H; y++) {
        for (int x = 0; x < FIELD_W; x++) {

            int cell = field_get(x, y);
            if (cell != SNAKE_EMPTY) {
                gc_set_color(gc, snake_colors[cell]);
                pos.x = x * BLOCK_SIZE;
                pos.y = y * BLOCK_SIZE;
                draw_fill_rect(gc, pos, (point_t){BLOCK_SIZE, BLOCK_SIZE});
            }
        }
    }
}

void game_tick(int key) {

    int snake_direction = prev_snake_dir; // 0 up , 1 down, 2 left, 3 right

    //con_printf("key = %d\n", key);
    if (key <= 0x104 && key >= 0x101) {
        snake_direction = key - 0x101;
        snake_direction &= 3;
        //con_printf("snake_direction = %d\n", snake_direction);
    }

    //player chose contr direction?
    if(prev_snake_dir == 0 && snake_direction == 1) {
        snake_direction = 0;
    }else if (prev_snake_dir == 1 && snake_direction == 0) {
        snake_direction = 1;
    }else if (prev_snake_dir == 2 && snake_direction == 3) {
        snake_direction = 2;
    }else if (prev_snake_dir == 3 && snake_direction == 2) {
        snake_direction = 3;
    }

   

    // compute new head
    point_t head = snake[0];
    switch (snake_direction) {
        case 0: head.y--; break;
        case 1: head.y++; break;
        case 2: head.x--; break;
        case 3: head.x++; break;
    }

    // 
    if (head.x < 0) head.x = FIELD_W - 1;
    if (head.x >= FIELD_W) head.x = 0;
    if (head.y < 0) head.y = FIELD_H - 1;
    if (head.y >= FIELD_H) head.y = 0;

    char hit = field_get(head.x, head.y);

    // collision with self = game over (still valid)
    if (hit == SNAKE_BODY) {
        return; // stop movement or later restart logic
    }

    // move tail (unless food)
    if (hit != SNAKE_FOOD) {
        point_t tail = snake[snake_len - 1];
        field_set(tail.x, tail.y, SNAKE_EMPTY);
        for (int i = snake_len - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
    } else {
        // food = grow
        if (snake_len < MAX_SNAKE_LEN) snake_len++;
        for (int i = snake_len - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        spawn_food();
    }

    prev_snake_dir = snake_direction;

    // place new head
    snake[0] = head;
    field_set(head.x, head.y, SNAKE_HEAD);

    // update previous head to body
    field_set(snake[1].x, snake[1].y, SNAKE_BODY);
}

int get_key() {
    //con_printf("called get_key()\n");

    if(key_read_key(0) == KEY_POWER) {
        return KEY_POWER;
    }

    if(key_read_key(1) != KEY_NONE) {
        con_printf("key 1\n"); // not found that button
    }

    if(key_read_key(2) == KEY_VIEWMODE) {
        return KEY_VIEWMODE;
    }

    int adc_key = key_read_adc(0);
    if(adc_key != KEY_NONE) {
        return adc_key;
    }

    adc_key = key_read_adc(1);
    if(adc_key != KEY_NONE) {
        return adc_key;
    }

    return KEY_NONE;
}

void main_game_thread(UINT start_v) {

    game_init();

    // need to call these function before any drawing
    ((void (*)(void))0x80058910UL)();
    ((void (*)(void))0x800589B4UL)();

    while (!quit_game)
    {
        


        struct bitmap_s* p_bitmap = get_osd_bitmap();

        if(!p_bitmap)
            con_printf("Can't get bitmap!\n");

        struct gc_s* gc = gc_create_from_bitmap(p_bitmap);

        if (!gc) 
            con_printf("Can't create gc!\n");

        // draw here
        draw_clear(gc, set_color(255, 255, 255, 128));

        game_render(gc);

        int key = get_key();
        game_tick(key);

        gc_destroy(gc);

        tx_thread_sleep(200);
    }
    
    return;
}


int main(void) {
    con_printf("Start of our code\n");

    // just for fun delete main gui thread 
    UINT status = tx_thread_suspend(gui_thread_p);

    con_printf("tx_thread_suspend status = %d\n", status);

    void* stack_p = malloc(THREAD_STACK_SIZE);

    tx_thread_create(pThread_structure, "Game", main_game_thread, 0, stack_p, THREAD_STACK_SIZE, 12, 12, 0, 1);

    return 0;
}


