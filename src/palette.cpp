//
//  palette.cpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/19.
//

#include "palette.hpp"

void Palette::setup(string palette_path) {
    ofBuffer buffer = ofBufferFromFile(palette_path);
    for (auto line : buffer.getLines()) {
        if (line.size() != 6) continue;
        colors.push_back(ofColor::fromHex(ofHexToInt(line)));
    }
}

void Palette::draw(int x, int y) {
    ofPushMatrix();
    ofTranslate(x, y);
    
    for (auto i = 0; i < colors.size(); i++) {
        ofFill();
        ofSetColor(colors.at(i));
        
        ofDrawRectangle(0, 0, palette_size, palette_size);
        
        if (i == current_palette) {
            ofNoFill();
            ofSetColor(255);
            ofSetLineWidth(3);
            ofDrawRectangle(0, 0, palette_size, palette_size);
        }
        
        ofTranslate(palette_size + palette_size * 0.2, 0);
    }
    ofPopMatrix();
}

int Palette::get_current_palette_num() {
    return current_palette;
}

ofColor Palette::get_current_color() {
    return colors.at(current_palette);
}

void Palette::previous_palette() {
    0 > current_palette - 1 ? current_palette = colors.size() - 1 : current_palette--;
}

void Palette::next_palette() {
    colors.size() == current_palette + 1 ? current_palette = 0 : current_palette++;
}

vector<ofColor> Palette::get_palette_colors() {
    return colors;
}
