#include "Definitions.h"
#include "JaamUtils.h"
#include <Preferences.h>
#include <WiFiManager.h>
#include <ESPAsyncWebServer.h>
#include <StreamString.h>
#include <ESPmDNS.h>
#include <async.h>
#include <ArduinoJson.h>
#include <NTPtime.h>
#if TELNET_ENABLED
#include <TelnetSpy.h>
#endif
#if ARDUINO_OTA_ENABLED
#include <ArduinoOTA.h>
#endif
#include "JaamHomeAssistant.h"
// to ignore the warning about the unused variable
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "JaamDisplay.h"
#if FW_UPDATE_ENABLED
#include <HTTPUpdate.h>
#endif
#include <ArduinoWebsockets.h>
#include "JaamLightSensor.h"
#include "JaamClimateSensor.h"
#include "JaamButton.h"
#if BUZZER_ENABLED
#include <melody_player.h>
#include <melody_factory.h>
#endif
#include <esp_task_wdt.h>

const PROGMEM char* VERSION = "4.2-b95";

struct Settings {
  const char*   apssid                 = "JAAM";
  const char*   softwareversion        = VERSION;
  int           pixelcount             = 26;
  int           bg_pixelcount          = 0;
  int           buttontime             = 100;
  int           powerpin               = 12;
  int           wifipin                = 14;
  int           datapin                = 25;
  int           hapin                  = 26;
  int           reservedpin            = 27;

  // ------- web config start
  char    devicename[31]         = "JAAM";
  char    devicedescription[51]  = "JAAM Informer";
  char    broadcastname[31]      = "jaam";
  char    ntphost[31]            = "pool.ntp.org";
  char    serverhost[31]         = "jaam.net.ua";
  int     websocket_port         = 2052;
  int     updateport             = 2095;
  char    bin_name[51]           = "";
  char    identifier[51]         = "github";
  int     legacy                 = 1;
  int     pixelpin               = 13;
  int     bg_pixelpin            = -1;
  int     service_ledpin         = -1;
  int     buttonpin              = -1;
  int     button2pin             = -1;
  int     alertpin               = -1;
  int     clearpin               = -1;
  int     buzzerpin              = -1;
  int     lightpin               = -1;
  int     alert_clear_pin_mode   = 0;
  float   alert_clear_pin_time   = 1;
  int     ha_mqttport            = 1883;
  char    ha_mqttuser[31]        = "";
  char    ha_mqttpassword[66]    = "";
  char    ha_brokeraddress[31]   = "";
  int     current_brightness     = 50;
  int     brightness             = 50;
  int     brightness_day         = 50;
  int     brightness_night       = 5;
  int     brightness_mode        = 0;
  int     home_alert_time        = 0;
  int     color_alert            = 0;
  int     color_clear            = 120;
  int     color_new_alert        = 30;
  int     color_alert_over       = 100;
  int     enable_explosions      = 1;
  int     color_explosion        = 180;
  int     enable_missiles        = 1;
  int     color_missiles         = 275;
  int     enable_drones          = 1;
  int     color_drones           = 330;
  int     color_home_district    = 120;
  int     brightness_alert       = 100;
  int     brightness_clear       = 100;
  int     brightness_new_alert   = 100;
  int     brightness_alert_over  = 100;
  int     brightness_explosion   = 100;
  int     brightness_home_district = 100;
  int     brightness_bg          = 100;
  int     brightness_service     = 50;
  int     weather_min_temp       = -10;
  int     weather_max_temp       = 30;
  int     alarms_auto_switch     = 1;
  int     home_district          = 7;
  int     kyiv_district_mode     = 1;
  int     service_diodes_mode    = 0;
  int     new_fw_notification    = 1;
  int     ha_light_brightness    = 50;
  int     ha_light_r             = 215;
  int     ha_light_g             = 7;
  int     ha_light_b             = 255;
  int     sound_on_min_of_sl     = 0;
  int     sound_on_alert         = 0;
  int     melody_on_alert        = 4;
  int     sound_on_alert_end     = 0;
  int     melody_on_alert_end    = 5;
  int     sound_on_explosion     = 0;
  int     melody_on_explosion    = 18;
  int     sound_on_every_hour    = 0;
  int     sound_on_button_click  = 0;
  int     mute_sound_on_night    = 0;
  int     melody_volume          = 100;
  int     invert_display         = 0;
  int     dim_display_on_night   = 1;
  int     ignore_mute_on_alert   = 0;


  // ------- Map Modes:
  // -------  0 - Off
  // -------  1 - Alarms
  // -------  2 - Weather
  // -------  3 - UA Flag
  // -------  4 - Random colors
  // -------  5 - Lamp
  int     map_mode               = 1;

  // ------- Display Modes:
  // -------  0 - Off
  // -------  1 - Clock
  // -------  2 - Home District Temperature
  // -------  3 - Tech info
  // -------  4 - Climate (if sensor installed)
  // -------  9 - Toggle modes
  int     display_mode           = 2;
  int     display_mode_time      = 5;
  int     toggle_mode_weather    = 1;
  int     toggle_mode_temp       = 1;
  int     toggle_mode_hum        = 1;
  int     toggle_mode_press      = 1;
  int     button_mode            = 0;
  int     button2_mode           = 0;
  int     button_mode_long       = 0;
  int     button2_mode_long      = 0;
  int     alarms_notify_mode     = 2;
  int     display_model          = 1;
  int     display_width          = 128;
  int     display_height         = 32;
  int     day_start              = 8;
  int     night_start            = 22;
  int     ws_alert_time          = 150000;
  int     ws_reboot_time         = 300000;
  int     min_of_silence         = 1;
  int     fw_update_channel      = 0;
  float   temp_correction        = 0;
  float   hum_correction         = 0;
  float   pressure_correction    = 0;
  float   light_sensor_factor    = 1;
  int     time_zone              = 2;
  int     alert_on_time          = 5;
  int     alert_off_time         = 5;
  int     explosion_time         = 3;
  int     alert_blink_time       = 2;
  // ------- web config end
};

#if TELNET_ENABLED
TelnetSpy SerialAndTelnet;
#define LOG SerialAndTelnet
#else
#define LOG Serial
#endif

Settings settings;

Firmware currentFirmware;
#if FW_UPDATE_ENABLED
Firmware latestFirmware;
#endif

using namespace websockets;

Preferences       preferences;
WiFiManager       wm;
WiFiClient        client;
WebsocketsClient  client_websocket;
AsyncWebServer    webserver(80);
NTPtime           timeClient(2);
DSTime            dst(3, 0, 7, 3, 10, 0, 7, 4); //https://en.wikipedia.org/wiki/Eastern_European_Summer_Time
Async             asyncEngine = Async(20);
JaamDisplay       display;
JaamLightSensor   lightSensor;
JaamClimateSensor climate;
JaamHomeAssistant ha;
std::map<int, int> displayModeHAMap;
#if BUZZER_ENABLED
MelodyPlayer* player;
#endif

enum ServiceLed {
  POWER,
  WIFI,
  DATA,
  HA,
  RESERVED
};

enum SoundType {
  MIN_OF_SILINCE,
  MIN_OF_SILINCE_END,
  REGULAR,
  ALERT_ON,
  ALERT_OFF,
  EXPLOSIONS,
  SINGLE_CLICK,
  LONG_CLICK
};

struct ServiceMessage {
  const char* title;
  const char* message;
  int textSize;
  long endTime;
  int expired;
};

ServiceMessage serviceMessage;

CRGB strip[26];
CRGB bg_strip[100];
CRGB service_strip[5];
int service_strip_update_index = 0;

uint8_t   alarm_leds[26];
long      alarm_time[26];
float     weather_leds[26];
long      explosions_time[26];
long      missiles_time[26];
long      drones_time[26];
uint8_t   flag_leds[26];

bool      isFirstDataFetchCompleted = false;

float     brightnessFactor = 0.5f;
int       minBrightness = 1;
float     minBlinkBrightness = 0.05f;

bool    shouldWifiReconnect = false;
bool    websocketReconnect = false;
bool    isDaylightSaving = false;
time_t  websocketLastPingTime = 0;
int     offset = 9;
bool    initUpdate = false;
#if FW_UPDATE_ENABLED
bool    fwUpdateAvailable = false;
char    newFwVersion[25];
#endif
char    currentFwVersion[25];
bool    apiConnected;
bool    haConnected;
int     prevMapMode = 1;
bool    alarmNow = false;
bool    pinAlarmNow = false;
long    homeExplosionTime = 0;
bool    minuteOfSilence = false;
bool    uaAnthemPlaying = false;
short   clockBeepInterval = -1;
bool    isMapOff = false;
bool    isDisplayOff = false;
bool    nightMode = false;
int     prevBrightness = -1;
int     needRebootWithDelay = -1;
int     beepHour = -1;
char    uptimeChar[25];
float   cpuTemp;
float   usedHeapSize;
float   freeHeapSize;
int     wifiSignal;

int     ledsBrightnessLevels[BR_LEVELS_COUNT]; // Array containing LEDs brightness values
int     currentDimDisplay = 0;

// 0 - Time
// 1 - Home District Temperature
// 2 - Climate Temperature
// 3 - Climate Humidity
// 4 - Climate Pressure
int     currentDisplayToggleMode = 0;
int     currentDisplayToggleIndex = 0;

JaamButton buttons;

#define NIGHT_BRIGHTNESS_LEVEL 2

int binsCount = 0;
char* bin_list[MAX_BINS_LIST_SIZE];

int testBinsCount = 0;
char*  test_bin_list[MAX_BINS_LIST_SIZE];

char chipID[13];
char localIP[16];

int ignoreDisplayModeOptions[DISPLAY_MODE_OPTIONS_MAX] = {-1, -1, -1, -1, -1, -1};
int ignoreSingleClickOptions[SINGLE_CLICK_OPTIONS_MAX] = {-1, -1, -1, -1, -1, -1, -1};
int ignoreLongClickOptions[LONG_CLICK_OPTIONS_MAX] = {-1, -1, -1, -1, -1, -1, -1, -1};

bool isBgStripEnabled() {
  return settings.bg_pixelpin > -1 && settings.bg_pixelcount > 0;
}

bool isServiceStripEnabled() {
  return settings.service_ledpin > -1;
}

bool isAlertPinEnabled() {
  return settings.alertpin > -1;
}

bool isClearPinEnabled() {
  return settings.clearpin > -1;
}

bool isBuzzerEnabled() {
  return settings.buzzerpin > -1;
}

bool isAnalogLightSensorEnabled() {
  return settings.lightpin > -1;
}

CRGB fromRgb(int r, int g, int b, float brightness) {
  // use brightnessFactor as a multiplier to get scaled brightness
  int scaledBrightness = (brightness == 0.0f) ? 0 : round(max(brightness, minBrightness * 1.0f) * 255.0f / 100.0f * brightnessFactor);
  return CRGB().setRGB(r, g, b).nscale8_video(scaledBrightness);
}

CRGB fromHue(int hue, float brightness) {
  RGBColor rgb = hue2rgb(hue);
  return fromRgb(rgb.r, rgb.g, rgb.b, brightness);
}

// Forward declarations
void displayCycle();

void showServiceMessage(const char* message, const char* title = "", int duration = 2000) {
  if (!display.isDisplayAvailable()) return;
  serviceMessage.title = title;
  serviceMessage.message = message;
  serviceMessage.textSize = display.getTextSizeToFitDisplay(message);
  serviceMessage.endTime = millis() + duration;
  serviceMessage.expired = false;
  displayCycle();
}

void rebootDevice(int time = 2000, bool async = false) {
  if (async) {
    needRebootWithDelay = time;
    return;
  }
  showServiceMessage("Перезавантаження..", "", time);
  delay(time);
  display.clearDisplay();
  display.display();
  ESP.restart();
}

int expMap(int x, int in_min, int in_max, int out_min, int out_max) {
  // Apply exponential transformation to the original input value x
  float normalized = (float)(x - in_min) / (in_max - in_min);
  float scaled = pow(normalized, 2);

  // Map the scaled value to the output range
  return (int)(scaled * (out_max - out_min) + out_min);
}

void playMelody(const char* melodyRtttl) {
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    Melody melody = MelodyFactory.loadRtttlString(melodyRtttl);
    player->playAsync(melody);
  }
#endif
}

void playMelody(SoundType type) {
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    switch (type) {
    case MIN_OF_SILINCE:
      playMelody(MOS_BEEP);
      break;
    case MIN_OF_SILINCE_END:
      playMelody(UA_ANTHEM);
      break;
    case ALERT_ON:
      playMelody(MELODIES[settings.melody_on_alert]);
      break;
    case ALERT_OFF:
      playMelody(MELODIES[settings.melody_on_alert_end]);
      break;
    case EXPLOSIONS:
      playMelody(MELODIES[settings.melody_on_explosion]);
      break;
    case REGULAR:
      playMelody(CLOCK_BEEP);
      break;
    case SINGLE_CLICK:
      playMelody(SINGLE_CLICK_SOUND);
      break;
    case LONG_CLICK:
      playMelody(LONG_CLICK_SOUND);
      break;
    }
  }
#endif
}

bool isItNightNow() {
  // if day and night start time is equels it means it's always day, return day
  if (settings.night_start == settings.day_start) return false;

  int currentHour = timeClient.hour();

  // handle case, when night start hour is bigger than day start hour, ex. night start at 22 and day start at 9
  if (settings.night_start > settings.day_start) return currentHour >= settings.night_start || currentHour < settings.day_start ? true : false;

  // handle case, when day start hour is bigger than night start hour, ex. night start at 1 and day start at 8
  return currentHour < settings.day_start && currentHour >= settings.night_start ? true : false;
}

// Determine the current brightness level
int getCurrentBrightnessLevel() {
  int currentValue = 0;
  int maxValue;
  if (lightSensor.isLightSensorAvailable()) {
    // Digital light sensor has higher priority. BH1750 measurmant range is 0..27306 lx. 500 lx - very bright indoor environment.
    currentValue = round(lightSensor.getLightLevel(settings.light_sensor_factor));
    maxValue = 500;
  } else if (isAnalogLightSensorEnabled()) {
    // reads the input on analog pin (value between 0 and 4095)
    currentValue = lightSensor.getPhotoresistorValue(settings.light_sensor_factor);
    // 2600 - very bright indoor environment.
    maxValue = 2600;
  }
  int level = map(min(currentValue, maxValue), 0, maxValue, 0, BR_LEVELS_COUNT - 1);
  // LOG.print("Brightness level: ");
  // LOG.println(level);
  return level;
}

int getNightModeType() {
  // Night Mode activated by button
  if (nightMode) return 1;
  // Night mode activated by time
  if (settings.brightness_mode == 1 && isItNightNow()) return 2;
  // Night mode activated by sensor
  if (settings.brightness_mode == 2 && getCurrentBrightnessLevel() <= NIGHT_BRIGHTNESS_LEVEL) return 3;
  // Night mode is off
  return 0;
}

bool needToPlaySound(SoundType type) {
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {

    // do not play any sound before websocket connection
    if (!isFirstDataFetchCompleted) return false;

    // ignore mute on alert
    if (SoundType::ALERT_ON == type && settings.sound_on_alert && settings.ignore_mute_on_alert) return true;

    // disable sounds on night mode
    if (settings.mute_sound_on_night && getNightModeType() > 0) return false;

    switch (type) {
    case MIN_OF_SILINCE:
      return settings.sound_on_min_of_sl;
    case MIN_OF_SILINCE_END:
      return settings.sound_on_min_of_sl;
    case ALERT_ON:
      return settings.sound_on_alert;
    case ALERT_OFF:
      return settings.sound_on_alert_end;
    case EXPLOSIONS:
      return settings.sound_on_explosion;
    case REGULAR:
      return settings.sound_on_every_hour;
    case SINGLE_CLICK:
    case LONG_CLICK:
      return settings.sound_on_button_click;
    }
  }
#endif
  return false;
}

void servicePin(ServiceLed type, uint8_t status, bool force) {
  if (force || ((settings.legacy == 0 || settings.legacy == 3) && settings.service_diodes_mode)) {
    int pin = 0;
    int scaledBrightness = (settings.brightness_service == 0) ? 0 : round(max(settings.brightness_service, minBrightness) * 255.0f / 100.0f * brightnessFactor);
    switch (type) {
      case POWER:
        pin = settings.powerpin;
        service_strip[0] = status ? CRGB(CRGB::Red).nscale8_video(scaledBrightness) : CRGB::Black;
        break;
      case WIFI:
        pin = settings.wifipin;
        service_strip[1] = status ? CRGB(CRGB::Blue).nscale8_video(scaledBrightness) : CRGB::Black;
        break;
      case DATA:
        pin = settings.datapin;
        service_strip[2] = status ? CRGB(CRGB::Green).nscale8_video(scaledBrightness) : CRGB::Black;
        break;
      case HA:
        pin = settings.hapin;
        service_strip[3] = status ? CRGB(CRGB::Yellow).nscale8_video(scaledBrightness) : CRGB::Black;
        break;
      case RESERVED:
        pin = settings.reservedpin;
        service_strip[4] = status ? CRGB(CRGB::White).nscale8_video(scaledBrightness) : CRGB::Black;
        break;
    }
    if (pin > 0 && settings.legacy == 0) {
      digitalWrite(pin, status);
    }
    if (isServiceStripEnabled() && settings.legacy == 3) {
      FastLED.show();
    }
  }
}

void reportSettingsChange(const char* settingKey, const char* settingValue) {
  char settingsInfo[100];
  JsonDocument settings;
  settings[settingKey] = settingValue;
  sprintf(settingsInfo, "settings:%s", settings.as<String>().c_str());
  client_websocket.send(settingsInfo);
  LOG.printf("Sent settings analytics: %s\n", settingsInfo);
}

void reportSettingsChange(const char* settingKey, int newValue) {
  char settingsValue[10];
  sprintf(settingsValue, "%d", newValue);
  reportSettingsChange(settingKey, settingsValue);
}

void reportSettingsChange(const char* settingKey, float newValue) {
  char settingsValue[10];
  sprintf(settingsValue, "%.1f", newValue);
  reportSettingsChange(settingKey, settingsValue);
}

static void printNtpStatus(NTPtime* timeClient) {
  LOG.print("NTP status: ");
    switch (timeClient->NTPstatus()) {
      case 0:
        LOG.println("OK");
        LOG.print("Current date and time: ");
        LOG.println(timeClient->unixToString("DD.MM.YYYY hh:mm:ss"));
        break;
      case 1:
        LOG.println("NOT_STARTED");
        break;
      case 2:
        LOG.println("NOT_CONNECTED_WIFI");
        break;
      case 3:
        LOG.println("NOT_CONNECTED_TO_SERVER");
        break;
      case 4:
        LOG.println("NOT_SENT_PACKET");
        break;
      case 5:
        LOG.println("WAITING_REPLY");
        break;
      case 6:
        LOG.println("TIMEOUT");
        break;
      case 7:
        LOG.println("REPLY_ERROR");
        break;
      case 8:
        LOG.println("NOT_CONNECTED_ETHERNET");
        break;
      default:
        LOG.println("UNKNOWN_STATUS");
        break;
    }
}

void syncTime(int8_t attempts) {
  timeClient.tick();
  if (timeClient.status() == UNIX_OK) return;
  LOG.println("Time not synced yet!");
  printNtpStatus(&timeClient);
  int8_t count = 1;
  while (timeClient.NTPstatus() != NTP_OK && count <= attempts) {
    LOG.printf("Attempt #%d of %d\n", count, attempts);
    if (timeClient.NTPstatus() != NTP_WAITING_REPLY) {
      LOG.println("Force update!");
      timeClient.updateNow();
    }
    timeClient.tick();
    if (count < attempts) delay(1000);
    count++;
    printNtpStatus(&timeClient);
  }
}

void displayMessage(const char* message, const char* title = "", int messageTextSize = -1) {
  display.displayMessage(message, title, messageTextSize);
}

char* getLocalIP() {
  strcpy(localIP, WiFi.localIP().toString().c_str());
  return localIP;
}

static void wifiEvents(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED: {
      char softApIp[16];
      strcpy(softApIp, WiFi.softAPIP().toString().c_str());
      displayMessage(softApIp, "Введіть у браузері:");
      WiFi.removeEvent(wifiEvents);
      break;
    }
    default:
      break;
  }
}

void apCallback(WiFiManager* wifiManager) {
  const char* message = wifiManager->getConfigPortalSSID().c_str();
  displayMessage(message, "Підключіться до WiFi:");
  WiFi.onEvent(wifiEvents);
}

void saveConfigCallback() {
  showServiceMessage(wm.getWiFiSSID(true).c_str(), "Збережено AP:");
  delay(2000);
  rebootDevice();
}

