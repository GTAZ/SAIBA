/**************************************************************************************** 
 * 14 - FUNCAO AJUSTE DOS PARAMETROS DO USUARIO ATRAVES DE GUI (Graphic User Interface) * 
 ****************************************************************************************/

void GUIadjust()
{
  Serial.println ("### 14. Inicia GUIadjust###");  // Comentario enviado para Monitor Serial 

  unsigned int yesORno = 0;   // Declara variavel local yesORno = 0
  unsigned int navigate = 1;  // Declara variavel local positiva igual a um (1) 
  int x = 0;
  
  int exit = 0;
  while(exit != 1)
  {
    Serial.println("Aguarda ate que o botao SELECT seja solto para iniciar o GUIadjust");
    lcd.clear();
    lcd.setCursor(0,0);             // Posiciona cursor
    lcd.print("Solte SELECT");      // Escreve no LCD
    lcd.setCursor(0,1);             // Posiciona cursor
    lcd.print("p/ prosseguir");     // Escreve no LCD
    lcd.setCursor(14,1);            // Posiciona cursor
    lcd.print(x);                   // Escreve no LCD 
    x++;
    int buttonState = buttonChk();  // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
    Serial.print("buttonState: ");  // Comentario enviado para Monitor Serial
    Serial.println(buttonState);    // Comentario enviado para Monitor Serial
    Serial.print("exit: ");         // Comentario enviado para Monitor Serial
    Serial.println(exit);           // Comentario enviado para Monitor Serial
    if (buttonState == 4)           // Enquanto o botao SELECT (buttonChk = 4, exit = 0) estiver pressionado coninua o loop WHILE
      exit = 0;                   
    else exit = 1; 
  }

  int exitGUIloop = 0;
  while(exitGUIloop != 1)
  {
    GUIloop:                        // Label para onde o loop de GUIadjust retorna para navegacao entre telas
    buttonState = buttonChk();      // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
    Serial.print("buttonState: ");  // Comentario enviado para Monitor Serial
    Serial.println(buttonState);    // Comentario enviado para Monitor Serial
    Serial.print("navigate: ");     // Comentario enviado para Monitor Serial
    Serial. println(navigate);      // Comentario enviado para Monitor Serial

    switch (navigate)    // Estrutura switch para navegacao entre as diversas telas de ajuste
    {
    case 1:  // Welcome page do GUI (Graphic User Interface) --------------------------------------------------------------
      {
        Serial.println("_GUIadjust");
        lcd.clear();                       	// Limpa LCD
        lcd.setCursor(0,0);                	// Posiciona cursor
        lcd.print("** GUI Adjust **");     	// Escreve no LCD
        lcd.setCursor(0,1);                	// Posiciona cursor
        lcd.print("*C U I D A D O!*");     	// Escreve no LCD
        delay(3000);                       	// Aguarda 3 milisegundos (3seg)
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          lcd.clear();                       	// Limpa LCD
          lcd.setCursor(0,0);                	// Posiciona cursor
          lcd.print("[>] Continua... ");     	// Escreve no LCD
          lcd.setCursor(0,1);                	// Posiciona cursor
          lcd.print("[<<] Cancela (X)");     	// Escreve no LCD
          buttonState = buttonChk();         	// Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          lcd.print(buttonState);            	// 
          if (buttonState == 0)                 // Se o botao DIREITA for pressionado
          {
            navigate++;                      	// Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;                       // Interrompe o loop SWITCH CASE 
          } 
          if (buttonState == 4)              	// Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                     	// Limpa LCD
            lcd.setCursor(0,0);              	// Posiciona cursor
            lcd.print("Sair GUIadjust ?");   	// Escreve no LCD
            lcd.setCursor(1,1);              	// Posiciona cursor
            lcd.print("[<<] Confirma");     	// Escreve no LCD
            delay(1500);                     	// Aguarda 1,5 segundos
            buttonState = buttonChk();       	// Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)            	// Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);   	//
              Serial.println("exitCaseLoop 1");	//
              goto GUIexit;                  	// Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                       	// Interrompe o loop SWITCH CASE
            }
          }    
        }
        //break;                               	// Interrompe o SWITCH CASE  e retorna para o WHILE principal (exitGUIloop)
      }

    case 2:  // Ajuste do tempo de irrigacao do Setor 1 -------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("Ajuste de tempo de irrigacao do Setor 1: ");
          Serial.println(irrigateTimerSect1);
          lcd.clear();                                           // Limpa LCD
          lcd.setCursor(0,0);                                    // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");                          // Escreve no LCD
          lcd.setCursor(0,1);                                    // Posiciona cursor
          lcd.print("Setor1: ");                                 // Escreve no LCD
          lcd.setCursor(8,1);                                    // Posiciona cursor
          lcd.print(irrigateTimerSect1, 0);                      // Escreve no LCD   
          lcd.setCursor(14,1);                                   // Posiciona cursor
          lcd.print("s");                                        // Escreve no LCD
          buttonState = buttonChk();                             // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                                  // Se o botao CIMA for pressionado
            irrigateTimerSect1 = (irrigateTimerSect1 + 30000);   // Incrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect1
          if (buttonState == 2)                                  // Se o botao BAIXO for pressionado
            irrigateTimerSect1 = (irrigateTimerSect1 - 30000);   // Decrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect1
          if (buttonState == 0)                                  // Se o botao DIREITA for pressionado
          {
            navigate++;                                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                                         // Limpa LCD
            lcd.setCursor(0,0);                                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");                       // Escreve no LCD
            lcd.setCursor(1,1);                                  // Posiciona cursor
            lcd.print("[<<] Confirma");                          // Escreve no LCD
            delay(1500);                                         // Aguarda 1,5 segundos
            buttonState = buttonChk();                           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);                       //
              Serial.println("exitCaseLoop 7");                  //
              goto GUIexit;                                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 3:  // Ajuste do tempo de irrigacao do Setor 2 --------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("Ajuste de tempo de irrigacao do Setor 2: ");
          Serial.println(irrigateTimerSect2);
          lcd.clear();                                           // Limpa LCD
          lcd.setCursor(0,0);                                    // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");                          // Escreve no LCD
          lcd.setCursor(0,1);                                    // Posiciona cursor
          lcd.print("Setor2: ");                                 // Escreve no LCD
          lcd.setCursor(8,1);                                    // Posiciona cursor
          lcd.print(irrigateTimerSect2, 0);                      // Escreve no LCD   
          lcd.setCursor(14,1);                                   // Posiciona cursor
          lcd.print("s");                                        // Escreve no LCD
          buttonState = buttonChk();                             // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                                  // Se o botao CIMA for pressionado
            irrigateTimerSect2 = (irrigateTimerSect2 + 30000);   // Incrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect2
          if (buttonState == 2)                                  // Se o botao BAIXO for pressionado
            irrigateTimerSect2 = (irrigateTimerSect2 - 30000);   // Decrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect2
          if (buttonState == 0)                                  // Se o botao DIREITA for pressionado
          {
            navigate++;                                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                                         // Limpa LCD
            lcd.setCursor(0,0);                                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");                       // Escreve no LCD
            lcd.setCursor(1,1);                                  // Posiciona cursor
            lcd.print("[<<] Confirma");                          // Escreve no LCD
            delay(1500);                                         // Aguarda 1,5 segundos
            buttonState = buttonChk();                           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);                       //
              Serial.println("exitCaseLoop 8");                  //
              goto GUIexit;                                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 4:  // Ajuste do tempo de irrigacao do Setor 3 -------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("Ajuste de tempo de irrigacao do Setor 3: ");
          Serial.println(irrigateTimerSect3);
          lcd.clear();                                           // Limpa LCD
          lcd.setCursor(0,0);                                    // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");                          // Escreve no LCD
          lcd.setCursor(0,1);                                    // Posiciona cursor
          lcd.print("Setor3: ");                                 // Escreve no LCD
          lcd.setCursor(8,1);                                    // Posiciona cursor
          lcd.print(irrigateTimerSect3, 0);                      // Escreve no LCD   
          lcd.setCursor(14,1);                                   // Posiciona cursor
          lcd.print("s");                                        // Escreve no LCD
          buttonState = buttonChk();                             // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                                  // Se o botao CIMA for pressionado
            irrigateTimerSect3 = (irrigateTimerSect3 + 30000);   // Incrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect3
          if (buttonState == 2)                                  // Se o botao BAIXO for pressionado
            irrigateTimerSect3 = (irrigateTimerSect3 - 30000);   // Decrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect3
          if (buttonState == 0)                                  // Se o botao DIREITA for pressionado
          {
            navigate++;                                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                                         // Limpa LCD
            lcd.setCursor(0,0);                                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");                       // Escreve no LCD
            lcd.setCursor(1,1);                                  // Posiciona cursor
            lcd.print("[<<] Confirma");                          // Escreve no LCD
            delay(1500);                                         // Aguarda 1,5 segundos
            buttonState = buttonChk();                           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);                       //
              Serial.println("exitCaseLoop 9");                  //
              goto GUIexit;                                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 5:  // Ajuste do tempo de irrigacao do Setor 4 --------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("Ajuste de tempo de irrigacao do Setor 4: ");
          Serial.println(irrigateTimerSect4);
          lcd.clear();                                            // Limpa LCD
          lcd.setCursor(0,0);                                     // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");                           // Escreve no LCD
          lcd.setCursor(0,1);                                     // Posiciona cursor
          lcd.print("Setor4: ");                                  // Escreve no LCD
          lcd.setCursor(8,1);                                     // Posiciona cursor
          lcd.print(irrigateTimerSect4, 0);                       // Escreve no LCD   
          lcd.setCursor(14,1);                                    // Posiciona cursor
          lcd.print("s");                                         // Escreve no LCD
          buttonState = buttonChk();                              // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                                   // Se o botao CIMA for pressionado
            irrigateTimerSect4 = (irrigateTimerSect4 + 30000);    // Incrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect4
          if (buttonState == 2)                                   // Se o botao BAIXO for pressionado
            irrigateTimerSect4 = (irrigateTimerSect4 - 30000);    // Decrementa em 30000 milisegundos (0,5 minutos) a variavel irrigateTimerSect4
          if (buttonState == 0)                                  // Se o botao DIREITA for pressionado
          {
            navigate++;                                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                                         // Limpa LCD
            lcd.setCursor(0,0);                                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");                       // Escreve no LCD
            lcd.setCursor(1,1);                                  // Posiciona cursor
            lcd.print("[<<] Confirma");                          // Escreve no LCD
            delay(1500);                                         // Aguarda 1,5 segundos
            buttonState = buttonChk();                           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);                       //
              Serial.println("exitCaseLoop 10");                 //
              goto GUIexit;                                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }


    case 6:  // Ajuste da hora matutina -----------------------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("case 2_Ajuste da hora matutina: ");
          Serial.println(irrigateClockHourMorning);
          Serial.println(navigate);
          lcd.clear();                          // Limpa LCD
          lcd.setCursor(0,0);                   // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");         // Escreve no LCD
          lcd.setCursor(0,1);                   // Posiciona cursor
          lcd.print("Hora manha: ");            // Escreve no LCD
          lcd.setCursor(12,1);                  // Posiciona cursor
          lcd.print(irrigateClockHourMorning);  // Escreve no LCD
          buttonState = buttonChk();            // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                 // Se o botao CIMA for pressionado
            ++irrigateClockHourMorning;         // Incrementa em 1 a variavel irrigateClockHourMorning
          if (buttonState == 2)                 // Se o botao BAIXO for pressionado
            --irrigateClockHourMorning;         // Decrementa em 1 a variavel irrigateClockHourMorning
          if (buttonState == 0)                 // Se o botao DIREITA for pressionado
          {
            navigate++;                         // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                 // Se o botao ESQUERDA for pressionado
          {
            navigate--;                         // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                 // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                        // Limpa LCD
            lcd.setCursor(0,0);                 // Posiciona cursor
            lcd.print("Sair GUIadjust ?");      // Escreve no LCD
            lcd.setCursor(1,1);                 // Posiciona cursor
            lcd.print("[<<] Confirma");         // Escreve no LCD
            delay(1500);                        // Aguarda 1,5 segundos
            buttonState = buttonChk();          // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)               // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);      //
              Serial.println("exitCaseLoop 2"); //
              goto GUIexit;                     // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                            // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 7:  // Ajuste do minuto matutino ---------------------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("case 3_Ajuste do minuto matutino: ");
          Serial.println(irrigateClockMinMorning);
          Serial.println(navigate);
          lcd.clear();                          // Limpa LCD
          lcd.setCursor(0,0);                   // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");         // Escreve no LCD
          lcd.setCursor(0,1);                   // Posiciona cursor
          lcd.print("Minuto manha: ");          // Escreve no LCD
          lcd.setCursor(14,1);                  // Posiciona cursor
          lcd.print(irrigateClockMinMorning);   // Escreve no LCD   
          buttonState = buttonChk();            // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                 // Se o botao CIMA for pressionado
            ++irrigateClockMinMorning;          // Incrementa em 1 a variavel irrigateClockMinMorning
          if (buttonState == 2)                 // Se o botao BAIXO for pressionado
            --irrigateClockMinMorning;          // Decrementa em 1 a variavel irrigateClockMinMorning
          if (buttonState == 0)                 // Se o botao DIREITA for pressionado
          {
            navigate++;                         // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                 // Se o botao ESQUERDA for pressionado
          {
            navigate--;                         // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                 // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                        // Limpa LCD
            lcd.setCursor(0,0);                 // Posiciona cursor
            lcd.print("Sair GUIadjust ?");      // Escreve no LCD
            lcd.setCursor(1,1);                 // Posiciona cursor
            lcd.print("[<<] Confirma");         // Escreve no LCD
            delay(1500);                        // Aguarda 1,5 segundos
            buttonState = buttonChk();          // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)               // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);      //
              Serial.println("exitCaseLoop 3"); //
              goto GUIexit;                     // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                            // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 8:  // Ajuste da hora vespertina ---------------------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("case 4_Ajuste da hora vespertina: ");
          Serial.println(irrigateClockHourAfternoon);
          lcd.clear();                            // Limpa LCD
          lcd.setCursor(0,0);                     // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");           // Escreve no LCD
          lcd.setCursor(0,1);                     // Posiciona cursor
          lcd.print("Hora tarde: ");              // Escreve no LCD
          lcd.setCursor(12,1);                    // Posiciona cursor
          lcd.print(irrigateClockHourAfternoon);  // Escreve no LCD
          buttonState = buttonChk();              // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                   // Se o botao CIMA for pressionado
            ++irrigateClockHourAfternoon;         // Incrementa em 1 a variavel irrigateClockHourAfternoon
          if (buttonState == 2)                   // Se o botao BAIXO for pressionado
            --irrigateClockHourAfternoon;         // Decrementa em 1 a variavel irrigateClockHourAfternoon
          if (buttonState == 0)                   // Se o botao DIREITA for pressionado
          {
            navigate++;                           // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                   // Se o botao ESQUERDA for pressionado
          {
            navigate--;                           // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                   // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                          // Limpa LCD
            lcd.setCursor(0,0);                   // Posiciona cursor
            lcd.print("Sair GUIadjust ?");        // Escreve no LCD
            lcd.setCursor(1,1);                   // Posiciona cursor
            lcd.print("[<<] Confirma");           // Escreve no LCD
            delay(1500);                          // Aguarda 1,5 segundos
            buttonState = buttonChk();            // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                 // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);        //
              Serial.println("exitCaseLoop 4");   //
              goto GUIexit;                       // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                              // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 9:  // Ajuste do minuto vespertina --------------------------------------------------------------------------------
      {
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("case 5_Ajuste do minuto vespertino: ");
          Serial.println(irrigateClockMinAfternoon);
          lcd.clear();                            // Limpa LCD
          lcd.setCursor(0,0);                     // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");           // Escreve no LCD
          lcd.setCursor(0,1);                     // Posiciona cursor
          lcd.print("Minuto tarde: ");            // Escreve no LCD
          lcd.setCursor(14,1);                    // Posiciona cursor
          lcd.print(irrigateClockMinAfternoon);   // Escreve no LCD   
          buttonState = buttonChk();              // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                   // Se o botao CIMA for pressionado
            ++irrigateClockMinAfternoon;          // Incrementa em 1 a variavel irrigateClockHourAfternoon
          if (buttonState == 2)                   // Se o botao BAIXO for pressionado
            --irrigateClockMinAfternoon;          // Decrementa em 1 a variavel irrigateClockHourAfternoon
          if (buttonState == 0)                   // Se o botao DIREITA for pressionado
          {
            navigate++;                           // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                   // Se o botao ESQUERDA for pressionado
          {
            navigate--;                           // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                   // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                          // Limpa LCD
            lcd.setCursor(0,0);                   // Posiciona cursor
            lcd.print("Sair GUIadjust ?");        // Escreve no LCD
            lcd.setCursor(1,1);                   // Posiciona cursor
            lcd.print("[<<] Confirma");           // Escreve no LCD
            delay(1500);                          // Aguarda 1,5 segundos
            buttonState = buttonChk();            // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                 // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);        //
              Serial.println("exitCaseLoop 5");   //
              goto GUIexit;                       // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                              // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 10:  // Ajuste do dia de irrigacao -------------------------------------------------------------------------------
      {
        Serial.print("case 6_Ajuste do dia de irrigacao");
        unsigned int yesORno = 0;

        // Segunda-Feira -----------------------------------------------------------------------------------
        int exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.println("Ajuste de DOW - Segunda-feira ");
          yesORno = irrigateDOWMon;      // Atribui o valor da variavel irrigateDOWMon para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Segunda: ");        // Escreve no LCD
          lcd.setCursor(9,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWMon = 1;          // Atribui valor 1 para a variavel do dia da irrigacao (Monday = 1)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWMon = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop SWITCH CASE
        }

        // Terca-Feira -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Terca-feira ");
          yesORno = irrigateDOWTue;      // Atribui o valor da variavel irrigateDOWTue para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Terca: ");          // Escreve no LCD
          lcd.setCursor(7,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWTue = 2;          // Atribui valor 2 para a variavel do dia da irrigacao (Thuesday = 2)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWTue = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop WHILE
        }

        // Quarta-Feira -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Quarta-feira ");
          yesORno = irrigateDOWWed;      // Atribui o valor da variavel irrigateDOWWed para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Quarta: ");         // Escreve no LCD
          lcd.setCursor(8,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWWed = 3;          // Atribui valor 1 para a variavel do dia da irrigacao (Wednwsday = 3)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWWed = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                   // Interrompe o loop WHILE
        }

        // Quinta-Feira -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Quinta-feira ");
          yesORno = irrigateDOWThu;      // Atribui o valor da variavel irrigateDOWThu para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Quinta: ");         // Escreve no LCD
          lcd.setCursor(8,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWThu = 4;          // Atribui valor 1 para a variavel do dia da irrigacao (Thuersday = 1)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWThu = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop WHILE     
        }

        // Sexta-Feira -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Sexta-feira ");
          yesORno = irrigateDOWFri;      // Atribui o valor da variavel irrigateDOWFri para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Sexta: ");          // Escreve no LCD
          lcd.setCursor(7,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWFri = 5;          // Atribui valor 1 para a variavel do dia da irrigacao (Friday = 5)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWFri = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop WHILE
        }

        // Sabado -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Sabado ");
          yesORno = irrigateDOWSat;      // Atribui o valor da variavel irrigateDOWSat para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Sabado: ");         // Escreve no LCD
          lcd.setCursor(8,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWSat = 6;          // Atribui valor 1 para a variavel do dia da irrigacao (Saturday = 6)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWSat = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop WHILE
        }

        // Domingo -----------------------------------------------------------------------------------
        exit = 0;
        while (exit != 1)                // Enquanto o botao DIREITA nao for pressionado roda o loop
        {
          Serial.print("Ajuste de DOW - Domingo ");
          yesORno = irrigateDOWSun;      // Atribui o valor da variavel irrigateDOWSun para a variavel yesORno
          lcd.clear();                   // Limpa LCD
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Domingo: ");        // Escreve no LCD
          lcd.setCursor(9,1);            // Posiciona cursor
          if (yesORno == 0)
            lcd.print("Nao");            // Escreve no LCD
          else lcd.print("Sim");         // Escreve no LCD
          Serial.println(yesORno);
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            irrigateDOWSun = 7;          // Atribui valor 1 para a variavel do dia da irrigacao (Sunday = 7)
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            irrigateDOWSun = 0;          // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
          if (buttonState == 0)          // Se o botao DIREITA for pressionado interrompe o loop
            exit = 1;                    // Interrompe o loop WHILE
        }
      }

    case 11:  // Creditos e Avisos ----------------------------------------------------------------------------------------
      {
        Serial.println("Creditos e avisos");
        lcd.clear();                             // Limpa as informacoes do LCD 
        lcd.setCursor(0,0);                      // Posiciona o cursor 
        lcd.print("SAIBA ver1.2");               // Escreve no LCD 
        lcd.setCursor(0,1);                      // Posiciona o cursor 
        lcd.print("DanielRosa(2015)");           // Escreve no LCD 
        delay(2000);                             // Exibe a mensagem por 3 segundos antes de prosseguir o programa
        lcd.clear();                             // Limpa as informacoes do LCD 
        lcd.setCursor(0,0);                      // Posiciona o cursor 
        lcd.print("Ajuste do DS1302");           // Escreve no LCD 
        lcd.setCursor(0,1);                      // Posiciona o cursor 
        lcd.print("* System Clock *");           // Escreve no LCD 
        delay(1500); 
        lcd.clear();                             // Limpa as informacoes do LCD 
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          lcd.setCursor(0,0);                    // Posiciona o cursor
          lcd.print("Ao sair religue");          // Escreve no LCD
          lcd.setCursor(0,1);                    // Posiciona o cursor
          lcd.print("writeProtect(ON)");         // Escreve no LCD
          
          int buttonState = buttonChk();         // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 0)                  // Se o botao DIREITA for pressionado
          {
            navigate++;                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                         // Limpa LCD
            lcd.setCursor(0,0);                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");       // Escreve no LCD
            lcd.setCursor(1,1);                  // Posiciona cursor
            lcd.print("[<<] Confirma");          // Escreve no LCD
            delay(1500);                         // Aguarda 1,5 segundos
            buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);       //
              Serial.println("exitCaseLoop 11"); //
              goto GUIexit;                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 12:  // Habilita o ajuste de hora e data do sistema --------------------------------------------------------------      
      {
        rtc.writeProtect(true);                  // Atribui valor 0 para a variavel do dia da irrigacao (0 nao sera reconhecido pelo check e nao irrigara neste dia)
        yesORno = 1;                             // Atribui o valor da variavel irrigateDOWSun para a variavel yesORno
        lcd.clear();                             // Limpa LCD
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          Serial.print("rtc.writeProtect: ");
          Serial.println(yesORno);
          lcd.setCursor(0,0);                    // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");          // Escreve no LCD
          lcd.setCursor(0,1);                    // Posiciona cursor
          lcd.print("writeProtect");             // Escreve no LCD
          lcd.setCursor(13,1);                   // Posiciona cursor
          if (yesORno == 0)
            lcd.print("OFF");                    // Escreve no LCD
          else lcd.print("ON");                  // Escreve no LCD
          buttonState = buttonChk();             // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                  // Se o botao CIMA for pressionado
          {
            rtc.writeProtect(true);              // Ativa a protecao de escrita no DS1302 (writeProtect = true)
            yesORno = 1;
          }
          if (buttonState == 2)                  // Se o botao BAIXO for pressionado
          {
            rtc.writeProtect(false);             // Desativa a protecao de escrita no DS1302 (writeProtect = false)
            yesORno = 0;
          }
          if (buttonState == 0)                  // Se o botao DIREITA for pressionado
          {
            navigate++;                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                         // Limpa LCD
            lcd.setCursor(0,0);                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");       // Escreve no LCD
            lcd.setCursor(1,1);                  // Posiciona cursor
            lcd.print("[<<] Confirma");          // Escreve no LCD
            delay(1500);                         // Aguarda 1,5 segundos
            buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);       //
              Serial.println("exitCaseLoop 12"); //
              goto GUIexit;                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 13:  // Ajusta o dia da semana (dow) -----------------------------------------------------------------------------
      {
        t = rtc.getTime();                       // Le dados do DS1302
        unsigned int i = (t.dow);                // Le o valor do dia da semana do DS1302 e atribui para a variavel i
        int exitCaseLoop = 0;
        while (exitCaseLoop != 1)
        {
          i = constrain(i, 1, 7);                // Declara e limita o valor da variavel i entre 1 e 7 (os sete dias da semana)
          char* dowString[] = {
            "NULL", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado", "Domingo"                                                                                                                                                                                                                };
          lcd.clear();                           // Limpa LCD
          lcd.setCursor(0,0);                    // Posiciona cursor
          lcd.print("[<] [+] [-] [>]");          // Escreve no LCD
          lcd.setCursor(0,1);                    // Posiciona cursor
          lcd.print("Hoje: ");                   // Escreve no LCD
          lcd.setCursor(6,1);                    // Posiciona cursor
          lcd.print(dowString[i]);               // Escreve no LCD
          lcd.setCursor(15,1);                   // Posiciona cursor
          lcd.print(i);                          // Escreve no LCD
          Serial.print("rtc.getDOW: ");
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(rtc.getDOWStr(FORMAT_SHORT));
          buttonState = buttonChk();             // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 1)                  // Se o botao CIMA for pressionado
          {
            ++i;                                 // Incrementa em 1 o indexador do String
            rtc.setDOW(i+1);                     // Escreve na memoria (DS1302) o valor ajustado do dia da semana
            Serial.print("rtc.getDOW: ");
            Serial.print(i);
            Serial.print(" = ");
            Serial.println(rtc.getDOWStr(FORMAT_SHORT));
          }
          if (buttonState == 2)                  // Se o botao BAIXO for pressionado
          {
            --i;                                 // Decrementa em 1 o indexador do String
            rtc.setDOW(i-1);                     // Escreve na memoria (DS1302) o valor ajustado do dia da semana
            Serial.print("rtc.getDOW: ");
            Serial.print(i);
            Serial.print(" = ");
            Serial.println(rtc.getDOWStr(FORMAT_SHORT));
          }
          if (buttonState == 0)                  // Se o botao DIREITA for pressionado
          {
            navigate++;                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 3)                  // Se o botao ESQUERDA for pressionado
          {
            navigate--;                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
          }
          if (buttonState == 4)                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
          {
            lcd.clear();                         // Limpa LCD
            lcd.setCursor(0,0);                  // Posiciona cursor
            lcd.print("Sair GUIadjust ?");       // Escreve no LCD
            lcd.setCursor(1,1);                  // Posiciona cursor
            lcd.print("[<<] Confirma");          // Escreve no LCD
            delay(1500);                         // Aguarda 1,5 segundos
            buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
            if (buttonState == 4)                // Verifica novamente se o botao Select esta pressionado
            {
              Serial.println(buttonState);       //
              Serial.println("exitCaseLoop 13"); //
              goto GUIexit;                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
              //break;                             // Interrompe o loop SWITCH CASE
            }
          } 
        }
        //break;
      }

    case 14:  // Ajusta a data no format dd, mm, aaaa  ---------------------------------------------------------------------
      {
        //int dd = 15;       // Declara a variavel de dia do mes com 01 
        //int mm = 07;       // Declara a variavel de mes do ano com 01 
        //int aaaa = 2015;   // Declara a variavel de ano com 2015
        t = rtc.getTime();               // Le dados do DS1302
        int dd = (t.date);               // Le o valor do dia do DS1302 e atribui para a variavel dd
        int mm = (t.mon);                // Le o valor do mes do DS1302 e atribui para a variavel mm
        int aaaa = (t.year);             // Le o valor do ano do DS1302 e atribui para a variavel aaaa

        lcd.clear();                     // Limpa LCD
        exit = 0;
        while (exit != 1)
        {
          Serial.print("rtc.setDate(dd: ");
          Serial.print(dd);
          Serial.println();
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("D:");               // Escreve no LCD
          lcd.setCursor(2,1);            // Posiciona cursor
          lcd.print(dd);                 // Escreve no LCD   
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          dd = constrain(dd, 01, 31);    // Declara e restringe a variavel de dia do mes entre 01 e 31
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            ++dd;                        // Incrementa em 1 a variavel do dia da semana
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            --dd;                        // Decrementa em 1 a variavel do dia da semana
          if (buttonState == 0)          // Se o botao DIREITA for pressionado
            exit = 1;                    // Interrompe o loop WHILE
          if (buttonState == 4)          // Se o botao DIREITA for pressionado
            goto GUIexit;                // Interrompe o loop WHILE  
          delay(250);
        }
        exit = 0;
        while (exit != 1)
        {
          Serial.print("rtc.setDate(dd mm: ");
          Serial.print(mm);
          Serial.println();
          lcd.setCursor(5,1);               // Posiciona cursor
          lcd.print("M:");                  // Escreve no LCD
          lcd.setCursor(7,1);               // Posiciona cursor
          lcd.print(mm);                    // Escreve no LCD   
          buttonState = buttonChk();        // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          mm = constrain(mm, 01, 12);       // Declara e restringe a variavel de mes do ano entre 01 e 12
          if (buttonState == 1)             // Se o botao CIMA for pressionado
            ++mm;                           // Incrementa em 1 a variavel do mes do ano
          if (buttonState == 2)             // Se o botao BAIXO for pressionado
            --mm;                           // Decrementa em 1 a variavel do mes do ano
          if (buttonState == 0)             // Se o botao DIREITA for pressionado
            exit = 1;                       // Interrompe o loop WHILE
          delay(250);  
        }
        exit = 0;
        while (exit != 1)
        {
          Serial.print("rtc.setDate(dd mm aaaa: ");
          Serial.print(aaaa);
          Serial.println();
          lcd.setCursor(10,1);                 // Posiciona cursor
          lcd.print("A:");                     // Escreve no LCD
          lcd.setCursor(12,1);                 // Posiciona cursor
          lcd.print(aaaa);                     // Escreve no LCD   
          buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          aaaa = constrain(aaaa, 2015, 2100);  // Declara e restringe a variavel de ano entre 2015 e 2100
          if (buttonState == 1)                // Se o botao CIMA for pressionado
            ++aaaa;                            // Incrementa em 1 a variavel do ano corrente
          if (buttonState == 2)                // Se o botao BAIXO for pressionado
            --aaaa;                            // Decrementa em 1 a variavel do ano corrente
          if (buttonState == 0)                // Se o botao DIREITA for pressionado
          {
            rtc.setDate(dd, mm, aaaa);         // Escreve no DS1302 o novo valor de data do sistema
            exit = 1;                          // Interrompe o loop WHILE
          }
          if (buttonState == 4)          // Se o botao DIREITA for pressionado
            goto GUIexit;    

            // Interrompe o loop WHILE
        }

        lcd.setCursor(0,0);              // Posiciona cursor
        lcd.print("[<] [+] [-] [>]");    // Escreve no LCD
        buttonState = buttonChk();       // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
        if (buttonState == 0)                  // Se o botao DIREITA for pressionado
        {
          navigate++;                          // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
        }
        if (buttonState == 3)                  // Se o botao ESQUERDA for pressionado
        {
          navigate--;                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
        }
        if (buttonState == 4)                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
        {
          lcd.clear();                         // Limpa LCD
          lcd.setCursor(0,0);                  // Posiciona cursor
          lcd.print("Sair GUIadjust ?");       // Escreve no LCD
          lcd.setCursor(1,1);                  // Posiciona cursor
          lcd.print("[<<] Confirma");          // Escreve no LCD
          delay(1500);                         // Aguarda 1,5 segundos
          buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 4)                // Verifica novamente se o botao Select esta pressionado
          {
            Serial.println(buttonState);       //
            Serial.println("exitCaseLoop 13"); //
            goto GUIexit;                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
            //break;                             // Interrompe o loop SWITCH CASE
          }
        } 
        //break;
      }

    case 15:  // Ajusta a hora no formato hh, mm, 00  ---------------------------------------------------------------------
      {
        //int hh = 12;       // Declara a variavel de hora do dia com 12 
        //int mm = 30;       // Declara a variavel de minuto com 30 
        
        t = rtc.getTime();               // Le dados do DS1302
        int hh = (t.hour);               // Le o valor da hora do DS1302 e atribui para a variavel hh
        int mm = (t.min);                // Le o valor do minuto do DS1302 e atribui para a variavel mm

        lcd.clear();                     // Limpa LCD
        int exit = 0;
        while (exit != 1)
        {
          Serial.print("rtc.setTime(hh: ");
          Serial.print(hh);
          Serial.println();
          lcd.setCursor(0,0);            // Posiciona cursor
          lcd.print("    [+] [-] [>]");  // Escreve no LCD
          lcd.setCursor(0,1);            // Posiciona cursor
          lcd.print("Hora:");            // Escreve no LCD
          lcd.setCursor(5,1);            // Posiciona cursor
          lcd.print(hh);                 // Escreve no LCD   
          buttonState = buttonChk();     // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          hh = constrain(hh, 00, 23);    // Declara e restringe a variavel de dia do mes entre 01 e 31
          if (buttonState == 1)          // Se o botao CIMA for pressionado
            ++hh;                        // Incrementa em 1 a variavel do dia da semana
          if (buttonState == 2)          // Se o botao BAIXO for pressionado
            --hh;                        // Decrementa em 1 a variavel do dia da semana
          if (buttonState == 0)          // Se o botao DIREITA for pressionado
            exit = 1;                    // Interrompe o loop WHILE
          delay(250);
        }
        exit = 0;
        while (exit != 1)
        {
          Serial.print("rtc.setTime(hh mm: ");
          Serial.print(mm);
          Serial.println();
          lcd.setCursor(0,0);             // Posiciona cursor
          lcd.print("    [+] [-] [>]");   // Escreve no LCD
          lcd.setCursor(8,1);             // Posiciona cursor
          lcd.print("Min:");              // Escreve no LCD
          lcd.setCursor(12,1);            // Posiciona cursor
          lcd.print(mm);                  // Escreve no LCD   
          buttonState = buttonChk();      // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          mm = constrain(mm, 00, 59);     // Declara e restringe a variavel de mes do ano entre 01 e 12
          if (buttonState == 1)           // Se o botao CIMA for pressionado
            ++mm;                         // Incrementa em 1 a variavel do mes do ano
          if (buttonState == 2)           // Se o botao BAIXO for pressionado
            --mm;                         // Decrementa em 1 a variavel do mes do ano
          if (buttonState == 0)           // Se o botao DIREITA for pressionado
          {
            rtc.setTime(hh, mm, 00);      // Escreve no DS1302 o novo valor de hora do sistema
            exit = 1;                     // Interrompe o loop WHILE
          }
          delay(250);
        }

        lcd.setCursor(0,0);              // Posiciona cursor
        lcd.print("[<] [+] [-] [>]");    // Escreve no LCD
        if (buttonState == 0)                  // Se o botao DIREITA for pressionado
        {
          navigate = 12;                       // Incrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
        }
        if (buttonState == 3)                  // Se o botao ESQUERDA for pressionado
        {
          navigate--;                          // Decrementa a variavel navigate em 1
            Serial.print("buttonState: ");
            Serial.println(buttonState);
            Serial.print("navigate: ");
            Serial.println(navigate);
            goto GUIloop;
        }
        if (buttonState == 4)                  // Se o botao SELECT for pressionado, sai do loop WHILE do case
        {
          lcd.clear();                         // Limpa LCD
          lcd.setCursor(0,0);                  // Posiciona cursor
          lcd.print("Sair GUIadjust ?");       // Escreve no LCD
          lcd.setCursor(1,1);                  // Posiciona cursor
          lcd.print("[<<] Confirma");          // Escreve no LCD
          delay(1500);                         // Aguarda 1,5 segundos
          buttonState = buttonChk();           // Le o botao atraves da funcao buttonChk e repassa este valor para a variavel buttonState
          if (buttonState == 4)                // Verifica novamente se o botao Select esta pressionado
          {
            Serial.println(buttonState);       //
            Serial.println("exitCaseLoop 13"); //
            goto GUIexit;                      // Vai para o LABEL GUIexit e encerra a funcao de GUIadjust
            //break;                             // Interrompe o loop SWITCH CASE
          }
        } 
        //break;
      }
      //break;
    }
    exitGUIloop = 1;  // Interrompe o loop WHILE
  }
GUIexit:
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fim do WHILE!");
    lcd.setCursor(0,1);
    lcd.print("** GUIexit **");
    Serial.println("Fim do loop WHILE principal do GUIadjust");
    delay(1000);
    exitGUIloop = 1;
  }  
}

/*** FIM da funcao de GUI Adjust ***/

