//
//  Model.cpp
//  pix2pix
//
//  Created by 福島 シオン on 2018/12/18.
//

#include "model.hpp"

Model::Model(string model_path, vector<string> input_op_names, vector<string> output_op_names) {
    init(model_path, input_op_names, output_op_names);
}

void Model::init(string model_path, vector<string> input_op_names, vector<string> output_op_names) {
    this->model_path = ofToDataPath(model_path);
    this->input_op_names = input_op_names;
    this->output_op_names = output_op_names;
    
    this->session = create_session();
    this->graph = load_graph();
    
    tensorflow::Status status = this->session->Create(*graph);
    if (!status.ok()) {
        ofLog(OF_LOG_ERROR, status.ToString());
        return;
    }
    
    for (auto op_name : this->input_op_names) {
        input_tensors.push_back(make_pair(op_name, tensorflow::Tensor()));
    }
}

void Model::init_input(tensorflow::DataType type, vector<tensorflow::int64> shape, int tensor_index) {
    input_tensors.at(tensor_index).second = tensorflow::Tensor(type, tensorflow::TensorShape(shape));
}

shared_ptr<tensorflow::Session> Model::create_session() {
    tensorflow::Session* session;
    ofLog(OF_LOG_NOTICE, "Create session.");
    tensorflow::Status status = tensorflow::NewSession(tensorflow::SessionOptions(), &session);
    if (!status.ok()) {
        ofLog(OF_LOG_ERROR, "Cannot create session!!");
        return nullptr;
    }
    return shared_ptr<tensorflow::Session>(session);
}

shared_ptr<tensorflow::GraphDef> Model::load_graph() {
    shared_ptr<tensorflow::GraphDef> graph(new tensorflow::GraphDef());
    ofLog(OF_LOG_NOTICE, "Load graph: " + this->model_path);
    tensorflow::Status status = tensorflow::ReadBinaryProto(tensorflow::Env::Default(), this->model_path, graph.get());
    if (!status.ok()) {
        ofLog(OF_LOG_ERROR, "Cannot load graph!!");
        return nullptr;
    }
    return graph;
}

bool Model::is_loaded() {
    return session != nullptr;
}

tensorflow::Tensor& Model::get_input_tensor(int i) {
    return input_tensors.at(i).second;
}

tensorflow::Tensor& Model::get_output_tensor(int i) {
    return output_tensors.at(i);
}

bool Model::run() {
    if (!is_loaded()) {
        ofLog(OF_LOG_ERROR, "Graph is not loaded!!");
        return false;
    }
    
    tensorflow::Status status = session->Run(input_tensors, output_op_names, {}, &output_tensors);
    if (!status.ok()) {
        ofLog(OF_LOG_ERROR, status.ToString());
        return false;
    }
    return true;
}

bool Model::run_image_to_image(const ofFloatImage& img_in, ofFloatImage& img_out, ofVec2f model_in_range, ofVec2f model_out_range, ofVec2f image_range) {
    Utils::image_to_tensor(img_in, get_input_tensor(), image_range, model_in_range);
    if(run()) {
        Utils::tensor_to_image(get_output_tensor(), img_out, model_out_range, image_range);
        return true;
    }
    return false;
}
