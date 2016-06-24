#pragma once

#include <pebble.h>
#include "flashcard_deck.h"

typedef struct flashcard_selector_context_t {
    void (*on_deck_selected)(void *ctx, flashcard_deck_t *deck);
} flashcard_selector_context_t;

void flashcard_selector_close();
void flashcard_selector_show(void (*on_selected)(void *ctx, flashcard_deck_t *selected_deck));

