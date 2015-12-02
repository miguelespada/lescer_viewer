//
//  arduino.h
//  lescer_viewer
//
//  Created by miguel on 21/09/15.
//
//

#ifndef __lescer_viewer__arduino__
#define __lescer_viewer__arduino__

#include "ofMain.h"
#include "app.h"


#define DATABUFFERSIZE 25   // needs to be big enough to hold the incomming messages
#define ARDUINO_BAUD_RATE 9600
#define ARDUINO_PORT_NAME "tty.usbmodem"

class Arduino
{
    App *app;
    

public:
    Arduino(App *a);;
    void update(ofEventArgs &args);
    
    ofSerial serial;
    
    char buffer[DATABUFFERSIZE];
    int bufferIndex;
    char startChar;
    char endChar;
    bool storeString;
    
    bool getSerialString();
    
    // arduino serial hot plugging
    int getArduinoPort();
    bool isArduinoConnected;
    
    void reconnectArduino();
    
    // request more data from arduino
    void sendArduinoDataRequest();
    float timer;
    
    void updateArduino();
    
    int sensorValues[4];



};


#endif /* defined(__lescer_viewer__arduino__) */
