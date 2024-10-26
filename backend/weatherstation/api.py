from flask import Flask
import requests
from PIL import Image
import io
import os

import logging

logger = logging.getLogger(__name__)

LOCATIONS = {
    'westpark': (50.772141, 6.0678051),
    'gk': (50.9672, 6.1175)
}

ICON_PATHS = {
    '01': 'sun.png',
    '02': 'partly-cloudy.png',
    '03': 'clouds.png',
    '04': 'clouds.png',
    '09': 'little-rain.png',
    '10': 'rain.png',
    '11': 'thunder.png',
    '13': 'snow.png',
    '50': 'mist.png',
}

class OpenWeatherAPI:
    def __init__(self):
        self.icon_buffer = {}

    def init_app(self, app: Flask):
        self.api_key = os.environ.get('API_KEY')
        pass

    def request_weather_data(self, lat_lon: tuple[int, int] = (0,0)):

        lat = lat_lon[0]
        lon = lat_lon[1]

        request_url = f"https://api.openweathermap.org/data/3.0/onecall?lat={lat}&lon={lon}&units=metric&lang=de&appid={self.api_key}"

        response = requests.get(request_url)

        return response.json()
    
    
    def get_icon(self, icon_id: str, size: int=2) -> Image.Image:
        """
        Retrieves an icon from openweathermap.
        Size is a scale either 2 or 4. Standard size (1) is 50x50 pixels
        """
        
        short_id = icon_id[:-1]

        path = f'resources/icons/{ICON_PATHS.get(short_id, "fallback.png")}'
        logger.debug(f"looking for icon {path}")
        return Image.open(path)
        url = f"https://openweathermap.org/img/wn/{icon_id}{f'@{size}x' if size in [2, 4] else ''}.png"
        response = requests.get(url)

        bytes = io.BytesIO(response.content)
        self.icon_buffer[(icon_id, size)] = bytes

        return Image.open(bytes)
    
def get_API_icon_path(icon_id):
    short_id = icon_id[:-1]
    return f'resources/icons/{ICON_PATHS.get(short_id, "fallback.png")}'
    
    
api = OpenWeatherAPI()
