import dotenv
from weatherstation import create_app

import logging

logging.getLogger('weatherstation').setLevel(logging.DEBUG)

if __name__ == "__main__":
    app = create_app()

    app.run(debug=True, host="0.0.0.0", port=6002)