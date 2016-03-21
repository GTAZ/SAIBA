/***************************************************************
 * 06 - FUNCAO DE PARADA DE EMERGENCIA DA BOMBA, INTERRUPCAO 0 *
 ***************************************************************
 * 
 * void EmergencyStop()
 * {
 * Serial.println("### 06. Funcao de parada de emergencia por botao acionado ###");
 * digitalWrite(PumpPin, LOW);    // Desliga a Bomba se o botao de emergencia estiver pressionado (true ou 1)
 * lcd.setCursor(0,0);
 * lcd.print("EmergencyStop   ");
 * lcd.setCursor(0,1);
 * lcd.print("    Pressionado!");
 * 
 * }
 *** FIM DA FUNCAO DE PARADA DE EMERGENCIA ***/



/*************************************************************************
 * 07 - FUNCAO DE PARADA DA BOMBA POR BAIXO NIVEL DE AGUA, INTERRUPCAO 1 *
 *************************************************************************
 * 
 * void tankLowLevel()
 * {
 * Serial.println("### 07. Funcao  de parada de energencia por baixo nivel de agua no tanque ###");
 * digitalWrite(PumpPin, LOW);               // Desliga a Bomba se o volume de agua no tanque estiver baixo (true = 1)
 * digitalWrite(tankFillSolenoidPin, HIGH);  // Liga a solenoide de enchimento do tanque com agua da rua
 * lcd.setCursor(0,0);                       // Posiciona o cursor
 * lcd.print("Cisterna Baixa");              // Escreve no LCD
 * lcd.setCursor(0,1);                       // Posiciona o cursor
 * lcd.print("...Enchendo...oO");            // Escreve no LCD
 * delay (180000);                           // Aguarda 180000ms (3min)
 * digitalWrite(tankFillSolenoidPin, LOW);   // Desliga a valvula solenoide de enchimento da tsnque com agua da rua
 * 
 * }
 *** FIM DA FUNCAO DE PARADA POR BAIXO NAVEL DE AGUA ***/
