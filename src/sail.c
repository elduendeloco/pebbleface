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

static int option=0;
static int rows=2;

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
		if(rows==2)
		{
			set_layer_contents(1, selectText(first), "N/A", "N/A");
			set_layer_contents(1, selectText(second), "N/A", "N/A");
		}
		else
		{
			set_layer_contents(selectText(first), "N/A", "N/A");
		}
}


/**
 * Richiede all'applicazione sul telefono le informazioni.
 */


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
    
    changeWithAnimation();
		sendCmd();
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
					set_layer_contents(dict_find(received, TEXT1)->value->cstring, 
														 dict_find(received, DATA1)->value->cstring, 
														 dict_find(received, UNIT1)->value->cstring);
    	}
        
    	else if(strcmp(status, "two") == 0) {
            
        	APP_LOG(APP_LOG_LEVEL_INFO, "Recieved status \"Two Row\"");
            
					set_layer_contents(1,
														 dict_find(received, TEXT1)->value->cstring, 
														 dict_find(received, DATA1)->value->cstring, 
														 dict_find(received, UNIT1)->value->cstring);
				  set_layer_contents(2,
														 dict_find(received, TEXT2)->value->cstring, 
														 dict_find(received, DATA2)->value->cstring, 
														 dict_find(received, UNIT2)->value->cstring);
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

static void init(void) {
    
    window = window_create();
    window_set_click_config_provider(window, click_config_provider_two);
    
	  app_message_register_inbox_received(in_receivede_handler);
    app_message_register_inbox_dropped(in_dropped_handler);
    app_message_register_outbox_sent(out_send_handler);
    app_message_register_outbox_failed(out_failed_handler);
    app_message_open(INBOUND_SIZE, OUTBOUND_SIZE);
    
    sendCmd();
    
    APP_LOG(APP_LOG_LEVEL_INFO, "---> 6");
}

static void deinit(void) {
    
	
    tick_timer_service_unsubscribe();
    app_message_deregister_callbacks();
    bluetooth_connection_service_unsubscribe();
    battery_state_service_unsubscribe();
    
    
}

int main(void) 
{
    init();
    APP_LOG(APP_LOG_LEVEL_INFO, "Done initializing, pushed window: %p", window);
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



