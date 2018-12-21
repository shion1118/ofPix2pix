//
//  palette.hpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/19.
//

#pragma once

#include "ofMain.h"

class Palette
{
    
public:
    const int palette_size = 25;
    
    void setup(string palette_path);
    void draw(int x=0, int y=0);
    int get_current_palette_num();
    ofColor get_current_color();
    void previous_palette();
    void next_palette();
    vector<ofColor> get_palette_colors();
    
protected:
    int current_palette = 0;
    vector<ofColor> colors;
    
};
