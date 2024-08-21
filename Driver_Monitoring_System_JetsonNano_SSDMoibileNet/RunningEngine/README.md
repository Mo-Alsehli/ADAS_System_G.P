# TRT Engine
*NVIDIA® TensorRT™, an SDK for high-performance deep learning inference, includes a deep learning inference optimizer and 
runtime that delivers low latency and high throughput for inference applications.*
![tensor-rt](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/941ebaba-da67-478f-a5a9-53944fb714b6)

## This project Depends on TensorRT Project:
[TensorRT Object Detection API](https://github.com/NVIDIA/TensorRT/tree/release/8.2/samples/python/tensorflow_object_detection_api)

## Abstract:
- This project was aimed to work only on images from a path.
- We edited 'infer.py' and the other files to be able to use the engine with live cam.
- Also we have added some functionality for GPS module.

## Running The Inference (Engine):
```
python infer.py \
    --engine /path/to/saved/engine.trt \
    --input /path/to/images \
    --output /path/to/output \
    --preprocessor fixed_shape_resizer \
    --labels /path/to/labels_coco.txt
```
