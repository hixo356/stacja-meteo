#include "wifi.h"
#include <esp_log.h>
#include <nvs_flash.h>

static int num_of_attempts = 0;

#define WIFI_SSID "Mi Note 10 Litee"
#define WIFI_PASSWORD "12345678"

Wifi::Wifi(const char *ssid, const char *password)
{
    printf("WIFI\n\n");
    wifi_event_group = xEventGroupCreate();
    printf("WIFI\n\n");

    nvs_flash_init();
    printf("WIFI\n\n");
    ESP_ERROR_CHECK(esp_netif_init());
    printf("WIFI\n\n");
    esp_event_loop_create_default();
    printf("WIFI\n\n");
    esp_netif_create_default_wifi_sta();
    printf("WIFI\n\n");
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);
    printf("WIFI\n\n");

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID, //(uint8_t)&ssid,
            .password = WIFI_PASSWORD //(uint8_t)&password}}; //eok7khz4y92f8exz
        }
    }; 
    printf("WIFI\n\n");

    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    printf("WIFI\n\n");
    esp_wifi_set_mode(WIFI_MODE_STA);
    printf("WIFI\n\n");

    esp_wifi_start();

    printf("WIFI\n\n");
    esp_wifi_connect();

    printf("WIFI\n\n");
}

Wifi::~Wifi()
{
    vEventGroupDelete(wifi_event_group);
}

void Wifi::wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("\n\n\nWiFi connecting...\n\n\n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("\n\n\nWiFi connected! Number of attempts: %d\n\n\n", num_of_attempts+1);
        num_of_attempts = 0;
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("\n\n\nWiFi lost connection!\n\n\n");
        num_of_attempts++; 
        connected = false;
        if (num_of_attempts < 15){esp_wifi_connect();}
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("\n\n\nESP got IP!\n\n\n");
        connected = true;
        break;
    default:
        break;
    }
}