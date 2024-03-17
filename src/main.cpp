#define NODE_NAME "32Sw1"
#define VERSION   "V 2.01"


#pragma region Includes
#include <Arduino.h>
#include "TAMC_GT911.h"
#include <TFT_eSPI.h>
#include <esp_now.h>
#include <WiFi.h>
#include <lvgl.h>
#include "Ui\ui.h"
#include "Ui\ui_events.h" 

#define TFT_HOR_RES   480
#define TFT_VER_RES   320
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
#define TOUCH_SDA  33
#define TOUCH_SCL  32
#define TOUCH_INT  21
#define TOUCH_RST 25
#define TOUCH_WIDTH  480
#define TOUCH_HEIGHT 320

TFT_eSPI tft = TFT_eSPI(TFT_HOR_RES, TFT_VER_RES); /* TFT instance */

TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

#pragma region Globals
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ TFT_HOR_RES * TFT_VER_RES / 10 ];




void loop() 
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data ) 
{
    tp.read();
    
    if( !tp.isTouched ) {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    else {
        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = tp.points[0].x;
        data->point.y = tp.points[0].y;

        
        Serial.print( "Data x " );
        Serial.print( data->point.x );

        Serial.print( ", Data y " );
        Serial.println( data->point.y );
        
    }
}
void setup() 
{    
    Serial.begin(74880);
    
    tp.begin();
    tp.setRotation(ROTATION_LEFT);
  
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    lv_init();
    
    lv_disp_draw_buf_init( &draw_buf, buf1, NULL, TFT_HOR_RES * TFT_VER_RES / 10 );

    //Display-Driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    disp_drv.hor_res = TFT_HOR_RES;
    disp_drv.ver_res = TFT_VER_RES;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    //Touch-Driver
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    ui_init(); 
}






