  #include <ESP8266WiFi.h>
 
 
  WiFiClient client;
  const char* ssid = "APX-XIAOMI";
  const char* password = "qwertyqwerty123456#";
  const char* host = "wemos.cl";
  const int sleepTimeS = 30;
  const int MaxRetry = 10;
  int sensorValue;
  int i;
  ADC_MODE(ADC_VCC);
  
  void setup(){

    Serial.begin(115200);
    delay(10);
          
    }
  void loop(){
  
  WiFi.begin(ssid,password);
  i=1;
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
    Serial.println("Connected to ");
    Serial.println(ssid);
    if  (i > MaxRetry ){

      Serial.println("Limite de intentos de conexion a red wifi alcanzado ");
      ESP.deepSleep(sleepTimeS * 1000000);
     
    };
    i++;
    };

  Serial.println("Hello, Internet");
  delay(500); 
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
  delay(500);

  const int httpPort = 80;
    i=1;
  while(!client.connect(host, httpPort)){
  
    delay(500);
    Serial.println(".");
    Serial.println("Connected to ");
    Serial.println(host);
    
    if  (i > MaxRetry ){

      Serial.println("Limite de intentos de conexion al servidor alcanzado ");
      ESP.deepSleep(sleepTimeS * 1000000);
      
    };
    i++;
    };
  
// We now create a URI for the request
  sensorValue = analogRead(A0);
  Serial.println("LECTURA DE A/D");
  Serial.println(sensorValue);
  String url = "/iot.php";

  Serial.print("Requesting URL: ");
  Serial.println(url);


  uint32_t getVcc = ESP.getVcc();  
  String messagebody = "Token=OscarSensorA-123456789&Dato="+String(sensorValue)+"&Descripcion=SONDA_A&Bateria_Status="+String(getVcc)+"&Tipo=HUMEDAD";
  Serial.print("requesting URL: ");

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " +
                String(messagebody.length()) + "\r\n\r\n");
    client.print(messagebody);
    
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  
  Serial.println("SE ENVIO POST");
  /*
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");*/

  ESP.deepSleep(sleepTimeS * 1000000);
  
} 
