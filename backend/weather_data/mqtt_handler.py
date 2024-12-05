import json
import os

import paho.mqtt.client as mqtt
from .models import WeatherData


MQTT_BROKER = 'broker.emqx.io'
MQTT_PORT = 1883
MQTT_TOPIC = 'esp32-test'
def on_connect(client, userdata, flags, rc):
    print("Connected " if rc == 0 else f"Conecting error: {rc}")
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    try:
        print(f"Odebrano wiadomość: {msg.payload.decode()}")
        data = json.loads(msg.payload.decode())
        WeatherData.objects.create(
            temperature=data['temperature'],
            pressure=data['pressure'],
            humidity=data['humidity'],
        )
        print("Data saved:",data)
    except Exception as e:
        print("Error with message:", e)

def start_mqtt():
    print("Starting MQTT server")
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    try:
        client.connect(MQTT_BROKER, MQTT_PORT,60)
        print("MQTT server connected({MQTT_BROKER}:{MQTT_PORT})")
        client.loop_start()
    except Exception as e:
        print("Error with MQTT server:", e)
