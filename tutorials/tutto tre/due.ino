//Task: change the underlying system via requests, Part 1
#include <WiFiNINA.h>

WiFiServer server(80);

void setup(){
    server.begin();
}

void loop(){
    WiFiClient client = server.available();

    if (client) {
        client.setTimeout(1000);

        //extract "GET /temperature HTTP/1.1"
        String method = client.readStringUntil(' ');
        String path = client.readStringUntil(' ');
        String version = client.readStringUntil('\n');
        version.trim();

        // Read the remaining request headers
        while (client.connected()) {
            String header = client.readStringUntil('\n');
            header.trim();

            if (header.length() == 0) {
            break;
            }
        }

        String status;
        String body;

        if (method == "GET" && path == "/temperature") {
            status = "200 OK";
            body = senMlEncode("temperature", 24.6, "Cel");
        }
        else {
            status = "404 Not Found";
            body = senMlEncode("error", 404, nullptr);
        }

        client.println("HTTP/1.1 " + status);
        client.print(body);

        client.stop();
    }
}