#if ARDUINO_OTA_ENABLED
void showOtaUpdateErrorMessage(ota_error_t error) {
  switch (error) {
    case OTA_AUTH_ERROR:
      showServiceMessage("Авторизація", "Помилка оновлення:", 5000);
      break;
    case OTA_CONNECT_ERROR:
      showServiceMessage("Збій підключення", "Помилка оновлення:", 5000);
      break;
    case OTA_RECEIVE_ERROR:
      showServiceMessage("Збій отримання", "Помилка оновлення:", 5000);
      break;
    default:
      showServiceMessage("Щось пішло не так", "Помилка оновлення:", 5000);
      break;
  }
}
#endif

void mapUpdate(float percents) {
  CRGB hue = fromHue(86, settings.current_brightness);
  int ledsCount = round(settings.pixelcount * percents);
  for (uint16_t i = 0; i < settings.pixelcount; i++) {
    if (i < ledsCount) {
      strip[i] = hue;
    } else {
      strip[i] = CRGB::Black;
    }
  }
  if (isBgStripEnabled()) {
    int bgLedsCount = round(settings.bg_pixelcount * percents);
    float bgBrightnessFactor = settings.brightness_bg / 100.0f;
    CRGB bgHue = fromHue(86, settings.current_brightness * bgBrightnessFactor);

    for (uint16_t i = 0; i < settings.bg_pixelcount; i++) {
      if (i < bgLedsCount) {
        bg_strip[i] = hue;
      } else {
        bg_strip[i] = CRGB::Black;
      }
    }
  }
  if (isServiceStripEnabled()) {
    fill_solid(service_strip, 5, CRGB::Black);
    service_strip[service_strip_update_index] = hue;
    if (service_strip_update_index == 4) {
      service_strip_update_index = 0;
    } else {
      service_strip_update_index++;
    }
  }
  FastLED.show();
}

#if FW_UPDATE_ENABLED || ARDUINO_OTA_ENABLED
void showUpdateProgress(size_t progress, size_t total) {
  if (total == 0) return;
  char progressText[5];
  sprintf(progressText, "%d%%", progress / (total / 100));
  showServiceMessage(progressText, "Оновлення:");
  mapUpdate(progress * 1.0f / total);
}

void showUpdateStart() {
  showServiceMessage("Починаємо!", "Оновлення:");
  delay(1000);
}

void showUpdateEnd() {
  showServiceMessage("Перезавантаження..", "Оновлення:");
  delay(1000);
}
#endif

#if FW_UPDATE_ENABLED
void showHttpUpdateErrorMessage(int error) {
  switch (error) {
    case HTTP_UE_TOO_LESS_SPACE:
      showServiceMessage("Замало місця", "Помилка оновлення:", 5000);
      break;
    case HTTP_UE_SERVER_NOT_REPORT_SIZE:
      showServiceMessage("Невідомий розмір файлу", "Помилка оновлення:", 5000);
      break;
    case HTTP_UE_BIN_FOR_WRONG_FLASH:
      showServiceMessage("Неправильний тип пам'яті", "Помилка оновлення:", 5000);
      break;
    default:
      showServiceMessage("Щось пішло не так", "Помилка оновлення:", 5000);
      break;
  }
}
#endif

void initBroadcast() {
  LOG.println("Init network device broadcast");

  if (!MDNS.begin(settings.broadcastname)) {
    LOG.println("Error setting up mDNS responder");
    showServiceMessage("Помилка mDNS");
    while (1) {
      delay(1000);
    }
  }
  LOG.printf("Device broadcasted to network: %s.local", settings.broadcastname);
  LOG.println();
}

int getCurrentMapMode() {
  if (minuteOfSilence || uaAnthemPlaying) return 3; // ua flag

  int currentMapMode = isMapOff ? 0 : settings.map_mode;
  int position = settings.home_district;
  switch (settings.alarms_auto_switch) {
    case 1:
      for (int j = 0; j < COUNTERS[position]; j++) {
        int alarm_led_id = calculateOffset(NEIGHBORING_DISTRICS[position][j], offset);
        if (alarm_leds[alarm_led_id] != 0) {
          currentMapMode = 1;
        }
      }
      break;
    case 2:
      if (alarm_leds[calculateOffset(position, offset)] != 0) {
        currentMapMode = 1;
      }
  }
  return currentMapMode;
}

void onMqttStateChanged(bool haStatus) {
  LOG.print("Home Assistant MQTT state changed! State: ");
  LOG.println(haStatus ? "Connected" : "Disconnected");
  haConnected = haStatus;
  servicePin(HA, haConnected ? HIGH : LOW, false);
  if (haConnected) {
    // Update HASensors values (Unlike the other device types, the HASensor doesn't store the previous value that was set. It means that the MQTT message is produced each time the setValue method is called.)
    ha.setMapModeCurrent(MAP_MODES[getCurrentMapMode()]);
    ha.setHomeDistrict(DISTRICTS_ALPHABETICAL[numDistrictToAlphabet(settings.home_district)]);
  }
}

// Forward declarations
void mapCycle();

bool saveMapMode(int newMapMode) {
  if (newMapMode == settings.map_mode) return false;

  if (newMapMode == 5) {
    prevMapMode = settings.map_mode;
  }
  settings.map_mode = newMapMode;
  preferences.begin("storage", false);
  preferences.putInt("mapmode", settings.map_mode);
  preferences.end();
  reportSettingsChange("map_mode", settings.map_mode);
  LOG.print("map_mode commited to preferences: ");
  LOG.println(settings.map_mode);
  ha.setLampState(settings.map_mode == 5);
  ha.setMapMode(settings.map_mode);
  ha.setMapModeCurrent(MAP_MODES[getCurrentMapMode()]);
  showServiceMessage(MAP_MODES[settings.map_mode], "Режим мапи:");
  // update to selected mapMode
  mapCycle();
  return true;
}

bool onNewLampStateFromHa(bool state) {
  if (settings.map_mode == 5 && state) return false;
  int newMapMode = state ? 5 : prevMapMode;
  return saveMapMode(newMapMode);
}

int getHaDisplayMode(int localDisplayMode) {
  return displayModeHAMap[localDisplayMode];
}

void updateInvertDisplayMode() {
  display.invertDisplay(settings.invert_display);
}

bool shouldDisplayBeOff() {
  return serviceMessage.expired && (isDisplayOff || settings.display_mode == 0);
}

int getBrightnessFromSensor(int brightnessLevels[]) {
  return brightnessLevels[getCurrentBrightnessLevel()];
}

int getCurrentBrightnes(int defaultBrightness, int dayBrightness, int nightBrightness, int brightnessLevels[]) {
  // highest priority for night mode, return night brightness
  if (nightMode) return nightBrightness;

  // // if nightMode deactivated return previous brightness
  // if (prevBrightness >= 0) {
  //   int tempBrightnes = prevBrightness;
  //   prevBrightness = -1;
  //   return tempBrightnes;
  // }

  // if auto brightness set to day/night mode, check current hour and choose brightness
  if (settings.brightness_mode == 1) return isItNightNow() ? nightBrightness : dayBrightness;

  // if auto brightnes set to light sensor, read sensor value end return appropriate brightness.
  if (settings.brightness_mode == 2) return brightnessLevels ? getBrightnessFromSensor(brightnessLevels) : getCurrentBrightnessLevel() <= NIGHT_BRIGHTNESS_LEVEL ? nightBrightness : dayBrightness;

  // if auto brightnes deactivated, return regular brightnes
  // default
  return defaultBrightness;
}

void updateDisplayBrightness() {
  if (!display.isDisplayAvailable()) return;
  int localDimDisplay = shouldDisplayBeOff() ? 0 : getCurrentBrightnes(0, 0, settings.dim_display_on_night ? 1 : 0, NULL);
  if (localDimDisplay == currentDimDisplay) return;
  currentDimDisplay = localDimDisplay;
  LOG.printf("Set display dim: %s\n", currentDimDisplay ? "ON" : "OFF");
  display.dim(currentDimDisplay);
}

//--Update
#if FW_UPDATE_ENABLED
void saveLatestFirmware() {
  const int *count = settings.fw_update_channel ? &testBinsCount : &binsCount;
  Firmware firmware = currentFirmware;
  for (int i = 0; i < *count; i++) {
    const char* filename = settings.fw_update_channel ? test_bin_list[i] : bin_list[i];
    if (prefix("latest", filename)) continue;
    Firmware parsedFirmware = parseFirmwareVersion(filename);
    if (firstIsNewer(parsedFirmware, firmware)) {
      firmware = parsedFirmware;
    }
  }
  latestFirmware = firmware;
  fwUpdateAvailable = firstIsNewer(latestFirmware, currentFirmware);
  fillFwVersion(newFwVersion, latestFirmware);
  LOG.printf("Latest firmware version: %s\n", newFwVersion);
  LOG.println(fwUpdateAvailable ? "New fw available!" : "No new firmware available");
}

void handleUpdateStatus(t_httpUpdate_return ret, bool isSpiffsUpdate) {
  LOG.printf("%s update status:\n", isSpiffsUpdate ? "Spiffs" : "Firmware");
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      LOG.printf("Error Occurred. Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      LOG.println("HTTP_UPDATE_NO_UPDATES");
      break;
    case HTTP_UPDATE_OK:
      if (isSpiffsUpdate) {
        LOG.println("Spiffs update successfully completed. Starting firmware update...");
      } else {
        LOG.println("Firmware update successfully completed. Rebooting...");
        rebootDevice();
      }
      break;
  }
}

void downloadAndUpdateFw(const char* binFileName, bool isBeta) {
  // disable watchdog timer while update
  disableLoopWDT();

  LOG.println("Starting firmware update...");
  char spiffUrlChar[100];
  char firmwareUrlChar[100];

  LOG.println("Building firmware url...");
  sprintf(
    firmwareUrlChar,
    "http://%s:%d%s%s",
    settings.serverhost,
    settings.updateport,
    isBeta ? "/beta/" : "/",
    binFileName
  );

  LOG.printf("Firmware url: %s\n", firmwareUrlChar);
  t_httpUpdate_return fwRet = httpUpdate.update(
    client,
    firmwareUrlChar,
    VERSION
    );
  handleUpdateStatus(fwRet, false);

  // enable watchdog timer after update
  enableLoopWDT();
}

void doUpdate() {
  if (initUpdate) {
    initUpdate = false;
    downloadAndUpdateFw(settings.bin_name, settings.fw_update_channel == 1);
  }
}
#endif
//--Update end

//--Service
void checkServicePins() {
  if (settings.legacy == 0 || settings.legacy == 3) {
    if (settings.service_diodes_mode) {
      // LOG.println("Dioded enabled");
      servicePin(POWER, HIGH, true);
      if (WiFi.status() != WL_CONNECTED) {
        servicePin(WIFI, LOW, true);
      } else {
        servicePin(WIFI, HIGH, true);
      }
      if (!haConnected) {
        servicePin(HA, LOW, true);
      } else {
        servicePin(HA, HIGH, true);
      }
      if (!client_websocket.available()) {
        servicePin(DATA, LOW, true);
      } else {
        servicePin(DATA, HIGH, true);
      }
    } else {
      // LOG.println("Dioded disables");
      servicePin(POWER, LOW, true);
      servicePin(WIFI, LOW, true);
      servicePin(HA, LOW, true);
      servicePin(DATA, LOW, true);
    }
  }
}

//--Service end

void nextMapMode() {
  int newMapMode = settings.map_mode + 1;
  if (newMapMode > 5) {
    newMapMode = 0;
  }
  saveMapMode(newMapMode);
}

bool saveDisplayMode(int newDisplayMode) {
  if (newDisplayMode == settings.display_mode) return false;
  settings.display_mode = newDisplayMode;
  preferences.begin("storage", false);
  preferences.putInt("dm", settings.display_mode);
  preferences.end();
  reportSettingsChange("display_mode", settings.display_mode);
  LOG.print("display_mode commited to preferences: ");
  LOG.println(settings.display_mode);
  int localDisplayMode = getLocalDisplayMode(settings.display_mode, ignoreDisplayModeOptions);
  if (display.isDisplayAvailable()) {
    ha.setDisplayMode(getHaDisplayMode(localDisplayMode));
  }
  showServiceMessage(DISPLAY_MODES[localDisplayMode], "Режим дисплея:", 1000);
  // update to selected displayMode
  displayCycle();
  return true;
}

void nextDisplayMode() {
  int newDisplayMode = settings.display_mode + 1;
  while (isInArray(newDisplayMode, ignoreDisplayModeOptions, DISPLAY_MODE_OPTIONS_MAX) || newDisplayMode > DISPLAY_MODE_OPTIONS_MAX - 1) {
    if (newDisplayMode > DISPLAY_MODE_OPTIONS_MAX - 1) {
      newDisplayMode = 0;
    } else {
      newDisplayMode++;
    }
  }
  if (newDisplayMode == DISPLAY_MODE_OPTIONS_MAX - 1) {
    newDisplayMode = 9;
  }

  saveDisplayMode(newDisplayMode);
}

void autoBrightnessUpdate() {
  int tempBrightness = getCurrentBrightnes(settings.brightness, settings.brightness_day, settings.brightness_night, ledsBrightnessLevels);
  if (tempBrightness != settings.current_brightness) {
    settings.current_brightness = tempBrightness;
    preferences.begin("storage", false);
    preferences.putInt("cbr", settings.current_brightness);
    preferences.end();
    LOG.print("set current brightness: ");
    LOG.println(settings.current_brightness);
  }
}

bool saveNightMode(bool newState) {
  nightMode = newState;
  if (nightMode) {
    prevBrightness = settings.brightness;
  }
  showServiceMessage(nightMode ? "Увімкнено" : "Вимкнено", "Нічний режим:");
  autoBrightnessUpdate();
  mapCycle();
  reportSettingsChange("nightMode", nightMode ? "true" : "false");
  LOG.print("nightMode: ");
  LOG.println(nightMode ? "true" : "false");
  ha.setNightMode(nightMode);
  return true;
}

//--Button start
void handleClick(int event, JaamButton::Action action) {
  SoundType soundType = action == JaamButton::Action::SINGLE_CLICK ? SoundType::SINGLE_CLICK : SoundType::LONG_CLICK;
  if (event != 0 && needToPlaySound(soundType)) playMelody(soundType);
  switch (event) {
    // change map mode
    case 1:
      nextMapMode();
      break;
    // change display mode
    case 2:
      nextDisplayMode();
      break;
    // toggle map
    case 3:
      isMapOff = !isMapOff;
      showServiceMessage(!isMapOff ? "Увімкнено" : "Вимкнено", "Мапу:");
      mapCycle();
      break;
    // toggle display
    case 4:
      isDisplayOff = !isDisplayOff;
      showServiceMessage(!isDisplayOff ? "Увімкнено" : "Вимкнено", "Дисплей:");
      break;
    // toggle display and map
    case 5:
      if (isDisplayOff != isMapOff) {
        isDisplayOff = false;
        isMapOff = false;
      } else {
        isMapOff = !isMapOff;
        isDisplayOff = !isDisplayOff;
      }
      showServiceMessage(!isMapOff ? "Увімкнено" : "Вимкнено", "Дисплей та мапу:");
      mapCycle();
      break;
    // toggle night mode
    case 6:
      saveNightMode(!nightMode);
      break;
    // toggle lamp (singl click) or reboot device (long click)
    case 7:
      if (action == JaamButton::Action::SINGLE_CLICK) {
        int newMapMode = settings.map_mode == 5 ? prevMapMode : 5;
        saveMapMode(newMapMode);
      } else if (JaamButton::Action::LONG_CLICK) {
        rebootDevice();
      }
      break;
#if FW_UPDATE_ENABLED
    case 100:
      char updateFileName[30];
      sprintf(updateFileName, "%s.bin", newFwVersion);
      downloadAndUpdateFw(updateFileName, settings.fw_update_channel == 1);
      break;
#endif
    default:
      // do nothing
      break;
  }
}

bool isButtonActivated() {
  return settings.button_mode != 0 || settings.button_mode_long != 0 || settings.button2_mode != 0 || settings.button2_mode_long != 0;
}

void singleClick(int mode) {
  handleClick(mode, JaamButton::SINGLE_CLICK);
}

void longClick(int modeLong) {
#if FW_UPDATE_ENABLED
  if (settings.new_fw_notification == 1 && fwUpdateAvailable && isButtonActivated() && !isDisplayOff) {
    handleClick(100, JaamButton::LONG_CLICK);
    return;
  }
#endif
  handleClick(modeLong, JaamButton::LONG_CLICK);
}

void buttonClick(const char* buttonName, int mode) {
#if TEST_MODE
  displayMessage("Single click!", buttonName);
#else
  singleClick(mode);
#endif
}

void buttonLongClick(const char* buttonName, int modeLong) {
#if TEST_MODE
  displayMessage("Long click!", buttonName);
#else
  longClick(modeLong);
#endif
}

bool saveLampBrightness(int newBrightness, bool saveToSettings, bool checkPrevBrightness) {
  if (checkPrevBrightness && settings.ha_light_brightness == newBrightness) return false;

  settings.ha_light_brightness = newBrightness;

  if (saveToSettings) {
    preferences.begin("storage", false);
    preferences.putInt("ha_lbri", settings.ha_light_brightness);
    preferences.end();
    reportSettingsChange("ha_light_brightness", settings.ha_light_brightness);
    LOG.print("ha_light_brightness commited to preferences: ");
    LOG.println(settings.ha_light_brightness);
    ha.setLampBrightness(newBrightness);
  }

  mapCycle();
  return true;
}

bool saveLampBrightness(int newBrightness) {
  return saveLampBrightness(newBrightness, true, true);
}

void saveCurrentLampBrightness() {
  LOG.println("Save current lamp brightness");
  saveLampBrightness(settings.ha_light_brightness, true, false);
}

char lampBrightnessMsg[4];

void buttonDuringLongClick(const char* buttonName, int modeLong, JaamButton::Action action) {
#if FW_UPDATE_ENABLED
  if (settings.new_fw_notification == 1 && fwUpdateAvailable && isButtonActivated() && !isDisplayOff) {
    return;
  }
#endif
  if (action == JaamButton::Action::DURING_LONG_CLICK) {
    switch (modeLong) {
      case 8:
        // if lamp mode is active, increase lamp brightness
        if (getCurrentMapMode() == 5) {
          int newBrightness = settings.ha_light_brightness + 1;
          if (newBrightness > 100) {
            newBrightness = 100;
          }
          saveLampBrightness(newBrightness, false, true);
          sprintf(lampBrightnessMsg, "%d%%", newBrightness);
          showServiceMessage(lampBrightnessMsg, "Яскравість лампи:");
        } else {
          showServiceMessage("Лише для режиму лампи");
        }
        break;
      case 9:
        // if lamp mode is active, decrease lamp brightness
        if (getCurrentMapMode() == 5) {
          int newBrightness = settings.ha_light_brightness - 1;
          if (newBrightness < 0) {
            newBrightness = 0;
          }
          saveLampBrightness(newBrightness, false, true);
          sprintf(lampBrightnessMsg, "%d%%", newBrightness);
          showServiceMessage(lampBrightnessMsg, "Яскравість лампи:");
        } else {
          showServiceMessage("Лише для режиму лампи");
        }
        break;
      default:
        // do nothing
        break;
  }
  } else if (action == JaamButton::Action::LONG_CLICK_END) {
    switch (modeLong) {
      case 8:
      case 9:
        if (getCurrentMapMode() == 5) {
          saveCurrentLampBrightness();
        }
        break;
      default:
        // do nothing
        break;
    }
  }
}

void button1Click() {
  LOG.println("Button 1 click");
  buttonClick("Button 1", settings.button_mode);
}

void button2Click() {
  LOG.println("Button 2 click");
  buttonClick("Button 2", settings.button2_mode);
}

void button1LongClick() {
  LOG.println("Button 1 long click");
  buttonLongClick("Button 1", settings.button_mode_long);
}

void button2LongClick() {
  LOG.println("Button 2 long click");
  buttonLongClick("Button 2", settings.button2_mode_long);
}

void button1DuringLongClick(JaamButton::Action action) {
  LOG.println("Button 1 during long click");
  buttonDuringLongClick("Button 1", settings.button_mode_long, action);
}

void button2DuringLongClick(JaamButton::Action action) {
  LOG.println("Button 2 during long click");
  buttonDuringLongClick("Button 2", settings.button2_mode_long, action);
}

void distributeBrightnessLevels() {
  distributeBrightnessLevelsFor(settings.brightness_day, settings.brightness_night, ledsBrightnessLevels, "Leds");
}

bool saveBrightness(int newBrightness) {
  if (settings.brightness == newBrightness) return false;
  settings.brightness = newBrightness;
  preferences.begin("storage", false);
  preferences.putInt("brightness", settings.brightness);
  preferences.end();
  reportSettingsChange("brightness", settings.brightness);
  LOG.print("brightness commited to preferences");
  LOG.println(settings.brightness);
  ha.setBrightness(newBrightness);
  autoBrightnessUpdate();
  return true;
}

