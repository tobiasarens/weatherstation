from flask import Flask, send_file
import io
import PIL.Image as Image
from array import array

from app.image import default_image_c_string, ImageProducer

def create_app():
    app = Flask(__name__)

    @app.route("/")
    def index():
        return "hello world"

    @app.route("/image")
    def get_image():

        ip = ImageProducer()
        #ip.load_c_string(default_image_c_string)
        ip.load_file('app/static/resources/Dio.png')
        img = io.BytesIO()
        ip.image.save(img, 'JPEG', quality=100)
        img.seek(0)
        return send_file(img, mimetype='image/jpeg')
    
    @app.route("/image_c")
    def get_c_str_image():

        ip = ImageProducer()
        ip.load_file('app/static/resources/Dio.png')
        result = ip.get_c_string()
        print(f"Result length: {len(result)}")
        return result

    return app