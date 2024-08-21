# DRIVER MONITORING SYSTEM USING JETSON NANO AND SSD MOBILE NET.

![JetsonNano](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/02a20108-aa39-4901-85c5-844339a784a1)
![image](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/5d12b0bc-5f8f-4e49-9622-d63ed4166a80)

# Summery

- This is an SSD Mobile Net pre-trained model that is customized for a driver monitoring system.
- Main Features:
  - Detect Open Eyes and Closed Eyes.
  - Detect Detect Drowsniss.
  - Detect Phone.

## Project Overview:

**We have Customized An SSD MobileNet model with our classes and layers to get the desired results.**

## Technologies:

- Nvidia Jetson Nano Board.
- Jetpack: 4.6
- Tensorflow.
- Tensorflow Object Detection API.
- SSD Mobile Net Pre-trained model.
- TensorRT.
- Other Libraries (numpy, ...etc).

## Procedure:

1. We downloaded our model and then customized it with our labels.
2. The Full Description For The Model Is Here: [DMS Model](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/tree/master/SSD_MobileNet_Model).
3. Create FreezGraph:

```
python exporter_main_v2.py \
    --input_type float_image_tensor \
    --trained_checkpoint_dir /path/to/ssd_mobilenet_v2_320x320_coco17_tpu-8/checkpoint \
    --pipeline_config_path /path/to/ssd_mobilenet_v2_320x320_coco17_tpu-8/pipeline.config \
    --output_directory /path/to/export
```

4. Create Onnx:

- The ONNX interchange format provides a way to export models from many frameworks, including PyTorch, TensorFlow, and TensorFlow 2, for use with the TensorRT runtime.
- Here is the command to create your Onnx:

```
python create_onnx.py \
    --pipeline_config /path/to/exported/pipeline.config \
    --saved_model /path/to/exported/saved_model \
    --onnx /path/to/save/model.onnx
```

5. Create TRT Engine:

- NVIDIA® TensorRT™ is an SDK for optimizing trained deep-learning models to enable high-performance inference.
- TensorRT contains a deep learning inference optimizer for trained deep learning models and a runtime for execution.
- After you have trained your deep learning model in a framework of your choice, TensorRT enables you to run it with higher throughput and lower latency.
  ![image](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/fdd9236d-719b-4bfc-b2f4-8b06682f846f)
- Create TRT Engine:
  - NOTE-> Where is TensorRT: `/usr/src/tensorrt/bin`

```
trtexec --onnx=resnet50_onnx_model.onnx --saveEngine=engine.trt
```

6. Run Inference

```
sudo python3 file_name.py --engine engine.trt --labels labels.txt --detection_type bbox --preprocessor fixed_shape_resizing -t 0.5
```

- For more information about TRT Engine And Running The Inference: [GOTO](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/tree/master/RunningEngine)

### Labeling Phase:

![Labeling-phase](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/5d439980-d8d2-459d-96f0-1ef0120900a6)

## Dataset Samples

![dataset-samples](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/90417595-35e3-47af-bcb2-92350383e5e2)

## Validation Results

![Validation Results](https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/8d0b08e0-ba09-4f06-9b93-72c23af679f1)

# Results:

- Finally our Trt Engine Works on average 20FPS.

### Eyes Opened and closed Detections:

https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/8cc592b4-6c37-4ef1-b923-606242de430c

### Phone seatbelt detections:

https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/857141d9-51b4-445d-bc18-cfb72a4605e4

### Drowsness Detection:

https://github.com/Mo-Alsehli/Driver_Monitoring_System_JetsonNano_SSDMobileNet/assets/98949843/c76d3187-96a7-45df-86a3-e467d769865d

### Resources:

- [Resource-1](https://github.com/NVIDIA/TensorRT/tree/release/8.2/samples/python/tensorflow_object_detection_api).
- [Resource-2](https://docs.nvidia.com/deeplearning/tensorrt/quick-start-guide/index.html#export-from-tf).
- [Resource-3](https://github.com/NVIDIA/TensorRT/blob/main/quickstart/IntroNotebooks/3.%20Using%20Tensorflow%202%20through%20ONNX.ipynb).
- [Resource-4](https://www.youtube.com/watch?v=yqkISICHH-U&t=16912s).
- [Resource-5](https://github.com/nicknochnack/TFODCourse).
