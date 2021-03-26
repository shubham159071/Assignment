import paho.mqtt.client as mqttClient
import time
import json
import pprint
 
def on_connect(client, userdata, flags, rc):
 
    if rc == 0:
        print("Connected to broker")
        global Connected               
        Connected = True                 
 
    else:
        print("Connection failed")
Connected = False   
broker_address= "broker.mqttdashboard.com"
port = 1883
client = mqttClient.Client("IOT_Assignment")
client.on_connect= on_connect
client.connect(broker_address, port=port)
client.loop_start()        
while Connected != True:    
    time.sleep(0.1)

try:
    
    date_time = time.strftime('%Y:%m:%d,%H:%M:%S')
    x =  {"now":date_time,"name":"Shubham"}
    msg = json.dumps(x,indent =3)
    client.publish("IoTAssignment_Shubham",msg)
    print (msg)
    time.sleep(5)\
    
except KeyboardInterrupt:
 
    client.disconnect()
    client.loop_stop()