bool saveDayBrightness(int newBrightness) {
  if (settings.brightness_day == newBrightness) return false;
  settings.brightness_day = newBrightness;
  preferences.begin("storage", false);
  preferences.putInt("brd", settings.brightness_day);
  preferences.end();
  reportSettingsChange("brightness_day", settings.brightness_day);
  LOG.print("brightness_day commited to preferences");
  LOG.println(settings.brightness_day);
  ha.setDayBrightness(newBrightness);
  autoBrightnessUpdate();
  distributeBrightnessLevels();
  return true;
}

bool saveNightBrightness(int newBrightness) {
  if (settings.brightness_night == newBrightness) return false;
  settings.brightness_night = newBrightness;
  preferences.begin("storage", false);
  preferences.putInt("brn", settings.brightness_night);
  preferences.end();
  reportSettingsChange("brightness_night", settings.brightness_night);
  LOG.print("brightness_night commited to preferences");
  LOG.println(settings.brightness_night);
  ha.setNightBrightness(newBrightness);
  autoBrightnessUpdate();
  distributeBrightnessLevels();
  return true;
}

bool saveAutoBrightnessMode(int autoBrightnessMode) {
  if (settings.brightness_mode == autoBrightnessMode) return false;
  settings.brightness_mode = autoBrightnessMode;
  preferences.begin("storage", false);
  preferences.putInt("bra", settings.brightness_mode);
  preferences.end();
  reportSettingsChange("brightness_mode", settings.brightness_mode);
  LOG.print("brightness_mode commited to preferences: ");
  LOG.println(settings.brightness_mode);
  ha.setAutoBrightnessMode(autoBrightnessMode);
  autoBrightnessUpdate();
  showServiceMessage(AUTO_BRIGHTNESS_MODES[settings.brightness_mode], "Авто. яскравість:");
  return true;
}

bool saveAutoAlarmMode(int newMode) {
  if (settings.alarms_auto_switch == newMode) return false;
  settings.alarms_auto_switch = newMode;
  preferences.begin("storage", false);
  preferences.putInt("aas", settings.alarms_auto_switch);
  preferences.end();
  reportSettingsChange("alarms_auto_switch", settings.alarms_auto_switch);
  LOG.print("alarms_auto_switch commited to preferences: ");
  LOG.println(settings.alarms_auto_switch);
  ha.setAutoAlarmMode(newMode);
  return true;
}

bool saveShowHomeAlarmTime(bool newState) {
  if (settings.home_alert_time == newState) return false;
  settings.home_alert_time = newState;
  preferences.begin("storage", false);
  preferences.putInt("hat", settings.home_alert_time);
  preferences.end();
  reportSettingsChange("home_alert_time", settings.home_alert_time ? "true" : "false");
  LOG.print("home_alert_time commited to preferences: ");
  LOG.println(settings.home_alert_time ? "true" : "false");
  if (display.isDisplayAvailable()) {
    ha.setShowHomeAlarmTime(newState);
  }
  return true;
}

bool saveLampRgb(int r, int g, int b) {
  if (settings.ha_light_r == r && settings.ha_light_g == g && settings.ha_light_b == b) return false;

  preferences.begin("storage", false);
  if (settings.ha_light_r != r) {
    settings.ha_light_r = r;
    preferences.putInt("ha_lr", settings.ha_light_r);
    LOG.print("ha_light_red commited to preferences: ");
    LOG.println(settings.ha_light_r);
  }
  if (settings.ha_light_g != g) {
    settings.ha_light_g = g;
    preferences.putInt("ha_lg", settings.ha_light_g);
    LOG.print("ha_light_green commited to preferences: ");
    LOG.println(settings.ha_light_g);
  }
  if (settings.ha_light_b != b) {
    settings.ha_light_b = b;
    preferences.putInt("ha_lb", settings.ha_light_b);
    LOG.print("ha_light_blue commited to preferences: ");
    LOG.println(settings.ha_light_b);
  }
  preferences.end();
  char rgbHex[8];
  sprintf(rgbHex, "#%02x%02x%02x", settings.ha_light_r, settings.ha_light_g, settings.ha_light_b);
  reportSettingsChange("ha_light_rgb", rgbHex);
  ha.setLampColor(settings.ha_light_r, settings.ha_light_g, settings.ha_light_b);
  mapCycle();
  return true;
}

bool saveHomeDistrict(int newHomeDistrict) {
  if (newHomeDistrict == settings.home_district) return false;
  settings.home_district = newHomeDistrict;
  preferences.begin("storage", false);
  preferences.putInt("hd", settings.home_district);
  preferences.end();
  reportSettingsChange("home_district", DISTRICTS[settings.home_district]);
  LOG.print("home_district commited to preferences: ");
  LOG.println(DISTRICTS[settings.home_district]);
  ha.setHomeDistrict(DISTRICTS_ALPHABETICAL[numDistrictToAlphabet(settings.home_district)]);
  ha.setMapModeCurrent(MAP_MODES[getCurrentMapMode()]);
  showServiceMessage(DISTRICTS[settings.home_district], "Домашній регіон:", 2000);
  return true;
}

//--Display start
void displayServiceMessage(ServiceMessage message) {
  displayMessage(message.message, message.title, message.textSize);
}

void showMinOfSilanceScreen(int screen) {
  switch (screen) {
  case 0:
    display.displayTextWithIcon(JaamDisplay::TRINDENT, "Шана", "Полеглим", "Героям!");
    break;
  case 1:
    display.displayTextWithIcon(JaamDisplay::TRINDENT, "Слава", "", "Україні!");
    break;
  case 2:
    display.displayTextWithIcon(JaamDisplay::TRINDENT, "Смерть", "", "ворогам!");
    break;
  default:
    break;
  }
}

void displayMinuteOfSilence() {
  // every 3 sec.
  int periodIndex = getCurrentPeriodIndex(3, 3, timeClient.second());
  showMinOfSilanceScreen(periodIndex);
}

void showHomeAlertInfo() {
  int periodIndex = getCurrentPeriodIndex(settings.display_mode_time, 2, timeClient.second());
  char title[50];
  if (periodIndex) {
    strcpy(title, DISTRICTS[settings.home_district]);
  } else {
    strcpy(title, "Тривога триває:");
  }
  char message[15];
  int position = calculateOffset(settings.home_district, offset);
  fillFromTimer(message, timeClient.unixGMT() - alarm_time[position]);

  displayMessage(message, title);
}

void clearDisplay() {
  display.clearDisplay();
  display.display();
}

void showClock() {
  char time[7];
  sprintf(time, "%02d%c%02d", timeClient.hour(), getDivider(timeClient.second()), timeClient.minute());
  const char* date = timeClient.unixToString("DSTRUA DD.MM.YYYY").c_str();
  displayMessage(time, date);
}

void showTemp() {
  int position = calculateOffset(settings.home_district, offset);
  char message[10];
  sprintf(message, "%.1f%cC", weather_leds[position], (char)128);
  displayMessage(message, DISTRICTS[settings.home_district]);
}

void showTechInfo() {
  int periodIndex = getCurrentPeriodIndex(settings.display_mode_time, 6, timeClient.second());
  char title[35];
  char message[25];
  switch (periodIndex) {
  case 0:
    // IP address
    strcpy(title, "IP-адреса мапи:");
    strcpy(message, getLocalIP());
    break;
  case 1:
    // Wifi Signal level
    strcpy(title, "Сигнал WiFi:");
    sprintf(message, "%d dBm", wifiSignal);
    break;
  case 2:
    // Uptime
    strcpy(title, "Час роботи:");
    fillFromTimer(message, millis() / 1000);
    break;
  case 3:
    // map-API status
    strcpy(title, "Статус map-API:");
    strcpy(message, apiConnected ? "Підключено" : "Відключено");
    break;
  case 4:
    // HA Status
    strcpy(title, "Home Assistant:");
    strcpy(message, haConnected ? "Підключено" : "Відключено");
    break;
  case 5:
    // Fw version
    strcpy(title, "Версія прошивки:");
    strcpy(message, currentFwVersion);
    break;
  default:
    break;
  }
  displayMessage(message, title);
}

int getClimateInfoSize() {
  int size = 0;
  if (climate.isTemperatureAvailable()) size++;
  if (climate.isHumidityAvailable()) size++;
  if (climate.isPressureAvailable()) size++;
  return size;
}

void showLocalTemp() {
  char message[10];
  sprintf(message, "%.1f%cC", climate.getTemperature(settings.temp_correction), (char)128);
  displayMessage(message, "Температура");
}

void showLocalHum() {
  char message[10];
  sprintf(message, "%.1f%%", climate.getHumidity(settings.hum_correction));
  displayMessage(message, "Вологість");
}

void showLocalPressure() {
  char message[12];
  sprintf(message, "%.1fmmHg", climate.getPressure(settings.pressure_correction));
  displayMessage(message, "Тиск");
}

void showLocalClimateInfo(int index) {
  if (index == 0 && climate.isTemperatureAvailable()) {
    showLocalTemp();
    return;
  }
  if (index <= 1 && climate.isHumidityAvailable()) {
    showLocalHum();
    return;
  }
  if (index <= 2 && climate.isPressureAvailable()) {
    showLocalPressure();
    return;
  }
}

void showClimate() {
  int periodIndex = getCurrentPeriodIndex(settings.display_mode_time, getClimateInfoSize(), timeClient.second());
  showLocalClimateInfo(periodIndex);
}

int getNextToggleMode(int periodIndex) {
  if (periodIndex == currentDisplayToggleIndex) return currentDisplayToggleMode;
  switch (currentDisplayToggleMode) {
  case 0:
    // if weather is enabled or no sensors available
    if (settings.toggle_mode_weather || !climate.isAnySensorAvailable()) {
      // show weather info
      return 1;
    }
  case 1:
    // if local temperature is enabled and available
    if (settings.toggle_mode_temp && climate.isTemperatureAvailable()) {
      // show local temperature
      return 2;
    }
  case 2:
    // if local humidity is enabled and available
    if (settings.toggle_mode_hum && climate.isHumidityAvailable()) {
      // show local humidity
      return 3;
    }
  case 3:
    // if local pressure is enabled and available
    if (settings.toggle_mode_press && climate.isPressureAvailable()) {
      // show local pressure
      return 4;
    }
    // else show time
  case 4:
  default:
    return 0;
  }
}

void showToggleModes() {
  int periodIndex = getCurrentPeriodIndex(settings.display_mode_time, 5, timeClient.second());
  int nextToggleMode = getNextToggleMode(periodIndex);
  currentDisplayToggleIndex = periodIndex;
  currentDisplayToggleMode = nextToggleMode;
  switch (currentDisplayToggleMode) {
  case 0:
    // Display Mode Clock
    showClock();
    break;
  case 1:
    // Display Mode Temperature
    showTemp();
    break;
  case 2:
    // Display Climate Temperature
    showLocalTemp();
    break;
  case 3:
    // Display Climate Humidity
    showLocalHum();
    break;
  case 4:
    // Display Climate Pressure
    showLocalPressure();
    break;
  default:
    break;
  }
}

void displayByMode(int mode) {
  switch (mode) {
    // Display Mode Off
    case 0:
      clearDisplay();
      break;
    // Display Mode Clock
    case 1:
      showClock();
      break;
    // Display Mode Temperature
    case 2:
      showTemp();
      break;
    case 3:
      showTechInfo();
      break;
    // Display Climate info from sensor
    case 4:
      showClimate();
      break;
    // Display Mode Switching
    case 9:
      showToggleModes();
      break;
    // Unknown Display Mode, clearing display...
    default:
      clearDisplay();
      break;
  }
}

#if FW_UPDATE_ENABLED
void showNewFirmwareNotification() {
  int periodIndex = getCurrentPeriodIndex(settings.display_mode_time, 2, timeClient.second());
  char title[50];
  char message[50];
  if (periodIndex) {
    strcpy(title, "Доступне оновлення:");
    strcpy(message, newFwVersion);
  } else if (!isButtonActivated()) {
    strcpy(title, "Введіть у браузері:");
    strcpy(message, getLocalIP());
  } else {
    strcpy(title, "Для оновл. натисніть");
    sprintf(message, "та тримайте кнопку %c", (char)24);
  }

  displayMessage(message, title);
}
#endif

void displayCycle() {
  if (!display.isDisplayAvailable()) return;

  updateDisplayBrightness();

  // Show service message if not expired (Always show, it's short message)
  if (!serviceMessage.expired) {
    displayServiceMessage(serviceMessage);
    return;
  }

  if (uaAnthemPlaying) {
    showMinOfSilanceScreen(1);
    return;
  }

  // Show Minute of silence mode if activated. (Priority - 0)
  if (minuteOfSilence) {
    displayMinuteOfSilence();
    return;
  }

  // Show Home Alert Time Info if enabled in settings and alarm in home district is enabled (Priority - 1)
  if (alarmNow && settings.home_alert_time == 1) {
    showHomeAlertInfo();
    return;
  }

  // Turn off display, if activated (Priority - 2)
  if (isDisplayOff) {
    clearDisplay();
    return;
  }

#if FW_UPDATE_ENABLED
  // Show New Firmware Notification if enabled in settings and New firmware available (Priority - 3)
  if (settings.new_fw_notification == 1 && fwUpdateAvailable) {
    showNewFirmwareNotification();
    return;
  }
#endif

  // Show selected display mode in other cases (Priority - last)
  displayByMode(settings.display_mode);
}

void serviceMessageUpdate() {
  if (!serviceMessage.expired && millis() > serviceMessage.endTime) {
    serviceMessage.expired = true;
  }
}
//--Display end

void updateHaTempSensors() {
  if (climate.isTemperatureAvailable()) {
    ha.setLocalTemperature(climate.getTemperature(settings.temp_correction));
  }
}

void updateHaHumSensors() {
  if (climate.isHumidityAvailable()) {
    ha.setLocalHumidity(climate.getHumidity(settings.hum_correction));
  }
}

void updateHaPressureSensors() {
  if (climate.isPressureAvailable()) {
    ha.setLocalPressure(climate.getPressure(settings.pressure_correction));
  }
}

void climateSensorCycle() {
  if (!climate.isAnySensorAvailable()) return;
  climate.read();
  updateHaTempSensors();
  updateHaHumSensors();
  updateHaPressureSensors();
}

void setAlertPin() {
  if (isAlertPinEnabled()) {
    LOG.println("alert pin: HIGH");
    digitalWrite(settings.alertpin, HIGH);
  }
}

void setClearPin() {
  if (isClearPinEnabled()) {
    LOG.println("clear pin: HIGH");
    digitalWrite(settings.clearpin, HIGH);
  }
}

void disableAlertPin() {
  if (isAlertPinEnabled()) {
    LOG.println("alert pin: LOW");
    digitalWrite(settings.alertpin, LOW);
  }
}

void disableClearPin() {
  if (isClearPinEnabled()) {
    LOG.println("clear pin: LOW");
    digitalWrite(settings.clearpin, LOW);
  }
}

void disableAlertAndClearPins() {
  disableAlertPin();
  disableClearPin();
}

//--Web server start

int getSettingsDisplayMode(int localDisplayMode) {
  return getSettingsDisplayMode(localDisplayMode, ignoreDisplayModeOptions);
}

void backupSettings(Print* response) {
  JsonDocument doc;
  doc["fw_version"] = VERSION;
  doc["chip_id"] = chipID;
  doc["time"] = timeClient.unixToString("DD.MM.YYYY hh:mm:ss").c_str();
  JsonArray settingsArray = doc["settings"].to<JsonArray>();
  preferences.begin("storage", true);
  for (const char* key : SETTINGS_KEYS) {
    // skip id key, we do not need to backup it
    if (strcmp(key, "id") == 0) continue;

    if (preferences.isKey(key)) {
      JsonObject setting = settingsArray.add<JsonObject>();
      setting["key"] = key;
      PreferenceType type = preferences.getType(key);
      switch (type) {
        case PT_I32:
          setting["value"] = preferences.getInt(key);
          setting["type"] = PF_INT;
          break;
        case PT_STR:
          setting["value"] = preferences.getString(key);
          setting["type"] = PF_STRING;
          break;
        case PT_BLOB:
          setting["value"] = preferences.getFloat(key);
          setting["type"] = PF_FLOAT;
          break;
        default:
          break;
      }
    }
  }
  preferences.end();

  response->print(doc.as<String>());
}

bool restoreSettings(JsonObject doc) {
  JsonArray settingsArray = doc["settings"].as<JsonArray>();
  preferences.begin("storage", false);
  bool restored = false;
  for (JsonObject setting : settingsArray) {
    const char* key = setting["key"];
    const char* type = setting["type"];

    // skip id key, we do not need to restore it
    if (strcmp(key, "id") == 0) continue;

    if (strcmp(type, PF_INT) == 0) {
      int valueInt = setting["value"].as<int>();
      preferences.putInt(key, valueInt);
      LOG.printf("Restored setting: '%s' with value '%d'\n", key, valueInt);
    } else if (strcmp(type, PF_STRING) == 0) {
      const char* valueStr = setting["value"].as<const char*>();
      preferences.putString(key, valueStr);
      LOG.printf("Restored setting: '%s' with value '%s'\n", key, valueStr);
    } else if (strcmp(type, PF_FLOAT) == 0) {
      float valueFloat = setting["value"].as<float>();
      preferences.putFloat(key, valueFloat);
      LOG.printf("Restored setting: '%s' with value '%f.2'\n", key, valueFloat);
    }
    restored = true;
  }
  preferences.end();
  return restored;
}

int checkboxIndex = 1;
int sliderIndex = 1;
int selectIndex = 1;
int inputFieldIndex = 1;

void addCheckbox(AsyncResponseStream* response, const char* name, bool isChecked, const char* label, const char* onChanges = NULL, bool disabled = false) {
  response->print("<div class='form-group form-check'>");
  response->print("<input name='");
  response->print(name);
  response->print("' type='checkbox' class='form-check-input' id='chb");
  response->print(checkboxIndex);
  if (onChanges) {
    response->print("'");
    response->print(" onchange='");
    response->print(onChanges);
  }
  response->print("'");
  if (isChecked) response->print(" checked");
  if (disabled) response->print(" disabled");
  response->print("/>");
  response->print(label);
  response->println("</div>");
  checkboxIndex++;
}

template <typename V>

void addSlider(AsyncResponseStream* response, const char* name, const char* label, V value, V min, V max, V step = 1, const char* unitOfMeasurement = "", bool disabled = false, bool needColorBox = false) {
  response->print(label);
  response->print(": <span id='sv");
  response->print(sliderIndex);
  response->print("'>");
  if (std::is_same<V, float>::value) {
    char stringValue[10];
    sprintf(stringValue, "%.1f", value);
    response->print(stringValue);
  } else {
    response->print(value);
  }
  response->print("</span>");
  response->print(unitOfMeasurement);
  if (needColorBox) {
    response->print("</br><div class='color-box' id='cb");
    response->print(sliderIndex);
    RGBColor valueColor = hue2rgb((int) value);
    response->print("' style='background-color: rgb(");
    response->print(valueColor.r);
    response->print(", ");
    response->print(valueColor.g);
    response->print(", ");
    response->print(valueColor.b);
    response->print(");'></div>");
  }
  response->print("<input type='range' name='");
  response->print(name);
  response->print("' class='form-control-range' id='s");
  response->print(sliderIndex);
  response->print("' min='");
  response->print(min);
  response->print("' max='");
  response->print(max);
  response->print("' step='");
  response->print(step);
  response->print("' value='");
  response->print(value);
  response->print("'");
  if (needColorBox) {
    response->print(" oninput='window.updateColAndVal(\"cb");
    response->print(sliderIndex);
    response->print("\", \"sv");
  } else {
    response->print(" oninput='window.updateVal(\"sv");
  }
  response->print(sliderIndex);
  response->print("\", this.value);'");
  if (disabled) response->print(" disabled");
  response->print("/>");
  response->println("</br>");
  sliderIndex++;
}

void addSelectBox(AsyncResponseStream* response, const char* name, const char* label, int setting, const char* options[], int optionsCount, int (*valueTransform)(int) = NULL, bool disabled = false, int ignoreOptions[] = NULL, const char* onChanges = NULL) {
  response->print(label);
  response->print(": <select name='");
  response->print(name);
  response->print("' class='form-control' id='sb");
  response->print(selectIndex);
  if (onChanges) {
    response->print("'");
    response->print(" onchange='");
    response->print(onChanges);
  }
  response->print("'");
  if (disabled) response->print(" disabled");
  response->print(">");
  for (int i = 0; i < optionsCount; i++) {
    if (ignoreOptions && isInArray(i, ignoreOptions, optionsCount)) continue;
    int transformedIndex;
    if (valueTransform) {
      transformedIndex = valueTransform(i);
    } else {
      transformedIndex = i;
    }
    response->print("<option value='");
    response->print(transformedIndex);
    response->print("'");
    if (setting == transformedIndex) response->print(" selected");
    response->print(">");
    response->print(options[i]);
    response->print("</option>");
  }
  response->print("</select>");
  response->println("</br>");
  selectIndex++;
}

