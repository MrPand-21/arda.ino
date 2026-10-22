//Task: change the underlying system via requests, Part 2
#include <Arduino_LSM6DSOX.h>
#include <WiFiNINA.h>

WiFiServer server(80);

const int LED_PIN = 2;
bool ledState = false;

setup(){

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.begin(9600);
    while(!Serial){};

    if(!IMU.begin()){
        Serial.println("Bozuk la bu");
        while(true){};
    }
    server.begin();
}

loop(){

    WiFiClient client = server.available();
    if(client){

        String method = client.readStringUntil(' ');
        String path = client.readStringUntil(' ');
        String version = client.readStringUntil(' ');
        version.trim();

        while(client.connected()){
            String nextHeader = client.readStringUntil(' ');
            nextHeader.trim();
            if(header.length() == 0){
                break;
            }
        }

        String status;
        String body;

        if (method != "GET") {
            status = "405 Method Not Allowed";
            body = senMlEncode("error", 405, nullptr);
        }
        else if(path=="/temperature"){
            if(IMU.temperatureAvailable()){
                int temperature = 0;
                IMU.readTemperature(temperature);

                status = "200 OK";
                body = senMlEncode("temperature", temperature, "Cel");
            }
            else {
                status = "503 Service Unavailable";
                body = senMlEncode("error", 503, nullptr);
            }
        }else if (path == "/led/1") {
            ledState = true;
            digitalWrite(LED_PIN, HIGH);

            status = "200 OK";
            body = senMlEncode("led", 1, nullptr);
        } else if (path == "/led/0") {
            ledState = false;
            digitalWrite(LED_PIN, LOW);

            status = "200 OK";
            body = senMlEncode("led", 0, nullptr);
        } else {
            status = "404 Not Found";
            body = senMlEncode("error", 404, nullptr);
        }

        client.println("HTTP/1.1 " + status);
        client.println("Content-Type: application/json");
        client.println("Connection: close");

        client.print("Content-Length: ");
        client.println(body.length());

        client.println();
        client.print(body);

        client.stop();
    }

}