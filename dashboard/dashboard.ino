#include <WiFi.h>
#include "packets.h"

#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define LCD_RD  2  
#define LCD_WR  4
#define LCD_RS  15   
#define LCD_CS  33  
#define LCD_RST 32 

#define LCD_D0 13
#define LCD_D1 12
#define LCD_D2 26
#define LCD_D3 25
#define LCD_D4 17
#define LCD_D5 16
#define LCD_D6 27
#define LCD_D7 14

#define bgColor 0x0000
#define textColor 0xFFFF
#define ersColor 0xFFE0
#define ersLapColor 0xFFFF
#define emptyColor 0x528A
#define sGearColor 0xD000
#define fuelColor 0x0661
#define fuelColor2 0xD000
#define drsActiveColor 0x0721
#define drsAvailableColor 0xF424
#define drsDisabledColor 0x528A
#define lights1Color 0x1EC2
#define lights2Color 0xF980
#define lights3Color 0xAB1E
#define lightsOffColor 0x528A


const char* ssid = "YOU_NETWORK";
const char* pass = "PASSWORD";

WiFiUDP udp;
unsigned int port = 20777;

PacketHeader Header;
struct packets{
  PacketMotionData MotionData;
  PacketSessionData SessionData;
  PacketLapData LapData;
  PacketEventData EventData;
  PacketParticipantsData ParticipantsData;
  PacketCarSetupData CarSetupData;
  PacketCarTelemetryData CarTelemetryData;
  PacketCarStatusData CarStatusData;
  PacketFinalClassificationData FinalClassificationData;
  PacketLobbyInfoData LobbyInfoData;
  PacketCarDamageData CarDamageData;
  PacketSessionHistoryData SessionHistoryData;
};

packets actual;
packets prev;

String sfill(String no, int chr){ 
  for(int i = 0; i < chr; i++){
    if (no.length() >= chr) 
      return no;
    else no = " " + no;
  }
}

void printOP(String sPrev, String sActual, int chr, int x, int y, uint16_t bg, uint16_t color){
  sPrev = sfill(sPrev, chr);
  sActual = sfill(sActual, chr);
  for(int i=0; i<chr; i++){
    if(sPrev.charAt(i) != sActual.charAt(i)){
      tft.setTextColor(bg);
      tft.setCursor(x, y);
      tft.print(sfill(String(sPrev.charAt(i)), i+1));
      tft.setTextColor(color);
      tft.setCursor(x, y);        
      tft.print(sfill(String(sActual.charAt(i)), i+1));
    }
  }
}
unsigned long tiempo;
unsigned long tiempo2;

String f_sfill(String str, int chr){
  for(int i = 0; i < chr; i++){
    if (str.length() >= chr) 
      return str;
    else str += " ";
  }
}

struct color16_t {
  uint16_t value;

  color16_t(uint16_t v) : value(v) {}
  color16_t(uint8_t r, uint8_t g, uint8_t b) :
    value((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3)) {}
};

uint16_t calcDamageColor(double damage) {
  uint8_t r = (uint8_t)(255 * damage);
  uint8_t g = (uint8_t)(255 * (1 - damage));
  return color16_t(r, g, 0).value;
}

void data(){
  char buffer[2048];
  int packetSize = udp.parsePacket();
  if(packetSize){
    udp.read(buffer, 2048);
    Header.get(buffer);
    switch(Header.m_packetId){
      case 0:
        //actual.MotionData.get(buffer);
        break;
      case 1:
        actual.SessionData.get(buffer);
        break;
      case 2:
        actual.LapData.get(buffer);
        break;
      case 3:
        //actual.EventData.get(buffer);
        break;
      case 4:
        //actual.ParticipantsData.get(buffer);
        break;
      case 5:
        //actual.CarSetupData.get(buffer);
        break;
      case 6:
        actual.CarTelemetryData.get(buffer);
        break;
      case 7:
        actual.CarStatusData.get(buffer);
        break;
      case 8:
        //actual.FinalClassificationData.get(buffer);
        break;
      case 9:
        //actual.LobbyInfoData.get(buffer);
        break;
      case 10:
        actual.CarDamageData.get(buffer);
        break;
      case 11:
        //actual.SessionHistoryData.get(buffer);
        break;
    }
  }
}

