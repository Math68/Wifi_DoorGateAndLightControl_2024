#include "websocket.h"

extern void setRelaisOn();
extern bool getDayState();
extern String InformClientAboutDoorsState();

static DoorAndLightWebsocket *wsinst = nullptr;

DoorAndLightWebsocket::DoorAndLightWebsocket(AsyncWebServer *_server, AsyncWebSocket *_ws):
    server(_server),
    ws(_ws)
{
    wsinst = this;
}

void DoorAndLightWebsocket::notifyClients(String Data)
{
  ws->textAll(Data);
}

void DoorAndLightWebsocket::onWSEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch(type){
    case WS_EVT_CONNECT:
      wsinst->sendClientInitialData(client);
    break;
    case WS_EVT_DISCONNECT:
    break;
    case WS_EVT_DATA:
      wsinst->handleClientRequest(arg, data, len);
    break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
    break;
  }
}

void DoorAndLightWebsocket::initWebSocket()
{
  ws->onEvent(onWSEvent);
  server->addHandler(ws);
}

void DoorAndLightWebsocket::DoorAndLightWebsocket::loop()
{
    ws->cleanupClients();
}

void DoorAndLightWebsocket::handleClientRequest(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    Serial.println(String((const char *)data));
        
    if(strcmp((char*)data, "clientRequestLightOn")==0)
    {
      //wsinst->notifyClients(RunModeState);
      if(getDayState() == NIGHT)
      {
        setRelaisOn();
      }
    } 
  }
}

void DoorAndLightWebsocket::sendClientInitialData(AsyncWebSocketClient *client)
{
  client->text(InformClientAboutDoorsState());
}