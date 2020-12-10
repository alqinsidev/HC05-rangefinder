String sendCmd (String command , const int timeout, bool debug){
  String response = "";
  Serial.println("->" + command);
  BTserial.println(command);
  long int time = millis();
  int i = 0;
  while ( (time+timeout ) > millis()){
    while (BTserial.available()){
      char c = BTserial.read();
      response +=c;
    }
  }
  if(debug)
  {
    Serial.println(response);
    Serial.println("======");
  }
  
  return response;
}
