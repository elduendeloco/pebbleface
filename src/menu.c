
//
//  menu.c
//  sail
//
//  Created by Francesco Di Carlo on 15/06/14.
//  Copyright (c) 2014 francescodicarlo. All rights reserved.
//

#include "pebble.h"
#include "sail.h"
#define NUM_MENU_SECTIONS 2
#define NUM_FIRST_MENU_ITEMS 6
#define NUM_SECOND_MENU_ITEMS 1

static Window *menu;

// This is a simple menu layer
static SimpleMenuLayer *menu_layer;

// A simple menu layer can have multiple sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

// Each section is composed of a number of menu items
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];
static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];


// You can capture when the user selects a menu icon with a menu item select callback
static void menu_select_callback(int index, void *ctx) {
    // Mark the layer to be updated
    int old_index=get_option_value();
    set_option_value(index);
    // Here we just change the subtitle to a literal string
    first_menu_items[old_index].subtitle = NULL;
    first_menu_items[index].subtitle = "Selected";
    layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// You can capture when the user selects a menu icon with a menu item select callback
static void menu_rows_callback(int index, void *ctx) {
    
    if (get_rows_value()==1) {
        second_menu_items[0].subtitle = "2 rows displaing";
        set_rows_value(2);
    }
    else {
        second_menu_items[0].subtitle = "1 row displaing";
        set_rows_value(1);
    }
    
    layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// This initializes the menu upon window load
static void window_load(Window *window) {
    
    // Although we already defined NUM_MENU_ITEMS, you can define
    // an int as such to easily change the order of menu items later
    
    //_________________FIRST MENU__________________________________
    
    // This is an example of how you'd set a simple menu item
    first_menu_items[0] = (SimpleMenuItem){
        // You should give each menu item a title and callback
        .title = "SPEED",
        .callback = menu_select_callback
    };
    // The menu items appear in the order saved in the menu items array
    first_menu_items[1] = (SimpleMenuItem){
        .title = "WIND",
        // You can also give menu items a subtitle
        //.subtitle = "Here's a subtitle",
        .callback = menu_select_callback
    };
    first_menu_items[2] = (SimpleMenuItem){
        .title = "HEADING",
        //.subtitle = "This has an icon",
        .callback = menu_select_callback
        // This is how you would give a menu item an icon
        //.icon = menu_icon_image,
    };
    first_menu_items[3] = (SimpleMenuItem){
        .title = "NAVIGATE",
        //.subtitle = "This has an icon",
        .callback = menu_select_callback
        // This is how you would give a menu item an icon
        //.icon = menu_icon_image,
    };
    first_menu_items[4] = (SimpleMenuItem){
        .title = "ENVIRONMENT",
        //.subtitle = "This has an icon",
        .callback = menu_select_callback
        // This is how you would give a menu item an icon
        //.icon = menu_icon_image,
    };
    first_menu_items[5] = (SimpleMenuItem){
        .title = "DEPTH",
        //.subtitle = "This has an icon",
        .callback = menu_select_callback
        // This is how you would give a menu item an icon
        //.icon = menu_icon_image,
    };
    first_menu_items[5] = (SimpleMenuItem){
        .title = "COUNTDOWN",
        //.subtitle = "This has an icon",
        .callback = menu_select_callback
        // This is how you would give a menu item an icon
        //.icon = menu_icon_image,
    };
    
    
    first_menu_items[get_option_value()].subtitle = "Selected";
    
    // Bind the menu items to the corresponding menu sections
    menu_sections[0]= (SimpleMenuSection){
        .title = "Chapter",
        .num_items = NUM_FIRST_MENU_ITEMS,
        .items = first_menu_items,
    };
    
    // __________________SECOND MENU______________________________
    
    second_menu_items[0] = (SimpleMenuItem){
        .title = "ROWS",
        .callback = menu_rows_callback
    };
    
    if (get_rows_value()==1) {
        second_menu_items[0].subtitle = "1 row displaing";
    }
    else {
        second_menu_items[0].subtitle = "2 rows displaing";
    }
    
    // Bind the menu items to the corresponding menu sections
    menu_sections[1]= (SimpleMenuSection){
        .title = "Layout",
        .num_items = NUM_SECOND_MENU_ITEMS,
        .items = second_menu_items
    };
    
    
    // Now we prepare to initialize the simple menu layer
    // We need the bounds to specify the simple menu layer's viewport size
    // In this case, it'll be the same as the window's
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);
    
    // Initialize the simple menu layer
    menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
    
    // Add it to the window for display
    layer_add_child(window_layer, simple_menu_layer_get_layer(menu_layer));
}

// Deinitialize resources on window unload that were initialized on window load
void window_unload(Window *window) {
    simple_menu_layer_destroy(menu_layer);
}

void menu_creator()
{
    menu = window_create();
    
    // Setup the window handlers
    window_set_window_handlers(menu, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload
    });
    
    window_stack_push(menu, true /* Animated */);
    
    
}

void menu_destroier()
{
    window_destroy(menu);
}
