/*
  SDCard.cpp - Adds SD Card Features to Grbl_ESP32
  Part of Grbl_ESP32

  Copyright (c) 2018 Barton Dring Buildlog.net

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Config.h"
#ifdef ENABLE_SD_CARD
#    include "SDCard.h"
#include <memory>

File                       myFile;
std::string                fileName;
bool                       SD_ready_next = false;  // Grbl has processed a line and is waiting for another
uint8_t                    SD_client     = CLIENT_SERIAL;
WebUI::AuthenticationLevel SD_auth_level = WebUI::AuthenticationLevel::LEVEL_GUEST;
uint32_t                   sd_current_line_number;     // stores the most recent line number read from the SD
static char                comment[LINE_BUFFER_SIZE];  // Line to be executed. Zero-terminated.

// attempt to mount the SD card
/*bool sd_mount()
{
  if(!SD.begin()) {
    report_status_message(Error::FsFailedMount, CLIENT_SERIAL);
    return false;
  }
  return true;
}*/

void listDir(fs::FS& fs, const char* dirname, uint8_t levels, uint8_t client) {
    //char temp_filename[128]; // to help filter by extension	TODO: 128 needs a definition based on something
    File root = fs.open(dirname);
    if (!root) {
        report_status_message(Error::FsFailedOpenDir, client);
        return;
    }
    if (!root.isDirectory()) {
        report_status_message(Error::FsDirNotFound, client);
        return;
    }
    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            if (levels) {
                listDir(fs, file.name(), levels - 1, client);
            }
        } else {
            grbl_sendf(CLIENT_ALL, "[FILE:%s|SIZE:%d]\r\n", file.name(), file.size());
        }
        file = root.openNextFile();
    }
}

boolean openFile(fs::FS& fs, const char* path, const char* mode) {
    get_sd_state(1);
    myFile = fs.open(path, mode);
    fileName = path;
    if (!myFile) {
        //report_status_message(Error::FsFailedRead, CLIENT_SERIAL);
        return false;
    }
    set_sd_state(SDState::BusyPrinting);
    SD_ready_next          = false;  // this will get set to true when Grbl issues "ok" message
    sd_current_line_number = 0;
    return true;
}

boolean closeFile() {
    if (!myFile) {
        return false;
    }
    set_sd_state(SDState::Idle);
    SD_ready_next          = false;
    sd_current_line_number = 0;
    myFile.close();
    SD.end();
    return true;
}

/*
  read a line from the SD card
  strip whitespace
  strip comments per http://linuxcnc.org/docs/ja/html/gcode/overview.html#gcode:comments
  make uppercase
  return true if a line is
*/
boolean readFileLine(char* line, int maxlen) {
    if (!myFile) {
        report_status_message(Error::FsFailedRead, SD_client);
        return false;
    }
    sd_current_line_number += 1;
    int len = 0;
    while (myFile.available()) {
        if (len >= maxlen) {
            return false;
        }
        char c = myFile.read();
        if (c == '\n') {
            break;
        }
        line[len++] = c;
    }
    line[len] = '\0';
    return len || myFile.available();
}

// return a percentage complete 50.5 = 50.5%
float sd_report_perc_complete() {
    if (!myFile) {
        return 0.0;
    }
    return (float)myFile.position() / (float)myFile.size() * 100.0f;
}

uint32_t sd_get_current_line_number() {
    return sd_current_line_number;
}

SDState sd_state = SDState::Idle;


SDState get_sd_state(bool refresh) {
    if (SDCARD_DET_PIN != UNDEFINED_PIN) {
        if (digitalRead(SDCARD_DET_PIN) != SDCARD_DET_VAL) {
            sd_state = SDState::NotPresent;
            return sd_state;
            //no need to go further if SD detect is not correct
        }
    }

    //if busy doing something return state
    if (!((sd_state == SDState::NotPresent) || (sd_state == SDState::Idle))) {
        return sd_state;
    }
    if (!refresh) {
        return sd_state;  //to avoid refresh=true + busy to reset SD and waste time
    }

    //SD is idle or not detected, let see if still the case
    SD.end();
    sd_state = SDState::NotPresent;
    //using default value for speed ? should be parameter
    //refresh content if card was removed
    if (SD.begin((GRBL_SPI_SS == -1) ? SS : GRBL_SPI_SS, SPI, GRBL_SPI_FREQ, "/sd", 2)) {
        if (SD.cardSize() > 0) {
            sd_state = SDState::Idle;
        }
    }
    return sd_state;
}

SDState set_sd_state(SDState state) {
    sd_state = state;
    return sd_state;
}

void sd_get_current_filename(char* name) {
    if (myFile) {
        strcpy(name, myFile.name());
    } else {
        name[0] = 0;
    }
}




int writeFileLine(const char *appendValue){
    if((!myFile && fileName.size()==0) || !appendValue) return -1;
    openFile(SD,fileName.c_str(),FILE_APPEND);
    int response = myFile.println(appendValue);
    closeFile();
    std::string aux = "Writed =" + std::string(appendValue) + "\n";
    client_write(CLIENT_ALL,(char*) aux.c_str());
    return response;
}

void sd_end_run(){
    char temp[50];
    sd_get_current_filename(temp);
    grbl_notifyf("SD print done", "%s print is successful", temp);
    char sent[100];
    sprintf(sent,"SD print done! %s ended\n",temp);
    client_write(CLIENT_SERIAL,sent);
    closeFile();  // close file and clear SD ready/running flags

    if (sys.programWillRepeat){ 
        sys.programWillRepeat = false;
        if(!openFile(SD,temp)){
            report_status_message(Error::FsFailedOpenFile,CLIENT_ALL);
            closeFile();
        }
        else SD_ready_next = true;
    }
}

Error openWriteFile(const char *fileName, WebUI::AuthenticationLevel auth, WebUI::ESPResponseStream* responseStream){
    Error error = Error::Ok;
    std::string mode = (SD.exists(fileName)?FILE_APPEND:FILE_WRITE);
    if(!fileName) error = Error::FsFailedOpenFile;
    if(!openFile(SD,fileName,mode.c_str())) error = Error::FsFailedOpenFile;
    return error;
}
Error appendToWriteFile(const char* line, WebUI::AuthenticationLevel auth, WebUI::ESPResponseStream* responseStream){
    Error error = Error::Ok;
    int writed = writeFileLine(line);
    if(writed<0) error = Error::FsFailedWrite;
    return error;
}
Error closeWriteFile(const char* value,   WebUI::AuthenticationLevel auth, WebUI::ESPResponseStream* responseStream){
    closeFile();
    return Error::Ok;
} 
#endif  //ENABLE_SD_CARD
