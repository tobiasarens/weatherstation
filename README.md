## Weather Station project
This project is a passion project inspired by something I found [here](https://www.hackster.io/lmarzen/esp32-e-paper-weather-display-a2f444) on hackster.io.  
It is a Weather display with an E-Ink display, that shows a weather forecast.

Since I don't want to plainly copy the code, but learn something, I want to do it myself.

### Hardware
For the hardware I oriented myself on the project: I have an FireBeetle ESP32-E as microcontroller and a Waveshare 5.83" Black and White E-Ink display.
Since the original project only offers support for 7 or 8 inch displays, I really have to do it myself.

### Project Structure
At least for the beginning, I want to create a small Flask backend that serves as proxy to the online weather forecast.
This way I can reduce the computing and image construction on the ESP such that it only requests to a specific endpoint and gets the image to display.
That allows me to focus on different tasks at once and I can easily swap out what to show on the display once it works.

Maybe I will change it later and remove the backend to make the display more versatile.
