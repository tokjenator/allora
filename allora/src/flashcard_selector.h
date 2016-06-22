#pragma once

#include <pebble.h>
#include "flashcard_deck.h"

void flashcard_selector_show(Window *window, void (*on_selected)(flashcard_deck_t *selected_deck));

