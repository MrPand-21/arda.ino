// MQTT introduces broker: 
// a server that forwards messages between clients.
// Your Arduino connects to the broker. Your Mac also connects to that broker. They exchange messages using named topics.
#include <WiFiNINA.h>
#include <PubSubClient.h>

const char BROKER[] = "test.mosquitto.org";
const int MQTT_PORT = 1883;

const char CLIENT_ID[] = "tiot-group0-yourname";

const char TEMP_TOPIC[] =
  "/tiot/group0/temperature";

WiFiClient wifi;
PubSubClient mqtt(wifi);

void setup(){
    mqtt.setServer(BROKER, MQTT_PORT);

    if (mqtt.connect(CLIENT_ID)) {
    Serial.println("Connected to MQTT broker.");

    String body = senMlEncode("temperature", 24.6, "Cel");

    bool sent = mqtt.publish(TEMP_TOPIC, body.c_str());
    Serial.println(sent ? "Publish succeeded." : "Publish failed.");

    }else {
        Serial.println("MQTT connection failed.");
    }
}

void loop() {
  mqtt.loop();
}