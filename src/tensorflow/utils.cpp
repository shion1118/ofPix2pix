//
//  Utils.cpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#include "utils.hpp"

void Utils::image_to_tensor(const ofFloatImage &src, tensorflow::Tensor &dst, const ofVec2f &in_range, const ofVec2f &out_range) {
    auto *in = src.getPixels().getData();
    auto dst_data = dst.flat<float>().data();
    int n = dst.NumElements();
    float scale, offset;
    
    calc_scale_offset(in_range, out_range, scale, offset);
    for (int i = 0; i < n; i++) {
        dst_data[i] = in[i] * scale + offset;
    }
}

void Utils::tensor_to_image(const tensorflow::Tensor &src, ofFloatImage &dst, const ofVec2f& in_range, const ofVec2f& out_range) {
    auto *out = dst.getPixels().getData();
    auto src_data = src.flat<float>().data();
    int n = src.NumElements();
    float scale, offset;
    
    calc_scale_offset(in_range, out_range, scale, offset);
    for (int i = 0; i < n; i++) {
        out[i] = src_data[i] * scale + offset;
    }
}

void Utils::calc_scale_offset(const ofVec2f &in_range, const ofVec2f &out_range, float &scale, float &offset) {
    float input_min = in_range.x;
    float input_max = in_range.y;
    float output_min = out_range.x;
    float output_max = out_range.y;
    
    if (fabs(input_max - input_min) > numeric_limits<float>::epsilon()) {
        scale = 1.0f / (input_max - input_min) * (output_max - output_min);
        offset = (output_min - input_min * scale);
    } else {
        scale = 1.0f;
        offset = 1.0f;
    }
}
