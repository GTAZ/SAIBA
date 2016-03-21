/*************************************************
 * 04 - FUNCAO DE CONFIGURACAO DO SISTEMA (SETUP)*
 *************************************************/

void setup()  // Funcao OBRIGATORIA para o Arduino
{
  Serial.begin(9600);                                                 // Inicializa a porta serial e a configura para boundrate de 9600
  Serial.println("### 04. Inicio da funcao obrigatoria Setup ###");   // Comentario enviado para Monitor Serial
  Serial.println();

  Serial.println("_Tempo de Irrigacao por setor");
  Serial.println(irrigateTimerSect1, 0);
  Serial.println(irrigateTimerSect2, 0);
  Serial.println(irrigateTimerSect3, 0);
  Serial.println(irrigateTimerSect4, 0);
  Serial.println("_Horario de Irrigacao");
  Serial.print("Manha: ");
  Serial.print(irrigateClockHourMorning);
  Serial.println(irrigateClockMinMorning);
  Serial.print("Tarde: ");
  Serial.print(irrigateClockHourAfternoon);
  Serial.println(irrigateClockMinAfternoon);
  Serial.println("_Dia de Irrigacao");
  Serial.print("Segunda :");
  Serial.println(irrigateDOWMon);
  Serial.print("Terca :");
  Serial.println(irrigateDOWTue);
  Serial.print("Quarta :");
  Serial.println(irrigateDOWWed);
  Serial.print("Quinta :");
  Serial.println(irrigateDOWThu);
  Serial.print("Sexta :");
  Serial.println(irrigateDOWFri);
  Serial.print("Sabado :");
  Serial.println(irrigateDOWSat);
  Serial.print("Domingo :");
  Serial.println(irrigateDOWSun);
  Serial.println();

  Serial.println("_Condicao de Irrigacao (1 = sim; 0 = nao)");
  Serial.println("Se ((checkRain() == 0)  &&  (checkIrrigateDOW() == 1) && (checkIrrigateClock() == 1))");
  Serial.print("Verificacao se ha chuva (checkRain): ");
  Serial.println(checkRain());
  Serial.print("Verificacao de dia de irrigacao (checkIrrigateDOW): ");
  Serial.println(checkIrrigateDOW());
  Serial.print("Verificacao de horario de irrigacao (checkIrrigateClock): ");
  Serial.println(checkIrrigateClock());
  Serial.println();


  //---------------------------------------------------------------------------------------------------------
  // 04.1 *** Atribuicao das interrupcoes de Parada de Emergencia e Baixo Nivel de Agua do Tanque ***
  //---------------------------------------------------------------------------------------------------------
  // attachInterrupt(0, EmergencyStop, LOW);    // Atribui A pino D02 a interrupcao 0 de parada de emergencia (funcao EmergencyStop) se o botao de emergencia for pressionado (false = 0, LOW) -> Necessita de porta logica NOT para inverter o comando do botao
  // attachInterrupt(1, tankLowLevel, LOW);     // (ou LOW) Atribui A pino D03 a interrupcao 1 de parada da bomba por baixo naivel no tanque (false = 0, LOW) -> Necessita de porta logica NOT para inverter o comando do alarme do controlador de nivel COEL 


  //---------------------------------------------------------------------------------------------------------
  // 04.2 *** DS1302 Set the clock to run-mode, and disable the write protection ***
  //---------------------------------------------------------------------------------------------------------
  rtc.halt(false);
  /* -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> */
  /* -> */
  /* -> */  // *** IMPORTANTE !!!! *** A rotina abaixo deve ser utilizada somente para acerto de dia, data e hora do DS1302 devendo ser rodada 1 unica vez ***    
  /* -> */
  /* -> */  rtc.writeProtect(false);      // Habilita (false) ou Desabilita (true) o modo de escrita no DS1302. Antes de ajustar qualquer parametro habilitar a escrita; desabilitar na sequencia
  /* -> */
  /* -> */  //rtc.setDOW(SATURDAY);        // Ajusta o dia da semana. Set Day-of-Week to 'FRIDAY'
  /* -> */  //rtc.setDate(10, 01, 2015);   // Ajusta dia, mes e ano. Set the date (dd, mm, yy)'
  /* -> */  //rtc.setTime(00, 02, 00);     // Ajusta o horario. Set the time (hr, min, sec, 24hr format)
  /* -> */
  /* -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> */


  //---------------------------------------------------------------------------------------------------------
  // 04.3 *** Inicializacao do sensor  de pressao atmosferica GY-65 BMP085  ***
  //---------------------------------------------------------------------------------------------------------
  Serial.println("_Setting up BMP085");
  Wire.begin();
  bmp085Calibration();


  //---------------------------------------------------------------------------------------------------------
  // 04.4 *** ATRIBUICAO DA PINAGEM ***
  //---------------------------------------------------------------------------------------------------------
  DHT11.attach(22);  // Atribui o pino D22 A sensor DHT11

  // Analogica ------------------------------------------------------------------------------
  pinMode(sensRainSizePin, INPUT);   // Configura o pino A1 do sensor de quantidade de precipitacao como de leitura
  pinMode(sensSect1Pin, INPUT);      // Configura o pino A08 do sensor de umidade da grama do Fundo como de leitura
  pinMode(sensSect2Pin, INPUT);      // Configura o pino A09 do sensor de umidade da grama da Rua Sol1 (vaga coberta) como de leitura
  pinMode(sensSect3Pin, INPUT);      // Configura o pino A10 do sensor de umidade da grama da Rua Sol2 (coqueiro) como de leitura
  pinMode(sensSect4Pin, INPUT);      // Configura o pino A11 do sensor de umidade da floreira de Begonias como de leitura

  // Digital --------------------------------------------------------------------------------
  // Pino D0 e D1 estao dedicados para a comunicacao Tx/Rx (bluetooth)
  // Pino D2 esta dedicado para a interrupcao do botao de emergencia
  // Pino D3 esta dedicado para a interrupcao de baixo nivel de agua no tanque
  // Pinos de D4 a D10 estao dedicados A LCD
  // Pinos de D11 a D13 estao dedicados A Real Time Clock (RTC) DS1302
  // Pinos D20 (SDA) e D21 (SCL) estao dedicados A sensor de presssao  BMP085
  // Pino D22 esta dedicado para a leitura do sensor de temperatura ambiente DHT11
  pinMode(sensRainPin, INPUT);            // Configura o pino D24 do sensor chuva como de leitura
  pinMode(sect1SolenoidPin, OUTPUT);      // Configura o pino D49 da Valvula solenoide do sect1Solenoid como de escrita
  pinMode(sect2SolenoidPin, OUTPUT);      // Configura o pino D47 da Valvula solenoide do sect2Solenoid como de escrita
  pinMode(sect3SolenoidPin, OUTPUT);      // Configura o pino D45 da Valvula solenoide do sect3Solenoid como de escrita
  pinMode(sect4SolenoidPin, OUTPUT);      // Configura o pino D43 da Valvula solenoide do sect4Solenoid como de escrita
  pinMode(tankFillSolenoidPin, OUTPUT);   // Configura o pino D39 da Valvula solenoide de enchimento do tanque com agua da rua como de escrita
  pinMode(PumpPin, OUTPUT);               // Configura o pino D53 da Bomba como de escrita


  //---------------------------------------------------------------------------------------------------------
  // 04.5 *** ATRIBUICAO INICIAL DO ESTADO DAS SAIDAS DIGITAIS ***
  //---------------------------------------------------------------------------------------------------------
  digitalWrite(sect1SolenoidPin, LOW);     // Garantia de que a valvula do setor 1 sera desligada sempre que o sistema for iniciado
  digitalWrite(sect2SolenoidPin, LOW);     // Garantia de que a valvula do setor 2 sera desligada sempre que o sistema for iniciado
  digitalWrite(sect3SolenoidPin, LOW);     // Garantia de que a valvula do setor 3 sera desligada sempre que o sistema for iniciado
  digitalWrite(sect4SolenoidPin, LOW);     // Garantia de que a valvula do setor 4 sera desligada sempre que o sistema for iniciado
  digitalWrite(tankFillSolenoidPin, LOW);  // Garantia de que a valvula do de enchimento do tanque com agua da rua sera desligada sempre que o sistema for iniciado
  digitalWrite(PumpPin, LOW);              // Garantia de que a bomba sera desligada sempre que o sistema for iniciado


  //---------------------------------------------------------------------------------------------------------
  // 04.6 *** Tela inicial do sistema quando ligado ***
  //---------------------------------------------------------------------------------------------------------
  lcd.begin(16,2);                // Configura o LCD com 16 colunas e 2 linhas de caracteres
  lcd.display();                  // Liga o LCD1602 Keypad Shield 
  lcd.clear();                    // Limpa as informacoes do LCD logo no inicio do programa
  lcd.setCursor(0,0);             // Posiciona o cursor na coluna 1 (0), linha 1 (0)
  lcd.print("SAIBA ver1.2");      // Escreve no LCD a mensagem "SAIBA ver1.1"
  lcd.setCursor(0,1);             // Posiciona o cursor na coluna 1 (0), linha 2 (1)
  lcd.print("DanielRosa(2015)");  // Escreve no LCD a mensagem "DanielRosa(2015)"
  delay(5000);                    // Exibe a mensagem por 5 segundos antes de prosseguir o programa
  lcd.clear();                    // Limpa o LCD

}
/*** FIM DA CONFIGURACAO DO SISTEMA (FUNCAO SETUP) ***/
