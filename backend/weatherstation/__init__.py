from flask import Flask, send_file, Blueprint
import io
import PIL.Image as Image
from array import array

from weatherstation.image import default_image_c_string, ip
from weatherstation.api import api
import os
import sys
import logging
from weatherstation.views import register_endpoints

logger = logging.getLogger(__name__)

def setup_logger():
    handler = logging.StreamHandler()
    handler.setFormatter(logging.Formatter('%(levelname)s %(name)s : %(message)s'))
    logger.addHandler(handler)
    logger.setLevel(logging.DEBUG)


def create_app():

    setup_logger()

    app = Flask(__name__)

    register_endpoints(app)
    ip.init_app(app)
    api.init_app(app)

    logger.debug("debug")
    logger.info("info")

    return app