from flask import send_file
import io

from weatherstation.image import ip
from weatherstation.api import api, LOCATIONS

def register_endpoints(app):
    @app.route("/")
    def index():
        return "hello world"

    @app.route("/image")
    def get_image():


        result = api.request_weather_data(LOCATIONS['gk'])

        ip.assemble_image(result)

        icon = api.get_icon('10d')#.convert('RGB')




        img = io.BytesIO()
        ip.image.save(img, 'PNG', quality=100)
        #icon.save(img, 'PNG', quality=100)
        img.seek(0)

        return send_file(img, mimetype='image/jpeg')

    @app.route("/image_c")
    def get_c_str_image():
        result = ip.get_c_string()

        result = api.request_weather_data(LOCATIONS['gk'])

        ip.assemble_image(result)

        result = ip.get_c_string()

        return result
    
    @app.route("/weatherdata")
    def get_weather_data():


        result = api.request_weather_data(LOCATIONS['gk'])
        return result