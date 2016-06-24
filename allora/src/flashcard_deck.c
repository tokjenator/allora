
#include "flashcard_deck.h"

#include <pebble.h>
#include <stdlib.h>

static Window *flashcard_deck_window;
static Layer *flashcard_layer;

static char *scale[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

static void draw_flashcard_front(flashcard_t *flashcard, GContext *ctx, GRect bounds) {
    GSize s = bounds.size;
    GPoint p = {.x = (s.w >> 1), .y = (s.h >> 1)};
    graphics_fill_circle(ctx, p, (s.w >> 2));
    //graphics_context_set_text_color(ctx, (GColor) GColorWhiteARGB8);
    //graphics_draw_text(ctx, scale[2], NULL, bounds, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}

static void draw_flashcard_back(flashcard_t *flashcard, GContext *ctx, GRect bounds) {
    GPoint p = {.x = 40, .y = 30};
    graphics_fill_circle(ctx, p, 10);
}

static void draw_flashcard_front_layer(struct Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);
    draw_flashcard_front(NULL, ctx, bounds);
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    flashcard_layer = layer_create(bounds);

    layer_set_update_proc(flashcard_layer, (LayerUpdateProc) draw_flashcard_front_layer);
    layer_add_child(window_layer, flashcard_layer);
}

static void window_unload(Window *window) {
    //menu_layer_destroy(menu_layer);
}

void flashcard_deck_close() {
    window_destroy(flashcard_deck_window);
}

void flashcard_deck_draw_card(flashcard_deck_t *deck) {
    if(flashcard_deck_window == NULL) {
        flashcard_deck_window = window_create();
        window_set_window_handlers(flashcard_deck_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload
        });
    }

    window_stack_push(flashcard_deck_window, true);
}

