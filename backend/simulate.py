import paho.mqtt.client as mqtt
import json
import time

# Konfiguracja brokera MQTT
MQTT_BROKER = "localhost"  # Adres brokera (jeśli działa lokalnie)
MQTT_PORT = 1883  # Port brokera
MQTT_TOPIC = "esp32/weather"  # Temat, którego używamy

# Funkcja symulująca dane z ESP32
def simulate_mqtt():
    client = mqtt.Client()

    # Połącz z brokerem
    client.connect(MQTT_BROKER, MQTT_PORT)

    print("Symulacja danych MQTT rozpoczęta...")

    while True:
        # Tworzenie przykładowych danych (zmieniające się wartości)
        data = {
            "temperature": round(20 + (2 * time.time() % 10), 2),
            "pressure": round(1010 + (time.time() % 5), 2),
            "humidity": round(40 + (3 * time.time() % 5), 2)
        }

        # Publikowanie danych w formacie JSON
        client.publish(MQTT_TOPIC, json.dumps(data))
        print(f"Wysłano dane: {data}")

        time.sleep(5)  # Co 5 sekund

# Uruchom symulację
if __name__ == "__main__":
    simulate_mqtt()
