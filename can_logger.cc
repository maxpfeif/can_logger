#include <can_logger.h>
#include <SdFat.h> 

// NOTE - we will need to include a timeing module so that we can record the time, but for now we can just call micros internalls, unless the specific 
// time at which the message was received is vital down to the microsecond, otherwise we can just call micros, or access our time method when the 
// message as saved and eat the little bit of delay, or add a factor to account for this if it really becomes a problem 

SdFatSdioEX sdEx;       // We're going to use Extended buffering for this to speed things up 
File file;

// Error messages stored in flash.
#define error(msg) sdEx.errorHalt(F(msg))

//  Initializes the logger with a filename to write to. 
//  Should only be called once, at the beginning of the log cycle 
//  passed a filename string 
bool initializeLogger(string filename) {
    // compute the size of the name chosen 
    const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;

    // need to create a new file, with the .csv extension 
    char filename[BASE_NAME_SIZE + 7] = filename "00.csv";

    // Find an unused file name.
    while (sdEx.exists(filename)) {
        if (filename[BASE_NAME_SIZE + 1] != '9') {
            filename[BASE_NAME_SIZE + 1]++;
        } else if (filename[BASE_NAME_SIZE] != '9') {
            filename[BASE_NAME_SIZE + 1] = '0';
            filename[BASE_NAME_SIZE]++;
        } else {
        error("Can't create file name");
        }
    }

    // Try to open the file, with create, write and exclude options 
    if (!file.open(filename, O_CREAT | O_WRITE | O_EXCL)) {
        error("file.open");
    }

    // if this won't begin 
    if (!sdEx.begin()) {
      sdEx.initErrorHalt("SdFatSdioEX begin() failed");
    }

    // make sdEx the current volume.
    sdEx.chvol();

    // Write the .csv file header 
    file.println("time, address, bus, data"); 
}


//  saves a can message to the logfile based on the input arguments 
// 
//  preconditions:  basic message content; bus, address and data     
//
//  postconditions: returns whether or not the save was successful 
// 
bool logMessage(uint16_t address, uint8_t bus, uint8_t data[8]) {
    // for now record time in micros 
    uint16_t log_time = micros(); 

    // print the data 
    file.print(micros()); file.print(","); file.print(address); file.print(bus);
    file.println(data); // might need to adjust this, not sure how its going to spit all of this shit out 
} 






