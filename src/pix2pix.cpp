//
//  pix2pix.cpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#include "pix2pix.hpp"

void Pix2pix::setup(string model_name, string test_img_name, ofVec2f input_range, ofVec2f output_range) {
    model.init(model_name, {INPUT_OP_NAME}, {OUTPUT_OP_NAME});
    if (!model.is_loaded()) {
        return;
    }
    // {batch size, image height, image width, number of channels}
    model.init_input(tensorflow::DT_FLOAT, {1, INPUT_SIZE, INPUT_SIZE, 3});
    
    this->input_range = input_range;
    this->output_range = output_range;
    
    test_img.load(test_img_name);
}

void Pix2pix::run(const ofFloatImage &img_input, ofFloatImage &img_output) {
    bool status = model.run_image_to_image(img_input, img_output, input_range, output_range, image_range);
    if (!status) {
        ofLog(OF_LOG_ERROR, "Some error!!");
    }
    img_output.update();
}

ofImage Pix2pix::get_test_img() {
    return test_img;
}
