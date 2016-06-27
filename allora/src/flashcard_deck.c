
#include "flashcard_deck.h"

#include <pebble.h>
#include <stdlib.h>

static Window *flashcard_deck_window;
static Layer *flashcard_layer;

static char *scale[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
static uint8_t background_colors[12] = {
  0b11110000,  // C
  0b11010000,  // C#
  0b11111000,  // D
  0b11010100,  // D#
  0b11111100,  // E
  0b11101100,  // F
  0b11000100,  // F#
  0b11001010,  // G
  0b11000101,  // G#
  0b11010110,  // A
  0b11010001,  // A#
  0b11110011   // B
};

static uint8_t counter = 0;

static void draw_tone_flashcard_front(uint8_t tone_key, GContext *ctx, GRect bounds) {
    GSize s = bounds.size;
    GPoint p = {.x = (s.w >> 1), .y = (s.h >> 1)};
    graphics_context_set_fill_color(ctx, (GColor) background_colors[tone_key]);
    graphics_fill_circle(ctx, p, (s.w >> 2));
    graphics_context_set_text_color(ctx, (GColor) GColorRedARGB8);
    graphics_draw_text(ctx, scale[tone_key], fonts_get_system_font(FONT_KEY_GOTHIC_24), bounds, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);    
}

static void draw_flashcard_front(flashcard_t *flashcard, GContext *ctx, GRect bounds) {
  
}

static void draw_flashcard_back(flashcard_t *flashcard, GContext *ctx, GRect bounds) {
    GPoint p = {.x = 40, .y = 30};
    graphics_fill_circle(ctx, p, 10);
}

static void draw_flashcard_front_layer(struct Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);
    draw_tone_flashcard_front(counter, ctx, bounds);
}

static void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {

}

static void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    counter = (counter + 1 < 12)? counter + 1 : 0;
    layer_mark_dirty(flashcard_layer);
}

static void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    counter = (counter > 0)? counter - 1 : 11;
    layer_mark_dirty(flashcard_layer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
}

static void window_load(Window *window) {
    window_set_click_config_provider(window, click_config_provider);
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

