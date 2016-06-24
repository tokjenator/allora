
#include "flashcard_selector.h"
#include <pebble.h>
#include <inttypes.h>

static Window *flashcard_selector_window;
static MenuLayer *menu_layer;

// Ugly, pragmatic temporary solution for storing flashcard deck selected callback
static void (*on_deck_selected)(void *ctx, flashcard_deck_t *deck);

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
    return 2;
}

static void draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
    switch(cell_index->row) {
    case 0:
        menu_cell_basic_draw(ctx, cell_layer, "Circle of Fifths next", NULL, NULL);
        break;
    case 1:
        menu_cell_basic_draw(ctx, cell_layer, "Circle of Fifths previous", NULL, NULL);
        break;
    default:
        break;
    }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
    return 18;
}

static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
    if(on_deck_selected != NULL) {
        on_deck_selected(NULL, NULL);
    }
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    menu_layer = menu_layer_create(bounds);
    menu_layer_set_click_config_onto_window(menu_layer, window);
#if defined(PBL_COLOR)
    menu_layer_set_normal_colors(menu_layer, GColorBlack, GColorWhite);
    menu_layer_set_highlight_colors(menu_layer, GColorRed, GColorWhite);
#endif
    menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
        .get_num_rows = get_num_rows_callback,
        .draw_row = draw_row_callback,
        .get_cell_height = get_cell_height_callback,
        .select_click = select_callback
    });
    layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

static void window_unload(Window *window) {
    //menu_layer_destroy(menu_layer);
}

void flashcard_selector_close() {
    window_destroy(flashcard_selector_window);
}

void flashcard_selector_show(void (*on_selected)(void *ctx, flashcard_deck_t *selected_deck)) {
    on_deck_selected = on_selected;
    if(flashcard_selector_window == NULL) {
        flashcard_selector_window = window_create();
        window_set_window_handlers(flashcard_selector_window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload
        });
    }

    window_stack_push(flashcard_selector_window, true);
}

