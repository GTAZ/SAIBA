/*************************************************** 
 * 15 - FUNCAO DE VERIFICACAO DO ESTADO DOS BOTOES * 
 ***************************************************/

int buttonChk()
{
  Serial.println ("### 15. Inicia buttonChk### ");    // Comentario enviado para Monitor Serial 
  int buttonChk = constrain(buttonChk, 0, 5);         // Limita o valor da variavel buttonChk entre 0 e 5
  int pressButton = analogRead(0);                    // Le a entrada analogica A0 e atribui seu valor para a variavel pressButton
  if (pressButton <= 100)
  {
    delay(750);                                       // Aguarda 750 milisegundos (0,75 segundos) para estabilizacao da leitura
    return 0;  // 0 = Direita
  }
  else if (pressButton > 101 && pressButton <= 200)
  {
    delay(350);                                       // Aguarda 350 milisegundos (0,35 segundos) para estabilizacao da leitura
    return 1;  // 1 = Cima
  }
  else if (pressButton > 201 && pressButton <= 400)
  {
    delay(350);                                       // Aguarda 350 milisegundos (0,35 segundos) para estabilizacao da leitura
    return 2;  // 2 = Baixo
  }
  else if (pressButton > 401 && pressButton <= 600)
  {
    delay(750);                                       // Aguarda 750 milisegundos (0,75 segundos) para estabilizacao da leitura
    return 3;  // 3 = Esquerda
  }
  else if (pressButton > 601 && pressButton <= 800)
  {
    delay(750);                                       // Aguarda 750 milisegundos (0,75 segundos) para estabilizacao da leitura
    return 4;  // 4 = Select
  }
  else //if (pressButton < 801)
  return 5;  // 5 = Botao nao pressionado
  Serial.print ("pressButton: ");                     // Comentario enviado para Monitor Serial 
  Serial.println (pressButton);                       // Comentario enviado para Monitor Serial 
}
/*** FIM da funcao de verificacao do estado dos botoes ***/


