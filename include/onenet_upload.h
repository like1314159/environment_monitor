// include/onenet_upload.h
#ifndef ONENET_UPLOAD_H
#define ONENET_UPLOAD_H

#include <curl/curl.h>

#define ONENET_API_KEY "你的API_KEY"
#define ONENET_DEVICE_ID "你的设备ID"
#define ONENET_UPLOAD_URL "http://api.heclouds.com/devices/" ONENET_DEVICE_ID "/datapoints"

int onenet_upload(int co2, float noise, float gas);
void onenet_global_cleanup();

#endif