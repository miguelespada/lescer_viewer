#include "session.h"

Session::Session(App *a){
    app = a;
    clear();
    speed = 1;
}

void Session::clear(){
    counter = 0;
    index = 0;
    bSaved = true;
    bNew = false;
    bSaving = false;
    timestamp = ofGetTimestampString();
}



void Session::add(){
    if (!bNew || !bSaving) return;
    bNew = false;
    counter ++;
    bSaved = false;
    
};

int Session::getSize(){
    return counter;
}

string Session::getTimeStamp(){
    if(getSize() == 0)
        return "0000-00-00-00-00-00-000";
    else
        return timestamp;
}

string Session::toCsvHead(){
    return "x;y;rot_x;rot_y;rot_z\n";
}

string Session::toCsv(){
    
    string csv = toCsvHead();
    for(int i = 0; i < getSize(); i ++){
        csv += app->getDataRow(i);
        if(i < getSize() - 1)
            csv += "\n";
    }
    return csv;
}

    
void Session::fromCsv(string csv){
    rows = ofSplitString(csv, "\n");
    counter = rows.size() - 1;
}

void Session::newPosition(){
    
    if(index < counter){
        for(int i = 0; i < speed; i ++){
            
            if(index < counter) {
                vector<string> tokens = ofSplitString(rows[index], ";");
                
                int pos_x = ofToInt(tokens[0]);
                int pos_y = ofToInt(tokens[1]);
                int x = ofToInt(tokens[2]);
                int y = ofToInt(tokens[3]);
                int z = ofToInt(tokens[4]);
                app->addData(pos_x, pos_y, x, y, z);
                index = index + 1;
            }
            else{
                break;
            }
        }
    }
}