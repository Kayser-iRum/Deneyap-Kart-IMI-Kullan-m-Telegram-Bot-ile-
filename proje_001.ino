
#include <deneyap.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> //Telegram botu için kütüphanemizi ekledik
#include <ArduinoJson.h>
#include <WiFi.h> // Wifi kütüphanesini ekledik
#include "lsm6dsm.h" // Dahili IMU kütüphanesi

const char* ssid = "00000000000000000000000000"; // İnternet ağınızın adı 
const char* password = "000000000000"; // İnternet ağınızın şifresi

LSM6DSM IMU;

#define BOTtoken "00000000000000000000000000000000000000000000" // Bunu Telegram üzerinden BotFather ile öğreneceğiz. Değiştirmeyi unutmayın
#define CHAT_ID "00000000" // Bunu Telegram üzerinden İdBot ile öğreneceğiz. Burayı değiştirmeyi unutmayın.

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



float deger_z; 
float deger_y; 
float deger_x;
void setup ( ) {
  Serial.begin(115200); // Seri haberleşme başlattık.
  IMU.begin(); 
  delay (100);
  client.setInsecure();
  Serial.print("İnternete bağlanıyor: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi bağlandı");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "UYGULAMA BAŞLATILDI", ""); // Uygulama başlatıldığında gönderilecek mesaj.

}

void loop ( ) {
  deger_z = IMU.readFloatGyroZ(); 
  deger_y = IMU.readFloatGyroY();
  deger_x = IMU.readFloatGyroX();

 if(deger_z && deger_y && deger_x > 20)
 {
   bot.sendMessage(CHAT_ID, "Hareket Algılandı", ""); // İsteğinize göre göndermek istediğiniz mesajı değiştirebilirsiniz. 
 }
}
