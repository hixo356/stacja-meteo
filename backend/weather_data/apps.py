from django.apps import AppConfig
import threading

class WeatherDataConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'weather_data'

    def ready(self):
        print('Ready')
        from .mqtt_handler import start_mqtt
        threading.Thread(target=start_mqtt, daemon=True).start()
