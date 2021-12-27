/* Read NPN water-meter-sensor
   Pinout:
   Sensor Blue: GND
   Sensor Brown: 5V
   Sensor Black -- A3 with internal pullup, might want external 10k?, mine works
   I use the LJ12A3-4-Z/BX-5V
*/

#include <EEPROM.h>

const int sensor = A3; // Beware that A6 and A7 have no internal pullup, and NEED the external 10k
const int keepalive_time = 10000; // wait time between posting stats if no new values. Milliseconds.
const int eeAddress = 0;

int lastval;
bool newval;
unsigned long last_time;

unsigned long read_counter() { unsigned long f; EEPROM.get(eeAddress, f); return f; }
void store_counter(unsigned long f) { EEPROM.put(eeAddress, f); }
void send_stats() { Serial.print(read_counter()); Serial.println(" l"); last_time = millis(); }

void setup()
{
  Serial.begin(115200);
  pinMode(sensor, INPUT_PULLUP);
  // store_counter(434296); // uncomment for initial meter-setting (and then reflash with line commented again)
  send_stats();
}

void loop()
{
  newval = digitalRead(sensor);
  
  if ( newval == 0) {
    if ( lastval > 0) {
      store_counter(read_counter() + 1);
      send_stats();
    }
  }

  if ((millis() - last_time) > keepalive_time) {
    send_stats();
  }

  lastval = newval;
  delay(10);
}
