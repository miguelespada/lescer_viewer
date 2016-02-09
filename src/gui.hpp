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
    
    
    ofxIntSlider playback_speed;
    ofxIntSlider trace;
    ofxIntSlider setasLife;
    
    ofxButton startTimeGame;
    ofxButton startFruitGame;
    ofxButton calibrate;
    ofxButton clear;
    
    ofxLabel name;
    ofxLabel exercice;
    ofxLabel timestamp;
    ofxLabel counter;
    ofxLabel index;
    ofxLabel current;
    
    
public:
    
    Gui(App *a, OscAdapter *o){
        app = a;
        osc = o;
        gui.setup();
        setasPanel.setup();
        setasPanel.setPosition(10, 150);
        init();
        
        bVisible = true;
        load();    }
    
    void draw(){
        name = app->metadata.name;
        exercice = app->metadata.exercice;
        string stamp =  app->session->timestamp;
        timestamp = stamp.substr(0, stamp.size()-7);
        counter = ofToString(app->session->getSize());
        index  = ofToString(app->session->index);
        
        current.setup( "actual", ofToString(app->currentTimeOrFruits) );
        
        app->heatmap.L = trace;
        app->session->speed = playback_speed;
        
        if(bVisible){
            gui.draw();
            if(app->metadata.exercice == "Setas"){
                
                setasPanel.draw();
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
    
    
    //--------------------------------------------------------------
    void init(){
        
        gui.add(name.setup("Nombre", name));
        gui.add(exercice.setup("Ejercicio", exercice));
        
        gui.add(timestamp.setup("Fecha", timestamp));
        gui.add(counter.setup("Contador", counter));
        
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
        
            
                setasPanel.add(timeCount.setup( "numero", 50, 0, 200 ));
                setasPanel.add(current.setup( "actual", ofToString(app->currentTimeOrFruits) ));
            
                setasPanel.add(nivel.setup( "nivel", 1, 1, 4 ));
                setasPanel.add(setasLife.setup( "life", 10, 5, 50 ));
            
                startTimeGame.addListener(this, &Gui::startTimeGamePressed);
                startFruitGame.addListener(this,&Gui::startFruitGamePressed);
                setasPanel.add(startTimeGame.setup("Time game"));
                setasPanel.add(startFruitGame.setup("Fruit game"));
        
            
        }
    }
    
    void calibratedPressed(){
        app->setRotationRef();
    }
    
    void clearPressed(){
        app->clear();
    }
    
    void startTimeGamePressed(){
        osc->sendAction("/startTimeGame", nivel, timeCount, setasLife);
        app->metadata.variation = "Time game: " + ofToString(int(nivel)) + "; Time: " +  ofToString(int(timeCount)) + "; Life: " +  ofToString(int(setasLife)) + ";";
        startGame();
    }
    
    void startFruitGamePressed(){
        osc->sendAction("/startCountGame", nivel, timeCount, setasLife);
        app->metadata.variation = "Count game :" + ofToString(int(nivel)) + "; Number: " +  ofToString(int(timeCount)) + "; Life: " +  ofToString(int(setasLife)) + ";";
        startGame();
    }
    
    void startGame(){
        app->clear();
        app->setCurrentState(new RecordingState(app));
        app->session->bSaving = true;
    }
};

