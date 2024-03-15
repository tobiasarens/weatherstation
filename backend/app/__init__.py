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
        ip.load_c_string(default_image_c_string)

        img = io.BytesIO()
        ip.image.save(img, 'JPEG', quality=100)
        img.seek(0)


        return send_file(img, mimetype='image/jpeg')

    return app