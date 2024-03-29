/*
 * This example also does something useful with "#define EZTIME_NETWORK_ENABLE" at the 
 * start of ezTime.h commented out. It will start the time at the time the code was
 * compiled. You have to set your local timezone information by hand in the 
 * LOCALTZ_POSIX define. (The string contains the names for your TZ in standard and
 * Daylight Saving Time, as well as the starting and ending point for DST and the 
 * offset to UTC.
 * 
 * If you do not want to look up the posix string you can simply provide a name and
 * the current UTC offset, like "PDT+7" 
 */


#include <ezTime.h>

#define LOCALTZ_POSIX	"PST+8PDT,M3.2.0/2,M11.1.0/2"		// US Pacific time

Timezone local;
Timezone berlin;

void setup() {

	Serial.begin(115200);
	Serial.println();

	local.setPosix(LOCALTZ_POSIX);
	local.setTime(time.compileTime());
	Serial.println("Local time  :  " + local.dateTime());

	berlin.setPosix("CET-1CEST,M3.4.0/2,M10.4.0/3");
	Serial.println("Berlin time :  " + berlin.dateTime());

	Serial.println("UTC         :  " + UTC.dateTime());
	
}

void loop() {
}
