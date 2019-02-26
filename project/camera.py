from picamera import PiCamera
import time

camera = PiCamera()

camera.start_preview()
time.sleep(3)

while raw_input() != 'q':
  camera.capture('/home/pi/photos/plastic/'+str(int(time.time()))+".jpg")


camera.stop_preview()