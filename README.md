# ICSParser
a Arduino ESP8266/ESP32 library to search for specific events in an ICS calendar

## Install
```cpp
cd /home/user/Arduino/libraries
git clone https://github.com/wladimir-computin/ICSParser.git
```

## Usage

### Header

``` #include <ICSParser.h> ```

### Init
Upload/Downlaod the "*.ics" file to your LittleFS storage. 

Create an ICSParser instance:

```cpp
File f = LittleFS.open("/calender.ics", "r");
ICSParser ics(&f);

// do stuff

f.close()
``` 

### Check a date for a specific event:

```cpp
bool checkDate(const char * search_str, int day, int month, int year);
``` 

For example, if you're interested if the event `Abfuhr Leichtverpackungen` happens on the `31.1.2023`, you would call:

```cpp
ics.checkDate("Abfuhr Leichtverpackungen", 31, 1, 2023);
``` 

You can also get an array of dates containing a specific event:

```cpp
struct Timestamp {
  int	sec = 0;
  int	min = 0;
  int	hour = 0;
  int	day = 0;
  int	mon = 0;
  int	year = 0;
};

int listDates(Timestamp * buffer, int buffer_len, const char * search_str);
```

Use it like this:

```cpp
const int max_events = 5 * 12;
auto timestamps = new Timestamp[max_events](); //large array, esp8266 have much more heap than stack memory.

File f = LittleFS.open("/calender.ics", "r");
ICSParser ics(&f);
int count = ics.listDates(timestamps, max_events), "Abfuhr Leichtverpackungen");

// do stuff
for (int i = 0; i < count; i++){
	Serial.printf("%2d.%2d.%4d\n", timestamps[i].day, timestamps[i].mon, timestamps[i].year);
}

//clean up
f.close();
delete timestamps;
```


