#pragma once

#include <inttypes.h>

typedef struct flashcard_t {

} flashcard_t;

typedef struct flashcard_deck_t {
    uint32_t id;
    uint16_t num_cards;
} flashcard_deck_t;

void flashcard_deck_draw_card(flashcard_deck_t *deck);

