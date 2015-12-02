//
//  arduino.cpp
//  lescer_viewer
//
//  Created by miguel on 21/09/15.
//
//

#include "arduino.h"

Arduino::Arduino(App *a){
    app = a;
    
    
    isArduinoConnected = false;
    
    ofAddListener(ofEvents().update, this, &Arduino::update);
    
}


//--------------------------------------------------------------
void Arduino::update(ofEventArgs &args){
    
    if(isArduinoConnected)
        updateArduino();
    
    reconnectArduino();

}

void Arduino::reconnectArduino(){
    int port = getArduinoPort();
    if(port>=0){
        if(isArduinoConnected){
            //cout << "Arduino is connected" << endl;
        }else{
            ofLogNotice() << "Trying to connect arduino...";
            serial.close();
            isArduinoConnected = serial.setup(serial.getDeviceList()[port].getDeviceName(), ARDUINO_BAUD_RATE);
        }
    }else{
        ofLogNotice() << "Arduino not present...";
        isArduinoConnected = false;
    }
}


int Arduino::getArduinoPort(){
    ofSerial serial;
    vector <ofSerialDeviceInfo> deviceList =  serial.getDeviceList();
    for(int i=0; i<deviceList.size(); i++){
        if(deviceList[i].getDeviceName().find(ARDUINO_PORT_NAME) != std::string::npos){
            return i;
        }
    }
    cout << "arduino port not found " << endl;
    return -1;
};


//--------------------------------------------------------------
void Arduino::updateArduino(){
    if(getSerialString()){
        // String available for parsing
        string str(buffer);

        vector<string> splitString = ofSplitString(str, ",");

    }

}
//--------------------------------------------------------------
bool Arduino::getSerialString(){
    startChar = '[';
    endChar = ']';
    bufferIndex = 0;
    storeString = false;                   // flag to put the data in our buffer
    
    while(serial.available() > 0){
        char incomingbyte = serial.readByte();
        
        if(storeString){
            if(bufferIndex == DATABUFFERSIZE){
                //cout << "Oops, index is pointing to an array element outside our buffer" << endl;
                bufferIndex = 0;
                break;
            }
            
            if(incomingbyte == endChar){
                //cout << "data string is complete" << endl;
                buffer[bufferIndex] = 0; //null terminate the C string
                return true;
            }
            else{
                buffer[bufferIndex++] = incomingbyte;
                buffer[bufferIndex] = 0; //null terminate the C string
            }
        }
        
        // doing the check here will drop the startChar from the buffer
        if(incomingbyte == startChar){
            bufferIndex = 0;
            storeString = true;
        }
    }
    
    //We've read in all the available Serial data, and don't have a valid string yet, so return false
    return false;
}
