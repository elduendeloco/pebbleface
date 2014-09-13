#include <pebble.h>
#include "menu.h"
#include "sail.h"

enum {
		STATUS,
    TEXT1,
    DATA1,
    UNIT1,
    TEXT2,
    DATA2,
    UNIT2
};


static Window *window;
static Layer *window_layer;

static int option=0;
static int rows=2;

static TextLayer *textField1;
static TextLayer *textField2;

static TextLayer *dataField1;
static TextLayer *dataField2;

static TextLayer *unitField1;
static TextLayer *unitField2;

//static GBitmap *icons   =   NULL;

static GFont font_small;
static GFont font_medium;
static GFont font_large;

static BitmapLayer *background_layer;

static GBitmap *background= NULL;

static GFont font_xsmall;
static GFont font_small;
static GFont font_medium;
static GFont font_large;

static AppSync aSync;
static uint8_t sync_buffer[64];

static const uint32_t INBOUND_SIZE = 128; // Inbound app message size
static const uint32_t OUTBOUND_SIZE = 128; // Outbound app message size

char *selectText(int value)
{
    switch (option) {
        case 0:
            if (value<length[option])
                return speedTexts[value];
            break;
        case 1:
            if (value<length[option])
                return windTexts[value];
            break;
        case 2:
            if (value<length[option])
                return headingTexts[value];
            break;
        case 3:
            if (value<length[option])
                return navigateTexts[value];
            break;
        case 4:
            if (value<length[option])
                return environmentTexts[value];
            break;
        case 5:
            if (value<length[option])
                return depthTexts[value];
            break;
            
        default:
            break;
    }
    return "Error";
}



static void changeWithAnimation()
{
    text_layer_set_text(textField1, selectText(first));
    text_layer_set_text(textField2, selectText(second));
}


/**
 * Richiede all'applicazione sul telefono le informazioni.
 */
void layout_config()
{
    
    if (rows==2) {
				text_layer_destroy(dataField1);
        text_layer_destroy(textField1);
        text_layer_destroy(unitField1);
			
        textField1 = text_layer_create(GRect(0, 0, 144, 24));
        text_layer_set_text_color(textField1, GColorWhite);
        text_layer_set_background_color(textField1, GColorBlack);
        text_layer_set_font(textField1, font_small);
        text_layer_set_text_alignment(textField1, GTextAlignmentLeft);
        text_layer_set_text(textField1, "SOG");

        dataField1 = text_layer_create(GRect(0, 25, 144, 40));
        text_layer_set_text_color(dataField1, GColorWhite);
        text_layer_set_background_color(dataField1, GColorBlack);
        text_layer_set_font(dataField1, font_medium);
        text_layer_set_text_alignment(dataField1, GTextAlignmentCenter);
        text_layer_set_text(dataField1, "N/A");

        unitField1 = text_layer_create(GRect(0, 65, 144, 20));
        text_layer_set_text_color(unitField1, GColorWhite);
        text_layer_set_background_color(unitField1, GColorBlack);
        text_layer_set_font(unitField1, font_small);
        text_layer_set_text_alignment(unitField1, GTextAlignmentLeft);
        text_layer_set_text(unitField1, "SOG");

        textField2 = text_layer_create(GRect(0, 85, 144, 24));
        text_layer_set_text_color(textField2, GColorWhite);
        text_layer_set_background_color(textField2, GColorBlack);
        text_layer_set_font(textField2, font_small);
        text_layer_set_text_alignment(textField2, GTextAlignmentLeft);
        text_layer_set_text(textField2, "SOG");

        dataField2 = text_layer_create(GRect(0, 109, 144, 40));
        text_layer_set_text_color(dataField2, GColorWhite);
        text_layer_set_background_color(dataField2, GColorBlack);
        text_layer_set_font(dataField2, font_medium);
        text_layer_set_text_alignment(dataField2, GTextAlignmentCenter);
        text_layer_set_text(dataField2, "N/A");

        unitField2 = text_layer_create(GRect(0, 148, 144, 20));
        text_layer_set_text_color(unitField2, GColorWhite);
        text_layer_set_background_color(unitField2, GColorBlack);
        text_layer_set_font(unitField2, font_small);
        text_layer_set_text_alignment(unitField2, GTextAlignmentLeft);
        text_layer_set_text(unitField2, "SOG");

        /*
        // ------ Setting up background_layer ------
        background_layer=bitmap_layer_create((GRect) { .origin = { 0, 98 }, .size = { 144, 70} });
        layer_set_bounds(bitmap_layer_get_layer(background_layer), GRect(0, 0, 144, 70));
        //background=gbitmap_create_with_resource(RESOURCE_ID_BACKGROUND);
        bitmap_layer_set_bitmap(background_layer, background);
        bitmap_layer_set_background_color(background_layer, GColorBlack);
        layer_add_child(window2row_layer, bitmap_layer_get_layer(background_layer));
         */
    }
    else if (rows==1)
    {
				text_layer_destroy(dataField1);
        text_layer_destroy(dataField2);
        text_layer_destroy(textField1);
        text_layer_destroy(textField2);
        text_layer_destroy(unitField1);
        text_layer_destroy(unitField2);
				
        textField1 = text_layer_create(GRect(0, 0, 144, 42));
        text_layer_set_text_color(textField1, GColorWhite);
        text_layer_set_background_color(textField1, GColorBlack);
        text_layer_set_font(textField1, font_medium);
        text_layer_set_text_alignment(textField1, GTextAlignmentLeft);
        text_layer_set_text(textField1, "SOG");
        
        dataField1 = text_layer_create(GRect(0, 53, 144, 84));
        text_layer_set_text_color(dataField1, GColorWhite);
        text_layer_set_background_color(dataField1, GColorBlack);
        text_layer_set_font(dataField1, font_large);
        text_layer_set_text_alignment(dataField1, GTextAlignmentCenter);
        text_layer_set_text(dataField1, "N/A");
        
        unitField1 = text_layer_create(GRect(0, 137, 144, 42));
        text_layer_set_text_color(unitField1, GColorWhite);
        text_layer_set_background_color(unitField1, GColorBlack);
        text_layer_set_font(unitField1, font_medium);
        text_layer_set_text_alignment(unitField1, GTextAlignmentLeft);
        text_layer_set_text(unitField1, "SOG");
    }
    changeWithAnimation();
}

