#include <pebble.h>

#include "flashcard_selector.h"

static Window *main_window;


static void on_deck_selected(void *ctx, flashcard_deck_t *deck) {

}

void init() {

    flashcard_selector_show(on_deck_selected);
}

void deinit() {
    // Destroy the Window
    flashcard_selector_close();
}

int main() {
  // Initialize the app
  init();

  // Wait for app events
  app_event_loop();

  // Deinitialize the app
  deinit();

  // App finished without error
  return 0;
}
