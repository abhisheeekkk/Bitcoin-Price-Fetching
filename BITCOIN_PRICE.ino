/* Made by Abhishek
 * GitHub = @abhisheeekkk
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "cJSON.h"

const char* ssid     = "*******";       //EDIIIT
const char* password = "*********";     //edit


void getData();
String payload = "";
const String endpoint = "https://api.coindesk.com/v1/bpi/currentprice.json";

void getData()
{
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    http.begin(endpoint); //Specify the URL
    int httpCode = http.GET();  //Make the request
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      int len = payload.length();
//      Serial.println(payload);
//      Serial.println(len);
//      Serial.println("FINE TILL HERE");

      char inp[payload.length() + 1];
      payload.toCharArray(inp, payload.length() + 1);
//      Serial.println(inp);

      cJSON * msg = NULL;
      msg = cJSON_Parse(inp);

      cJSON * timee = cJSON_GetObjectItem(msg, "time");
      cJSON * updated = cJSON_GetObjectItem(timee, "updated");

      cJSON * coinname = cJSON_GetObjectItem(msg, "chartName");
      cJSON * priceitr = cJSON_GetObjectItem(msg, "bpi");

      cJSON * priceitrusd = cJSON_GetObjectItem(priceitr, "USD");

      cJSON * rate = cJSON_GetObjectItem(priceitrusd, "rate");
      cJSON * currency = cJSON_GetObjectItem(priceitrusd, "description");
      Serial.printf("The rate of per %s is %s %s on %s.(Source - Coindesk)", coinname->valuestring, rate->valuestring, currency->valuestring, updated->valuestring);
      Serial.println();
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("connecting");


  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.println(".");
  }
  Serial.println("CONECTED!!");
  
}

void loop() {
  Serial.println("************************************************************************************************************************");
  delay(60000);
  getData();

}
