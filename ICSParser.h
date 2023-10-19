/*
  ICSParser.h - Library to parse ICS Calendar files.
  The aim of this library is, to enable you to easily search for words in the event description on given days.
  This will be used to evaluate if tomorrow the trash will be emtied. 
  So that an output can signal to put out the trash.
  Created by Jannis Dohm, 2020-02-12.
  Released under MIT License.
  211206 Kr move from FS, deprecated, to LittleFS
  Rewrite by David Wischnjak, 2023-10-19.
*/
#pragma once

#include <FS.h> //filesystem for ESP8266: http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/filesystem.html under LGPL V2.1h"

struct Timestamp {
  int	sec = 0;
  int	min = 0;
  int	hour = 0;
  int	day = 0;
  int	mon = 0;
  int	year = 0;
};

class ICSParser
{
  public:
    ICSParser(File * ics_file);
    // the file name has to be given as "/filename" with leading "/" due to compatibility to FS filesystem
    bool checkDate(const char * search_str, int day, int month, int year);
    int listDates(Timestamp * buffer, int buffer_len, const char * search_str);

  private:
    File * _file;
    static constexpr char BEGIN_VEVENT[] = "BEGIN:VEVENT";
    static constexpr char END_VEVENT[] = "END:VEVENT";
    static constexpr char DTSTART[] = "DTSTART";
    static constexpr char END_VCALENDAR[] = "END:VCALENDAR";
};
