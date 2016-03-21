/**************************************
 * 12 - FUNCAO DE RESET DOS ATUADORES *
 **************************************/

void resetSystem()
{
  Serial.println ("### 12. Inicia resetSystem###");  // Comentario enviado para Monitor Serial 
  lcd.clear();                                       // Limpa o LCD
  lcd.setCursor(0,0);                                // Posiciona o cursor 
  lcd.print("ResetSystem *ON*");                     // Escreve no LCD 
  lcd.setCursor(0,1);                                // Posiciona o cursor 
  lcd.print("desligando reles");                     // Escreve no LCD 
  digitalWrite(PumpPin, LOW);                        // Desliga a bomba
  digitalWrite(sect1SolenoidPin, LOW);               // Desliga a valvula solenoide do Setor 1 (Grama Back_quintal)
  digitalWrite(sect2SolenoidPin, LOW);               // Desliga a valvula solenoide do Setor 2 (Grama Sol1_garagens)
  digitalWrite(sect3SolenoidPin, LOW);               // Desliga a valvula solenoide do Setor 3 (Grama Sol2_coqueiro)
  digitalWrite(sect4SolenoidPin, LOW);               // Desliga a valvula solenoide do Setor 4 (Floreiras)
  digitalWrite(tankFillSolenoid, LOW);               // Desliga a valvula solenoide de enchimento do tanque com agua da rua
  delay(2000);                                       // Exibe a mensagem por 2 segundos antes de prosseguir o programa
  lcd.clear();                                       // Limpa o LCD

}
/*** FIM DA FUNCAO DE RESET DOS ATUADORES ***/
