#ifndef CAN_LOGGER_H
#define CAN_LOGGER_H

//  what does this puppy need to do:
//      take in a standard format for CAN messages 
//          timestamp
//          message ID 
//          bus 
//          data
//
//      save the output to the SD card in the same .csv format that Cabana uses 

//#define FILENAME 'canslator_log'

#include <can_logger.cc>

bool logMessage(float time, uint16_t address, uint8_t bus, uint8_t data[8]); 
bool initializeLogger(string filename); 


#endif 
