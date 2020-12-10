int t1 = 4000;
int t2 = 3000;
int t3 = 500;
bool debug = true;

void slaveMode(){
  sendCmd("AT+ORGL",t1,debug);
  sendCmd("AT+NAME=\"BT-KIREI\"",t1,debug);
  sendCmd("AT",t1,debug);
}

void masterMode(){
  sendCmd("AT+ORGL",t3,debug);
  sendCmd("AT+CMODE=1",t1,debug);
  sendCmd("AT+ROLE=0",t1,debug);
  sendCmd("AT+INIT",t2,debug);
  sendCmd("AT+IAC=9e8b33",t2,debug);
  sendCmd("AT+CLASS=0x00",t1,debug);
  sendCmd("AT+INQM=1,9,48",t1,debug);
}
