#include "Server.hpp"

#define mqtt_host "localhost"
#define mqtt_port 1883
static int run = 1;

using namespace std;

void connectToServer() {
    string ip = "localhost: 1883";
    string id = "consumer";

    mqtt::client client(ip, id, mqtt::create_options(MQTTVERSION_5));

    client.connect();
    client.subscribe("in");
    client.start_consuming();

    mqtt::const_message_ptr messagePointer;
    
}