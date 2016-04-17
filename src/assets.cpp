#include "assets.h"

void Assets::loadAssets(){
    loadImage(&cabeza_x, "cabeza 2.png");
    loadImage(&cabeza_y, "cabeza 3.png");
    loadImage(&cabeza_z, "cabeza 1.png");
    loadImage(&wireframe, "wireframe.png");
    loadImage(&on, "on.png");
    loadImage(&off, "off.png");
    loadImage(&rec_on, "rec_on.png");
    loadImage(&rec_off, "rec_off.png");
    loadImage(&play_on, "play_on.png");
    loadImage(&play_off, "play_off.png");
    loadImage(&saved, "saved.png");
    loadImage(&unsaved, "unsaved.png");
    loadImage(&error, "error.png");
    loadImage(&campo, "campo.png");
    loadImage(&ciudad, "ciudad.png");
    loadImage(&setas, "setas.png");
    loadImage(&supermercado, "supermercado.jpg");
    loadImage(&joystick, "joystick.png");
    loadImage(&wireframe_head, "wireframe_head.png");
    
}

bool Assets::isViewer(){
    return getData("viewer").asBool();
}

string Assets::dataPath(){
    return getData("data_path").asString();
}

int Assets::maxLife(int i){
    if(i == 0) return 0;
    return ejercicios_settings["items_life"].asInt();
}

int Assets::maxTime(int i){
    if(i == 0) return 0;
    return ejercicios_settings["maximo_tiempo"].asInt();
}

int Assets::maxItems(int i){
    if(i == 0) return 0;
    return ejercicios_settings["numero_frutas"].asInt();
}

string Assets::exerciceText(int i){
    if(i == 0) return "Selecciona ejercicio";
    return ejercicios_settings["texto"].asString();
}

int Assets::exerciceCode(int i){
    if(i == 0) return 0;
    return ejercicios_settings["code"].asInt();
}