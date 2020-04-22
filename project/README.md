Refer to instructions on https://www.tensorflow.org/hub/tutorials/image_retraining

### Capturing training images to build your own dataset
Requirements:
Raspberry Pi 3
Pi Camera

Step 1:
Modify this line in camera.py with your own directory
camera.capture('/home/pi/photos/plastic/'+str(int(time.time()))+".jpg")

Step 2:
python camera.py

### Training the model
The model is trained in a docker container with...
python retrain.py \
    --image_dir ~/photos \
    --tfhub_module https://tfhub.dev/google/imagenet/mobilenet_v2_100_224/feature_vector/2

You can specify your own image directory and other TensorFlow Hub module
Further instructions can be found at https://www.tensorflow.org/hub/tutorials/image_retraining#other_model_architectures

Algorithm:
1.	Handshake with Pi and Arduino
2.	Display the ready message on both the Pi terminal and the Arduino LCD
3.	Place the trash on the platform and pick "paper" or "plastic"
4.	Wait for the machine to finish classifing the image and verify the choice