void set_option_value (int value)
{
    option= value;
    first=0;
    second=1;
    
}

int get_option_value ()
{
    return option;
}

void set_rows_value (int value)
{
    rows= value;
    layout_config(rows);
    
}


int get_rows_value ()
{
    return rows;
}



void sendCmd() {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    APP_LOG(APP_LOG_LEVEL_INFO, "1");
    dict_write_tuplet(iter, &TupletInteger(1, rows));
    switch(option){
        case 0:
            dict_write_tuplet(iter, &TupletCString(2, speedTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, speedTexts[second] ));
            break;
        case 1:
            dict_write_tuplet(iter, &TupletCString(2, windTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, windTexts[second] ));
            break;
        case 2:
            dict_write_tuplet(iter, &TupletCString(2, headingTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, headingTexts[second] ));
            break;
        case 3:
            dict_write_tuplet(iter, &TupletCString(2, navigateTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, navigateTexts[second] ));
            break;
        case 4:
            dict_write_tuplet(iter, &TupletCString(2, environmentTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, environmentTexts[second] ));
            break;
        case 5:
            dict_write_tuplet(iter, &TupletCString(2, depthTexts[first] ));
            dict_write_tuplet(iter, &TupletCString(3, depthTexts[second] ));
            break;
        default:
            break;
    }
    
    dict_write_end(iter);
	    APP_LOG(APP_LOG_LEVEL_INFO, "1");
    app_message_outbox_send();
    APP_LOG(APP_LOG_LEVEL_INFO, "2");
}

/**
 * Aggiorna i valori del meteo nei layer.
 */




static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    menu_creator();
}

static void two_data_up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if (first==length[get_option_value()]-1 && second==0) {
        first=1;
    }
    else if (first==length[get_option_value()]-1)
    {
        first=0;
    }
    else if (first+1==second)
    {
        if (second==length[get_option_value()]-1) {
            first=0;
        }
        else
            first=first+1;
    }
    
    sendCmd();
    changeWithAnimation();
    APP_LOG(APP_LOG_LEVEL_INFO, "Message sent");
}

static void two_down_click_handler(ClickRecognizerRef recognizer, void *context) {
    if (second==length[get_option_value()]-1 && first==0) {
        second=1;
    }
    else if (second==length[get_option_value()]-1)
    {
        second=0;
    }
    else if (second+1==first)
    {
        if (first==length[get_option_value()]-1) {
            second=0;
        }
        else
            second=second+1;
    }
    
    sendCmd();
    changeWithAnimation();
    APP_LOG(APP_LOG_LEVEL_INFO, "Message sent");
}

static void one_data_up_click_handler(ClickRecognizerRef recognizer, void *context)
{
    if (first==length[get_option_value()]-1)
        first=0;
    else
        first++;
    
    sendCmd();
    changeWithAnimation();
    APP_LOG(APP_LOG_LEVEL_INFO, "Message sent");
}

