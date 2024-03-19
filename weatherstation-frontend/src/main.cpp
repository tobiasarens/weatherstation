#include <Arduino.h>

#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "ImageService.h"
#include "Config.h"
#include "BackendService.h"
#include "util.h"
#include "Display.h"

ImageService imageService;
BackendService backendService;
Display display;

WiFiClient client;

unsigned char image_buffer[38880];

void setup() {

  Serial.begin(115200);
  while(!Serial) {

  }

  Serial.println("Starting");

  int status = 0;

  WiFi.begin(wifi::ssid, wifi::pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("wifi connected");

  display.init();
  memcpy(image_buffer, gImage_5in83_V2, 38880);

  backendService.getImage(image_buffer);

  display.showImage(image_buffer);

  display.poweroff();


  Serial.println("END");
  return;

  //backendService.getImage(image_buffer);
  /*
    if (client.connect(backend::hostname, backend::port)) {

      Serial.println("Connection successfull");

      client.println("GET " + *"/image_c" + *" HTTP/1.1");
      client.println("Host: " + *backend::hostname);
      client.println("Connection: close");
      client.println();

      while(client.connected()) {
          if (client.available()) {
              char c = client.read();
              Serial.print(int(c));
          }
      }
      Serial.println("End of response");

  } else {
      Serial.println("Connection was not successfull");
  }
  */

  return;

  printf("EPD_5IN83_V2_test Demo\r\n");
  DEV_Module_Init();

  printf("e-Paper Init and Clear...\r\n");
  EPD_5IN83_V2_Init();
  EPD_5IN83_V2_Clear();
  DEV_Delay_ms(500);

  //Create a new image cache
  UBYTE *BlackImage;
  /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
  UWORD Imagesize = ((EPD_5IN83_V2_WIDTH % 8 == 0) ? (EPD_5IN83_V2_WIDTH / 8 ) : (EPD_5IN83_V2_WIDTH / 8 + 1)) * EPD_5IN83_V2_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while(1);
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, EPD_5IN83_V2_WIDTH, EPD_5IN83_V2_HEIGHT, 180, WHITE);

#if 1   // show image for array   
  printf("show image for array\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(imageService.getImagePointer());
  EPD_5IN83_V2_Display(BlackImage);
  DEV_Delay_ms(500);
#endif

#if 0   // Drawing on the image
  //1.Select Image
  printf("SelectImage:BlackImage\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  printf("Drawing:BlackImage\r\n");
  Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
  Paint_DrawString_CN(130, 0, " 你好abc", &Font12CN, BLACK, WHITE);
  Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);

  printf("EPD_Display\r\n");
  EPD_5IN83_V2_Display(BlackImage);
  DEV_Delay_ms(2000);
#endif

  //printf("Clear...\r\n");
  //EPD_5IN83_V2_Clear();

  printf("Goto Sleep...\r\n");
  EPD_5IN83_V2_Sleep();

  EPD_5IN83_V2_Init();
  EPD_5IN83_V2_Clear();


  EPD_5IN83_V2_Sleep();

  free(BlackImage);
  BlackImage = NULL;
}

void loop() {
  // put your main code here, to run repeatedly:
}