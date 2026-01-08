sudo apt install mosquitto mosquitto-clients libmosquitto-dev

#to start the broker
sudo systemctl start mosquitto

#publish from cli
mosquitto_pub -h localhost -p 1883 -t request/ticket -m '{"lineNumber":5,"validityDays":30}'