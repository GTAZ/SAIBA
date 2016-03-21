/**********************************************
 * 08 - FUNCAO DE VERIFICACAO DE PRECIPITACAO *
 **********************************************/

int checkRain(void)
{
  Serial.println ("### 08. Inicia checkRain ###");     // Comentario enviado para Monitor Serial 
  float ambDHT11Temp = DHT11.temperature;              // Atribui a leiura de Temperatura ambiente do sensor DHT11 para a variavel ambTemp
  float ambDHT11Hmdt = DHT11.humidity;                 // Atribui a leiura de Umidade ambiente do sensor DHT11 para a variavel ambHmdt
  float ambDHT11DewPt = DHT11.dewPoint();              // Atribui a leiura de Dew Point ambiente do sensor DHT11 para a variavel ambDewPt
  int sensRain = digitalRead(sensRainPin);             // Le o estado do pino do sensor de chuva e atribui seu valor para a variavel digital deste sensor
  Serial.print("sensRain: ");                          // Comentario enviado para Monitor Serial 
  Serial.println(sensRain);                            // Comentario enviado para Monitor Serial 
  float sensRainSize = analogRead(sensRainSizePin);    // Le o valor do pino do sensor de quantidade de chuva e atribui seu valor para a variavel analogica deste sensor
  Serial.print("sensRainSize: ");                      // Comentario enviado para Monitor Serial 
  Serial.println(sensRainSize);                        // Comentario enviado para Monitor Serial 


  /*if ((bmpBaro <= baroRainLimit) && (sensRain != 1) && (ambDHT11DewPt >= ambDewPtKimit))
  {
    Serial.println ("return 1");
    return 1;                   
  }  */
  return 0;    // Teste para verificacao de precipitacao desabilitado ate que os sensores sejam fisicamente ligados ao sistema
  
  Serial.println(checkRain());                         // Comentario enviado para Monitor Serial
}
/*** FIM DA FUNCAO DE VERIFICACAO DE PRECIPITACAO ***/

