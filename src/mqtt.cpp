#include "mqtt.h"

Mqtt::Mqtt(Wifi *wifi){
    ESP_LOGI(TAG, "STARTING MQTT CLIENT");

    esp_mqtt_client_config_t config = {
        .broker = {
            .address = {
                    .uri = "mqtt://broker.emqx.io:1883"
            }
        },
        .session = {
            .protocol_ver = MQTT_PROTOCOL_V_5,
        },
        .network = {
            .disable_auto_reconnect = true,
        }
    };

    while(!wifi->get_connected_status()){vTaskDelay(100);}

    client = esp_mqtt_client_init(&config);

    esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

Mqtt::~Mqtt(){
    vEventGroupDelete(mqtt_event_group);
}

void Mqtt::mqtt_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data){
    //ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", event_base, event_id);

    switch (event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        // MQTT_CONNECTED = 1;
        break;

    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    
    default:
        break;
    }
}