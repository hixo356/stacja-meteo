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
    return render(request, 'dashboard.html', {'latest_data': latest_data})
    all_data = WeatherData.objects.all()
    return render(request, 'dashboard.html', {'latest_data': latest_data, 'all_data': all_data})
