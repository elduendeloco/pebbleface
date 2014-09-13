//
//  sail.h
//  sail
//
//  Created by Francesco Di Carlo on 20/07/14.
//  Copyright (c) 2014 francescodicarlo. All rights reserved.
//

#ifndef sail_sail_h
#define sail_sail_h

static int first=0;
static int second=1;

static int length[]={8, 7,  6, 14, 4, 3};

static char *speedTexts[]={"Speed", "Max speed", "Average", "SOG", "VMG", "Log", "Trip", "Timer"};
static char *windTexts[]={"App Wind Speed", "App Wind Angle", "True Wind Speed", "True Wind Angle", "Ground Wind Angle", "Wind Force", "Wind Dir"};
static char *headingTexts[]={"Current Heading", "Locked Heading", "Tack course", "COG", "CMG", "DMG"};
static char *navigateTexts[]={"BTW", "DTW", "XTE", "Waypoint", "Latitude", "Longitude", "COG", "SOG", "SAT", "HDOP", "Heading", "Speed", "Rolling road", "VMG to waypoint"};
static char *environmentTexts[]={"Sea Temp", "Battery", "Time", "Date"};
static char *depthTexts[]={"Current depth", "Min depth", "Max depth"};


void sendCmd();
void set_option_value (int value);
int get_option_value ();
void set_rows_value (int value);
int get_rows_value ();
char* selectText(int value);

#endif

