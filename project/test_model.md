Test your model

python label_image.py \
--graph=/tmp/output_graph.pb --labels=/tmp/output_labels.txt \
--input_layer=Placeholder \
--output_layer=final_result \
--input_height=224 \
--input_width=224 \
--image=/home/pi/photos/paper/1550970684.jpg