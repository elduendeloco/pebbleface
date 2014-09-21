
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *one_window;
static GFont s_res_roboto_condensed_21;
static GFont s_res_font_48;
static TextLayer *typelayer;
static TextLayer *unitlayer;
static TextLayer *datalayer;

static void initialise_ui(void) {
  one_window = window_create();
  window_set_background_color(one_window, GColorBlack);
  window_set_fullscreen(one_window, true);
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_font_48 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_48));
  // typelayer
  typelayer = text_layer_create(GRect(2, 0, 142, 28));
  text_layer_set_background_color(typelayer, GColorBlack);
  text_layer_set_text_color(typelayer, GColorWhite);
  text_layer_set_text(typelayer, "...");
  text_layer_set_font(typelayer, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(one_window), (Layer *)typelayer);
  
  // unitlayer
  unitlayer = text_layer_create(GRect(2, 140, 144, 28));
  text_layer_set_background_color(unitlayer, GColorBlack);
  text_layer_set_text_color(unitlayer, GColorWhite);
  text_layer_set_text(unitlayer, "...");
  text_layer_set_font(unitlayer, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(one_window), (Layer *)unitlayer);
  
  // datalayer
  datalayer = text_layer_create(GRect(0, 55, 144, 56));
  text_layer_set_background_color(datalayer, GColorBlack);
  text_layer_set_text_color(datalayer, GColorWhite);
  text_layer_set_text(datalayer, "...");
  text_layer_set_text_alignment(datalayer, GTextAlignmentCenter);
  text_layer_set_font(datalayer, s_res_font_48);
  layer_add_child(window_get_root_layer(one_window), (Layer *)datalayer);
}

static void destroy_ui(void) {
  window_destroy(one_window);
  text_layer_destroy(typelayer);
  text_layer_destroy(unitlayer);
  text_layer_destroy(datalayer);
  fonts_unload_custom_font(s_res_font_48);
}
// END AUTO-GENERATED UI CODE

void set_layer_contents(char *type, char *data, char *unit)
{
	text_layer_set_text(typelayer, type);
	text_layer_set_text(datalayer, data);
	text_layer_set_text(unitlayer, unit);
}	

void update_data(char *data)
{
	text_layer_set_text(datalayer, data);
}


static void handle_window_unload(Window* window) {
  destroy_ui();
}

Window *show_one_layer(void) {
    initialise_ui();
    window_set_window_handlers(one_window, (WindowHandlers) {
    .unload = handle_window_unload,
    });
    window_stack_push(one_window, true);
	return one_window;
}

void hide_one_layer(void) {
    window_stack_remove(one_window, true);
}
