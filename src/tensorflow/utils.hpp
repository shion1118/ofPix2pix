//
//  utils.hpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#pragma once

#include "ofMain.h"
#include "tf_includes.h"

class Utils
{
    
public:
    static void image_to_tensor(const ofFloatImage &src, tensorflow::Tensor &dst, const ofVec2f& in_range=ofVec2f(), const ofVec2f& out_range=ofVec2f());
    static void tensor_to_image(const tensorflow::Tensor &src, ofFloatImage &dst, const ofVec2f& in_range=ofVec2f(), const ofVec2f& out_range=ofVec2f());
    static void calc_scale_offset(const ofVec2f& in_range, const ofVec2f& out_range, float& scale, float &offset);
    
};
