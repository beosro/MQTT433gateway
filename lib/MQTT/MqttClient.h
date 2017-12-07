/**
  MQTT433gateway - MQTT 433.92 MHz radio gateway utilizing ESPiLight
  Project home: https://github.com/puuu/MQTT433gateway/

  The MIT License (MIT)

  Copyright (c) 2017 Jan Losinski

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation files
  (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <PubSubClient.h>
#include <Settings.h>
#include <WString.h>
#include <WiFiClient.h>

class SetHandler;

class MqttClient {
 public:
  using HandlerCallback =
      std::function<void(const String &topic_part, const String &payload)>;
  using SettingHandlerCallback = std::function<void(const String &payload)>;

  MqttClient(const Settings &settings, WiFiClient &client);

  void begin();

  bool connect();

  bool reconnect();

  bool subsrcibe();

  void loop();

  void sendCode(const String &protocol, const String &payload);
  void sendLog(int status, const String &protocol, const String &message);
  void sendRaw(const String &data);
  void sendOta(const String &topic, const String payload);

  void onSet(const String &url_part, const SettingHandlerCallback &cb);
  void onOta(const HandlerCallback &cb);
  void onRfData(const HandlerCallback &cb);

  ~MqttClient();

 private:
  void onMessage(char *topic, uint8_t *payload, unsigned int length);

  const Settings &settings;
  PubSubClient *mqttClient = nullptr;

  HandlerCallback codeCallback;
  const SetHandler *setHandlers = nullptr;
  HandlerCallback otaCallback;
};

#endif  // MQTTCLIENT_H
