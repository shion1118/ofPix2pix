#  pix2pix

pix2pix using openFrameworks.
![](https://camo.qiitausercontent.com/f7e4683e473426dada4daf4a3650b4d12e50bfd1/68747470733a2f2f71696974612d696d6167652d73746f72652e73332e616d617a6f6e6177732e636f6d2f302f33353835392f38666632303133612d626237352d316666622d353634302d6430633266383635363663632e676966)

##  About pis2pix
https://phillipi.github.io/pix2pix/  
Image-to-Image Translation with Conditional Adversarial Networks  
Phillip Isola, Jun-Yan Zhu, Tinghui Zhou, Alexei A. Efros  
CVPR, 2017.

## Getting Started
### Prerequisites
- openFrameworks 0.10.1

To build TensorFlow from source.
- Python 3.6.5
- Bazel 0.20.0

### Build TensorFlow
[Build from source | TensorFlow](https://www.tensorflow.org/install/source)  
Build TensorFlow from source.  
Clone tensorflow and checkout latest version.
```bash
$ git clone https://github.com/tensorflow/tensorflow.git
$ cd tensorflow
$ git checkout -b v1.12.0 refs/tags/v1.12.0
```

Configure environment settings.  
If you use Mac, select default settings (Y/n, N/y).
```bash
$ ./configure
```

Build using bazel.
```bash
$ bazel build -c opt //tensorflow:libtensorflow_cc.so
...

Target //tensorflow:libtensorflow_cc.so up-to-date:
  bazel-bin/tensorflow/libtensorflow_cc.so
INFO: Elapsed time: 2231.907s, Critical Path: 214.42s
INFO: 4193 processes: 4191 darwin-sandbox, 2 local.
INFO: Build completed successfully, 4257 total actions

$ ls -lh bazel-bin/tensorflow/libtensorflow_cc.so
-r-xr-xr-x  1 shfukush  wheel   177M 12 13 15:08 bazel-bin/tensorflow/libtensorflow_cc.
```

### Install TensorFlow library (Mac)
Install TensorFlow libarary.  
Notice: change file extension of library to `.dylib`.
```bash
$ install -m 0644 bazel-bin/tensorflow/libtensorflow_cc.so /usr/local/lib/libtensorflow_cc.dylib
$ install_name_tool -id /usr/local/lib/libtensorflow_cc.dylib /usr/local/lib/libtensorflow_cc.dylib
```

Copy header files to `/usr/local/include/tensorflow/`.  
Script is here - [copy_headers.sh](https://gist.github.com/shion1118/03c2ad587b1b83a6adfc48c8976b440e)

### Import Project
Clone or fork this repository.  
Launch projectGenerator and import project.

### Setting library path
Open Xcode and project, setting library path.  

| Item | Path |
|---|---|
| Header Search Paths | /usr/local/include/tensorflow/ |
| Library Search Paths | /usr/local/lib/ |
| Link Binary With Libraries | 	libtensorflow_cc.dylib |

### Import Graph(model) file
This project using *Labels to Street Scene* graph.  
Please download `labels_2_street_scene.zip` from [Release](https://github.com/shion1118/ofPix2pix/releases).  
And copy `graph_l2s.pb` to `bin/data/`.

All done !
