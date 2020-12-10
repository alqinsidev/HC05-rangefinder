#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
#define buzz 8
#define btn 12
#define busyPin 13

#define scanTimeout 5000
#define maxScan 5

#define distanceTreshold 2

String rawInq = "";
bool parsing = false;
int count = 0;
String data[maxScan];
String rssi[maxScan];
int q = 0;
bool plus = false;
bool analyze = false;
int deviceScanned = 0;
bool busy = false;

void setup() {
  pinMode(buzz,OUTPUT);
  pinMode(btn,INPUT_PULLUP);
  pinMode(busyPin,OUTPUT);

  busy = true;
  digitalWrite(busyPin,HIGH);
  Serial.begin(9600);
  BTserial.begin(38400);
  delay(1000);
//  masterMode();
  buzzer(200,1);
  busy = false;
  digitalWrite(busyPin,LOW);

}

void loop() {
  int action = digitalRead(btn);
  if(!action && !busy)
  {
      busy = true;
      digitalWrite(busyPin,HIGH);
      Serial.println("Scanning ...");
      BTserial.println("AT+INQ");
      parsing = true;
  }

  if(parsing){
    parsingBT();
  }

  if(analyze)
  {
    computeData();
  }
}

void parsingBT(){
  long int time = millis();
  int i = 0;
  while ( (time+scanTimeout ) > millis()){
    if(BTserial.available()){
      char inChar = BTserial.read();
      if(inChar == '+')
      {
        plus = true;
      }
      if(plus)
      {
       rawInq += inChar; 
      }
      if(inChar == '\n' && plus)
      {
        plus = false;
        data[q] = rawInq.substring(0,rawInq.length()-1);
        data[q] += ';';
        rawInq = "";
        q++;
        deviceScanned++;
      }
    }
  }
  Serial.println("Device found :" + String(deviceScanned));
  q=0;
  deviceScanned = 0;
  parsing = false;
  BTserial.println("AT+INQC");
//  delay(3000);
  Serial.println("Scan stopped");
  Serial.println();
  analyze = true;
}

void computeData(){
  int j = 0;
  int jumlah = 0;
  int aware = 0;
  for(j=0;j<maxScan;j++)
  {
    if(data[j] != "")
    {
     int x = 0;
     Serial.println("Data["+String(j)+"] :" + data[j]);
     int len = data[j].length();
     String info = "";
     int c = 0;
     for(x=0;x<len;x++)
     {
      if(data[j][x] != ',')
      {
        info += data[j][x];
      }
      else {
        c++;
        if(c == 3)
        {
          Serial.println("RSSI HEX: " + info);
          int rssiC = ~(-((int)hexToDec(info)));
          rssiC = rssiC * -1;
          rssi[j] = rssiC;
          float up = (-69) - rssiC;
          float down = 20;
          float pangkat = up/down;
          Serial.println("Pangkat :"+String(pangkat));
          float jarak = pow(10,pangkat);
          if(jarak <= distanceTreshold)
          {
            aware++;
          }
          Serial.println("RSSI: " + String(rssiC));
          Serial.println("Apx Distance: " + String(jarak) + "m");
          jumlah++;
        }
        info ="";
      }
     }
    }
  }
  analyze = false;

  for(j=0;j<maxScan;j++)
  {
    data[j]="";
  }
  busy = false;
  digitalWrite(busyPin,LOW);
  Serial.println("===================");
  if(aware>0)
  {
    Serial.println("Need to keep distance : " + String(aware) + " Device");
  }
  else{
    Serial.println("No device under " +String(distanceTreshold) +"m");
    badumts();
  }
  Serial.println();
  Serial.println("===================");
  Serial.println();
  buzzer(100,aware);
}

void buzzer(int jeda,int looping){
  int x = 0;
  for(x=0;x<looping;x++){
    tone(buzz,100);
    delay(jeda);
    noTone(buzz);
    delay(50);
  }
}
