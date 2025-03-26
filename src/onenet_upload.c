// src/onenet_upload.c
#include "onenet_upload.h"
#include <stdio.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

int onenet_upload(int co2, float noise, float gas) {
    CURL *curl;
    CURLcode res;
    char json_data[256];
    
    snprintf(json_data, sizeof(json_data),
             "{\"datastreams\":["
             "{\"id\":\"CO2\",\"datapoints\":[{\"value\":%d}]},"
             "{\"id\":\"noise\",\"datapoints\":[{\"value\":%.1f}]},"
             "{\"id\":\"gas\",\"datapoints\":[{\"value\":%.1f}]}"
             "]}",
             co2, noise, gas);
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "api-key: " ONENET_API_KEY);
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl = curl_easy_init();
    if (!curl) return -1;
    
    curl_easy_setopt(curl, CURLOPT_URL, ONENET_UPLOAD_URL);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    
    res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    
    return res == CURLE_OK ? 0 : -1;
}

void onenet_global_cleanup() {
    curl_global_cleanup();
}