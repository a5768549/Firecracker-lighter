/*
 * Firecracker-lighter
 * Copyright 2020 a5768549
 *
 * GitHub Project：https://github.com/a5768549/Firecracker-lighter
 */
 
#include <ArduinoJson.h>

String inData;

//目前有BUG，內網無法使用，請用ngrok內網穿透後再使用。
String host   = "http://projectgroup.team:8080/Firecracker/";

char server_iot[] = "iot.cht.com.tw"; 
String host_iot   = "iot.cht.com.tw";

String CK = "PKE5W4E7RYXFKK1A5Z";
String device_id = "24563062097";

String Device = "1";

HTTPClient http;
WiFiClientSecure client;

void post_status(int _status)
{
  DynamicJsonDocument post_data(2048);
  post_data["device"] = Device;
  post_data["action"] = "status";
  post_data["value"]  = _status;

  String json;
  serializeJson(post_data, json);

  http.begin(host + "api.php");
  int httpCode = http.POST(json);
 
  if (httpCode > 0) 
  {
    String payload = http.getString();
    //Serial.println(httpCode);
    Serial.println("status " + payload);
  }
  else 
  {
    Serial.println("Error on HTTP request");
  }
  http.end();
}

void get_time()
{
  DynamicJsonDocument post_data(2048);
  post_data["device"] = Device;
  post_data["action"] = "time";

  String json;
  serializeJson(post_data, json);
  
  http.begin(host + "api.php");
  int httpCode = http.POST(json);
 
  if (httpCode > 0) 
  {
    String payload = http.getString();
    //Serial.println(httpCode);
    Serial.println(payload);
    Setting_time = payload;
  }
  else 
  {
    Serial.println("Error on HTTP request");
  }
  http.end();
}

void send_dht_temp(float value,float value2,float value3)
{
  if(value == 0 || value2 == 0)
  {
    return;
  }
  
  StaticJsonDocument<100> raw_data_temp;
  JsonArray temp_temp_nested = raw_data_temp.createNestedArray();
  temp_temp_nested.add(value);
  
  JsonArray humi_temp_nested = raw_data_temp.createNestedArray();
  humi_temp_nested.add(value2);

  JsonArray pm25_temp_nested = raw_data_temp.createNestedArray();
  pm25_temp_nested.add(value3);
  
  StaticJsonDocument<200> post_data;
  JsonArray  post_data_array  = post_data.to<JsonArray>();
  
  JsonObject temperature_nested = post_data_array.createNestedObject();
  temperature_nested["id"]    = "temp";
  temperature_nested["value"] = temp_temp_nested;
 
  JsonObject humidity_nested = post_data_array.createNestedObject();
  humidity_nested["id"]    = "humi";
  humidity_nested["value"] = humi_temp_nested;

  JsonObject pm25_nested = post_data_array.createNestedObject();
  pm25_nested["id"]    = "pm25";
  pm25_nested["value"] = pm25_temp_nested;

  String json;
  serializeJson(post_data, json);
  
  Serial.println(json);

  client.connect(server_iot,443);
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
  client.stop();
  delay(100);
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
  
  client.connect(server_iot,443);
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
