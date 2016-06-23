#pragma once

#include <pebble.h>
#include "flashcard_deck.h"


void flashcard_selector_close();
void flashcard_selector_show(void (*on_selected)(void *ctx, flashcard_deck_t *selected_deck));

