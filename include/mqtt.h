#ifndef MQTT_H
#define MQTT_H

#include <mqtt.h>
#include <mqtt_client.h>
#include <mqtt5_client.h>
#include <esp_event.h>
#include <esp_log.h>
#include <freertos/event_groups.h>

#include "wifi.h"

#define TAG "MQTT client"

class Mqtt{
    public:
        Mqtt(Wifi *wifi);
        ~Mqtt();
        static void mqtt_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
        esp_mqtt5_client_handle_t client;
    private:
        EventGroupHandle_t mqtt_event_group;
        const int CONNECTED_BIT = BIT0;
};

#endif