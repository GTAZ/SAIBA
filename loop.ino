/**************************
 * 05 - CORPO DO PROGRAMA *
 **************************/

void loop()  // Funcao OBRIGATORIA para o Arduino
{
  Serial.println ("### 05. Inicia LOOP obrigatorio ###");  // Comentario enviado para Monitor Serial
  digitalWrite(PumpPin, LOW);                              // Inicia o loop do corpo do programa desligando a bomba

  float ambTemp = DHT11.temperature;     // Atribui a leiura de Temperatura ambiente do sensor DHT11 para a varivel ambTemp
  float ambHmdt = DHT11.humidity;        // Atribui a leiura de Umidade ambiente do sensor DHT11 para a varivel ambHmdt
  float ambDewPt = DHT11.dewPoint();     // Atribui a leiura de Dew Point ambiente do sensor DHT11 para a varivel ambDewPt
  Serial.print ("Temperatura DHT11: ");  // Comentario enviado para Monitor Serial
  Serial.println (ambTemp, 1);           // Comentario enviado para Monitor Serial
  Serial.print ("Umidade DHT11: ");      // Comentario enviado para Monitor Serial
  Serial.println (ambHmdt,1 );           // Comentario enviado para Monitor Serial
  Serial.print ("DewPoint DHT11: ");     // Comentario enviado para Monitor Serial
  Serial.println (ambDewPt, 2);          // Comentario enviado para Monitor Serial
  Serial.println();  

  bmpTemp = bmp085GetTemperature(bmp085ReadUT());                          // Le a temperatura do sensor BMP085 e atribui para a variavel bmpTemp
  bmpBaro = bmp085GetPressure(bmp085ReadUP());                             // Le a presssao do sensor BMP085 e atribui para a variavel bmpBaro
  bmpCalcAlt = (float)44330 * (1 - pow(((float) bmpBaro/p0), 0.190295));   // Calcula a altitude pela presssao atmosferica : altitude = 44330 * [1 - (p / p0)^1/5.255]  ou  p = p0 * [1 - (altitude/44330)]^5.255
  Serial.print ("Temperatura BMP085: ");  
  Serial.print (bmpTemp);                        // Comentario enviado para Monitor Serial
  Serial.println (" Celcius");
  Serial.print ("Presssao BMP085: ");  
  Serial.print (bmpBaro);                        // Comentario enviado para Monitor Serial
  Serial.println (" Pascal (PA)");
  Serial.print ("Altitude Calculada BMP085: ");  
  Serial.print (bmpCalcAlt);                     // Comentario enviado para Monitor Serial
  Serial.println (" metros");
  Serial.println();


  //---------------------------------------------------------------------------------------------------------
  // 05.1 *** Monta a tela principal ***
  //---------------------------------------------------------------------------------------------------------
  Serial.println ("_Monta tela principal");  // Comentario enviado para Monitor Serial

  //Escreve o valor da temperatura ambiente no canto superior esquerdo");  
  lcd.setCursor(0,0);
  lcd.print((float)DHT11.temperature, 0);  // abmTemp = (float)DHT11.temperature
  lcd.setCursor(2,0);
  lcd.print("C");

  //Escreve o valor da umidade ambiente logo apos o valor de temperatura");  
  lcd.setCursor(4,0);
  lcd.println((float)DHT11.humidity, 0);  // abmTemp = (float)DHT11.humidity
  lcd.setCursor(6,0);
  lcd.print("%");

  // Escreve o valor do DewPoint ambiente no canto superior direito");  
  lcd.setCursor(7,0);
  lcd.print(" dew");
  lcd.setCursor(11,0);
  lcd.print((float)DHT11.dewPoint(), 1);  // abmTemp = (float)DHT11.dewPoint
  lcd.setCursor(15,0);
  lcd.print("C");

  // Display time centered on the upper line");  
  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr());              // Horario = rtc.getTimeStr()

  // Display abbreviated Day-of-Week in the lower left corner");  
  lcd.setCursor(8, 1);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));   // Dia da semana no formato abreviado = rtc.getDOWStr(FORMAT_SHORT)

  // Display date in the lower right corner");  
  lcd.setCursor(11, 1);
  lcd.print(rtc.getDateStr(FORMAT_SHORT));  // Data = rtc.getDateStr(FORMAT_SHORT)

  //delay(10);


  //---------------------------------------------------------------------------------------------------------
  // 05.2 *** Automacao da irrigacao ***
  //---------------------------------------------------------------------------------------------------------
  Serial.println ("// *** Automacao da irrigacao ***");  // Comentario enviado para Monitor Serial

  //Verifica se o sensor de chuva esta seco (funcao checkRain FALSA), se o dia da semana esta correto (funcao checkIrrigateDOW VERDADEIRA) e se o horario esta correto (funcao checkIrrigateClock VERDADEIRA)
  if ((checkRain() == 0)  &&  (checkIrrigateDOW() == 1.0) && (checkIrrigateClock() == 1.0))  //Se a condicoes forem todas atendidas inicia a funcao irrigate, caso contrario segue o programa
    irrigate();


  //---------------------------------------------------------------------------------------------------------
  // 05.3 *** Check dos botoes ***
  //---------------------------------------------------------------------------------------------------------
  Serial.println ("// *** Check dos botoes ***");  // Comentario enviado para Monitor Serial

  buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
  Serial.println (buttonState);  // Enviado para o Monitor Serial o valor da botao pressionado

  if (buttonState == 0)  // Se o botao da Direita (<100) for pressionado, inicia Funcao irrigate
  {
    Serial.println ("buttonState = 0 (<100); Direita: inicia ciclo de irrigacao");  // Comentario enviado para Monitor Serial
    irrigate();
  }

  else if (buttonState == 3)  // Se o botao da Esquerda (<600) for pressionado, mostra o valor da umidade do solo em cada setor por 3 segundos
  {
    Serial.println ("buttonState = 3 (450 a 600); Esqueda: mostra o valor da umidade do solo em cada setor");  // Comentario enviado para Monitor Serial
    lcd.clear();                    // Limpa o LCD     
    lcd.setCursor (0,0);            // Posiciona o cursor na coluna 1 (0), linha 1 (0)
    lcd.print ("Umidade do Solo");  // Escreve no LCD
    lcd.setCursor (0,1);            // Posiciona o cursor
    lcd.print ("nao disponivel");   // Escreve no LCD
    delay (3000);                   // Exibe a mensagem por 3 segundos antes de prosseguir o programa
    lcd.clear();                    // Limpa o LCD
  }

  else if (buttonState == 1)  // Se o botao para Cima (<200) for pressionado, mostra o valor da presssao barometrica no display por 3 segundos
  {
    Serial.println ("buttonState = 1 (101 a 200); Cima: mostra o valor da presssao atmosferica");  // Comentario enviado para Monitor Serial
    lcd.clear();                                   // Limpa o LCD     
    lcd.setCursor (0,0);                           // Posiciona o cursor 
    lcd.print ((bmpTemp * 0.1), 1);                // Mostra na primeira linha do Display o valor da temperatura medida pelo sensor de presssao barometrica
    lcd.setCursor (4,0);                           // Posiciona o cursor 
    lcd.print ("C");                               // Escreve no LCD a palavra "Celcius"
    lcd.setCursor (6,0);                           // Posiciona o cursor 
    lcd.print((float)DHT11.humidity, 0);           // Mostra no Display o valor da presssao barometrica medida pelo sensor de presssao barometrica
    lcd.setCursor (8,0);                           // Posiciona o cursor   
    lcd.print ("%");                               // Escreve no LCD a o simbolo "%"    
    lcd.setCursor (10,0);                          // Posiciona o cursor 
    lcd.print (bmpCalcAlt, 1);                     // Escreve no LCD o valor calculado da altitude local
    lcd.setCursor (15,0);                          // Posiciona o cursor 
    lcd.print ("m");                               // Escreve no LCD a palavra "m"
    lcd.setCursor (0,1);                           // Posiciona o cursor 
    lcd.print (bmpBaro * 0.001, 2);                // Mostra no Display o valor da presssao barometrica medida pelo sensor de presssao barometrica
    lcd.setCursor (5,1);                           // Posiciona o cursor 
    lcd.print ("kPa");                             // Escreve no LCD a palavra "kPa"
    lcd.setCursor (9,1);                           // Posiciona o cursor   
    lcd.print (bmpBaro * (9.87 * 0.000001), 2);    // Mostra no Display o valor da presssao barometrica convertida em Atmosfera
    lcd.setCursor (13,1);                          // Posiciona o cursor   
    lcd.print ("atm");                             // Escreve no LCD a o simbolo "%" 
    delay (5000);                                  // Exibe a mensagem por 3 segundos antes de prosseguir o programa
    lcd.clear();                                   // Limpa o LCD  
    weatherDiff = (bmpBaro - ePressure);           // Verifica a condicao ambiental atraves da diferenca da pressao atmosferica atual menos (-) a pressao calculada ePressure
    if (weatherDiff > 250)
    {
      lcd.setCursor (0,0);    
      lcd.print ("Ceu limpo");
      lcd.setCursor (4,1);
      lcd.print ("[Ensolarado]");
    }
    else if ((weatherDiff <= 250) || (weatherDiff >= -250))
    {
      lcd.setCursor (0,0);    
      lcd.print ("Parcialmente"); 
      lcd.setCursor (0,1);  
      lcd.print ("nublado [Nuvens]");
    }
    else if (weatherDiff > -250)
    {
      lcd.setCursor (0,0);
      lcd.print ("Ceu encoberto");
      lcd.setCursor (6,1);
      lcd.print ("[Chuvoso]");
    }
    delay (3000);
    lcd.clear(); 
  }

  else if (buttonState == 2)  // Se o botao para Baixo (<400) for pressionado, mostra o valor da quantidade de precipitacao no sensor de chuva por 3 segundos
  {
    Serial.println ("buttonState = 2 (301 a 400); Baixo: Mostra valor do sensor de chuva");  // Comentario enviado para Monitor Serial
    lcd.clear();                    // Limpa o LCD     
    lcd.setCursor (0,0);            // Posiciona o cursor na coluna 1 (0), linha 1 (0)
    lcd.print ("Sensor de chuva");  // Escreve no LCD
    lcd.setCursor (0,1);            // Posiciona o cursor
    lcd.print ("desativado");       // Escreve no LCD
    delay (3000);                   // Exibe a mensagem por 3 segundos antes de prosseguir o programa
    lcd.clear();                    // Limpa o LCD
  }

  else if (buttonState == 4)  // Se o botao Select (<600) for pressionado, invoca a funcao GUIadjust
  {
    Serial.println ("buttonState = 4 (701 a 800); Select: Inicia funcao GUIadjuste");  // Comentario enviado para Monitor Serial
    GUIadjust();
  }
}   
/*** FIM DO CORPO DO PROGRAMA (funcao obrigatoria LOOP) ***/
