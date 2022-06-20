#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000ULL

const int soundPin = 23;
#define SOUND_CHAN 0

RTC_DATA_ATTR int bootCount = 0;



static bool btScanAsync = true;
static bool btScanSync = false;
bool Eck = false;


void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice) {
  if(pDevice->getName() == "ECK³"){
    Eck = true;
  }
}

void setup() {
  ledcSetup(SOUND_CHAN, 1E5, 12);
  ledcAttachPin(soundPin, SOUND_CHAN);
  Serial.begin(115200);
  SerialBT.begin("ECK³"); //Bluetooth device name
  SerialBT.discoverAsync(btAdvertisedDeviceFound,random(200,1000));
}

void loop() {
  int timout = random(200,1000);
  esp_sleep_enable_timer_wakeup(timout * 3 * mS_TO_S_FACTOR);
  delay(timout);
  if(Eck == true){
    Serial.println("Gefunden");
    esp32tone(600, 1000);
    esp32tone(1200, 1000);
    esp32tone(2400, 1000);
    esp32tone(600, 1000);
    esp32tone(1200, 1000);
    esp32tone(2400, 1000);
    esp32tone(600, 1000);
    esp32tone(1200, 1000);
    esp32tone(2400, 1000);
  }
  else{
    Serial.println("Keine Eier");
  }
  esp_deep_sleep_start();
}


// tone methods for ESP32
void esp32tone(int frequency, unsigned long duration)
{
  ledcWriteTone(SOUND_CHAN, frequency);
  if (duration > 0)
  {
#ifdef SLEEPDELAY
    DelayLightSleep(duration);
#else
    delay(duration);
#endif
    ledcWrite(SOUND_CHAN, 0);
  }
}

void esp32tone(int frequency)
{
  ledcWriteTone(SOUND_CHAN, frequency);
}
