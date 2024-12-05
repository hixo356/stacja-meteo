from django.shortcuts import render
from .models import WeatherData

def dashboard(request):
    try:
        latest_data = WeatherData.objects.latest('timestamp')
    except WeatherData.DoesNotExist:
        latest_data = {
            'temperature': 'Brak danych',
            'pressure': 'Brak danych',
            'humidity': 'Brak danych',
        }
        all_data = []
    else:
        all_data = WeatherData.objects.all().order_by('timestamp')
    if all_data:
        temperatures = [entry.temperature for entry in all_data][-20:]
        timestamps = [entry.timestamp.strftime("%H:%M:%S") for entry in all_data][-20:]
    else:
        temperatures = []
        timestamps = []
    return render(request, 'dashboard.html', {
        'latest_data': latest_data,
        'temperatures': temperatures,
        'timestamps': timestamps
    })
