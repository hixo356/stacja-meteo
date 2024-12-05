#ifndef WIFI_H
#define WIFI_H

#include <esp_wifi.h>
#include <esp_event.h>
#include <freertos/event_groups.h>
#include <esp_netif.h>

class Wifi{
    public:
        Wifi(const char *ssid, const char *password);
        ~Wifi();
        static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
        bool get_connected_status() { return connected; };
    private:
        EventGroupHandle_t wifi_event_group;
        const int CONNECTED_BIT = BIT0;
        static inline bool connected = false;
};

#endif