void bg(void){
  tft.fillScreen(0x0000);
  tft.setRotation(1);
  for(int x = 0; x <= 15; x++)
    tft.fillCircle((x*32)+16, 16, 15, 0x528A);
  tft.drawFastHLine(0,33,480, 0xFFFF);
  tft.drawFastHLine(0,290,480, 0xFFFF);
  
  tft.drawFastVLine(160,33,257, 0xFFFF);
  tft.drawFastVLine(320,33,257, 0xFFFF);
  tft.drawFastHLine(0,85,160,0xFFFF);
  tft.drawFastHLine(320,85,160,0xFFFF);
  
  tft.drawFastHLine(0,130,160,0xFFFF);
  tft.drawFastHLine(320,130,160,0xFFFF);
  
  tft.drawFastHLine(0,180,160,0xFFFF);
  tft.drawFastHLine(320,180,160,0xFFFF);

  tft.drawFastHLine(160,240,160, 0xFFFF);
  
  tft.drawFastVLine(320,33,257, 0xFFFF);
  tft.drawFastHLine(160,190,160, 0xFFFF);//
  tft.drawFastVLine(240,290,30, 0xFFFF);

  tft.drawFastVLine(80,180,110, 0xFFFF);  
  tft.drawFastVLine(400,180,110, 0xFFFF);

  //Elementos Fijos
  //Speed
  tft.setTextSize(2);
  tft.setCursor(10, 45);
  tft.print("Km/h");
  //ers
  tft.setCursor(42,298);
  tft.print("%");
  //ers lap
  tft.setCursor(282,298);
  tft.print("%");
  //position
  tft.setTextSize(4);
  tft.setCursor(40, 95);
  tft.print("P");
  //lap
  tft.setCursor(330, 95);
  tft.print("L");
  tft.setTextColor(textColor);
  tft.setCursor(357, 95);
  tft.print("  /");

  tft.setTextSize(3);
  tft.setCursor(85, 254);    
  tft.print("   %");
  tft.setCursor(325, 254);
  tft.print("   %");
  tft.setCursor(5, 254);    
  tft.print("   %");
  tft.setCursor(405, 254);    
  tft.print("   %");
  //tft.setCursor(405, 95);
  //tft.print("/");
  //Wheels
  tft.drawRoundRect(8,219,59,28,5,0xffff);
  tft.drawRoundRect(7,218,61,30,6,0xffff);
  
  tft.drawRoundRect(88,219,59,28,5,0xffff);
  tft.drawRoundRect(87,218,61,30,6,0xffff);
  
  tft.drawRoundRect(328,219,59,28,5,0xffff);
  tft.drawRoundRect(327,218,61,30,6,0xffff);
  
  tft.drawRoundRect(408,219,59,28,5,0xffff);
  tft.drawRoundRect(407,218,61,30,6,0xffff);
}
void first(void){
  tft.setTextSize(4);
  tft.setTextColor(drsDisabledColor);
  tft.setCursor(40, 140);
  tft.print("DRS");
  tft.setCursor(380, 140);
  tft.print("OT");
  printOP("1", "0", 5, 357, 95, bgColor, textColor);
  printOP("1", "0", 2, 70, 95, bgColor, textColor);
  printOP("1", "0", 2, 357, 95, bgColor, textColor);
  printOP("1", "0", 3, 80, 45, bgColor, textColor);
  printOP("1", "0", 5, 348, 45, bgColor, textColor);
  printOP("1","+0.00", 5, 170, 250, bgColor, fuelColor);
  
  tft.setTextSize(3);
  tft.setTextColor(textColor);
  tft.setCursor(85, 254);
  tft.print("  0%");
  tft.setCursor(325, 254);
  tft.print("  0%");
  tft.setCursor(5, 254);
  tft.print("  0%");
  tft.setCursor(405, 254);
  tft.print("  0%");
  printOP("1", "0", 3, 92, 190, bgColor, textColor);
  printOP("1", "0", 3, 92, 222, bgColor, textColor);
  printOP("1", "0", 3, 332, 190, bgColor, textColor);
  printOP("1", "0", 3, 332, 222, bgColor, textColor);
  printOP("1", "0", 3, 12, 190, bgColor, textColor);
  printOP("1", "0", 3, 12, 222, bgColor, textColor);
  printOP("1", "0", 3, 412, 190, bgColor, textColor);
  printOP("1", "0", 3, 412, 222, bgColor, textColor);
  printOP("1", "0", 3, 85, 254, bgColor, textColor);
  printOP("1", "0", 3, 325, 254, bgColor, textColor);
  printOP("1", "0", 3, 5, 254, bgColor, textColor);
  printOP("1", "0", 3, 405, 254, bgColor, textColor);

  tft.setTextSize(17);
  tft.setCursor(198, 50);
  tft.setTextColor(textColor);
  tft.print("N");

  tft.setTextSize(2);
  tft.setTextColor(textColor);
  tft.setCursor(5,298);
  tft.print("  0");
  tft.setCursor(245,298);
  tft.print("  0");
  tft.fillRect(map(0, 0, 100, 0, 180)+55, 299, map(100, 0, 100, 0, 180), 12, ersColor);
  tft.fillRect(map(0, 0, 100, 0, 180)+295, 299, map(100, 0, 100, 0, 180), 12, ersLapColor);

}

