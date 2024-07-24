#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#define NIGHT 0

class DoorAndLightWebsocket
{
public:
    DoorAndLightWebsocket(AsyncWebServer *_server, AsyncWebSocket *_ws);

    void initWebSocket();
    void notifyClients(String Data);

    void loop();

private:
    AsyncWebServer *server = nullptr;
    AsyncWebSocket *ws = nullptr;

    static void onWSEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void handleClientRequest(void *arg, uint8_t *data, size_t len);
    void sendClientInitialData(AsyncWebSocketClient *client);
};