//
//  pix2pix.hpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#pragma once

#include "model.hpp"

class Pix2pix
{
    
public:
    const int INPUT_SIZE = 256;
    const int OUTPUT_SIZE = 256;
    const string INPUT_OP_NAME = "generator/generator_inputs";
    const string OUTPUT_OP_NAME = "generator/generator_outputs";
    
    void setup(string model_name, string test_img_name, ofVec2f input_range, ofVec2f output_range);
    void run(const ofFloatImage& img_input, ofFloatImage& img_output);
    ofImage get_test_img();
    
protected:
    Model model;
    ofVec2f input_range;
    ofVec2f output_range;
    ofVec2f image_range = ofVec2f(0, 1);
    ofImage test_img;
};
