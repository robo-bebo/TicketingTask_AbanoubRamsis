sudo apt install mosquitto mosquitto-clients libmosquitto-dev

#to start the broker
sudo systemctl start mosquitto

#publish from cli
mosquitto_pub -h localhost -p 1883 -t request/ticket -m '{"lineNumber":5,"validityDays":30}'

mosquitto_pub -h localhost -p 1883 -t validate/ticket -m 'eyJWYWxpZGl0eURheXMiOjMwLCJjcmVhdGlvbkRhdGUiOiIyMDI2LTAxLTA5IDE5OjM2OjAyIiwibGluZU51bWJlciI6NSwidGlja2V0SUQiOjQwNTg5MTIyNDI3NDMxODY3ODB9'

curl -v -X POST http://localhost:8080/requestTicket \
     -H "Content-Type: application/json" \
     -d '{"lineNumber":3,"validityDays":7}'