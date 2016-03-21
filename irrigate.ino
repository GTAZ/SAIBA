/*******************************************
 * 11 - FUNCAO DE ACIONAMENTO DA IRRIGACAO *
 *******************************************/

void irrigate()
{ 
  Serial.println ("### 11. Inicia irrigate###");  // Comentario enviado para Monitor Serial 
  digitalWrite(PumpPin, LOW);                     // Garante que a bomba esteja desligada no inicio da funcao de irrigacao

  // Setor 1 ------------------------------------------------------------------------------
  digitalWrite(sect1SolenoidPin, HIGH);   // Liga a valvula solenoide do Setor 1
  digitalWrite(PumpPin, HIGH);            // Liga a bomba
  for (x = ((irrigateTimerSect1) / 1000); x != 0; x = x - 1)   // Enquanto x for maior ou igual a 0 a subrotina sera executada
  {
    Serial.println ("Irrigando Setor1");  // Comentario enviado para Monitor Serial 
    Serial.println(irrigateTimerSect1);
    Serial.println(x);
    lcd.clear();                     // Limpa o LCD
    lcd.setCursor(0,0);              // Posiciona o cursor 
    lcd.print("Irrigando Setor1");   // Escreve no LCD 
    lcd.setCursor(0,1);              // Posiciona o cursor 
    lcd.print("Tempo = ");           // Escreve no LCD 
    lcd.setCursor(8,1);              // Posiciona o cursor 
    lcd.print(x);                    // Divide o valor de x por 1000 (tranforma de milisegundos para segundos) e escreve no LCD 
    lcd.setCursor(12,1);             // Posiciona o cursor 
    lcd.print("seg.");               // Escreve no LCD
    delay(1000);
    buttonState = buttonChk();       // Leitura do valor da porta digital A0
    Serial.println (buttonState);    // Enviado A Monitor Serial o valor da botao pressionado 
    if (buttonState == 0)            // Se o botao da Direita (<100) for pressionado, interrompe o a irrigacao do setor e inicia a irrigacao do proximo setor
      break;
  } 
  digitalWrite(sect1SolenoidPin, LOW);    // Desliga a valvula solenoide do Setor 1
  //digitalWrite(PumpPin, LOW);             // Desliga a bomba

  Serial.println ("FIM irrigacao Setor 1");  // Comentario enviado para Monitor Serial 
  lcd.clear();                       // Limpa o LCD
  lcd.setCursor(0,0);                // Posiciona o cursor 
  lcd.print("**FIM Irrigacao**");    // Escreve no LCD
  lcd.setCursor(0,1);                // Posiciona o cursor 
  lcd.print("**** Setor 1 ****");    // Escreve no LCD
  delay(2000);                       // Aguarda 2 segundos
  lcd.clear();                       // Limpa o LCD


  // Setor 2 ------------------------------------------------------------------------------
  digitalWrite(sect2SolenoidPin, HIGH);   // Liga a valvula solenoide do Setor 2
  digitalWrite(PumpPin, HIGH);            // Liga a bomba
  for (x = ((irrigateTimerSect2) / 1000); x != 0; x = x - 1)   // Enquanto x for maior ou igual a 0 a subrotina sera executada
  {
    Serial.println ("Irrigando Setor 2");  // Comentario enviado para Monitor Serial 
    Serial.println(irrigateTimerSect2);
    Serial.println(x);    
    lcd.clear();                      // Limpa o LCD
    lcd.setCursor(0,0);               // Posiciona o cursor 
    lcd.print("Irrigando Setor2");    // Escreve no LCD 
    lcd.setCursor(0,1);               // Posiciona o cursor 
    lcd.print("Tempo = ");            // Escreve no LCD 
    lcd.setCursor(8,1);               // Posiciona o cursor 
    lcd.print(x);                     // Divide o valor de x por 1000 (tranforma de milisegundos para segundos) e escreve no LCD 
    lcd.setCursor(12,1);              // Posiciona o cursor 
    lcd.print("seg.");                // Escreve no LCD 
    delay(1000);
    buttonState = buttonChk();      // Leitura do valor da porta digital A0
    Serial.println (buttonState);   // Enviado A Monitor Serial o valor da botao pressionado 
    if (buttonState == 0)           // Se o botao da Direita (<100) for pressionado, interrompe o a irrigacao do setor e inicia a irrigacao do proximo setor
      break;
  } 
  digitalWrite(sect2SolenoidPin, LOW);    // Desliga a valvula solenoide do Setor 2
  //digitalWrite(PumpPin, LOW);             // Desliga a bomba

  Serial.println ("FIM irrigacao Setor 2");
  lcd.clear();                       // Limpa o LCD
  lcd.setCursor(0,0);                // Posiciona o cursor 
  lcd.print("**FIM Irrigacao**");    // Escreve no LCD
  lcd.setCursor(0,1);                // Posiciona o cursor 
  lcd.print("**** Setor 2 ****");    // Escreve no LCD
  delay(2000);                       // Aguarda 2 segundos
  lcd.clear();                       // Limpa o LCD


  // Setor 3 ------------------------------------------------------------------------------
  digitalWrite(sect3SolenoidPin, HIGH);   // Liga a valvula solenoide do Setor 3
  digitalWrite(PumpPin, HIGH);            // Liga a bomba
  for (x = ((irrigateTimerSect3) / 1000); x != 0; x = x - 1)   // Enquanto x for maior ou igual a 0 a subrotina sera executada
  {
    Serial.println ("Irrigando Setor 3");  // Comentario enviado para Monitor Serial 
    Serial.println(irrigateTimerSect3);
    Serial.println(x);
    lcd.clear();                      // Limpa o LCD
    lcd.setCursor(0,0);               // Posiciona o cursor 
    lcd.print("Irrigando Setor3");    // Escreve no LCD 
    lcd.setCursor(0,1);               // Posiciona o cursor 
    lcd.print("Tempo = ");            // Escreve no LCD 
    lcd.setCursor(8,1);               // Posiciona o cursor 
    lcd.print(x);                     // Divide o valor de x por 1000 (tranforma de milisegundos para segundos) e escreve no LCD 
    lcd.setCursor(12,1);              // Posiciona o cursor 
    lcd.print("seg.");                // Escreve no LCD 
    delay(1000);
    buttonState = buttonChk();      // Leitura do valor da porta digital A0
    Serial.println (buttonState);   // Enviado A Monitor Serial o valor da botao pressionado 
    if (buttonState == 0)           // Se o botao da Direita (<100) for pressionado, interrompe o a irrigacao do setor e inicia a irrigacao do proximo setor
      break;
  } 
  digitalWrite(sect3SolenoidPin, LOW);    // Desliga a valvula solenoide do Setor 3
  //digitalWrite(PumpPin, LOW);             // Desliga a bomba

  Serial.println ("FIM irrigacao Setor 3");  // Comentario enviado para Monitor Serial 
  lcd.clear();                       // Limpa o LCD
  lcd.setCursor(0,0);                // Posiciona o cursor 
  lcd.print("**FIM Irrigacao**");    // Escreve no LCD
  lcd.setCursor(0,1);                // Posiciona o cursor 
  lcd.print("**** Setor 3 ****");    // Escreve no LCD
  delay(2000);                       // Aguarda 2 segundos
  lcd.clear();                       // Limpa o LCD


  // Setor 4 ------------------------------------------------------------------------------
  digitalWrite(sect4SolenoidPin, HIGH);   // Liga a valvula solenoide do Setor 1
  digitalWrite(PumpPin, HIGH);            // Liga a bomba
  for (x = ((irrigateTimerSect4) / 1000); x != 0; x = x - 1)   // Enquanto x for maior ou igual a 0 a subrotina sera executada
  {
    Serial.println ("Irrigando Setor 4");    // Comentario enviado para Monitor Serial 
    Serial.println(irrigateTimerSect1);
    Serial.println(x);
    lcd.clear();                      // Limpa o LCD
    lcd.setCursor(0,0);               // Posiciona o cursor 
    lcd.print("Irrigando Setor4");    // Escreve no LCD 
    lcd.setCursor(0,1);               // Posiciona o cursor 
    lcd.print("Tempo = ");            // Escreve no LCD 
    lcd.setCursor(8,1);               // Posiciona o cursor 
    lcd.print(x);                     // Divide o valor de x por 1000 (tranforma de milisegundos para segundos) e escreve no LCD 
    lcd.setCursor(12,1);              // Posiciona o cursor 
    lcd.print("seg.");                // Escreve no LCD 
    delay(1000);
    buttonState = buttonChk();      // Leitura do valor da porta digital A0
    Serial.println (buttonState);   // Enviado A Monitor Serial o valor da botao pressionado 
    if (buttonState == 0)           // Se o botao da Direita (<100) for pressionado, interrompe o a irrigacao do setor e inicia a irrigacao do proximo setor
      break;
  } 
  digitalWrite(PumpPin, LOW);             // Desliga a bomba
  digitalWrite(sect4SolenoidPin, LOW);    // Desliga a valvula solenoide do Setor 4

  Serial.println ("FIM irrigacao Setor 4");  // Comentario enviado para Monitor Serial 
  lcd.clear();                       // Limpa o LCD
  lcd.setCursor(0,0);                // Posiciona o cursor 
  lcd.print("**FIM Irrigacao**");    // Escreve no LCD
  lcd.setCursor(0,1);                // Posiciona o cursor 
  lcd.print("**** Setor 4 ****");    // Escreve no LCD
  delay(2000);                       // Aguarda 2 segundos
  lcd.clear();                       // Limpa o LCD

  // Desacionamento da bomba
  digitalWrite(PumpPin, LOW);    // Garante o desligamento da bomba
  delay(1000);                   // Aguarda 1 segundos

}
/*** FIM DA FUNCAO DE ACIONAMENTO DA IRRIGACAO ***/
