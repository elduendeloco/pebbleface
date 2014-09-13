#include "two_layer.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_font_14;
static GFont s_res_font_34;
static TextLayer *typelayer_1;
static TextLayer *unitlayer_1;
static TextLayer *typelayer_2;
static TextLayer *unitlayer_2;
static TextLayer *datalayer_2;
static InverterLayer *s_inverterlayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_font_14 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_14));
  s_res_font_34 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_34));
  // typelayer_1
  typelayer_1 = text_layer_create(GRect(0, 0, 144, 19));
  text_layer_set_background_color(typelayer_1, GColorBlack);
  text_layer_set_text_color(typelayer_1, GColorWhite);
  text_layer_set_text(typelayer_1, "Speed");
  text_layer_set_font(typelayer_1, s_res_font_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)typelayer_1);
  
  // unitlayer_1
  unitlayer_1 = text_layer_create(GRect(0, 64, 144, 19));
  text_layer_set_background_color(unitlayer_1, GColorBlack);
  text_layer_set_text_color(unitlayer_1, GColorWhite);
  text_layer_set_text(unitlayer_1, "knt");
  text_layer_set_font(unitlayer_1, s_res_font_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)unitlayer_1);
  
  // typelayer_2
  typelayer_2 = text_layer_create(GRect(0, 85, 144, 19));
  text_layer_set_background_color(typelayer_2, GColorBlack);
  text_layer_set_text_color(typelayer_2, GColorWhite);
  text_layer_set_text(typelayer_2, "Wind Angle");
  text_layer_set_text_alignment(typelayer_2, GTextAlignmentRight);
  text_layer_set_font(typelayer_2, s_res_font_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)typelayer_2);
  
  // unitlayer_2
  unitlayer_2 = text_layer_create(GRect(0, 149, 144, 19));
  text_layer_set_background_color(unitlayer_2, GColorBlack);
  text_layer_set_text_color(unitlayer_2, GColorWhite);
  text_layer_set_text(unitlayer_2, "Degrees");
  text_layer_set_text_alignment(unitlayer_2, GTextAlignmentRight);
  text_layer_set_font(unitlayer_2, s_res_font_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)unitlayer_2);
  
  // datalayer_2
  datalayer_2 = text_layer_create(GRect(0, 106, 144, 40));
  text_layer_set_background_color(datalayer_2, GColorBlack);
  text_layer_set_text_color(datalayer_2, GColorWhite);
  text_layer_set_text(datalayer_2, "365");
  text_layer_set_text_alignment(datalayer_2, GTextAlignmentCenter);
  text_layer_set_font(datalayer_2, s_res_font_34);
  layer_add_child(window_get_root_layer(s_window), (Layer *)datalayer_2);
  
  // s_inverterlayer_1
  s_inverterlayer_1 = inverter_layer_create(GRect(0, 82, 144, 2));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(typelayer_1);
  text_layer_destroy(unitlayer_1);
  text_layer_destroy(typelayer_2);
  text_layer_destroy(unitlayer_2);
  text_layer_destroy(datalayer_2);
  inverter_layer_destroy(s_inverterlayer_1);
  fonts_unload_custom_font(s_res_font_14);
  fonts_unload_custom_font(s_res_font_34);
}
// END AUTO-GENERATED UI CODE
void set_layer_contents(int layer, char *type, char *data, char *unit)
{
	if (layer==1)
	{
		text_layer_set_text(typelayer_1, type);
		text_layer_set_text(datalayer_1, data);
		text_layer_set_text(unitlayer_1, unit);
	
	}
	else
	{
		text_layer_set_text(typelayer_2, type);
		text_layer_set_text(datalayer_2, data);
		text_layer_set_text(unitlayer_2, unit);
	}
}	

void update_data(int layer, char *data)
{
	if 	(layer=1)
		text_layer_set_text(datalayer_1, data);
	else
		text_layer_set_text(datalayer_2, data);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_two_layers(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_two_layers(void) {
  window_stack_remove(s_window, true);
}
