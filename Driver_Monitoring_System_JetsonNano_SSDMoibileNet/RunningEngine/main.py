import infer_cam1 
import sys
from infer_cam1 import detections_data
import time
from twilio.rest import Client
import serial
import pynmea2
def get_location():

    serial_port = serial.Serial(
    port="/dev/ttyTHS1",
    baudrate=9600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    )
    # Wait a second to let the port initialize
    time.sleep(1)
        # Send a simple header
    while True:
        if serial_port.inWaiting() > 0:
            data = serial_port.readline()
            if data[0:6] == b"$GPRMC":
                newmsg=pynmea2.parse(data.decode('utf-8'))
                lat=newmsg.latitude
                lng=newmsg.longitude
                if lng != 0 and lat!= 0:
                    return lat , lng
def send_message():
    
    account_sid = 'AC7e3f3869b68feacb7fab50a7e60a21ed'
    auth_token = '4951c53efeccf448313ce715b3e581a7'
    client = Client(account_sid, auth_token)
    lat, lng = get_location()
    text="The Driver at bad health condition here: "
    text+="http://maps.google.com/maps?q=loc:{:.5f},{:.5f}".format(lat,lng)
    message = client.messages.create(  from_='+19495652418',
                                       body = text,
                                       to='+201021736432')
def main(args):
    labels = []
    eyes_flag= 0;
    yawning_flag = 0
    start_time_eyes = 0
    start_time_yawning = 0
    current_time_eyes = 0
    current_time_yawning = 0
    status = 0
    eyes_closed = 0
    yawning_cnt = 0
    flag = 1
    time_span = 0
    ffs = 0
    trt_infer = infer_cam1.TensorRTInfer(args.engine, args.preprocessor, args.detection_type, args.iou_threshold)
    print("Engine built ####### starting detection")
    if args.labels:   ### loading labels
        with open(args.labels) as f:
            for i, label in enumerate(f):
                labels.append(label.strip())
    cap = infer_cam1.cv2.VideoCapture("v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480, framerate = 30/1 ! videoconvert ! video/x-raw,format=BGR ! appsink")
    end = 0
    font = infer_cam1.cv2.FONT_HERSHEY_COMPLEX
    while cap.isOpened():
        start = time.time()
        ret, frame = cap.read()  # 0.033s/frame
        frame = infer_cam1.cv2.resize(frame, (320,320))
        batcher = infer_cam1.ImageBatcher(frame, *trt_infer.input_spec(), preprocessor=args.preprocessor)
        for batch, images, scales in batcher.get_batch():
            detections = trt_infer.infer(batch, scales, args.nms_threshold) # 0.033s/detection
            dect = []
            for d in detections[0]:
               dect.append(d['class'])
               print(dect)
            #print(dect)
            fps = 1/(start - end)
            end = start
            fps = int(fps)
            fps = str(fps)
            detections_data = detections   
            ############ yawning counter#############
            # if len(dect) == 2 : 
            #     if dect[0] == 2 or dect[1] == 2:
            #         yawning = 1 
            # else: 
            #     yawning = 0
            # if len(dect) == 1:
            #     if dect[0] == 2:
            #         yawning = 1
            #     else:
            #          yawning = 0
            # if len(dect) != 0: 
            #     if yawning  and yawning_flag == 0:
            #         start_time_yawning = 0
            #         start_time_yawning = time.time()
            #         yawning_flag = 1
            #     elif yawning and yawning_flag == 1:
            #         current_time_yawning = time.time()
            #     if current_time_yawning-start_time_yawning >= 1.5 and flag == 1:
            #         yawning_cnt = yawning_cnt + 1
            #         print(f"yawned : {yawning_cnt} times")
            #         current_time_yawning = 0
            #         flag  = 0
            #     if not yawning:
            #         yawning_flag = 0
            #         start_time_yawning = 0
            #         current_time_yawning = 0 
            #         flag = 1 
            #         current_time_yawning = 0
            # ##### eyes_closed_warning
            # if len(dect) == 1 : 
            #     if dect[0] == 1 :
            #         eyes_closed = 1
            #     else:
            #         eyes_closed = 0
            #     if eyes_closed and eyes_flag == 0:
            #         start_time_eyes = 0
            #         start_time_eyes = time.time()
            #         eyes_flag = 1
            #         #print(d['class'])
            #     elif eyes_closed and eyes_flag == 1 :
            #         #current_time_eyes = 0
            #         current_time_eyes = time.time()
            #         time_span = current_time_eyes - start_time_eyes 
            #         #print(time_span) 
            #     if int(time_span) != ffs and int(time_span) >= 1:
            #         print(f"Eyes closed for {int(time_span)} seconds")
            #         ffs = int(time_span)
            #         if int(time_span) == 50:
            #             #send_message()
            #     #if eyes_closed and time_span <= int(time_span)+0.07 and time_span >= 1: 
            #         #if int(time_span) == 5:
            #             send_message()
            #     #    print(f"Eyes closed for {int(time_span)} seconds")
            #     #    current_time_eyes - start_time_eyes 
            #     if not eyes_closed:
            #         eyes_flag = 0  
            #         current_time_eyes = 0
            #         time_span = 0


            img_with_detectinos = infer_cam1.visualize_detections(frame , detections[0], labels)
            img_with_detectinos = frame
            img_with_detectinos = infer_cam1.np.asarray(img_with_detectinos)
            #img_with_detectinos = infer_cam1.cv2.cvtColor(img_with_detectinos, infer_cam1.cv2.COLOR_RGB2BGR)
            #infer_cam1.cv2.putText(img_with_detectinos, fps, (7,70), font, 3, (100,255,0), 3, infer_cam1.cv2.LINE_AA)
            infer_cam1.cv2.imshow("Detections", infer_cam1.cv2.resize(img_with_detectinos, (800, 600)))
        if infer_cam1.cv2.waitKey(10) & 0xFF == ord('q'):
             cap.release()
             infer_cam1.cv2.destroyAllWindows()
             break
if __name__ == "__main__":
    parser = infer_cam1.argparse.ArgumentParser()
    parser.add_argument("-e", "--engine", default=None, help="The serialized TensorRT engine")
    #parser.add_argument("-i", "--input", default=None, help="Path to the image or directory to process")
    #parser.add_argument("-o", "--output", default=None, help="Directory where to save the visualization results")
    parser.add_argument("-l", "--labels", default="./labels_coco.txt", 
                        help="File to use for reading the class labels from, default: ./labels_coco.txt")
    parser.add_argument("-d", "--detection_type", default="bbox", choices=["bbox", "segmentation"],
                        help="Detection type for COCO, either bbox or if you are using Mask R-CNN's instance segmentation - segmentation")
    parser.add_argument("-t", "--nms_threshold", type=float, 
                        help="Override the score threshold for the NMS operation, if higher than the threshold in the engine.")
    parser.add_argument("--iou_threshold", default=0.5, type=float, 
                        help="Select the IoU threshold for the mask segmentation. Range is 0 to 1. Pixel values more than threshold will become 1, less 0")                                                              
    parser.add_argument("--preprocessor", default="fixed_shape_resizer", choices=["fixed_shape_resizer", "keep_aspect_ratio_resizer"],
                        help="Select the image preprocessor to use based on your pipeline.config, either 'fixed_shape_resizer' or 'keep_aspect_ratio_resizer', default: fixed_shape_resizer")
    args = parser.parse_args()
    if not all([args.engine, args.preprocessor]):
        parser.print_help()
        print("\nThese arguments are required: --engine and --preprocessor")
        sys.exit(1)
    main(args)
    


