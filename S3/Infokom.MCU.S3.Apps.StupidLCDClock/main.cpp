#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "time.h"

// Thirrja e librarisë sonë të personalizuar
#include <Infokom.MCU.ESP32.S3.Sensors.h>

const char *WIFI_SSID = "YOUR_WIFI_SSID";
const char *WIFI_PASS = "YOUR_WIFI_PASSWORD";

// Konfigurimi NTP (CET - Vlorë, Shqipëri)
const char *NTP_HOST = "pool.ntp.org";
const long GMTZONE_OFFSET = 3600;
const int DAYSAVE_OFFSET = 3600;

int lastSecond = -1;

// Instancimi i objekteve tona
InfokomLightController environment(4, 5, 1500, 2000);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	Serial.begin(115200);

	environment.begin();

	Wire.begin(8, 9);
	lcd.init();
	lcd.backlight();

	lcd.setCursor(0, 0);
	lcd.print("Lidhje me Wi-Fi");

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	lcd.clear();
	lcd.print("Wi-Fi U Lidh!");
	delay(1000);

	configTime(GMTZONE_OFFSET, DAYSAVE_OFFSET, NTP_HOST);
	lcd.clear();
}

void loop()
{
	if (environment.isDark())
	{
		lcd.noBacklight();
	}
	else
	{
		lcd.backlight();
	}

	struct tm timeinfo;
	if (getLocalTime(&timeinfo))
	{
		char dateBuffer[16];
		char timeBuffer[16];

		strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &timeinfo);
		strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);

		lcd.setCursor(0, 0);
		lcd.print("Data: ");
		lcd.print(dateBuffer);

		lcd.setCursor(0, 1);
		lcd.print("Ora:  ");
		lcd.print(timeBuffer);

		if (timeinfo.tm_sec != lastSecond)
		{
			lastSecond = timeinfo.tm_sec;
			environment.triggerBeep(50);
		}
	}

	delay(50);
}
