#ifndef __Session__
#define __Session__

#include "app.h"

class Session{
    
    App *app;
    
public:
    int counter;
    int index;
    string timestamp;
    
    bool bSaved = 0;
    bool bNew; 
    
    Session(App *a);
    
    void clear();
    
    void add();
    
    int getSize();
    
    string getTimeStamp();
    
    string toCsvHead();
    string toCsv();
    
    void fromCsv(string s);
    void newPosition();
    vector<string> rows;
    bool bSaving;
    int speed;
};


#endif