#include <HTTPClient.h>
#include <ArduinoJson.h>

String inData;

//目前有BUG，內網無法使用，請用ngrok內網穿透後再使用。
char server[] = "644ecbcb66fa.ngrok.io"; 
String host   = "644ecbcb66fa.ngrok.io";
String Device = "1";

WiFiClient client;

void post_status(int _status)
{
  DynamicJsonDocument post_data(2048);
  post_data["device"] = Device;
  post_data["action"] = "status";
  post_data["value"]  = _status;

  String json;
  serializeJson(post_data, json);

  client.flush();

  if (client.connect(server, 80)) 
  {
    Serial.println("connected");
    client.println("POST /api.php HTTP/1.0");
    client.println("Host: " + host);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(10);
  }
}

String get_time()
{
  DynamicJsonDocument post_data(2048);
  post_data["device"] = Device;
  post_data["action"] = "time";

  String json;
  serializeJson(post_data, json);

  if (client.connect(server, 80)) 
  {
    Serial.println("connected");
    client.println("POST /api.php HTTP/1.0");
    client.println("Host: " + host);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(10);
  }
}