void addInputText(AsyncResponseStream* response, const char* name, const char* label, const char* type, const char* value, int maxLength = -1) {
  response->print(label);
  response->print(": <input type='");
  response->print(type);
  response->print("' name='");
  response->print(name);
  response->print("' class='form-control'");
  if (maxLength >= 0) {
    response->print(" maxlength='");
    response->print(maxLength);
    response->print("'");
  }
  response->print(" id='if");
  response->print(inputFieldIndex);
  response->print("' value='");
  response->print(value);
  response->print("'>");
  response->println("</br>");
  inputFieldIndex++;
}

template <typename V>

void addCard(AsyncResponseStream* response, const char* title, V value, const char* unitOfMeasurement = "", int size = 1, int precision = 1) {
  response->print("<div class='col-auto mb-2'>");
  response->print("<div class='card' style='width: 15rem; height: 9rem;'>");
  response->print("<div class='card-header d-flex'>");
  response->print(title);
  response->print("</div>");
  response->print("<div class='card-body d-flex'>");
  response->print("<h");
  response->print(size);
  response->print(" class='card-title m-auto'>");
  if (std::is_same<V, float>::value) {
    char valueStr[10];
    sprintf(valueStr, "%.*f", precision, value);
    response->print(valueStr);
  } else if (std::is_same<V, int>::value) {
    char valueStr[10];
    sprintf(valueStr, "%d", value);
    response->print(valueStr);
  } else {
    response->print(value);
  }
  response->print(unitOfMeasurement);
  response->print("</h");
  response->print(size);
  response->print(">");
  response->print("</div>");
  response->print("</div>");
  response->print("</div>");
}

