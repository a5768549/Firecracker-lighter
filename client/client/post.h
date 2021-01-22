/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
#include <ArduinoJson.h>

String inData;

//目前有BUG，內網無法使用，請用ngrok內網穿透後再使用。
char server[] = "projectgroup.team"; 
String host   = "projectgroup.team";
int port = 8080;

char server_iot[] = "iot.cht.com.tw"; 
String host_iot   = "iot.cht.com.tw";

String CK = "PKE5W4E7RYXFKK1A5Z";
String device_id = "24563062097";

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

  if (client.connect(server, port)) 
  {
    Serial.println("connected");
    client.println("POST /Firecracker/api.php HTTP/1.0");
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

void get_time()
{
  DynamicJsonDocument post_data(2048);
  post_data["device"] = Device;
  post_data["action"] = "time";

  String json;
  serializeJson(post_data, json);
  if (client.connect(server, port)) 
  {
    Serial.println("connected");
    client.println("POST /Firecracker/api.php HTTP/1.0");
    client.println("Host: " + host);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(100);
  }
}

void send_dht_temp(float value)
{
  if(value == 0)
  {
    return;
  }
  StaticJsonDocument<100> temp;
  JsonArray temperature_temp_nested = temp.createNestedArray();
  temperature_temp_nested.add(value);
  
  StaticJsonDocument<200> post_data;
  JsonArray  temperature_array  = post_data.to<JsonArray>();
  JsonObject temperature_nested = temperature_array.createNestedObject();
  temperature_nested["id"]    = "temp";
  temperature_nested["value"] = temperature_temp_nested;

  String json;
  serializeJson(post_data, json);

  if (client.connect(server_iot, 80)) 
  {
    Serial.println("connected");
    client.println("POST /iot/v1/device/24563062097/rawdata HTTP/1.1");
    client.println("Host: " + host_iot);
    client.println("CK: " + CK);
    client.println("device_id: " + device_id);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(100);
  }
}

void send_dht_humi(float value)
{
  if(value == 0)
  {
    return;
  }
  StaticJsonDocument<100> temp;
  JsonArray humidity_temp_nested = temp.createNestedArray();
  humidity_temp_nested.add(value);
  
  StaticJsonDocument<200> post_data;
  JsonArray  humidity_array  = post_data.to<JsonArray>();
  JsonObject humidity_nested = humidity_array.createNestedObject();
  humidity_nested["id"]    = "humi";
  humidity_nested["value"] = humidity_temp_nested;

  String json;
  serializeJson(post_data, json);

  if (client.connect(server_iot, 80)) 
  {
    Serial.println("connected");
    client.println("POST /iot/v1/device/24563062097/rawdata HTTP/1.1");
    client.println("Host: " + host_iot);
    client.println("CK: " + CK);
    client.println("device_id: " + device_id);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(100);
  }
}

void send_pm25(float value)
{
  if(value == 0)
  {
    return;
  }
  StaticJsonDocument<100> temp;
  JsonArray humidity_temp_nested = temp.createNestedArray();
  humidity_temp_nested.add(value);
  
  StaticJsonDocument<200> post_data;
  JsonArray  humidity_array  = post_data.to<JsonArray>();
  JsonObject humidity_nested = humidity_array.createNestedObject();
  humidity_nested["id"]    = "pm25";
  humidity_nested["value"] = humidity_temp_nested;

  String json;
  serializeJson(post_data, json);

  if (client.connect(server_iot, 80)) 
  {
    Serial.println("connected");
    client.println("POST /iot/v1/device/24563062097/rawdata HTTP/1.1");
    client.println("Host: " + host_iot);
    client.println("CK: " + CK);
    client.println("device_id: " + device_id);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.print  ("Content-Length: ");
    client.println(json.length());
    client.println();
    client.print  (json);
    client.println("Connection: close");
    delay(100);
  }
}