static void one_down_click_handler(ClickRecognizerRef recognizer, void *context) {
    
    if (first==0)
        first=length[get_option_value()]-1;
    else
        first--;
    
    sendCmd();
    changeWithAnimation();
    APP_LOG(APP_LOG_LEVEL_INFO, "Message sent");
}

static void click_config_provider_two(void *context) {
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_UP, two_data_up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, two_down_click_handler);
}
static void click_config_provider_one(void *context) {
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_UP, one_data_up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, one_down_click_handler);
}

void in_dropped_handler(AppMessageResult reason, void *context)
{
    APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped: %s", (char*)reason);
}


void in_receivede_handler(DictionaryIterator *received, void *context)
{
    char *status=(char*)dict_find(received, STATUS)->value;
    
    if(status!=NULL)
    {
    	APP_LOG(APP_LOG_LEVEL_INFO, "status ok");
    	if(strcmp(status, "one") == 0)
    	{
					text_layer_set_text(dataField1, dict_find(received, TEXT1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, DATA1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, UNIT1)->value->cstring);	
    	}
        
    	else if(strcmp(status, "two") == 0) {
            
        	APP_LOG(APP_LOG_LEVEL_INFO, "Recieved status \"Two Row\"");
            
        	// Copia i dati ricevuti nel messaggio nei buffer opportuni.
					text_layer_set_text(dataField1, dict_find(received, TEXT1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, DATA1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, UNIT1)->value->cstring);	
					text_layer_set_text(dataField1, dict_find(received, TEXT1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, DATA1)->value->cstring);
					text_layer_set_text(dataField1, dict_find(received, UNIT1)->value->cstring);	
    	}
        
    	else {
        	APP_LOG(APP_LOG_LEVEL_INFO, "Status Error");
    	}
	}
	else
	{
        APP_LOG(APP_LOG_LEVEL_INFO, "datas error");
	}
}




// Ricevuta di consegna avvenuta.
void out_send_handler (DictionaryIterator *sent, void *context)
{
    APP_LOG(APP_LOG_LEVEL_INFO, "Message sent");
    changeWithAnimation();
}

// ricevuta di consegna fallita.
void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context)
{
    APP_LOG(APP_LOG_LEVEL_INFO, "Failed to send message: %s", (char*)reason);
}




static void window_load(Window *window) {
    window_layer = window_get_root_layer(window);
    
    
    font_small = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_20));
    font_medium	= fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_28));
    font_large = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_48));
    
    APP_LOG(APP_LOG_LEVEL_INFO, "---> LOADING....");
    layout_config();
    
    layer_add_child(window_layer, text_layer_get_layer(textField1));
    layer_add_child(window_layer, text_layer_get_layer(dataField1));
    layer_add_child(window_layer, text_layer_get_layer(unitField1));
    
    layer_add_child(window_layer, text_layer_get_layer(textField2));
    layer_add_child(window_layer, text_layer_get_layer(dataField2));
    layer_add_child(window_layer, text_layer_get_layer(unitField2));
    
    APP_LOG(APP_LOG_LEVEL_INFO, "---> LOADING....");

    //app_sync_init(&aSync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
            //      sync_tuple_changed_callback, sync_error_callback, NULL);
}

static void window_unload(Window *window) {
    app_sync_deinit(&aSync);
}

static void init(void) {
    
    window = window_create();
    window_set_click_config_provider(window, click_config_provider_two);
    window_set_background_color(window, GColorBlack);
    window_set_fullscreen(window, true);
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    
	  app_message_register_inbox_received(in_receivede_handler);
    app_message_register_inbox_dropped(in_dropped_handler);
    app_message_register_outbox_sent(out_send_handler);
    app_message_register_outbox_failed(out_failed_handler);
    app_message_open(INBOUND_SIZE, OUTBOUND_SIZE);
    
    //sendCmd();
    
    window_stack_push(window, true);
    APP_LOG(APP_LOG_LEVEL_INFO, "---> 6");
}

static void deinit(void) {
    
    window_destroy(window);
    tick_timer_service_unsubscribe();
    app_message_deregister_callbacks();
    bluetooth_connection_service_unsubscribe();
    battery_state_service_unsubscribe();
    
    
}

int main(void) {
    init();
    
    APP_LOG(APP_LOG_LEVEL_INFO, "Done initializing, pushed window: %p", window);
    ;
    app_event_loop();
    deinit();
}

/*
 Tuplet value = TupletInteger(1, options);
 DictionaryIterator *iter;
 app_message_outbox_begin(&iter);
 
 if (iter == NULL) {
 return;
 }
 
 dict_write_tuplet(iter, &value);
 dict_write_end(iter);
 app_message_outbox_send();
*/



