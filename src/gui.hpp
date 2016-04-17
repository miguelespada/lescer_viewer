#include "ofxGui.h"
#include "app.h"
#include "session.h"
#include "assets.h"
#include "recordingState.h"

class Gui
{
    ofxPanel gui;
    ofxPanel setasPanel;
    App *app;
    OscAdapter *osc;
    bool bVisible;
    
    
    ofxFloatSlider timeCount;
    ofxIntSlider nivel;
    ofxLabel nivel_as_string;
    
    
    ofxIntSlider playback_speed;
    ofxIntSlider trace;
    ofxLabel setasLife;
    
    ofxButton startTimeGame;
    ofxButton startFruitGame;
    ofxButton calibrate;
    ofxButton clear;
    
    ofxLabel name;
    ofxLabel exercice;
    ofxLabel code;
    ofxLabel timestamp;
    ofxLabel time;
    ofxLabel counter;
    ofxLabel index;
    ofxLabel current;
    
public:
    
    Gui(App *a, OscAdapter *o){
        app = a;
        osc = o;
        gui.setup();
        setasPanel.setup();
        setasPanel.setPosition(10, 250);
        init();
        
        bVisible = true;
        load();
    }
    
    void draw(){
        name = app->metadata.name;
        exercice = app->metadata.exercice;
        string stamp =  app->session->timestamp.substr(0, stamp.size()-7);
        timestamp = day(stamp);
        counter = ofToString(app->session->getSize());
        index  = ofToString(app->session->index);
        
        
        app->heatmap.L = trace;
        app->session->speed = playback_speed;
        
        if(bVisible){
            gui.draw();
            if(app->metadata.exercice == "Setas"){
                setasPanel.draw();
                current = ofToString(app->reactions.n_hits) + "/" + ofToString(Assets::getInstance()->maxItems(app->metadata.variation));
                time = ofToString(app->ellapsedTime, 1) + "/" + ofToString(Assets::getInstance()->maxTime(app->metadata.variation)) ;
                code = ofToString(Assets::getInstance()->exerciceCode(app->metadata.variation)) ;
                
            }
        }
    }
    
    void load(){
        string path = ofToDataPath("gui.xml");
        ofLogNotice() << "Loading gui from: " << path;
        gui.loadFromFile(path);
    }
    
    void save(){
        string path = ofToDataPath("gui.xml");
        ofLogNotice() << "Saving gui to: " << path;
        gui.saveToFile(path);
    }
    
    void toggleVisibility(){
        bVisible = !bVisible;
    }
    
    string day(string stamp){
        vector<string>date = ofSplitString(stamp, "-");
        if(date.size() < 5) return "";
        return  date[2] + "/" + date[1] + "/" + date[0] + " " + date[3] + ":" + date[4];
    }
    
    //--------------------------------------------------------------
    void init(){
        
        gui.add(name.setup("Paciente", name));
        gui.add(exercice.setup("Ejercicio", exercice));
        gui.add(timestamp.setup("Fecha", timestamp));
        
        gui.add(counter.setup("Frames", counter));
        trace = 400;
        if(Assets::getInstance()->isViewer()){
            gui.add(index.setup("Posicion", index));
            gui.add(playback_speed.setup( "speed",  2, 1, 20));
            gui.add(trace.setup( "trace",  400, 100, 5000 ));
        }
        else{
            
            gui.add(calibrate.setup("Calibrate"));
            gui.add(clear.setup("Clear"));
        
            
            calibrate.addListener(this,&Gui::calibratedPressed);
            clear.addListener(this,&Gui::clearPressed);
        
            
            setasPanel.add(current.setup("Frutas", ""));
            setasPanel.add(time.setup("Tiempo", ""));
            setasPanel.add(code.setup("Code", ""));
            
            setasPanel.add(setasLife.setup( "Maximo vida frutas: " + ofToString(Assets::getInstance()->maxLife(app->metadata.variation)) ));
        
        }
    }
    
    void calibratedPressed(){
        app->setRotationRef();
    }
    
    void clearPressed(){
        app->clear();
    }
    
};