void addHeader(AsyncResponseStream* response) {
  response->println("<!DOCTYPE html>");
  response->println("<html lang='uk'>");
  response->println("<head>");
  response->println("<meta charset='UTF-8'>");
  response->println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  response->print("<title>");
  response->print(settings.devicename);
  response->println("</title>");
  // To prevent favicon request
  response->println("<link rel='icon' href='data:image/png;base64,iVBORw0KGgo='>");
  response->println("<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/css/bootstrap.min.css' integrity='sha384-xOolHFLEh07PJGoPkLv1IbcEPTNtaed2xpHsD9ESMhqIYd0nLMwNLD69Npy4HI+N' crossorigin='anonymous'>");
  response->print("<link rel='stylesheet' href='https://");
  response->print(settings.serverhost);
  response->println("/static/jaam_v1.css'>");
  response->println("</head>");
  response->println("<body>");
  response->println("<div class='container mt-3'  id='accordion'>");
  response->print("<h2 class='text-center'>");
  response->print(settings.devicedescription);
  response->print(" ");
  response->print(currentFwVersion);
  response->println("</h2>");
  response->println("<div class='row justify-content-center'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->print("<img class='full-screen-img' src='https://");
  response->print(settings.serverhost);
  response->print("/");
  switch (getCurrentMapMode()) {
    case 0:
      response->print("off_map.png");
      break;
    case 2:
      response->print("weather_map.png");
      break;
    case 3:
      response->print("flag_map.png");
      break;
    case 4:
      response->print("random_map.png");
      break;
    case 5:
      response->print("lamp_map.png");
      break;
    default:
      response->print("alerts_map.png");
  }
  response->println("'>");
  response->println("</div>");
  response->println("</div>");
#if FW_UPDATE_ENABLED
  if (fwUpdateAvailable) {
    response->println("<div class='row justify-content-center'>");
    response->println("<div class='by col-md-9 mt-2'>");
    response->println("<div class='alert alert-success text-center'>");
    response->print("Доступна нова версія прошивки - <b>");
    response->print(newFwVersion);
    response->println("</b></br>Для оновлення перейдіть в розділ <b><a href='/firmware'>Прошивка</a></b></h8>");
    response->println("</div>");
    response->print("<div class='alert alert-info text-rigth' id='release-notes' data-version='");
    response->print(newFwVersion);
    response->println("'>Завантажити опис оновлення?</div>");
    response->print("<div class='text-center'><button class='btn btn-info' onclick='fetchReleaseNotes()'>Отримати опис оновлення</button></div><br>");
    response->println("</div>");
    response->println("</div>");
  }
#endif
  response->println("<div class='row justify-content-center'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->print("Локальна IP-адреса: <b>");
  response->print(getLocalIP());
  response->println("</b>");
  if (display.isDisplayEnabled()) {
    response->println("</br>Дисплей: <b>");
    if (display.isDisplayAvailable()) {
      response->print(display.getDisplayModel());
      response->print(" (128x");
      response->print(display.height());
      response->print(")");
    } else {
      response->print("Немає");
    }
    response->println("</b>");
  }
  if (lightSensor.isLightSensorEnabled()) {
    response->println("</br>Сенсор освітлення: <b>");
    response->print(lightSensor.getSensorModel());
    response->println("</b>");
  }
  if (climate.isAnySensorEnabled()) {
    response->println("</br>Сенсор клімату: <b>");
    response->print(climate.getSensorModel());
    response->println("</b>");
  }
  response->println("</div>");
  response->println("</div>");
}

void addLinks(AsyncResponseStream* response) {
  response->println("<div class='row justify-content-center'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->println("<a href='/brightness' class='btn btn-success'>Яскравість</a>");
  response->println("<a href='/colors' class='btn btn-success'>Кольори</a>");
  response->println("<a href='/modes' class='btn btn-success'>Режими</a>");
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    response->println("<a href='/sounds' class='btn btn-success'>Звуки</a>");
  }
#endif
  response->println("<a href='/telemetry' class='btn btn-primary'>Телеметрія</a>");
  response->println("<a href='/dev' class='btn btn-warning'>DEV</a>");
#if FW_UPDATE_ENABLED
  response->println("<a href='/firmware' class='btn btn-danger'>Прошивка</a>");
#endif
  response->println("</div>");
  response->println("</div>");
}

void addFooter(AsyncResponseStream* response) {
  response->println("<div class='position-fixed bottom-0 right-0 p-3' style='z-index: 5; right: 0; bottom: 0;'>");
  response->println("<div id='saved-toast' class='toast hide' role='alert' aria-live='assertive' aria-atomic='true' data-delay='2000'>");
  response->println("<div class='toast-body'>");
  response->println("💾 Налаштування збережено!");
  response->println("</div>");
  response->println("</div>");
  response->println("<div id='reboot-toast' class='toast hide' role='alert' aria-live='assertive' aria-atomic='true' data-delay='2000'>");
  response->println("<div class='toast-body'>");
  response->println("💾 Налаштування збережено! Перезавантаження...");
  response->println("</div>");
  response->println("</div>");
  response->println("<div id='restore-toast' class='toast hide' role='alert' aria-live='assertive' aria-atomic='true' data-delay='2000'>");
  response->println("<div class='toast-body'>");
  response->println("✅ Налаштування відновлено! Перезавантаження...");
  response->println("</div>");
  response->println("</div>");
  response->println("<div id='restore-error-toast' class='toast hide' role='alert' aria-live='assertive' aria-atomic='true' data-delay='2000'>");
  response->println("<div class='toast-body'>");
  response->println("🚫 Помилка відновлення налаштувань!");
  response->println("</div>");
  response->println("</div>");
  response->println("</div>");
  response->println("</div>");
  response->println("<script src='https://cdn.jsdelivr.net/npm/jquery@3.5.1/dist/jquery.slim.min.js' integrity='sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj' crossorigin='anonymous'></script>");
  response->println("<script src='https://cdn.jsdelivr.net/npm/bootstrap@4.6.2/dist/js/bootstrap.bundle.min.js' integrity='sha384-Fy6S3B9q64WdZWQUiU+q4/2Lc9npb8tCaSX9FK7E8HnRr0Jz8D6OP9dO5Vg3Q9ct' crossorigin='anonymous'></script>");
  response->println("<script src='https://cdn.jsdelivr.net/npm/js-cookie@3.0.5/dist/js.cookie.min.js'></script>");
#if FW_UPDATE_ENABLED
  if (fwUpdateAvailable) {
    response->println("<script src='https://cdn.jsdelivr.net/npm/marked/marked.min.js'></script>");
  }
#endif
  response->print("<script src='https://");
  response->print(settings.serverhost);
  response->println("/static/jaam_v1.js'></script>");
  response->print("<script src='https://");
  response->print(settings.serverhost);
  response->println("/static/jaam_v2.js'></script>");
  response->println("</body>");
  response->println("</html>");
}

void handleBrightness(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  response->println("<form action='/saveBrightness' method='POST'>");
  response->println("<div class='row justify-content-center'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->print("<div class='alert alert-success' role='alert'>Поточний рівень яскравості: <b>");
  response->print(settings.map_mode == 5 ? settings.ha_light_brightness : settings.current_brightness);
  response->println("%</b><br>\"Нічний режим\": <b>");
  int nightModeType = getNightModeType();
  response->print(nightModeType == 0 ? "Вимкнено" : nightModeType == 1 ? "Активовано кнопкою" : nightModeType == 2 ? "Активовано за часом доби" : "Активовано за даними сенсора освітлення");
  response->println("</b></div>");
  addSlider(response, "brightness", "Загальна", settings.brightness, 0, 100, 1, "%", settings.brightness_mode == 1 || settings.brightness_mode == 2);
  addSlider(response, "brightness_day", "Денна", settings.brightness_day, 0, 100, 1, "%", settings.brightness_mode == 0);
  addSlider(response, "brightness_night", "Нічна", settings.brightness_night, 0, 100, 1, "%");
  addSlider(response, "day_start", "Початок дня", settings.day_start, 0, 24, 1, " година", settings.brightness_mode == 0 || settings.brightness_mode == 2);
  addSlider(response, "night_start", "Початок ночі", settings.night_start, 0, 24, 1, " година", settings.brightness_mode == 0 || settings.brightness_mode == 2);
  if (display.isDisplayAvailable()) {
    addCheckbox(response, "dim_display_on_night", settings.dim_display_on_night, "Знижувати яскравість дисплею у нічний час");
  }
  addSelectBox(response, "brightness_auto", "Автоматична яскравість", settings.brightness_mode, AUTO_BRIGHTNESS_MODES, AUTO_BRIGHTNESS_OPTIONS_COUNT);
  addSlider(response, "brightness_alert", "Області з тривогами", settings.brightness_alert, 0, 100, 1, "%");
  addSlider(response, "brightness_clear", "Області без тривог", settings.brightness_clear, 0, 100, 1, "%");
  addSlider(response, "brightness_new_alert", "Нові тривоги", settings.brightness_new_alert, 0, 100, 1, "%");
  addSlider(response, "brightness_alert_over", "Відбій тривог", settings.brightness_alert_over, 0, 100, 1, "%");
  addSlider(response, "brightness_explosion", "Вибухи", settings.brightness_explosion, 0, 100, 1, "%");
  addSlider(response, "brightness_home_district", "Домашній регіон", settings.brightness_home_district, 0, 100, 1, "%");
  if (isBgStripEnabled()) {
    addSlider(response, "brightness_bg", "Фонова LED-стрічка", settings.brightness_bg, 0, 100, 1, "%");
  }
  if (isServiceStripEnabled()) {
    addSlider(response, "brightness_service", "Сервісні LED", settings.brightness_service, 0, 100, 1, "%");
  }
  if (lightSensor.isAnySensorAvailable()) {
    addSlider(response, "light_sensor_factor", "Коефіцієнт чутливості сенсора освітлення", settings.light_sensor_factor, 0.1f, 30.0f, 0.1f);
  }
  response->println("<p class='text-info'>Детальніше про сенсор освітлення на <a href='https://github.com/J-A-A-M/ukraine_alarm_map/wiki/%D0%A1%D0%B5%D0%BD%D1%81%D0%BE%D1%80-%D0%BE%D1%81%D0%B2%D1%96%D1%82%D0%BB%D0%B5%D0%BD%D0%BD%D1%8F'>Wiki</a>.</p>");
  response->println("<button type='submit' class='btn btn-info'>Зберегти налаштування</button>");
  response->println("</div>");
  response->println("</div>");
  response->println("</form>");

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleColors(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  response->println("<form action='/saveColors' method='POST'>");
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  addSlider(response, "color_alert", "Області з тривогами", settings.color_alert, 0, 360, 1, "", false, true);
  addSlider(response, "color_clear", "Області без тривог", settings.color_clear, 0, 360, 1, "", false, true);
  addSlider(response, "color_new_alert", "Нові тривоги", settings.color_new_alert, 0, 360, 1, "", false, true);
  addSlider(response, "color_alert_over", "Відбій тривог", settings.color_alert_over, 0, 360, 1, "", false, true);
  addSlider(response, "color_explosion", "Вибухи", settings.color_explosion, 0, 360, 1, "", false, true);
  addSlider(response, "color_missiles", "Ракетна небезпека", settings.color_missiles, 0, 360, 1, "", false, true);
  addSlider(response, "color_drones", "Загроза БПЛА", settings.color_drones, 0, 360, 1, "", false, true);
  addSlider(response, "color_home_district", "Домашній регіон", settings.color_home_district, 0, 360, 1, "", false, true);
  response->println("<button type='submit' class='btn btn-info'>Зберегти налаштування</button>");
  response->println("</div>");
  response->println("</div>");
  response->println("</form>");

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleModes(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  response->println("<form action='/saveModes' method='POST'>");
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  if (settings.legacy == 1 || settings.legacy == 2) {
  addSelectBox(response, "kyiv_district_mode", "Режим діода \"Київська область\"", settings.kyiv_district_mode, KYIV_LED_MODE_OPTIONS, KYIV_LED_MODE_COUNT, [](int i) -> int {return i + 1;});
  }
  addSelectBox(response, "map_mode", "Режим мапи", settings.map_mode, MAP_MODES, MAP_MODES_COUNT);
  addSlider(response, "color_lamp", "Колір режиму \"Лампа\"", rgb2hue(settings.ha_light_r, settings.ha_light_g, settings.ha_light_b), 0, 360, 1, "", false, true);
  addSlider(response, "brightness_lamp", "Яскравість режиму \"Лампа\"", settings.ha_light_brightness, 0, 100, 1, "%");
  if (display.isDisplayAvailable()) {
    addSelectBox(response, "display_mode", "Режим дисплея", settings.display_mode, DISPLAY_MODES, DISPLAY_MODE_OPTIONS_MAX, getSettingsDisplayMode, false, ignoreDisplayModeOptions);
    addCheckbox(response, "invert_display", settings.invert_display, "Інвертувати дисплей (темний шрифт на світлому фоні)");
    addSlider(response, "display_mode_time", "Час перемикання дисплея", settings.display_mode_time, 1, 60, 1, " с.");
    if (climate.isAnySensorAvailable()) {
      response->println("Відображати в режимі \"Перемикання\":<br><br>");
      addCheckbox(response, "toggle_mode_weather", settings.toggle_mode_weather, "Погоду у домашньому регіоні");
      if (climate.isTemperatureAvailable()) addCheckbox(response, "toggle_mode_temp", settings.toggle_mode_temp, "Температуру в приміщенні");
      if (climate.isHumidityAvailable()) addCheckbox(response, "toggle_mode_hum", settings.toggle_mode_hum, "Вологість");
      if (climate.isPressureAvailable()) addCheckbox(response, "toggle_mode_press", settings.toggle_mode_press, "Тиск");
    }
  }

  if (climate.isTemperatureAvailable()) {
    addSlider(response, "temp_correction", "Корегування температури", settings.temp_correction, -10.0f, 10.0f, 0.1f, "°C");
  }
  if (climate.isHumidityAvailable()) {
    addSlider(response, "hum_correction", "Корегування вологості", settings.hum_correction, -20.0f, 20.0f, 0.5f, "%");
  }
  if (climate.isPressureAvailable()) {
    addSlider(response, "pressure_correction", "Корегування атмосферного тиску", settings.pressure_correction, -50.0f, 50.0f, 0.5f, " мм.рт.ст.");
  }
  addSlider(response, "weather_min_temp", "Нижній рівень температури (режим 'Погода')", settings.weather_min_temp, -20, 10, 1, "°C");
  addSlider(response, "weather_max_temp", "Верхній рівень температури (режим 'Погода')", settings.weather_max_temp, 11, 40, 1, "°C");
  if (buttons.isButton1Enabled()) {
    addSelectBox(response, "button_mode", "Режим кнопки (Single Click)", settings.button_mode, SINGLE_CLICK_OPTIONS, SINGLE_CLICK_OPTIONS_MAX, NULL, false, ignoreSingleClickOptions);
    addSelectBox(response, "button_mode_long", "Режим кнопки (Long Click)", settings.button_mode_long, LONG_CLICK_OPTIONS, LONG_CLICK_OPTIONS_MAX, NULL, false, ignoreLongClickOptions);
  }
  if (buttons.isButton2Enabled()) {
    addSelectBox(response, "button2_mode", "Режим кнопки 2 (Single Click)", settings.button2_mode, SINGLE_CLICK_OPTIONS, SINGLE_CLICK_OPTIONS_MAX, NULL, false, ignoreSingleClickOptions);
    addSelectBox(response, "button2_mode_long", "Режим кнопки 2 (Long Click)", settings.button2_mode_long, LONG_CLICK_OPTIONS, LONG_CLICK_OPTIONS_MAX, NULL, false, ignoreLongClickOptions);
  }
  addSelectBox(response, "home_district", "Домашній регіон", settings.home_district, DISTRICTS_ALPHABETICAL, DISTRICTS_COUNT, alphabetDistrictToNum);
  if (display.isDisplayAvailable()) {
    addCheckbox(response, "home_alert_time", settings.home_alert_time, "Показувати тривалість тривоги у домашньому регіоні");
  }
  addSelectBox(response, "alarms_notify_mode", "Відображення на мапі нових тривог, відбою, вибухів та інших загроз", settings.alarms_notify_mode, ALERT_NOTIFY_OPTIONS, ALERT_NOTIFY_OPTIONS_COUNT);
  addCheckbox(response, "enable_explosions", settings.enable_explosions, "Показувати сповіщення про вибухи");
  addCheckbox(response, "enable_missiles", settings.enable_missiles, "Показувати сповіщення про ракетну небезпеку");
  addCheckbox(response, "enable_drones", settings.enable_drones, "Показувати сповіщення про загрозу БПЛА");
  addSlider(response, "alert_on_time", "Тривалість відображення початку тривоги", settings.alert_on_time, 1, 10, 1, " хв.", settings.alarms_notify_mode == 0);
  addSlider(response, "alert_off_time", "Тривалість відображення відбою", settings.alert_off_time, 1, 10, 1, " хв.", settings.alarms_notify_mode == 0);
  addSlider(response, "explosion_time", "Тривалість відображення інформації про вибухи, ракети та БПЛА", settings.explosion_time, 1, 10, 1, " хв.", settings.alarms_notify_mode == 0);
  addSlider(response, "alert_blink_time", "Тривалість анімації зміни яскравості", settings.alert_blink_time, 1, 5, 1, " с.", settings.alarms_notify_mode != 2);
  addSelectBox(response, "alarms_auto_switch", "Перемикання мапи в режим тривоги у випадку тривоги у домашньому регіоні", settings.alarms_auto_switch, AUTO_ALARM_MODES, AUTO_ALARM_MODES_COUNT);
  if (settings.legacy == 0 || settings.legacy == 3) {
    addCheckbox(response, "service_diodes_mode", settings.service_diodes_mode, "Ввімкнути сервісні діоди");
  }
  addCheckbox(response, "min_of_silence", settings.min_of_silence, "Активувати режим \"Хвилина мовчання\" (щоранку о 09:00)");
  addSlider(response, "time_zone", "Часовий пояс (зсув відносно Ґрінвіча)", settings.time_zone, -12, 12, 1, " год.");
  response->println("<button type='submit' class='btn btn-info'>Зберегти налаштування</button>");
  response->println("</div>");
  response->println("</div>");
  response->println("</form>");

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleSounds(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

#if BUZZER_ENABLED
  response->println("<form action='/saveSounds' method='POST'>");
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  addCheckbox(response, "sound_on_min_of_sl", settings.sound_on_min_of_sl, "Відтворювати звуки під час \"Xвилини мовчання\"");
  addCheckbox(response, "sound_on_alert", settings.sound_on_alert, "Звукове сповіщення при тривозі у домашньому регіоні", "window.disableElement(\"melody_on_alert\", !this.checked);");
  addSelectBox(response, "melody_on_alert", "Мелодія при тривозі у домашньому регіоні", settings.melody_on_alert, MELODY_NAMES, MELODIES_COUNT, NULL, settings.sound_on_alert == 0, NULL, "window.playTestSound(this.value);");
  addCheckbox(response, "sound_on_alert_end", settings.sound_on_alert_end, "Звукове сповіщення при скасуванні тривоги у домашньому регіоні", "window.disableElement(\"melody_on_alert_end\", !this.checked);");
  addSelectBox(response, "melody_on_alert_end", "Мелодія при скасуванні тривоги у домашньому регіоні", settings.melody_on_alert_end, MELODY_NAMES, MELODIES_COUNT, NULL, settings.sound_on_alert_end == 0, NULL, "window.playTestSound(this.value);");
  addCheckbox(response, "sound_on_explosion", settings.sound_on_explosion, "Звукове сповіщення при вибухах у домашньому регіоні", "window.disableElement(\"melody_on_explosion\", !this.checked);");
  addSelectBox(response, "melody_on_explosion", "Мелодія при вибухах у домашньому регіоні", settings.melody_on_explosion, MELODY_NAMES, MELODIES_COUNT, NULL, settings.sound_on_explosion == 0, NULL, "window.playTestSound(this.value);");
  addCheckbox(response, "sound_on_every_hour", settings.sound_on_every_hour, "Звукове сповіщення щогодини");
  addCheckbox(response, "sound_on_button_click", settings.sound_on_button_click, "Сигнали при натисканні кнопки");
  addCheckbox(response, "mute_sound_on_night", settings.mute_sound_on_night, "Вимикати всі звуки у \"Нічному режимі\"", "window.disableElement(\"ignore_mute_on_alert\", !this.checked);");
  addCheckbox(response, "ignore_mute_on_alert", settings.ignore_mute_on_alert, "Сигнали тривоги навіть у \"Нічному режимі\"", NULL, settings.mute_sound_on_night == 0);
  addSlider(response, "melody_volume", "Гучність мелодії", settings.melody_volume, 0, 100, 1, "%");
  response->println("<button type='submit' class='btn btn-info aria-expanded='false'>Зберегти налаштування</button>");
  response->println("<button type='button' class='btn btn-primary float-right' onclick='playTestSound();' aria-expanded='false'>Тест динаміка</button>");
  response->println("</div>");
  response->println("</div>");
  response->println("</form>");
#endif

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleTelemetry(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  response->println("<form action='/refreshTelemetry' method='POST'>");
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->println("<div class='row justify-content-center'>");
  addCard(response, "Час роботи", uptimeChar, "", 4);
  addCard(response, "Температура ESP32", cpuTemp, "°C");
  addCard(response, "Вільна памʼять", freeHeapSize, "кБ");
  addCard(response, "Використана памʼять", usedHeapSize, "кБ");
  addCard(response, "WiFi сигнал", wifiSignal, "dBm");
  addCard(response, DISTRICTS[settings.home_district], weather_leds[calculateOffset(settings.home_district, offset)], "°C");
  if (ha.isHaEnabled()) {
    addCard(response, "Home Assistant", haConnected ? "Підключено" : "Відключено", "", 2);
  }
  addCard(response, "Сервер тривог", client_websocket.available() ? "Підключено" : "Відключено", "", 2);
  if (climate.isTemperatureAvailable()) {
    addCard(response, "Температура", climate.getTemperature(settings.temp_correction), "°C");
  }
  if (climate.isHumidityAvailable()) {
    addCard(response, "Вологість", climate.getHumidity(settings.hum_correction), "%");
  }
  if (climate.isPressureAvailable()) {
    addCard(response, "Тиск", climate.getPressure(settings.pressure_correction), "mmHg", 2);
  }
  if (lightSensor.isLightSensorAvailable()) {
    addCard(response, "Освітленість", lightSensor.getLightLevel(settings.light_sensor_factor), "lx");
  }
  response->println("</div>");
  response->println("<button type='submit' class='btn btn-info mt-3'>Оновити значення</button>");
  response->println("</div>");
  response->println("</div>");
  response->println("</form>");

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleDev(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->println("<form action='/saveDev' method='POST'>");
  addSelectBox(response, "legacy", "Режим прошивки", settings.legacy, LEGACY_OPTIONS, LEGACY_OPTIONS_COUNT);
  if ((settings.legacy == 1 || settings.legacy == 2) && display.isDisplayEnabled()) {
    addSelectBox(response, "display_model", "Тип дисплею", settings.display_model, DISPLAY_MODEL_OPTIONS, DISPLAY_MODEL_OPTIONS_COUNT);
    addSelectBox(response, "display_height", "Розмір дисплею", settings.display_height, DISPLAY_HEIGHT_OPTIONS, DISPLAY_HEIGHT_OPTIONS_COUNT, [](int i) -> int {return i == 0 ? 32 : 64;});
  }
  if (ha.isHaEnabled()) {
    addInputText(response, "ha_brokeraddress", "Адреса mqtt Home Assistant", "text", settings.ha_brokeraddress, 30);
    addInputText(response, "ha_mqttport", "Порт mqtt Home Assistant", "number", String(settings.ha_mqttport).c_str());
    addInputText(response, "ha_mqttuser", "Користувач mqtt Home Assistant", "text", settings.ha_mqttuser, 30);
    addInputText(response, "ha_mqttpassword", "Пароль mqtt Home Assistant", "text", settings.ha_mqttpassword, 65);
  }
  addInputText(response, "ntphost", "Адреса сервера NTP", "text", settings.ntphost, 30);
  addInputText(response, "serverhost", "Адреса сервера даних", "text", settings.serverhost, 30);
  addInputText(response, "websocket_port", "Порт Websockets", "number", String(settings.websocket_port).c_str());
  addInputText(response, "updateport", "Порт сервера прошивок", "number", String(settings.updateport).c_str());
  addInputText(response, "devicename", "Назва пристрою", "text", settings.devicename, 30);
  addInputText(response, "devicedescription", "Опис пристрою", "text", settings.devicedescription, 50);
  addInputText(response, "broadcastname", ("Локальна адреса (" + String(settings.broadcastname) + ".local)").c_str(), "text", settings.broadcastname, 30);
  if (settings.legacy == 1 || settings.legacy == 2) {
    addInputText(response, "pixelpin", "Керуючий пін лед-стрічки", "number", String(settings.pixelpin).c_str());
    addInputText(response, "bg_pixelpin", "Керуючий пін фонової лед-стрічки (-1 - стрічки немає)", "number", String(settings.bg_pixelpin).c_str());
    addInputText(response, "bg_pixelcount", "Кількість пікселів фонової лед-стрічки", "number", String(settings.bg_pixelcount).c_str());
    addInputText(response, "buttonpin", "Керуючий пін кнопки 1 (-1 - вимкнено)", "number", String(settings.buttonpin).c_str());
    addInputText(response, "button2pin", "Керуючий пін кнопки 2 (-1 - вимкнено)", "number", String(settings.button2pin).c_str());
  }
  addSelectBox(response, "alert_clear_pin_mode", "Режим роботи пінів тривоги та відбою", settings.alert_clear_pin_mode, ALERT_PIN_MODES_OPTIONS, ALERT_PIN_MODES_COUNT);
  addInputText(response, "alertpin", "Пін тривоги у домашньому регіоні (має бути output, -1 - вимкнено)", "number", String(settings.alertpin).c_str());
  addInputText(response, "clearpin", "Пін відбою у домашньому регіоні (має бути output, лише для Імпульсного режиму, -1 - вимкнено)", "number", String(settings.clearpin).c_str());
  addSlider(response, "alert_clear_pin_time", "Тривалість замикання пінів тривоги та відбою в Імпульсному режимі", settings.alert_clear_pin_time, 0.5f, 10.0f, 0.5f, " с.");

  if (settings.legacy != 3) {
    addInputText(response, "lightpin", "Пін фоторезистора (має бути input, -1 - вимкнено)", "number", String(settings.lightpin).c_str());
#if BUZZER_ENABLED
    addInputText(response, "buzzerpin", "Керуючий пін динаміка (має бути output, -1 - вимкнено)", "number", String(settings.buzzerpin).c_str());
#endif
  }
  response->println("<b>");
  response->println("<p class='text-danger'>УВАГА: будь-яка зміна налаштування в цьому розділі призводить до примусового перезаватаження мапи.</p>");
  response->println("<p class='text-danger'>УВАГА: деякі зміни налаштувань можуть привести до відмови прoшивки, якщо налаштування будуть несумісні. Будьте впевнені, що Ви точно знаєте, що міняється і для чого.</p>");
  response->println("<p class='text-danger'>У випадку, коли мапа втратить працездатність після змін, перезавантаження i втрати доступу до сторінки керування - необхідно перепрошити мапу з нуля за допомогою скетча updater.ino (або firmware.ino, якщо Ви збирали прошивку самі) з репозіторія JAAM за допомогою Arduino IDE, виставивши примусове стирання памʼяті в меню Tools -> Erase all memory before sketch upload</p>");
  response->println("</b>");
  response->println("<button type='submit' class='btn btn-info' aria-expanded='false'>Зберегти налаштування</button>");
  response->print("<a href='http://");
  response->print(getLocalIP());
  response->println(":8080/0wifi' target='_blank' class='btn btn-primary float-right' aria-expanded='false'>Змінити налаштування WiFi</a>");
  response->println("</form>");
  response->println("</div>");
  response->println("</div>");
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->println("<b><p class='text'>У цьому розділі можна зберегти та відновити налаштування мапи. Зберігаються всі налаштування, крім налаштувань WiFi.</p></b>");
  response->println("<form id='form_restore' action='/restore' method='POST' enctype='multipart/form-data'>");
  response->println("<a href='/backup' target='_blank' class='btn btn-info' aria-expanded='false'>Завантажити налаштування</a>");
  response->println("<label for='restore' class='btn btn-primary float-right' aria-expanded='false'>Відновити налаштування</label>");
  response->println("<input id='restore' name='restore' type='file' style='visibility:hidden;' onchange='javascript:document.getElementById(\"form_restore\").submit();' accept='application/json'/>");
  response->println("</form>");
  response->println("</div>");
  response->println("</div>");

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleFirmware(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  #if FW_UPDATE_ENABLED
  response->println("<div class='row justify-content-center' data-parent='#accordion'>");
  response->println("<div class='by col-md-9 mt-2'>");
  response->println("<form action='/saveFirmware' method='POST'>");
  if (display.isDisplayAvailable()) addCheckbox(response, "new_fw_notification", settings.new_fw_notification, "Сповіщення про нові прошивки на екрані");
  addSelectBox(response, "fw_update_channel", "Канал оновлення прошивок", settings.fw_update_channel, FW_UPDATE_CHANNELS, FW_UPDATE_CHANNELS_COUNT);
  response->println("<b><p class='text-danger'>УВАГА: BETA-прошивки можуть вивести мапу з ладу i містити помилки. Якщо у Вас немає можливості прошити мапу через кабель, будь ласка, залишайтесь на каналі PRODUCTION!</p></b>");
  response->println("<button type='submit' class='btn btn-info'>Зберегти налаштування</button>");
  response->println("</form>");
  response->println("<form action='/update' method='POST'>");
  response->println("Файл прошивки");
  response->println("<select name='bin_name' class='form-control' id='sb16'>");
  const int count = settings.fw_update_channel ? testBinsCount : binsCount;
  for (int i = 0; i < count; i++) {
    String filename = String(settings.fw_update_channel ? test_bin_list[i] : bin_list[i]);
    response->print("<option value='");
    response->print(filename);
    response->print("'");
    if (i == 0) response->print(" selected");
    response->print(">");
    response->print(filename);
    response->println("</option>");
  }
  response->println("</select>");
  response->println("</br>");
  response->println("<button type='submit' class='btn btn-danger'>ОНОВИТИ ПРОШИВКУ</button>");
  response->println("</form>");
  response->println("</div>");
  response->println("</div>");
#endif

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void handleRoot(AsyncWebServerRequest* request) {
  // reset indexes
  checkboxIndex = 1;
  sliderIndex = 1;
  selectIndex = 1;
  inputFieldIndex = 1;

  AsyncResponseStream* response = request->beginResponseStream("text/html");

  addHeader(response);
  addLinks(response);

  addFooter(response);

  response->setCode(200);
  request->send(response);
}

void saveInt(int *setting, const char* settingsKey, int newValue, const char* paramName) {
  preferences.begin("storage", false);
  *setting = newValue;
  preferences.putInt(settingsKey, *setting);
  preferences.end();
  reportSettingsChange(paramName, *setting);
  LOG.printf("%s commited to preferences: %d\n", paramName, *setting);
}

bool saveInt(const AsyncWebParameter* param, int *setting, const char* settingsKey, bool (*saveFun)(int) = NULL, void (*additionalFun)(void) = NULL) {
  if (!param) return false;
  int newValue = param->value().toInt();
  if (saveFun) {
    return saveFun(newValue);
  }
  if (newValue != *setting) {
    const char* paramName = param->name().c_str();
    saveInt(setting, settingsKey, newValue, paramName);
    if (additionalFun) {
      additionalFun();
    }
    return true;
  }
  return false;
}

bool saveFloat(const AsyncWebParameter* param, float *setting, const char* settingsKey, bool (*saveFun)(float) = NULL, void (*additionalFun)(void) = NULL) {
  if (!param) return false;
  float paramValue = param->value().toFloat();
  if (saveFun) {
    return saveFun(paramValue);
  }
  if (paramValue != *setting) {
    preferences.begin("storage", false);
    const char* paramName = param->name().c_str();
    *setting = paramValue;
    preferences.putFloat(settingsKey, *setting);
    preferences.end();
    reportSettingsChange(paramName, *setting);
    LOG.printf("%s commited to preferences: %.1f\n", paramName, *setting);
    if (additionalFun) {
      additionalFun();
    }
    return true;
  }
  return false;
}

bool saveBool(const AsyncWebParameter* param, const char* paramName, int *setting, const char* settingsKey, bool (*saveFun)(bool) = NULL, void (*additionalFun)(void) = NULL) {
  int paramValue = param ? 1 : 0;
  if (saveFun) {
    return saveFun(paramValue);
  }
  if (paramValue != *setting) {
    preferences.begin("storage", false);
    *setting = paramValue;
    preferences.putInt(settingsKey, *setting);
    preferences.end();
    reportSettingsChange(paramName, *setting ? "true" : "false");
    LOG.printf("%s commited to preferences: %s\n", paramName, *setting ? "true" : "false");
    if (additionalFun) {
      additionalFun();
    }
    return true;
  }
  return false;
}

bool saveString(const AsyncWebParameter* param, char* setting, const char* settingsKey, bool (*saveFun)(const char*) = NULL, void (*additionalFun)(void) = NULL) {
  if (!param) return false;
  const char* paramValue = param->value().c_str();
  if (saveFun) {
    return saveFun(paramValue);
  }
  if (strcmp(paramValue, setting) != 0) {
    preferences.begin("storage", false);
    const char* paramName = param->name().c_str();
    strcpy(setting, paramValue);
    preferences.putString(settingsKey, setting);
    preferences.end();
    reportSettingsChange(paramName, setting);
    LOG.printf("%s commited to preferences: %s\n", paramName, setting);
    if (additionalFun) {
      additionalFun();
    }
    return true;
  }
  return false;
}

#if FW_UPDATE_ENABLED
void handleUpdate(AsyncWebServerRequest* request) {
  LOG.println("do_update triggered");
  initUpdate = true;
  if (request->hasParam("bin_name", true)) {
    const char* bin_name = request->getParam("bin_name", true)->value().c_str();
    strcpy(settings.bin_name, bin_name);
  }
  request->redirect("/");
}
#endif

AsyncWebServerResponse* redirectResponce(AsyncWebServerRequest* request, const char* location, bool saved, bool reboot = false, bool restore = false, bool restoreError = false) {
  AsyncWebServerResponse* response = request->beginResponse(302);
  response->addHeader("Location", location);
  response->addHeader("Set-Cookie", "scroll=true");
  if (saved) response->addHeader("Set-Cookie", "saved=true");
  if (restore) response->addHeader("Set-Cookie", "restore=true");
  if (restoreError) response->addHeader("Set-Cookie", "restore-error=true");
  return response;
}

void handleSaveBrightness(AsyncWebServerRequest *request) {
  bool saved = false;
  saved = saveInt(request->getParam("brightness", true), &settings.brightness, "brightness", saveBrightness) || saved;
  saved = saveInt(request->getParam("brightness_day", true), &settings.brightness_day, "brd", saveDayBrightness) || saved;
  saved = saveInt(request->getParam("brightness_night", true), &settings.brightness_night, "brn", saveNightBrightness) || saved;
  saved = saveInt(request->getParam("day_start", true), &settings.day_start, "ds") || saved;
  saved = saveInt(request->getParam("night_start", true), &settings.night_start, "ns") || saved;
  saved = saveInt(request->getParam("brightness_auto", true), &settings.brightness_mode, "bra", saveAutoBrightnessMode) || saved;
  saved = saveInt(request->getParam("brightness_alert", true), &settings.brightness_alert, "ba") || saved;
  saved = saveInt(request->getParam("brightness_clear", true), &settings.brightness_clear, "bc") || saved;
  saved = saveInt(request->getParam("brightness_new_alert", true), &settings.brightness_new_alert, "bna") || saved;
  saved = saveInt(request->getParam("brightness_alert_over", true), &settings.brightness_alert_over, "bao") || saved;
  saved = saveInt(request->getParam("brightness_explosion", true), &settings.brightness_explosion, "bex") || saved;
  saved = saveInt(request->getParam("brightness_home_district", true), &settings.brightness_home_district, "bhd") || saved;
  saved = saveInt(request->getParam("brightness_bg", true), &settings.brightness_bg, "bbg") || saved;
  saved = saveInt(request->getParam("brightness_service", true), &settings.brightness_service, "bs", NULL, checkServicePins) || saved;
  saved = saveFloat(request->getParam("light_sensor_factor", true), &settings.light_sensor_factor, "lsf") || saved;
  saved = saveBool(request->getParam("dim_display_on_night", true), "dim_display_on_night", &settings.dim_display_on_night, "ddon", NULL, updateDisplayBrightness) || saved;

  if (saved) autoBrightnessUpdate();

  request->send(redirectResponce(request, "/brightness", saved));
}

void handleSaveColors(AsyncWebServerRequest* request) {
  bool saved = false;
  saved = saveInt(request->getParam("color_alert", true), &settings.color_alert, "coloral") || saved;
  saved = saveInt(request->getParam("color_clear", true), &settings.color_clear, "colorcl") || saved;
  saved = saveInt(request->getParam("color_new_alert", true), &settings.color_new_alert, "colorna") || saved;
  saved = saveInt(request->getParam("color_alert_over", true), &settings.color_alert_over, "colorao") || saved;
  saved = saveInt(request->getParam("color_explosion", true), &settings.color_explosion, "colorex") || saved;
  saved = saveInt(request->getParam("color_missiles", true), &settings.color_missiles, "colormi") || saved;
  saved = saveInt(request->getParam("color_drones", true), &settings.color_drones, "colordr") || saved;
  saved = saveInt(request->getParam("color_home_district", true), &settings.color_home_district, "colorhd") || saved;

  request->send(redirectResponce(request, "/colors", saved));
}

void handleSaveModes(AsyncWebServerRequest* request) {
  bool saved = false;
  saved = saveInt(request->getParam("map_mode", true), &settings.map_mode, "mapmode", saveMapMode) || saved;
  saved = saveInt(request->getParam("brightness_lamp", true), &settings.ha_light_brightness, "ha_lbri", saveLampBrightness) || saved;
  saved = saveInt(request->getParam("display_mode", true), &settings.display_mode, "dm", saveDisplayMode) || saved;
  saved = saveInt(request->getParam("home_district", true), &settings.home_district, "hd", saveHomeDistrict) || saved;
  saved = saveInt(request->getParam("display_mode_time", true), &settings.display_mode_time, "dmt") || saved;
  saved = saveBool(request->getParam("toggle_mode_weather", true), "toggle_mode_weather", &settings.toggle_mode_weather, "tmw") || saved;
  saved = saveBool(request->getParam("toggle_mode_temp", true), "toggle_mode_temp", &settings.toggle_mode_temp, "tmt") || saved;
  saved = saveBool(request->getParam("toggle_mode_hum", true), "toggle_mode_hum", &settings.toggle_mode_hum, "tmh") || saved;
  saved = saveBool(request->getParam("toggle_mode_press", true), "toggle_mode_press", &settings.toggle_mode_press, "tmp") || saved;
  saved = saveFloat(request->getParam("temp_correction", true), &settings.temp_correction, "ltc", NULL, climateSensorCycle) || saved;
  saved = saveFloat(request->getParam("hum_correction", true), &settings.hum_correction, "lhc", NULL, climateSensorCycle) || saved;
  saved = saveFloat(request->getParam("pressure_correction", true), &settings.pressure_correction, "lpc", NULL, climateSensorCycle) || saved;
  saved = saveInt(request->getParam("weather_min_temp", true), &settings.weather_min_temp, "mintemp") || saved;
  saved = saveInt(request->getParam("weather_max_temp", true), &settings.weather_max_temp, "maxtemp") || saved;
  saved = saveInt(request->getParam("button_mode", true), &settings.button_mode, "bm") || saved;
  saved = saveInt(request->getParam("button2_mode", true), &settings.button2_mode, "b2m") || saved;
  saved = saveInt(request->getParam("button_mode_long", true), &settings.button_mode_long, "bml") || saved;
  saved = saveInt(request->getParam("button2_mode_long", true), &settings.button2_mode_long, "b2ml") || saved;
  saved = saveInt(request->getParam("kyiv_district_mode", true), &settings.kyiv_district_mode, "kdm") || saved;
  saved = saveBool(request->getParam("home_alert_time", true), "home_alert_time", &settings.home_alert_time, "hat", saveShowHomeAlarmTime) || saved;
  saved = saveInt(request->getParam("alarms_notify_mode", true), &settings.alarms_notify_mode, "anm") || saved;
  saved = saveBool(request->getParam("enable_explosions", true), "enable_explosions", &settings.enable_explosions, "eex") || saved;
  saved = saveBool(request->getParam("enable_missiles", true), "enable_missiles", &settings.enable_missiles, "emi") || saved;
  saved = saveBool(request->getParam("enable_drones", true), "enable_drones", &settings.enable_drones, "edr") || saved;
  saved = saveInt(request->getParam("alert_on_time", true), &settings.alert_on_time, "aont") || saved;
  saved = saveInt(request->getParam("alert_off_time", true), &settings.alert_off_time, "aoft") || saved;
  saved = saveInt(request->getParam("explosion_time", true), &settings.explosion_time, "ext") || saved;
  saved = saveInt(request->getParam("alert_blink_time", true), &settings.alert_blink_time, "abt") || saved;
  saved = saveInt(request->getParam("alarms_auto_switch", true), &settings.alarms_auto_switch, "aas", saveAutoAlarmMode) || saved;
  saved = saveBool(request->getParam("service_diodes_mode", true), "service_diodes_mode", &settings.service_diodes_mode, "sdm", NULL, checkServicePins) || saved;
  saved = saveBool(request->getParam("min_of_silence", true), "min_of_silence", &settings.min_of_silence, "mos") || saved;
  saved = saveBool(request->getParam("invert_display", true), "invert_display", &settings.invert_display, "invd", NULL, updateInvertDisplayMode) || saved;
  saved = saveInt(request->getParam("time_zone", true), &settings.time_zone, "tz", NULL, []() {
    timeClient.setTimeZone(settings.time_zone);
  }) || saved;

  if (request->hasParam("color_lamp", true)) {
    int selectedHue = request->getParam("color_lamp", true)->value().toInt();
    RGBColor rgb = hue2rgb(selectedHue);
    saved = saveLampRgb(rgb.r, rgb.g, rgb.b) || saved;
  }

  request->send(redirectResponce(request, "/modes", saved));
}

void handleSaveSounds(AsyncWebServerRequest* request) {
  bool saved = false;
  saved = saveBool(request->getParam("sound_on_min_of_sl", true), "sound_on_min_of_sl", &settings.sound_on_min_of_sl, "somos") || saved;
  saved = saveBool(request->getParam("sound_on_alert", true), "sound_on_alert", &settings.sound_on_alert, "soa") || saved;
  saved = saveInt(request->getParam("melody_on_alert", true), &settings.melody_on_alert, "moa") || saved;
  saved = saveBool(request->getParam("sound_on_alert_end", true), "sound_on_alert_end", &settings.sound_on_alert_end, "soae") || saved;
  saved = saveInt(request->getParam("melody_on_alert_end", true), &settings.melody_on_alert_end, "moae") || saved;
  saved = saveBool(request->getParam("sound_on_explosion", true), "sound_on_explosion", &settings.sound_on_explosion, "soex") || saved;
  saved = saveInt(request->getParam("melody_on_explosion", true), &settings.melody_on_explosion, "moex") || saved;
  saved = saveBool(request->getParam("sound_on_every_hour", true), "sound_on_every_hour", &settings.sound_on_every_hour, "soeh") || saved;
  saved = saveBool(request->getParam("sound_on_button_click", true), "sound_on_button_click", &settings.sound_on_button_click, "sobc") || saved;
  saved = saveBool(request->getParam("mute_sound_on_night", true), "mute_sound_on_night", &settings.mute_sound_on_night, "mson") || saved;
  saved = saveBool(request->getParam("ignore_mute_on_alert", true), "ignore_mute_on_alert", &settings.ignore_mute_on_alert, "imoa") || saved;
  saved = saveInt(request->getParam("melody_volume", true), &settings.melody_volume, "mv", NULL, []() {
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    player->setVolume(expMap(settings.melody_volume, 0, 100, 0, 255));
  }
#endif
  }) || saved;

  request->send(redirectResponce(request, "/sounds", saved));
}

void handleRefreshTelemetry(AsyncWebServerRequest* request) {
  request->send(redirectResponce(request, "/telemetry", false));
}

void handleSaveDev(AsyncWebServerRequest* request) {
  bool reboot = false;
  reboot = saveInt(request->getParam("legacy", true), &settings.legacy, "legacy") || reboot;
  reboot = saveInt(request->getParam("display_height", true), &settings.display_height, "dh") || reboot;
  reboot = saveInt(request->getParam("display_model", true), &settings.display_model, "dsmd") || reboot;
  reboot = saveString(request->getParam("ha_brokeraddress", true), settings.ha_brokeraddress, "ha_brokeraddr") || reboot;
  reboot = saveInt(request->getParam("ha_mqttport", true), &settings.ha_mqttport, "ha_mqttport") || reboot;
  reboot = saveString(request->getParam("ha_mqttuser", true), settings.ha_mqttuser, "ha_mqttuser") || reboot;
  reboot = saveString(request->getParam("ha_mqttpassword", true), settings.ha_mqttpassword, "ha_mqttpass") || reboot;
  reboot = saveString(request->getParam("devicename", true), settings.devicename, "dn") || reboot;
  reboot = saveString(request->getParam("devicedescription", true), settings.devicedescription, "dd") || reboot;
  reboot = saveString(request->getParam("broadcastname", true), settings.broadcastname, "bn") || reboot;
  reboot = saveString(request->getParam("serverhost", true), settings.serverhost, "wshost") || reboot;
  reboot = saveString(request->getParam("ntphost", true), settings.ntphost, "ntph") || reboot;
  reboot = saveInt(request->getParam("websocket_port", true), &settings.websocket_port, "wsnp") || reboot;
  reboot = saveInt(request->getParam("updateport", true), &settings.updateport, "upp") || reboot;
  reboot = saveInt(request->getParam("pixelpin", true), &settings.pixelpin, "pp") || reboot;
  reboot = saveInt(request->getParam("bg_pixelpin", true), &settings.bg_pixelpin, "bpp") || reboot;
  reboot = saveInt(request->getParam("bg_pixelcount", true), &settings.bg_pixelcount, "bpc") || reboot;
  reboot = saveInt(request->getParam("buttonpin", true), &settings.buttonpin, "bp") || reboot;
  reboot = saveInt(request->getParam("button2pin", true), &settings.button2pin, "b2p") || reboot;
  reboot = saveInt(request->getParam("alert_clear_pin_mode", true), &settings.alert_clear_pin_mode, "acpm", NULL, disableAlertAndClearPins) || reboot;
  reboot = saveInt(request->getParam("alertpin", true), &settings.alertpin, "ap") || reboot;
  reboot = saveInt(request->getParam("clearpin", true), &settings.clearpin, "cp") || reboot;
  reboot = saveFloat(request->getParam("alert_clear_pin_time", true), &settings.alert_clear_pin_time, "acpt", NULL, disableAlertAndClearPins) || reboot;
  reboot = saveInt(request->getParam("lightpin", true), &settings.lightpin, "lp") || reboot;
  reboot = saveInt(request->getParam("buzzerpin", true), &settings.buzzerpin, "bzp") || reboot;

  if (reboot) {
    rebootDevice(3000, true);
  }
  request->send(redirectResponce(request, "/dev", false, reboot));
}

void handleBackup(AsyncWebServerRequest* request) {
  AsyncResponseStream* response = request->beginResponseStream("application/json");
  backupSettings(response);
  char filenameHeader[65];
  sprintf(filenameHeader, "attachment; filename=\"jaam_backup_%s.json\"", timeClient.unixToString("YYYY.MM.DD_hh-mm-ss").c_str());
  response->addHeader("Content-Disposition", filenameHeader);
  response->setCode(200);
  request->send(response);
}

StreamString jsonBody;

void handleRestoreBody(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  LOG.println("Received restore json part...");
  LOG.printf("Filename: %s\n", filename.c_str());
  size_t totalSize = request->contentLength();
  LOG.printf("File size: %d\n", totalSize);
  LOG.printf("Part Size: %d\n", len);
  if (totalSize > MAX_JSON_SIZE) {
    LOG.println("File size is too big!");
    return;
  }
  jsonBody.write(data, len);
}

void handleRestore(AsyncWebServerRequest *request) {
  LOG.println("Restoring settings...");
  const char* jsonString = jsonBody.c_str();
  LOG.printf("JSON to restore: %s\n", jsonString);
  JsonDocument json;
  deserializeJson(json, jsonString);
  bool restored = restoreSettings(json.as<JsonObject>());
  if (restored) {
    rebootDevice(3000, true);
  }
  jsonBody.clear();
  LOG.printf("Setting restored: %s\n", restored ? "true" : "false");
  request->send(redirectResponce(request, "/dev", false, false, restored, !restored));
}

#if FW_UPDATE_ENABLED
void handleSaveFirmware(AsyncWebServerRequest* request) {
  bool saved = false;
  saved = saveBool(request->getParam("new_fw_notification", true), "new_fw_notification", &settings.new_fw_notification, "nfwn") || saved;
  saved = saveInt(request->getParam("fw_update_channel", true), &settings.fw_update_channel, "fwuc", NULL, saveLatestFirmware) || saved;

  request->send(redirectResponce(request, "/firmware", saved));
}
#endif

#if BUZZER_ENABLED
void handlePlayTestSound(AsyncWebServerRequest* request) {
  if (isBuzzerEnabled()) {
    int soundId = request->getParam("id", false)->value().toInt();
    playMelody(MELODIES[soundId]);
    showServiceMessage(MELODY_NAMES[soundId], "Мелодія");
    request->send(200, "text/plain", "Test sound played!");
  }
}
#endif

void setupRouting() {
  LOG.println("Init WebServer");
  webserver.on("/", HTTP_GET, handleRoot);
  webserver.on("/brightness", HTTP_GET, handleBrightness);
  webserver.on("/saveBrightness", HTTP_POST, handleSaveBrightness);
  webserver.on("/colors", HTTP_GET, handleColors);
  webserver.on("/saveColors", HTTP_POST, handleSaveColors);
  webserver.on("/modes", HTTP_GET, handleModes);
  webserver.on("/saveModes", HTTP_POST, handleSaveModes);
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    webserver.on("/sounds", HTTP_GET, handleSounds);
    webserver.on("/saveSounds", HTTP_POST, handleSaveSounds);
  }
#endif
  webserver.on("/telemetry", HTTP_GET, handleTelemetry);
  webserver.on("/refreshTelemetry", HTTP_POST, handleRefreshTelemetry);
  webserver.on("/dev", HTTP_GET, handleDev);
  webserver.on("/saveDev", HTTP_POST, handleSaveDev);
#if FW_UPDATE_ENABLED
  webserver.on("/firmware", HTTP_GET, handleFirmware);
  webserver.on("/saveFirmware", HTTP_POST, handleSaveFirmware);
  webserver.on("/update", HTTP_POST, handleUpdate);
#endif
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    webserver.on("/playTestSound", HTTP_GET, handlePlayTestSound);
  }
#endif
  webserver.on("/backup", HTTP_GET, handleBackup);
  webserver.on("/restore", HTTP_POST, handleRestore, handleRestoreBody, NULL);
  webserver.begin();
  LOG.println("Webportal running");
}
//--Web server end

//--Service messages start
void uptime() {
  int   uptimeValue   = millis() / 1000;
  fillUptime(uptimeValue, uptimeChar);

  float totalHeapSize = ESP.getHeapSize() / 1024.0;
  freeHeapSize  = ESP.getFreeHeap() / 1024.0;
  usedHeapSize  = totalHeapSize - freeHeapSize;
  cpuTemp       = temperatureRead();
  wifiSignal    = WiFi.RSSI();

  ha.setUptime(uptimeValue);
  ha.setWifiSignal(wifiSignal);
  ha.setFreeMemory(freeHeapSize);
  ha.setUsedMemory(usedHeapSize);
  ha.setCpuTemp(cpuTemp);
}

void connectStatuses() {
  LOG.print("Map API status: ");
  apiConnected = client_websocket.available();
  LOG.println(apiConnected ? "Connected" : "Disconnected");
  haConnected = false;
  if (ha.isHaAvailable()) {
    haConnected = ha.isMqttConnected();
    LOG.print("Home Assistant MQTT status: ");
    LOG.println(haConnected ? "Connected" : "Disconnected");
    if (haConnected) {
      servicePin(HA, HIGH, false);
    } else {
      servicePin(HA, LOW, false);
    }
    ha.setMapApiConnect(apiConnected);
  }
}

//--Service messages end

static JsonDocument parseJson(const char* payload) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    LOG.printf("Deserialization error: $s\n", error.f_str());
    return doc;
  } else {
    return doc;
  }
}

#if FW_UPDATE_ENABLED
static void fillBinList(JsonDocument data, const char* payloadKey, char* binsList[], int *binsCount) {
  JsonArray arr = data[payloadKey].as<JsonArray>();
  *binsCount = min(static_cast<int>(arr.size()), MAX_BINS_LIST_SIZE);
  for (int i = 0; i < *binsCount; i++) {
    const char* filename = arr[i].as<const char*>();
    binsList[i] = new char[strlen(filename)];
    strcpy(binsList[i], filename);
  }
  LOG.printf("Successfully parsed %s list. List size: %d\n", payloadKey, *binsCount);
}
#endif

void alertPinCycle() {
  if (isAlertPinEnabled() && settings.alert_clear_pin_mode == 0) {
    if (alarmNow && digitalRead(settings.alertpin) == LOW) {
      setAlertPin();
    }
    if (!alarmNow && digitalRead(settings.alertpin) == HIGH) {
      disableAlertPin();
    }
  }
  if (isAlertPinEnabled() && settings.alert_clear_pin_mode == 1 && alarmNow && !pinAlarmNow) {
    pinAlarmNow = true;
    if (!isFirstDataFetchCompleted) {
      LOG.println("Do not set alert pin on first data fetch");
      return;
    }
    setAlertPin();
    long timeoutMs = settings.alert_clear_pin_time * 1000;
    LOG.printf("Alert pin will be disabled in %d ms\n", timeoutMs);
    asyncEngine.setTimeout(disableAlertPin, timeoutMs);
  }
  if (isClearPinEnabled() && settings.alert_clear_pin_mode == 1 && !alarmNow && pinAlarmNow) {
    pinAlarmNow = false;
    if (!isFirstDataFetchCompleted) {
      LOG.println("Do not set clear pin on first data fetch");
      return;
    }
    setClearPin();
    long timeoutMs = settings.alert_clear_pin_time * 1000;
    LOG.printf("Clear pin will be disabled in %d ms\n", timeoutMs);
    asyncEngine.setTimeout(disableClearPin, timeoutMs);
  }
}

void checkHomeDistrictAlerts() {
  int ledStatus = alarm_leds[calculateOffset(settings.home_district, offset)];
  int localHomeExplosions = explosions_time[calculateOffset(settings.home_district, offset)];
  bool localAlarmNow = ledStatus == 1;
  if (localAlarmNow != alarmNow) {
    alarmNow = localAlarmNow;
    if (alarmNow && needToPlaySound(ALERT_ON)) playMelody(ALERT_ON);
    if (!alarmNow && needToPlaySound(ALERT_OFF)) playMelody(ALERT_OFF);

    alertPinCycle();

    if (alarmNow) {
      showServiceMessage("Тривога!", DISTRICTS[settings.home_district], 5000);
    } else {
      showServiceMessage("Відбій!", DISTRICTS[settings.home_district], 5000);
    }
    ha.setAlarmAtHome(alarmNow);
  }
  if (localHomeExplosions != homeExplosionTime) {
    homeExplosionTime = localHomeExplosions;
    if (homeExplosionTime > 0 && timeClient.unixGMT() - homeExplosionTime < settings.explosion_time * 60 && settings.alarms_notify_mode > 0) {
      showServiceMessage("Вибухи!", DISTRICTS[settings.home_district], 5000);
      if (needToPlaySound(EXPLOSIONS)) playMelody(EXPLOSIONS);
    }
  }
}

//--Websocket process start

void onMessageCallback(WebsocketsMessage message) {
  LOG.print("Got Message: ");
  LOG.println(message.data());
  JsonDocument data = parseJson(message.data().c_str());
  String payload = data["payload"];
  if (!payload.isEmpty()) {
    if (payload == "ping") {
      LOG.println("Heartbeat from server");
      websocketLastPingTime = millis();
    } else if (payload == "alerts") {
      for (int i = 0; i < 26; ++i) {
        alarm_leds[calculateOffset(i, offset)] = data["alerts"][i][0];
        alarm_time[calculateOffset(i, offset)] = data["alerts"][i][1];
      }
      LOG.println("Successfully parsed alerts data");
    } else if (payload == "weather") {
      for (int i = 0; i < 26; ++i) {
        weather_leds[calculateOffset(i, offset)] = data["weather"][i];
      }
      LOG.println("Successfully parsed weather data");
      ha.setHomeTemperature(weather_leds[calculateOffset(settings.home_district, offset)]);
    } else if (payload == "explosions") {
      for (int i = 0; i < 26; ++i) {
        explosions_time[calculateOffset(i, offset)] = data["explosions"][i];
      }
      LOG.println("Successfully parsed explosions data");
    } else if (payload == "missiles") {
      for (int i = 0; i < 26; ++i) {
        missiles_time[calculateOffset(i, offset)] = data["missiles"][i];
      }
      LOG.println("Successfully parsed missiles data");
    } else if (payload == "drones") {
      for (int i = 0; i < 26; ++i) {
        drones_time[calculateOffset(i, offset)] = data["drones"][i];
      }
      LOG.println("Successfully parsed drones data");
#if FW_UPDATE_ENABLED
    } else if (payload == "bins") {
      fillBinList(data, "bins", bin_list, &binsCount);
      saveLatestFirmware();
    } else if (payload == "test_bins") {
      fillBinList(data, "test_bins", test_bin_list, &testBinsCount);
      saveLatestFirmware();
#endif
    }
  }
  checkHomeDistrictAlerts();
  alertPinCycle();
  isFirstDataFetchCompleted = true;
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    apiConnected = true;
    LOG.println("connnection opened");
    servicePin(DATA, HIGH, false);
    websocketLastPingTime = millis();
    ha.setMapApiConnect(apiConnected);
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    apiConnected = false;
    LOG.println("connnection closed");
    servicePin(DATA, LOW, false);
    ha.setMapApiConnect(apiConnected);
  } else if (event == WebsocketsEvent::GotPing) {
    LOG.println("websocket ping");
    websocketLastPingTime = millis();
  } else if (event == WebsocketsEvent::GotPong) {
    LOG.println("websocket pong");
  }
}

void socketConnect() {
  LOG.println("connection start...");
  showServiceMessage("підключення...", "Сервер даних");
  client_websocket.onMessage(onMessageCallback);
  client_websocket.onEvent(onEventsCallback);
  long startTime = millis();
  char webSocketUrl[100];
  sprintf(
    webSocketUrl,
    "ws://%s:%d/data_v3",
    settings.serverhost,
    settings.websocket_port
  );
  LOG.println(webSocketUrl);
  client_websocket.connect(webSocketUrl);
  if (client_websocket.available()) {
    LOG.print("connection time - ");
    LOG.print(millis() - startTime);
    LOG.println("ms");
    char chipIdInfo[25];
    sprintf(chipIdInfo, "chip_id:%s", chipID);
    LOG.println(chipIdInfo);
    client_websocket.send(chipIdInfo);
    char firmwareInfo[100];
    sprintf(firmwareInfo, "firmware:%s_%s", currentFwVersion, settings.identifier);
    LOG.println(firmwareInfo);
    client_websocket.send(firmwareInfo);

    char userInfo[250];
    JsonDocument userInfoJson;
    userInfoJson["legacy"] = settings.legacy;
    userInfoJson["kyiv_mode"] = settings.kyiv_district_mode;
    userInfoJson["display_model"] = display.getDisplayModel();
    if (display.isDisplayAvailable()) userInfoJson["display_height"] = settings.display_height;
    userInfoJson["bh1750"] = lightSensor.isLightSensorAvailable();
    userInfoJson["bme280"] = climate.isBME280Available();
    userInfoJson["bmp280"] = climate.isBMP280Available();
    userInfoJson["sht2x"] = climate.isSHT2XAvailable();
    userInfoJson["sht3x"] = climate.isSHT3XAvailable();
    userInfoJson["ha"] = ha.isHaAvailable();
    sprintf(userInfo, "user_info:%s", userInfoJson.as<String>().c_str());
    LOG.println(userInfo);
    client_websocket.send(userInfo);
    client_websocket.ping();
    websocketReconnect = false;
    showServiceMessage("підключено!", "Сервер даних", 3000);
  } else {
    showServiceMessage("недоступний", "Сервер даних", 3000);
  }
}

void websocketProcess() {
  if (millis() - websocketLastPingTime > settings.ws_alert_time) {
    websocketReconnect = true;
  }
  if (millis() - websocketLastPingTime > settings.ws_reboot_time) {
    rebootDevice(3000, true);
  }
  if (!client_websocket.available() or websocketReconnect) {
    LOG.println("Reconnecting...");
    socketConnect();
  }
}
//--Websocket process end

//--Map processing start

CRGB processAlarms(int led, long time, int expTime, int missilesTime, int dronesTime, int position, float alertBrightness, float notificationBrightness, bool isBgStrip) {
  CRGB hue;
  float localBrightnessAlert = isBgStrip ? settings.brightness_bg / 100.0f : settings.brightness_alert / 100.0f;
  float localBrightnessClear = isBgStrip ? settings.brightness_bg / 100.0f : settings.brightness_clear / 100.0f;
  float localBrightnessHomeDistrict = isBgStrip ? settings.brightness_bg / 100.0f : settings.brightness_home_district / 100.0f;

  int localDistrict = calculateOffsetDistrict(settings.kyiv_district_mode, settings.home_district, offset);
  int colorSwitch;

  unix_t currentTime = timeClient.unixGMT();

  // explosions has highest priority
  if (settings.enable_explosions && expTime > 0 && currentTime - expTime < settings.explosion_time * 60 && settings.alarms_notify_mode > 0) {
    colorSwitch = settings.color_explosion;
    hue = fromHue(colorSwitch, notificationBrightness * settings.brightness_explosion);
    return hue;
  }

  // missiles has second priority
  if (settings.enable_missiles && missilesTime > 0 && currentTime - missilesTime < settings.explosion_time * 60 && settings.alarms_notify_mode > 0) {
    colorSwitch = settings.color_missiles;
    hue = fromHue(colorSwitch, notificationBrightness * settings.brightness_explosion);
    return hue;
  }

  // drones has third priority
  if (settings.enable_drones && dronesTime > 0 && currentTime - dronesTime < settings.explosion_time * 60 && settings.alarms_notify_mode > 0) {
    colorSwitch = settings.color_drones;
    hue = fromHue(colorSwitch, notificationBrightness * settings.brightness_explosion);
    return hue;
  }

  switch (led) {
    case ALERT:
      if (currentTime - time < settings.alert_on_time * 60 && settings.alarms_notify_mode > 0) {
        colorSwitch = settings.color_new_alert;
        hue = fromHue(colorSwitch, alertBrightness * settings.brightness_new_alert);
      } else {
        colorSwitch = settings.color_alert;
        hue = fromHue(colorSwitch, settings.current_brightness * localBrightnessAlert);
      }
      break;
    case CLEAR:
      if (currentTime - time < settings.alert_off_time * 60 && settings.alarms_notify_mode > 0) {
        colorSwitch = settings.color_alert_over;
        hue = fromHue(colorSwitch, alertBrightness * settings.brightness_alert_over);
      } else {
        float localBrightness;
        if (position == localDistrict) {
          colorSwitch = settings.color_home_district;
          localBrightness = localBrightnessHomeDistrict;
        } else {
          colorSwitch = settings.color_clear;
          localBrightness = localBrightnessClear;
        }
        hue = fromHue(colorSwitch, settings.current_brightness * localBrightness);
      }
      break;
  }
  return hue;
}

float getFadeInFadeOutBrightness(float maxBrightness, long fadeTime) {
  float fixedMaxBrightness = (maxBrightness > 0.0f && maxBrightness < minBlinkBrightness) ? minBlinkBrightness : maxBrightness;
  float minBrightness = fixedMaxBrightness * 0.01f;
  int progress = micros() % (fadeTime * 1000);
  int halfBlinkTime = fadeTime * 500;
  float blinkBrightness;
  if (progress < halfBlinkTime) {
    blinkBrightness = mapf(progress, 0, halfBlinkTime, minBrightness, fixedMaxBrightness);
  } else {
    blinkBrightness = mapf(progress, halfBlinkTime + 1, halfBlinkTime * 2, fixedMaxBrightness, minBrightness);
  }
  return blinkBrightness;
}

void playMinOfSilenceSound() {
  playMelody(MIN_OF_SILINCE);
}

void checkMinuteOfSilence() {
  bool localMinOfSilence = (settings.min_of_silence == 1 && timeClient.hour() == 9 && timeClient.minute() == 0);
  if (localMinOfSilence != minuteOfSilence) {
    minuteOfSilence = localMinOfSilence;
    ha.setMapModeCurrent(MAP_MODES[getCurrentMapMode()]);
    // play mos beep every 2 sec during min of silence
    if (minuteOfSilence && needToPlaySound(MIN_OF_SILINCE)) {
      clockBeepInterval = asyncEngine.setInterval(playMinOfSilenceSound, 2000); // every 2 sec
    }
    // turn off mos beep
    if (!minuteOfSilence && clockBeepInterval >= 0) {
      asyncEngine.clearInterval(clockBeepInterval);
    }
#if BUZZER_ENABLED
    // play UA Anthem when min of silence ends
    if (isBuzzerEnabled() && !minuteOfSilence && needToPlaySound(MIN_OF_SILINCE_END)) {
      playMelody(MIN_OF_SILINCE_END);
      uaAnthemPlaying = true;
    }
#endif
  }
}

int processWeather(float temp) {
  float minTemp = settings.weather_min_temp;
  float maxTemp = settings.weather_max_temp;
  float normalizedValue = float(temp - minTemp) / float(maxTemp - minTemp);
  if (normalizedValue > 1) {
    normalizedValue = 1;
  }
  if (normalizedValue < 0) {
    normalizedValue = 0;
  }
  int hue = round(275 + normalizedValue * (0 - 275));
  hue %= 360;
  return hue;
}

void mapReconnect() {
  float localBrightness = getFadeInFadeOutBrightness(settings.current_brightness / 200.0f, settings.alert_blink_time * 1000);
  CRGB hue = fromHue(64, localBrightness * settings.current_brightness);
  for (uint16_t i = 0; i < 26; i++) {
    strip[i] = hue;
  }
  if (isBgStripEnabled()) {
    float brightness_factror = settings.brightness_bg / 100.0f;
    fill_solid(bg_strip, settings.bg_pixelcount, fromHue(64, localBrightness * settings.current_brightness * brightness_factror));
  }
  FastLED.show();
}

void mapOff() {
  fill_solid(strip, settings.pixelcount, CRGB::Black);
  if (isBgStripEnabled()) {
    fill_solid(bg_strip, settings.bg_pixelcount, CRGB::Black);
  }
  FastLED.show();
}

void mapLamp() {
  fill_solid(strip, settings.pixelcount, fromRgb(settings.ha_light_r, settings.ha_light_g, settings.ha_light_b, settings.ha_light_brightness));
  if (isBgStripEnabled()) {
    float brightness_factror = settings.brightness_bg / 100.0f;
    fill_solid(bg_strip, settings.bg_pixelcount, fromRgb(settings.ha_light_r, settings.ha_light_g, settings.ha_light_b, settings.ha_light_brightness * brightness_factror));
  }
  FastLED.show();
}

void mapAlarms() {
  uint8_t adapted_alarm_leds[settings.pixelcount];
  long adapted_alarm_timers[settings.pixelcount];
  long adapted_explosion_timers[settings.pixelcount];
  long adapted_missiles_timers[settings.pixelcount];
  long adapted_drones_timers[settings.pixelcount];
  adaptLeds(settings.kyiv_district_mode, alarm_leds, adapted_alarm_leds, settings.pixelcount, offset);
  adaptLeds(settings.kyiv_district_mode, alarm_time, adapted_alarm_timers, settings.pixelcount, offset);
  adaptLeds(settings.kyiv_district_mode, explosions_time, adapted_explosion_timers, settings.pixelcount, offset);
  adaptLeds(settings.kyiv_district_mode, missiles_time, adapted_missiles_timers, settings.pixelcount, offset);
  adaptLeds(settings.kyiv_district_mode, drones_time, adapted_drones_timers, settings.pixelcount, offset);
  if (settings.kyiv_district_mode == 4) {
    if (adapted_alarm_leds[25] == 0 and adapted_alarm_leds[7 + offset] == 0) {
      adapted_alarm_leds[7 + offset] = 0;
      adapted_alarm_timers[7 + offset] = max(adapted_alarm_timers[25], adapted_alarm_timers[7 + offset]);
    }
    if (adapted_alarm_leds[25] == 1 or adapted_alarm_leds[7 + offset] == 1) {
      adapted_alarm_leds[7 + offset] = 1;
      adapted_alarm_timers[7 + offset] = max(adapted_alarm_timers[25], adapted_alarm_timers[7 + offset]);
    }
    adapted_explosion_timers[7 + offset] = max(adapted_explosion_timers[25], adapted_explosion_timers[7 + offset]);
    adapted_missiles_timers[7 + offset] = max(adapted_missiles_timers[25], adapted_missiles_timers[7 + offset]);
    adapted_drones_timers[7 + offset] = max(adapted_drones_timers[25], adapted_drones_timers[7 + offset]);
  }
  float blinkBrightness = settings.current_brightness / 100.0f;
  float notificationBrightness = settings.current_brightness / 100.0f;
  if (settings.alarms_notify_mode == 2) {
    blinkBrightness = getFadeInFadeOutBrightness(blinkBrightness, settings.alert_blink_time * 1000);
    notificationBrightness = getFadeInFadeOutBrightness(notificationBrightness, settings.alert_blink_time * 500);
  }
  for (uint16_t i = 0; i < settings.pixelcount; i++) {
    strip[i] = processAlarms(
      adapted_alarm_leds[i],
      adapted_alarm_timers[i],
      adapted_explosion_timers[i],
      adapted_missiles_timers[i],
      adapted_drones_timers[i],
      i,
      blinkBrightness,
      notificationBrightness,
      false
    );
  }
  if (isBgStripEnabled()) {
    // same as for local district
    int localDistrict = calculateOffsetDistrict(settings.kyiv_district_mode, settings.home_district, offset);
    fill_solid(
      bg_strip,
      settings.bg_pixelcount,
      processAlarms(
        adapted_alarm_leds[localDistrict],
        adapted_alarm_timers[localDistrict],
        adapted_explosion_timers[localDistrict],
        adapted_missiles_timers[localDistrict],
        adapted_drones_timers[localDistrict],
        localDistrict,
        blinkBrightness,
        notificationBrightness,
        true
      )
    );
  }
  FastLED.show();
}

void mapWeather() {
  float adapted_weather_leds[settings.pixelcount];
  adaptLeds(settings.kyiv_district_mode, weather_leds, adapted_weather_leds, settings.pixelcount, offset);
  if (settings.kyiv_district_mode == 4) {
    adapted_weather_leds[7 + offset] = (weather_leds[25] + weather_leds[7]) / 2.0f;
  }
  for (uint16_t i = 0; i < settings.pixelcount; i++) {
    strip[i] = fromHue(processWeather(adapted_weather_leds[i]), settings.current_brightness);
  }
  if (isBgStripEnabled()) {
    // same as for local district
    int localDistrict = calculateOffsetDistrict(settings.kyiv_district_mode, settings.home_district, offset);
    float brightness_factror = settings.brightness_bg / 100.0f;
    fill_solid(bg_strip, settings.bg_pixelcount, fromHue(processWeather(adapted_weather_leds[localDistrict]), settings.current_brightness * brightness_factror));
  }
  FastLED.show();
}

void mapFlag() {
  uint8_t adapted_flag_leds[settings.pixelcount];
  adaptLeds(settings.kyiv_district_mode, flag_leds, adapted_flag_leds, settings.pixelcount, offset);
  for (uint16_t i = 0; i < settings.pixelcount; i++) {
    strip[i] = fromHue(adapted_flag_leds[i], settings.current_brightness);
  }
  if (isBgStripEnabled()) {
      // 180 - blue color
    float brightness_factror = settings.brightness_bg / 100.0f;
    fill_solid(bg_strip, settings.bg_pixelcount, fromHue(180, settings.current_brightness * brightness_factror));
  }
  FastLED.show();
}

void mapRandom() {
  int randomLed = random(settings.pixelcount);
  int randomColor = random(360);
  strip[randomLed] = fromHue(randomColor, settings.current_brightness);
  if (isBgStripEnabled()) {
    int bgRandomLed = random(settings.bg_pixelcount);
    int bgRandomColor = random(360);
    float brightness_factror = settings.brightness_bg / 100.0f;
    bg_strip[bgRandomLed] = fromHue(bgRandomColor, settings.current_brightness * brightness_factror);
  }
  FastLED.show();
}

void mapCycle() {
  int currentMapMode = getCurrentMapMode();
  // show mapRecconect mode if websocket is not connected and map mode != 0
  if (websocketReconnect && currentMapMode) {
    currentMapMode = 1000;
  }
  switch (currentMapMode) {
    case 0:
      mapOff();
      break;
    case 1:
      mapAlarms();
      break;
    case 2:
      mapWeather();
      break;
    case 3:
      mapFlag();
      break;
    case 4:
      mapRandom();
      break;
    case 5:
      mapLamp();
      break;
    case 1000:
      mapReconnect();
      break;
  }
}

//--Map processing end

void rebootCycle() {
  if (needRebootWithDelay != -1) {
    int localDelay = needRebootWithDelay;
    needRebootWithDelay = -1;
    rebootDevice(localDelay);
  }
}

void checkCurrentTimeAndPlaySound() {
  if (needToPlaySound(REGULAR) && beepHour != timeClient.hour() && timeClient.minute() == 0 && timeClient.second() == 0) {
    beepHour = timeClient.hour();
    playMelody(REGULAR);
  }
}

void calculateStates() {
  // check if we need activate "minute of silence mode"
  checkMinuteOfSilence();

  // check alert in home district
  checkHomeDistrictAlerts();

#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    checkCurrentTimeAndPlaySound();

    if (uaAnthemPlaying && !player->isPlaying()) {
      uaAnthemPlaying = false;
    }
  }
#endif
  // update service message expiration
  if (display.isDisplayAvailable()) serviceMessageUpdate();
}

void updateHaLightSensors() {
  if (lightSensor.isLightSensorAvailable()) {
    ha.setLightLevel(lightSensor.getLightLevel(settings.light_sensor_factor));
  }
}

void lightSensorCycle() {
  lightSensor.read();
  updateHaLightSensors();
}

void initChipID() {
  uint64_t chipid = ESP.getEfuseMac();
  sprintf(chipID, "%04x%04x", (uint32_t)(chipid >> 32), (uint32_t)chipid);
  LOG.printf("ChipID Inited: '%s'\n", chipID);
}

void initSettings() {
  LOG.println("Init settings");
  preferences.begin("storage", true);

  preferences.getString("dn", settings.devicename, sizeof(settings.devicename));
  preferences.getString("dd", settings.devicedescription, sizeof(settings.devicedescription));
  preferences.getString("bn", settings.broadcastname, sizeof(settings.broadcastname));
  preferences.getString("wshost", settings.serverhost, sizeof(settings.serverhost));
  preferences.getString("ntph", settings.ntphost, sizeof(settings.ntphost));
  preferences.getString("id", settings.identifier, sizeof(settings.identifier));
  settings.websocket_port         = preferences.getInt("wsnp", settings.websocket_port);
  settings.updateport             = preferences.getInt("upp", settings.updateport);
  settings.legacy                 = preferences.getInt("legacy", settings.legacy);
  settings.current_brightness     = preferences.getInt("cbr", settings.current_brightness);
  settings.brightness             = preferences.getInt("brightness", settings.brightness);
  settings.brightness_day         = preferences.getInt("brd", settings.brightness_day);
  settings.brightness_night       = preferences.getInt("brn", settings.brightness_night);
  settings.brightness_mode        = preferences.getInt("bra", settings.brightness_mode);
  settings.home_alert_time        = preferences.getInt("hat", settings.home_alert_time);
  settings.color_alert            = preferences.getInt("coloral", settings.color_alert);
  settings.color_clear            = preferences.getInt("colorcl", settings.color_clear);
  settings.color_new_alert        = preferences.getInt("colorna", settings.color_new_alert);
  settings.color_alert_over       = preferences.getInt("colorao", settings.color_alert_over);
  settings.color_explosion        = preferences.getInt("colorex", settings.color_explosion);
  settings.color_missiles         = preferences.getInt("colormi", settings.color_missiles);
  settings.color_drones           = preferences.getInt("colordr", settings.color_drones);
  settings.color_home_district    = preferences.getInt("colorhd", settings.color_home_district);
  settings.brightness_alert       = preferences.getInt("ba", settings.brightness_alert);
  settings.brightness_clear       = preferences.getInt("bc", settings.brightness_clear);
  settings.brightness_new_alert   = preferences.getInt("bna", settings.brightness_new_alert);
  settings.brightness_alert_over  = preferences.getInt("bao", settings.brightness_alert_over);
  settings.brightness_explosion   = preferences.getInt("bex", settings.brightness_explosion);
  settings.brightness_home_district = preferences.getInt("bhd", settings.brightness_home_district);
  settings.brightness_bg          = preferences.getInt("bbg", settings.brightness_bg);
  settings.brightness_service     = preferences.getInt("bs", settings.alert_on_time);
  settings.alarms_auto_switch     = preferences.getInt("aas", settings.alarms_auto_switch);
  settings.home_district          = preferences.getInt("hd", settings.home_district);
  settings.kyiv_district_mode     = preferences.getInt("kdm", settings.kyiv_district_mode);
  settings.map_mode               = preferences.getInt("mapmode", settings.map_mode);
  settings.display_mode           = preferences.getInt("dm", settings.display_mode);
  settings.display_mode_time      = preferences.getInt("dmt", settings.display_mode_time);
  settings.toggle_mode_weather    = preferences.getInt("tmw", settings.toggle_mode_weather);
  settings.toggle_mode_temp       = preferences.getInt("tmt", settings.toggle_mode_temp);
  settings.toggle_mode_hum        = preferences.getInt("tmh", settings.toggle_mode_hum);
  settings.toggle_mode_press      = preferences.getInt("tmp", settings.toggle_mode_press);
  settings.button_mode            = preferences.getInt("bm", settings.button_mode);
  settings.button2_mode           = preferences.getInt("b2m", settings.button2_mode);
  settings.button_mode_long       = preferences.getInt("bml", settings.button_mode_long);
  settings.button2_mode_long      = preferences.getInt("b2ml", settings.button2_mode_long);
  settings.alarms_notify_mode     = preferences.getInt("anm", settings.alarms_notify_mode);
  settings.enable_explosions      = preferences.getInt("eex", settings.enable_explosions);
  settings.enable_missiles        = preferences.getInt("emi", settings.enable_missiles);
  settings.enable_drones          = preferences.getInt("edr", settings.enable_drones);
  settings.weather_min_temp       = preferences.getInt("mintemp", settings.weather_min_temp);
  settings.weather_max_temp       = preferences.getInt("maxtemp", settings.weather_max_temp);
  preferences.getString("ha_brokeraddr", settings.ha_brokeraddress, sizeof(settings.ha_brokeraddress));
  settings.ha_mqttport            = preferences.getInt("ha_mqttport", settings.ha_mqttport);
  preferences.getString("ha_mqttuser", settings.ha_mqttuser, sizeof(settings.ha_mqttuser));
  preferences.getString("ha_mqttpass", settings.ha_mqttpassword, sizeof(settings.ha_mqttpassword));
  settings.display_model          = preferences.getInt("dsmd", settings.display_model);
  settings.display_width          = preferences.getInt("dw", settings.display_width);
  settings.display_height         = preferences.getInt("dh", settings.display_height);
  settings.day_start              = preferences.getInt("ds", settings.day_start);
  settings.night_start            = preferences.getInt("ns", settings.night_start);
  settings.pixelpin               = preferences.getInt("pp", settings.pixelpin);
  settings.bg_pixelpin            = preferences.getInt("bpp", settings.bg_pixelpin);
  settings.bg_pixelcount          = preferences.getInt("bpc", settings.bg_pixelcount);
  settings.service_ledpin         = preferences.getInt("slp", settings.service_ledpin);
  settings.buttonpin              = preferences.getInt("bp", settings.buttonpin);
  settings.button2pin             = preferences.getInt("b2p", settings.button2pin);
  settings.alert_clear_pin_mode   = preferences.getInt("acpm", settings.alert_clear_pin_mode);
  settings.alertpin               = preferences.getInt("ap", settings.alertpin);
  settings.clearpin               = preferences.getInt("cp", settings.clearpin);
  settings.alert_clear_pin_time   = preferences.getFloat("acpt", settings.alert_clear_pin_time);
  settings.buzzerpin              = preferences.getInt("bzp", settings.buzzerpin);
  settings.lightpin               = preferences.getInt("lp", settings.lightpin);
  settings.service_diodes_mode    = preferences.getInt("sdm", settings.service_diodes_mode);
  settings.new_fw_notification    = preferences.getInt("nfwn", settings.new_fw_notification);
  settings.ws_alert_time          = preferences.getInt("wsat", settings.ws_alert_time);
  settings.ws_reboot_time         = preferences.getInt("wsrt", settings.ws_reboot_time);
  settings.ha_light_brightness    = preferences.getInt("ha_lbri", settings.ha_light_brightness);
  settings.ha_light_r             = preferences.getInt("ha_lr", settings.ha_light_r);
  settings.ha_light_g             = preferences.getInt("ha_lg", settings.ha_light_g);
  settings.ha_light_b             = preferences.getInt("ha_lb", settings.ha_light_b);
  settings.min_of_silence         = preferences.getInt("mos", settings.min_of_silence);
  settings.fw_update_channel      = preferences.getInt("fwuc", settings.fw_update_channel);
  settings.temp_correction        = preferences.getFloat("ltc", settings.temp_correction);
  settings.hum_correction         = preferences.getFloat("lhc", settings.hum_correction);
  settings.pressure_correction    = preferences.getFloat("lpc", settings.pressure_correction);
  settings.light_sensor_factor    = preferences.getFloat("lsf", settings.light_sensor_factor);
  settings.sound_on_min_of_sl     = preferences.getInt("somos", settings.sound_on_min_of_sl);
  settings.sound_on_alert         = preferences.getInt("soa", settings.sound_on_alert);
  settings.sound_on_alert_end     = preferences.getInt("soae", settings.sound_on_alert_end);
  settings.sound_on_every_hour    = preferences.getInt("soeh", settings.sound_on_every_hour);
  settings.sound_on_button_click  = preferences.getInt("sobc", settings.sound_on_button_click);
  settings.sound_on_explosion     = preferences.getInt("soex", settings.sound_on_explosion);
  settings.melody_on_alert        = preferences.getInt("moa", settings.melody_on_alert);
  settings.melody_on_alert_end    = preferences.getInt("moae", settings.melody_on_alert_end);
  settings.melody_on_explosion    = preferences.getInt("moex", settings.melody_on_explosion);
  settings.mute_sound_on_night    = preferences.getInt("mson", settings.mute_sound_on_night);
  settings.invert_display         = preferences.getInt("invd", settings.invert_display);
  settings.dim_display_on_night   = preferences.getInt("ddon", settings.dim_display_on_night);
  settings.time_zone              = preferences.getInt("tz", settings.time_zone);
  settings.ignore_mute_on_alert   = preferences.getInt("imoa", settings.ignore_mute_on_alert);
  settings.alert_on_time          = preferences.getInt("aont", settings.alert_on_time);
  settings.alert_off_time         = preferences.getInt("aoft", settings.alert_off_time);
  settings.explosion_time         = preferences.getInt("ext", settings.explosion_time);
  settings.alert_blink_time       = preferences.getInt("abt", settings.alert_blink_time);
  settings.melody_volume          = preferences.getInt("mv", settings.melody_volume);

  preferences.end();

  currentFirmware = parseFirmwareVersion(VERSION);
  fillFwVersion(currentFwVersion, currentFirmware);
  LOG.printf("Current firmware version: %s\n", currentFwVersion);
  distributeBrightnessLevels();
}

void initLegacy() {
#if TEST_MODE
  settings.legacy = 3;
#endif
  switch (settings.legacy) {
  case 0:
    LOG.println("Mode: jaam 1");
    for (int i = 0; i < 26; i++) {
      flag_leds[calculateOffset(i, offset)] = LEGACY_FLAG_LEDS[i];
    }

    pinMode(settings.powerpin, OUTPUT);
    pinMode(settings.wifipin, OUTPUT);
    pinMode(settings.datapin, OUTPUT);
    pinMode(settings.hapin, OUTPUT);
    //pinMode(settings.reservedpin, OUTPUT);

    servicePin(POWER, HIGH, false);

    settings.kyiv_district_mode = 3;
    settings.pixelpin = 13;
    settings.bg_pixelpin = -1;
    settings.bg_pixelcount = 0;
    settings.service_ledpin = -1;
    settings.buttonpin = 35;
    settings.button2pin = -1;
    settings.display_model = 1;
    settings.display_height = 64;
    break;
  case 1:
    LOG.println("Mode: transcarpathia");
    offset = 0;
    for (int i = 0; i < 26; i++) {
      flag_leds[i] = LEGACY_FLAG_LEDS[i];
    }
    settings.service_diodes_mode = 0;
    break;
  case 2:
    LOG.println("Mode: odesa");
    for (int i = 0; i < 26; i++) {
      flag_leds[calculateOffset(i, offset)] = LEGACY_FLAG_LEDS[i];
    }
    settings.service_diodes_mode = 0;
    break;
  case 3:
    LOG.println("Mode: jaam 2");
    for (int i = 0; i < 26; i++) {
      flag_leds[calculateOffset(i, offset)] = LEGACY_FLAG_LEDS[i];
    }

    settings.kyiv_district_mode = 3;
    settings.pixelpin = 13;
    settings.bg_pixelpin = 12;
    settings.bg_pixelcount = 44;
    settings.service_ledpin = 25;
    settings.buttonpin = 4;
    settings.button2pin = 2;
    settings.buzzerpin = 33;
    settings.display_model = 2;
    settings.display_height = 64;
    brightnessFactor = 0.3f;
    minBrightness = 2;
    minBlinkBrightness = 0.07f;
    break;
  }
  LOG.printf("Offset: %d\n", offset);
}

void initButtons() {
  LOG.println("Init buttons");

  buttons.setButton1Pin(settings.buttonpin);
  buttons.setButton1ClickListener(button1Click);
  buttons.setButton1LongClickListener(button1LongClick);
  buttons.setButton1DuringLongClickListener(button1DuringLongClick);

  buttons.setButton2Pin(settings.button2pin);
  buttons.setButton2ClickListener(button2Click);
  buttons.setButton2LongClickListener(button2LongClick);
  buttons.setButton2DuringLongClickListener(button2DuringLongClick);
}

void initBuzzer() {
#if BUZZER_ENABLED
  if (isBuzzerEnabled()) {
    player = new MelodyPlayer(settings.buzzerpin, 0, LOW);
    player->setVolume(expMap(settings.melody_volume, 0, 100, 0, 255));
  }
#endif
}

void initAlertPin() {
  if (isAlertPinEnabled()) {
    LOG.printf("alertpin: %d\n", settings.alertpin);
    pinMode(settings.alertpin, OUTPUT);
  }
}

void initClearPin() {
  if (isClearPinEnabled() && settings.alert_clear_pin_mode == 1) {
    LOG.printf("clearpin: %d\n", settings.clearpin);
    pinMode(settings.clearpin, OUTPUT);
  }
}

void initFastledStrip(uint8_t pin, const CRGB *leds, int pixelcount) {
  switch (pin)
  {
  case 2:
    FastLED.addLeds<NEOPIXEL, 2>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 4:
    FastLED.addLeds<NEOPIXEL, 4>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 12:
    FastLED.addLeds<NEOPIXEL, 12>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 13:
    FastLED.addLeds<NEOPIXEL, 13>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 14:
    FastLED.addLeds<NEOPIXEL, 14>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 15:
    FastLED.addLeds<NEOPIXEL, 15>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 16:
    FastLED.addLeds<NEOPIXEL, 16>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 17:
    FastLED.addLeds<NEOPIXEL, 17>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 18:
    FastLED.addLeds<NEOPIXEL, 18>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 25:
    FastLED.addLeds<NEOPIXEL, 25>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 26:
    FastLED.addLeds<NEOPIXEL, 26>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 27:
    FastLED.addLeds<NEOPIXEL, 27>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 32:
    FastLED.addLeds<NEOPIXEL, 32>(const_cast<CRGB*>(leds), pixelcount);
    break;
  case 33:
    FastLED.addLeds<NEOPIXEL, 33>(const_cast<CRGB*>(leds), pixelcount);
    break;
  default:
    LOG.print("This PIN is not supported for LEDs: ");
    LOG.println(pin);
    break;
  }
}

void initStrip() {
  LOG.println("Init leds");
  LOG.print("pixelpin: ");
  LOG.println(settings.pixelpin);
  LOG.print("pixelcount: ");
  LOG.println(settings.pixelcount);
  initFastledStrip(settings.pixelpin, strip, settings.pixelcount);
  if (isBgStripEnabled()) {
    LOG.print("bg pixelpin: ");
    LOG.println(settings.bg_pixelpin);
    LOG.print("bg pixelcount: ");
    LOG.println(settings.bg_pixelcount);
    initFastledStrip(settings.bg_pixelpin, bg_strip, settings.bg_pixelcount);
  }
  if (isServiceStripEnabled()) {
    LOG.print("service ledpin: ");
    LOG.println(settings.service_ledpin);
    initFastledStrip(settings.service_ledpin, service_strip, 5);
    checkServicePins();
  }
  FastLED.setDither(DISABLE_DITHER);
  mapFlag();
}

void initDisplayOptions() {
  if (!display.isDisplayAvailable()) {
    // remove display related options from singl click optins list
    ignoreSingleClickOptions[0] = 2;
    ignoreSingleClickOptions[1] = 4;
    ignoreSingleClickOptions[2] = 5;
    // change single click option to default if it's not available
    if (isInArray(settings.button_mode, ignoreSingleClickOptions, SINGLE_CLICK_OPTIONS_MAX)) {
      saveInt(&settings.button_mode, "bm", 0, "button_mode");
    }
    if (isInArray(settings.button2_mode, ignoreSingleClickOptions, SINGLE_CLICK_OPTIONS_MAX)) {
      saveInt(&settings.button2_mode, "b2m", 0, "button2_mode");
    }

    // remove display related options from long click optins list
    ignoreLongClickOptions[0] = 2;
    ignoreLongClickOptions[1] = 4;
    ignoreLongClickOptions[2] = 5;
    // change long click option to default if it's not available
    if (isInArray(settings.button_mode_long, ignoreLongClickOptions, LONG_CLICK_OPTIONS_MAX)) {
      saveInt(&settings.button_mode_long, "bml", 0, "button_mode_long");
    }
    if (isInArray(settings.button2_mode_long, ignoreLongClickOptions, LONG_CLICK_OPTIONS_MAX)) {
      saveInt(&settings.button2_mode_long, "b2ml", 0, "button2_mode_long");
    }
  }
}

void initDisplayModes() {
  if (!climate.isAnySensorAvailable()) {
    // remove climate sensor options from display optins list
    ignoreDisplayModeOptions[0] = 4;
    // change display mode to "changing" if it's not available
    if (isInArray(settings.display_mode, ignoreDisplayModeOptions, DISPLAY_MODE_OPTIONS_MAX)) {
      saveDisplayMode(9);
    }
  }
}

void initDisplay() {
  display.begin(static_cast<JaamDisplay::DisplayModel>(settings.display_model), settings.display_width, settings.display_height);

  if (display.isDisplayAvailable()) {
    display.clearDisplay();
    display.setTextColor(2); // INVERSE
    updateInvertDisplayMode();
    updateDisplayBrightness();
    display.displayTextWithIcon(JaamDisplay::TRINDENT, "Just Another", "Alert Map", currentFwVersion);
    delay(3000);
  }
  initDisplayOptions();
}

void initSensors() {
  lightSensor.begin(settings.legacy);
  if (lightSensor.isLightSensorAvailable()) {
    lightSensorCycle();
  }
  if (isAnalogLightSensorEnabled()) {
    lightSensor.setPhotoresistorPin(settings.lightpin);
  }

  // init climate sensor
  climate.begin();
  // try to get climate sensor data
  climateSensorCycle();

  initDisplayModes();
}

void initUpdates() {
#if ARDUINO_OTA_ENABLED
  ArduinoOTA.onStart(showUpdateStart);
  ArduinoOTA.onEnd(showUpdateEnd);
  ArduinoOTA.onProgress(showUpdateProgress);
  ArduinoOTA.onError(showOtaUpdateErrorMessage);
  ArduinoOTA.begin();
#endif
#if FW_UPDATE_ENABLED
  Update.onProgress(showUpdateProgress);
  httpUpdate.onStart(showUpdateStart);
  httpUpdate.onEnd(showUpdateEnd);
  httpUpdate.onProgress(showUpdateProgress);
  httpUpdate.onError(showHttpUpdateErrorMessage);
#endif
}

void initHA() {
  if (shouldWifiReconnect) return;

  LOG.println("Init Home assistant API");

  if (!ha.initDevice(settings.ha_brokeraddress, settings.devicename, currentFwVersion, settings.devicedescription, chipID)) {
    LOG.println("Home Assistant is not available!");
    return;
  }

  ha.initUptimeSensor();
  ha.initWifiSignalSensor();
  ha.initFreeMemorySensor();
  ha.initUsedMemorySensor();
  ha.initCpuTempSensor(temperatureRead());
  ha.initBrightnessSensor(settings.brightness, saveBrightness);
  ha.initDayBrightnessSensor(settings.brightness_day, saveDayBrightness);
  ha.initNightBrightnessSensor(settings.brightness_night, saveNightBrightness);
  ha.initMapModeSensor(settings.map_mode, MAP_MODES, MAP_MODES_COUNT, saveMapMode);
  if (display.isDisplayAvailable()) {
    displayModeHAMap = ha.initDisplayModeSensor(getLocalDisplayMode(settings.display_mode, ignoreDisplayModeOptions), DISPLAY_MODES,
      DISPLAY_MODE_OPTIONS_MAX, ignoreDisplayModeOptions, saveDisplayMode, getSettingsDisplayMode);
    ha.initDisplayModeToggleSensor(nextDisplayMode);
    ha.initShowHomeAlarmTimeSensor(settings.home_alert_time, saveShowHomeAlarmTime);
  }
  ha.initAutoAlarmModeSensor(settings.alarms_auto_switch, AUTO_ALARM_MODES, AUTO_ALARM_MODES_COUNT, saveAutoAlarmMode);
  ha.initAutoBrightnessModeSensor(settings.brightness_mode, AUTO_BRIGHTNESS_MODES, AUTO_BRIGHTNESS_OPTIONS_COUNT, saveAutoBrightnessMode);
  ha.initMapModeCurrentSensor();
  ha.initHomeDistrictSensor();
  ha.initMapApiConnectSensor(apiConnected);
  ha.initRebootSensor([] { rebootDevice(); });
  ha.initMapModeToggleSensor(nextMapMode);
  ha.initLampSensor(settings.map_mode == 5, settings.ha_light_brightness, settings.ha_light_r, settings.ha_light_g, settings.ha_light_b,
    onNewLampStateFromHa, saveLampBrightness, saveLampRgb);
  ha.initAlarmAtHomeSensor(alarmNow);
  if (climate.isTemperatureAvailable()) {
    ha.initLocalTemperatureSensor(climate.getTemperature(settings.temp_correction));
  }
  if (climate.isHumidityAvailable()) {
    ha.initLocalHumiditySensor(climate.getHumidity(settings.hum_correction));
  }
  if (climate.isPressureAvailable()) {
    ha.initLocalPressureSensor(climate.getPressure(settings.pressure_correction));
  }
  if (lightSensor.isLightSensorAvailable()) {
    ha.initLightLevelSensor(lightSensor.getLightLevel(settings.light_sensor_factor));
  }
  ha.initHomeTemperatureSensor();
  ha.initNightModeSensor(nightMode, saveNightMode);

  ha.connectToMqtt(settings.ha_mqttport, settings.ha_mqttuser, settings.ha_mqttpassword, onMqttStateChanged);
}

void initWifi() {
  LOG.println("Init Wifi");
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // reset settings - wipe credentials for testing
  // wm.resetSettings();

  wm.setHostname(settings.broadcastname);
  wm.setTitle(settings.devicename);
  wm.setConfigPortalBlocking(true);
  wm.setConnectTimeout(3);
  wm.setConnectRetries(10);
  wm.setAPCallback(apCallback);
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setConfigPortalTimeout(180);
  servicePin(WIFI, LOW, false);
  showServiceMessage(wm.getWiFiSSID(true).c_str(), "Підключення до:", 5000);
  char apssid[20];
  sprintf(apssid, "%s_%s", settings.apssid, chipID);
  if (!wm.autoConnect(apssid)) {
    LOG.println("Reboot");
    rebootDevice(5000);
    return;
  }
  // Connected to WiFi
  LOG.println("connected...yeey :)");
  servicePin(WIFI, HIGH, false);
  showServiceMessage("Підключено до WiFi!");
  wm.setHttpPort(8080);
  wm.startWebPortal();
  delay(5000);
  setupRouting();
  initUpdates();
  initBroadcast();
  initHA();
  socketConnect();
  showServiceMessage(getLocalIP(), "IP-адреса мапи:", 5000);
}

void wifiReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    LOG.println("WiFI Reconnect");
    shouldWifiReconnect = true;
    initWifi();
  }
}

void initTime() {
  LOG.println("Init time");
  LOG.printf("NTP host: %s\n", settings.ntphost);
  timeClient.setHost(settings.ntphost);
  timeClient.setTimeZone(settings.time_zone);
  timeClient.setDSTauto(&dst); // auto update on summer/winter time.
  timeClient.setTimeout(5000); // 5 seconds waiting for reply
  timeClient.begin();
  syncTime(7);
}

void showLocalLightLevel() {
  char message[10];
  sprintf(message, "%.1f lx", lightSensor.getLightLevel(settings.light_sensor_factor));
  displayMessage(message, "Освітлення");
}

#if TEST_MODE
void runSelfTests() {
  mapFlag();
  playMelody(UA_ANTHEM);
  servicePin(POWER, HIGH, true);
  servicePin(WIFI, HIGH, true);
  servicePin(DATA, HIGH, true);
  servicePin(HA, HIGH, true);
  servicePin(RESERVED, HIGH, true);
  showLocalTemp();
  sleep(2);
  showLocalHum();
  sleep(2);
  showLocalPressure();
  sleep(2);
  showLocalLightLevel();
  sleep(2);
  displayMessage("Please test buttons");
}
#endif

void syncTimePeriodically() {
  syncTime(2);
}

void setup() {
  LOG.begin(115200);

  initChipID();
  initSettings();
  initLegacy();
  initButtons();
  initBuzzer();
  initAlertPin();
  initClearPin();
  initStrip();
  initDisplay();
  initSensors();
#if TEST_MODE
  runSelfTests();
#else
  initWifi();
  initTime();

  asyncEngine.setInterval(uptime, 5000);
  asyncEngine.setInterval(connectStatuses, 60000);
  asyncEngine.setInterval(mapCycle, 1000);
  asyncEngine.setInterval(displayCycle, 100);
  asyncEngine.setInterval(wifiReconnect, 1000);
  asyncEngine.setInterval(autoBrightnessUpdate, 1000);
  #if FW_UPDATE_ENABLED
  asyncEngine.setInterval(doUpdate, 1000);
  #endif
  asyncEngine.setInterval(websocketProcess, 3000);
  asyncEngine.setInterval(alertPinCycle, 1000);
  asyncEngine.setInterval(rebootCycle, 500);
  asyncEngine.setInterval(lightSensorCycle, 2000);
  asyncEngine.setInterval(climateSensorCycle, 5000);
  asyncEngine.setInterval(calculateStates, 500);
  asyncEngine.setInterval(syncTimePeriodically, 60000);
#endif
  esp_err_t result  = esp_task_wdt_init(WDT_TIMEOUT, true);
  if (result == ESP_OK) {
    LOG.println("Watchdog timer enabled");
    enableLoopWDT();
  } else {
    LOG.println("Watchdog timer NOT enabled");
  }
}

void loop() {
#if TELNET_ENABLED
  LOG.handle();
#endif
#if TEST_MODE==0
  wm.process();
  asyncEngine.run();
#if ARDUINO_OTA_ENABLED
  ArduinoOTA.handle();
#endif
  ha.loop();
  client_websocket.poll();
  if (getCurrentMapMode() == 1 && settings.alarms_notify_mode == 2) {
    mapCycle();
  }
#endif
  buttons.tick();
}
