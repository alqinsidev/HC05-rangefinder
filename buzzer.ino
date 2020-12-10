// fungsi nada
void DO(){
  tone(buzz, 262);
}
void RE(){
  tone(buzz, 294);
}
void MI(){
  tone(buzz, 330);
}
void FA(){
  tone(buzz, 349);
}
void SOL(){
  tone(buzz, 395);
}
void LA(){
  tone(buzz, 440);
}
void SI(){
  tone(buzz, 494);
}
void DOO(){
  tone(buzz, 523);
}
void DIAM(){
  noTone(buzz);
}

void badumts(){
  DOO();
  delay(400);
  DIAM();
  delay(10);
  SOL();
  delay(200);
  DIAM();
  delay(10);
  SOL();
  delay(200);
  DIAM();
  delay(10);
  LA();
  delay(300);
  DIAM();
  delay(50);
  SOL();
  delay(700);
  SI();
  delay(300);
  DOO();
  delay(700);
  DIAM();
}