void drawSession(void){
  tft.setTextSize(4);
  if (actual.SessionData.m_totalLaps != prev.SessionData.m_totalLaps){
    printOP(String(prev.SessionData.m_totalLaps), String(actual.SessionData.m_totalLaps), 5, 357, 95, bgColor, textColor);
    prev.SessionData.m_totalLaps = actual.SessionData.m_totalLaps;
  }
}
void drawLapData(void){
  //Position
  tft.setTextSize(4);
  if (actual.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition != prev.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition){
    printOP(String(prev.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition), String(actual.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition), 2, 70, 95, bgColor, textColor);
    prev.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition = actual.LapData.m_lapData[Header.m_playerCarIndex].m_carPosition;
  }
  //Lap
  if (actual.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum != prev.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum){
    printOP(String(prev.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum), String(actual.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum), 2, 357, 95, bgColor, textColor);
    prev.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum = actual.LapData.m_lapData[Header.m_playerCarIndex].m_currentLapNum;
  }

}
void drawCarTelemetry(void){
  //Gear
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear){
    tft.setTextSize(17);
    tft.setCursor(198, 50);
    tft.setTextColor(bgColor);
    if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear < 0) tft.print("R");
    else if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear == 0) tft.print("N");
    else tft.print(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear);
    tft.setCursor(198, 50);
    tft.setTextColor(textColor);
    if(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear < 0) tft.print("R");
    else if(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear == 0) tft.print("N");
    else tft.print(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear);

    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear;
  }
  //suggested Gear
  if (prev.CarTelemetryData.m_suggestedGear != actual.CarTelemetryData.m_suggestedGear ){
    if(actual.CarTelemetryData.m_suggestedGear == 0){
      tft.setTextSize(5);
      tft.fillRect(245,205,21,16, bgColor);
      
      tft.setTextColor(bgColor);
      tft.setCursor(210, 198);
      tft.print(prev.CarTelemetryData.m_suggestedGear);
    }
    else{
      tft.setTextColor(sGearColor, bgColor);
      tft.setTextSize(5);
  
      tft.setCursor(210, 198);
      tft.print(actual.CarTelemetryData.m_suggestedGear);
      if(actual.CarTelemetryData.m_suggestedGear > actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_gear)
        tft.fillTriangle(245,220,265,220,255,205, sGearColor);
      else
        tft.fillTriangle(245,205,265,205,255,220, sGearColor);
    }
    prev.CarTelemetryData.m_suggestedGear = actual.CarTelemetryData.m_suggestedGear;
  }
  //Throttle
  if ((int)(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle*100) != (int)(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle*100)){
    int p_prev = 100-(int)(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle*100);
    int p_actu = 100-(int)(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle*100);
    if (p_prev < p_actu){
      //tft.fillRect(161, 189, 10, -156, fuelColor);
      tft.fillRect(161, map(p_prev, 0, 100, 0, 156)+34, 15, map(p_actu-p_prev, 0, 100, 0, 156), bgColor);
    }
    else if(p_prev > p_actu){
      tft.fillRect(161, map(p_actu, 0, 100, 0, 156)+34, 15, map(p_prev-p_actu, 0, 100, 0, 156), fuelColor);
    }
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_throttle;
  }
  //Brake
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake){
    int p_prev = 100-(int)(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake*100);
    int p_actu = 100-(int)(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake*100);
    if (p_prev < p_actu){
      //tft.fillRect(161, 189, 10, -156, fuelColor);
      tft.fillRect(320, map(p_prev, 0, 100, 0, 156)+34, -15, map(p_actu-p_prev, 0, 100, 0, 156), bgColor);
    }
    else if(p_prev > p_actu){
      tft.fillRect(320, map(p_actu, 0, 100, 0, 156)+34, -15, map(p_prev-p_actu, 0, 100, 0, 156), fuelColor2);
    }
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_brake;
  }
  //Speed
  tft.setTextSize(4);
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed), 3, 80, 45, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_speed;
  }
  //RPM
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM), 5, 348, 45, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_engineRPM;
  }
  //DRS
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs){
    if(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs)
      tft.setTextColor(drsActiveColor);
    else if(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed)
      tft.setTextColor(drsAvailableColor);
    else
      tft.setTextColor(drsDisabledColor);
    tft.setCursor(40, 140);
    tft.print("DRS");

    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs;
  }
  //lights
  if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent > actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent){
    for(int x = map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15); x <= map(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15); x++)
      if(x < 5 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights1Color);
      else if (x < 10 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights2Color);
      else if (x < 15 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights3Color);
      else
        tft.fillCircle((x*32)+16, 16, 15, lightsOffColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent;
  }
  else if (prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent < actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent){
    for(int x = map(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15); x <= map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15); x++)
      if(x < 5 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights1Color);
      else if (x < 10 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights2Color);
      else if (x < 15 && x < map(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent, 0, 100, 0, 15))
        tft.fillCircle((x*32)+16, 16, 15, lights3Color);
      else
        tft.fillCircle((x*32)+16, 16, 15, lightsOffColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_revLightsPercent;
  }
  //Wheels
  tft.setTextSize(3);
  //BL
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0]), 3, 92, 190, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[0];
  }
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0]), 3, 92, 222, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[0];
  }
  
  //BR
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1]), 3, 332, 190, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[1];
  }
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1]), 3, 332, 222, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[1];
  }
  
  //FL
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2]), 3, 12, 190, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[2];
  }
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2]){
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2]), 3, 12, 222, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[2];
  }
  
  //FR
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3]){
    tft.setCursor(412, 190);
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3]), 3, 412, 190, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresSurfaceTemperature[3];
  }
  if(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3] != actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3]){
    tft.setCursor(412, 222);
    printOP(String(prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3]), String(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3]), 3, 412, 222, bgColor, textColor);
    prev.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3] = actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_tyresInnerTemperature[3];
  }

}
void drawCarStatus(void){
  //DRS 
  tft.setTextSize(4);
  if (prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed != actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed){
    if(actual.CarTelemetryData.m_carTelemetryData[Header.m_playerCarIndex].m_drs)
      tft.setTextColor(drsActiveColor);
    else if(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed)
      tft.setTextColor(drsAvailableColor);
    else
      tft.setTextColor(drsDisabledColor);
    tft.setCursor(40, 140);
    tft.print("DRS");

    prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed = actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_drsAllowed;
  }
  //OT
  if (prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployMode != actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployMode ){
    
    tft.setCursor(380, 140);
    if (actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployMode == 3)
      tft.setTextColor(drsActiveColor);
    else
      tft.setTextColor(drsDisabledColor);
    tft.print("OT");

    prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployMode = actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployMode;
  }
  //ers
  tft.setTextSize(2);
  if ( (int)(( 100 / 4000000.0) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy) != (int)(( 100 / 4000000.0) *actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy)){
    printOP(String((int)(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy * ( 100 / 4000000.0))), String((int)(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy * ( 100 / 4000000.0))), 3, 5, 298, bgColor, textColor);

    if(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy > prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy){
      tft.fillRect(map((int)(( 100 / 4000000.0) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy), 0, 100, 0, 180)+55, 299, map((int)(( 100 / 4000000.0) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy) - (int)(( 100 / 4000000.0) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy), 0, 100, 0, 180), 12, ersColor);
    }
    else if (actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy < prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy){
      tft.fillRect(map((int)(( 100 / 4000000.0) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy), 0, 100, 0, 180)+55, 299, map((int)(( 100 / 4000000.0) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy) - (int)(( 100 / 4000000.0) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy), 0, 100, 0, 180), 12, emptyColor);
    }

    prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy = actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersStoreEnergy;
  }

  //ers lap
  if ((int)(100 - ( 100 / 4000964.25 ) *prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap) != (int)(100 - ( 100 / 4000964.25 ) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap)){
    printOP(String( (int)( 100 - ( 100 / 4000964.25 ) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap)), String( (int)( 100 - ( 100 / 4000964.25 ) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap)), 3, 245, 298, bgColor, textColor);
    if(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap > actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap){
      tft.fillRect(map((int)( 100.0 - ( 100.0 / 4000964.25 ) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap), 0, 100, 0, 180)+295, 299, map((int)(100.0 - ( 100.0 / 4000964.25 ) * (actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap) -(int)(100.0 - ( 100.0 / 4000964.25 ) * prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap)), 0, 100, 0, 180), 12, ersLapColor);
    }
    else if (prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap < actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap){
      tft.fillRect(map((int)( 100.0 - ( 100.0 / 4000964.25 ) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap), 0, 100, 0, 180)+295, 299, map((int)(100.0 - ( 100.0 / 4000964.25 ) * (prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap) -(int)(100.0 - ( 100.0 / 4000964.25 ) * actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap)), 0, 100, 0, 180), 12, emptyColor);
    }

    prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap = actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_ersDeployedThisLap;
  }

  tft.setTextSize(4);
  //Fuel
  if (prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps != actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps){
    if(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps>=0){
      if(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps>=0){
        printOP("+"+String(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps),"+"+String(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps), 5, 170, 250, bgColor, fuelColor);
      }else{
        printOP("+"+String(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps),String(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps), 5, 170, 250, bgColor, fuelColor2);
      }
    }
    else{
      if(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps>=0){
        printOP(String(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps),"+"+String(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps), 5, 170, 250, bgColor, fuelColor);
      }else{
        printOP(String(prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps),String(actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps), 5, 170, 250, bgColor, fuelColor2);
      }      
    }
    prev.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps = actual.CarStatusData.m_carStatusData[Header.m_playerCarIndex].m_fuelRemainingLaps;
  }
}
void drawCarDamage(void){
  //Wheels
  tft.setTextSize(3);
  //BL
  if(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0] != actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0]){
    printOP(String(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0]), String(actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0]), 3, 85, 254, bgColor, textColor);
    prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0] = actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[0];
  }
  
  //BR
  if(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1] != actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1]){
    printOP(String(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1]), String(actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1]), 3, 325, 254, bgColor, textColor);
    prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1] = actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[1];
  }
  
  //FL
  if(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2] != actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2]){
    printOP(String(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2]), String(actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2]), 3, 5, 254, bgColor, textColor);
    prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2] = actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[2];
  }
  
  //FR
  if(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3] != actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3]){
    printOP(String(prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3]), String(actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3]), 3, 405, 254, bgColor, textColor);
    prev.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3] = actual.CarDamageData.m_carDamageData[Header.m_playerCarIndex].m_tyresDamage[3];
  }
}


void setup() {
  //Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    //Serial.println("Connecting to Wifi...");
  }
  //Serial.println("Connected to the Wifi network");
  udp.begin(port);

  tft.reset();
  uint16_t identifier = tft.readID();
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);
  bg();
  first();
  
}

void loop() {
  
  data();
  if(micros()-tiempo >= 33333){
    tiempo = micros();
    drawSession();
    drawLapData();
    drawCarTelemetry();
    drawCarStatus();
    drawCarDamage();
  }
  
}
