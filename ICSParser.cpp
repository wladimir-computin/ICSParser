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

#include "ICSParser.h"

ICSParser::ICSParser(File * ics_file) {
  _file = ics_file;
}


int ICSParser::listDates(Timestamp * buffer, int buffer_len, const char * search_str){
  _file->seek(0,SeekSet);
  int buffer_pos = 0;
  while(_file->findUntil(BEGIN_VEVENT, END_VCALENDAR)){
    int vevent_pos = _file->position();
    if(_file->findUntil(search_str, END_VEVENT)){
      _file->seek(vevent_pos,SeekSet);
      if(_file->findUntil(DTSTART, END_VEVENT)){
        if(_file->findUntil(":", "\n")){
          char strtime[16];
          Timestamp &t = buffer[buffer_pos++];
          _file->readBytesUntil('\n', strtime, (sizeof(strtime) / sizeof(strtime[0])) - 1);
          sscanf(strtime, "%4d%2d%2dT%2d%2d%2d", &(t.year), &(t.mon), &(t.day), &(t.hour), &(t.min), &(t.sec));
          if(buffer_pos >= buffer_len){
            return buffer_pos;
          }
        }
      }
    }
  }
  return buffer_pos;
}

bool ICSParser::checkDate(const char * search_str, int day, int month, int year){
  char search_date[9];
  snprintf(search_date, sizeof(search_date) / sizeof(search_date[0]), "%04d%02d%02d", year, month, day);
  _file->seek(0,SeekSet);
  while(_file->findUntil(BEGIN_VEVENT, END_VCALENDAR)){
    int vevent_pos = _file->position();
    if(_file->findUntil(DTSTART, END_VEVENT)){
      if(_file->findUntil(search_date, "\n")){
        _file->seek(vevent_pos,SeekSet);
        if(_file->findUntil(search_str, END_VEVENT)){
            return true;
        }
      }
    }
  }
  return false;
}
