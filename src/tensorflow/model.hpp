//
//  Model.hpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#pragma once

#include "utils.hpp"

class Model
{

public:
    Model() {};
    Model(string model_path, vector<string> input_op_names, vector<string> output_op_names);
    void init(string model_path, vector<string> input_op_names, vector<string> output_op_names);
    void init_input(tensorflow::DataType type, vector<tensorflow::int64> shape, int tensor_index=0);
    bool is_loaded();
    tensorflow::Tensor& get_input_tensor(int i=0);
    tensorflow::Tensor& get_output_tensor(int i=0);
    bool run_image_to_image(const ofFloatImage& img_in, ofFloatImage& img_out, ofVec2f model_in_range=ofVec2f(), ofVec2f model_out_range=ofVec2f(), ofVec2f image_range=ofVec2f(0, 1));
    
protected:
    string model_path;
    shared_ptr<tensorflow::Session> session;
    shared_ptr<tensorflow::GraphDef> graph;
    vector<string> input_op_names;
    vector<string> output_op_names;
    vector<pair<string, tensorflow::Tensor>> input_tensors;
    vector<tensorflow::Tensor> output_tensors;
    
    shared_ptr<tensorflow::Session> create_session();
    shared_ptr<tensorflow::GraphDef> load_graph();
    bool run();
};
