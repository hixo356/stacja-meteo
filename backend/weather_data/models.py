from django.db import models

# Create your models here.
class WeatherData(models.Model):
    temperature = models.FloatField()
    pressure = models.FloatField()
    humidity = models.FloatField()
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f'{self.timestamp}: Temperature={self.temperature}, Pressure={self.pressure}, Humidity={self.humidity}'