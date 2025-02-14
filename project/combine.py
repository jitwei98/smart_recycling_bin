from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse

import numpy as np
import tensorflow as tf

import serial # module for serial port communication
from picamera import PiCamera
import time

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

def initialize():
  ser.write("sending via RPi\n".encode('utf-8'))
  response = ser.readline()
  # print(response.decode('utf-8'))
  while True:
    if response.decode('utf-8') == "Hello World!\n":
      break
    response = ser.readline()

  print("Starting the game......\n")

def wait_for_photo():
  response = ser.readline()
  while True:
    # print(response.decode('utf-8'))
    if response.decode('utf-8') == "s":
      break
    response = ser.readline()
    # print(responses)
  print("3,2,1 cheese!")
  capture()


def capture():
  camera = PiCamera()
  # camera.start_preview()
  time.sleep(1)
  # while raw_input() != 'q':
  camera.capture('/home/pi/imageToLabel.jpg')
  # camera.stop_preview()

# ---------------Label Image---------------------------------------------------------------------------------

def load_graph(model_file):
  graph = tf.Graph()
  graph_def = tf.GraphDef()

  with open(model_file, "rb") as f:
    graph_def.ParseFromString(f.read())
  with graph.as_default():
    tf.import_graph_def(graph_def)

  return graph


def read_tensor_from_image_file(file_name,
                                input_height=299,
                                input_width=299,
                                input_mean=0,
                                input_std=255):
  input_name = "file_reader"
  output_name = "normalized"
  file_reader = tf.read_file(file_name, input_name)
  if file_name.endswith(".png"):
    image_reader = tf.image.decode_png(
        file_reader, channels=3, name="png_reader")
  elif file_name.endswith(".gif"):
    image_reader = tf.squeeze(
        tf.image.decode_gif(file_reader, name="gif_reader"))
  elif file_name.endswith(".bmp"):
    image_reader = tf.image.decode_bmp(file_reader, name="bmp_reader")
  else:
    image_reader = tf.image.decode_jpeg(file_reader, channels=3, name="jpeg_reader")
  float_caster = tf.cast(image_reader, tf.float32)
  dims_expander = tf.expand_dims(float_caster, 0)
  resized = tf.image.resize_bilinear(dims_expander, [input_height, input_width])
  normalized = tf.divide(tf.subtract(resized, [input_mean]), [input_std])
  sess = tf.Session()
  result = sess.run(normalized)

  return result


def load_labels(label_file):
  label = []
  proto_as_ascii_lines = tf.gfile.GFile(label_file).readlines()
  for l in proto_as_ascii_lines:
    label.append(l.rstrip())
  return label
  
def classify():
  file_name = "tensorflow/examples/label_image/data/grace_hopper.jpg"
  model_file = "tensorflow/examples/label_image/data/inception_v3_2016_08_28_frozen.pb"
  label_file = "tensorflow/examples/label_image/data/imagenet_slim_labels.txt"
  input_height = 299
  input_width = 299
  input_mean = 0
  input_std = 255
  input_layer = "input"
  output_layer = "InceptionV3/Predictions/Reshape_1"

  parser = argparse.ArgumentParser()
  parser.add_argument("--image", help="image to be processed")
  parser.add_argument("--graph", help="graph/model to be executed")
  parser.add_argument("--labels", help="name of file containing labels")
  parser.add_argument("--input_height", type=int, help="input height")
  parser.add_argument("--input_width", type=int, help="input width")
  parser.add_argument("--input_mean", type=int, help="input mean")
  parser.add_argument("--input_std", type=int, help="input std")
  parser.add_argument("--input_layer", help="name of input layer")
  parser.add_argument("--output_layer", help="name of output layer")
  args = parser.parse_args()

  # if args.graph:
    # model_file = args.graph
  model_file = "/tmp/output_graph.pb"
  # if args.image:
    # file_name = args.image
  file_name = "/home/pi/imageToLabel.jpg"
  # if args.labels:
    # label_file = args.labels
  label_file = "/tmp/output_labels.txt"
  # if args.input_height:
    # input_height = args.input_height
  input_height = 224
  # if args.input_width:
    # input_width = args.input_width
  input_width = 224

  if args.input_mean:
    input_mean = args.input_mean
  if args.input_std:
    input_std = args.input_std
  # if args.input_layer:
  #   input_layer = args.input_layer
  input_layer = "Placeholder"
  # if args.output_layer:
    # output_layer = args.output_layer
  output_layer = "final_result"

  graph = load_graph(model_file)
  t = read_tensor_from_image_file(
      file_name,
      input_height=input_height,
      input_width=input_width,
      input_mean=input_mean,
      input_std=input_std)

  input_name = "import/" + input_layer
  output_name = "import/" + output_layer
  input_operation = graph.get_operation_by_name(input_name)
  output_operation = graph.get_operation_by_name(output_name)

  with tf.Session(graph=graph) as sess:
    results = sess.run(output_operation.outputs[0], {
        input_operation.outputs[0]: t
    })
  results = np.squeeze(results)

  top_k = results.argsort()[-5:][::-1]
  labels = load_labels(label_file)
  for i in top_k:
    print(labels[i], results[i])
  # TODO: finish the game logic
  if results[0] > results[1]:
    send_classification_result(labels[0])
  else:
    send_classification_result(labels[1])


# ---------------------------------------------------------------------------------------------------------

# result = A or B
def send_classification_result(result):
    if result == "paper":
        print("---paper")
        ser.write("l\n".encode('utf-8'))
    elif result == "plastic":
        print("---plastic")
        ser.write("r\n".encode('utf-8'))

def main():
    initialize()
    wait_for_photo()
    classify()

if __name__=="__main__":
    main()

