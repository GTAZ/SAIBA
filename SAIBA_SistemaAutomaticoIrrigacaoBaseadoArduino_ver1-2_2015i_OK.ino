/********************************************************************************************
 *  ######################################################################################  *
 *  ###  S.A.I.B.A.  -  Sistema Automatico de Irrigacao Baseado em Arduino  (ver 1.1)  ###  *
 *  ######################################################################################  *
 *                                                                                          *
 *  Software desenvolvido por: Daniel Brocanello Rosa                                       *
 *                             Valinhos (-22.9705555556,-46.9958333333; 660m)               *
 *                             Sao Paulo - Brasil                                           *
 *                             (ver 1.0) Maio-Novembro, 2013                                *
 *                             (ver 1.1) Janeiro, 2015                                      *  Inclusao da rotina de utilizacao dos botoes para selecao de funcao desejada;  Inclusao do calculo de altitude e previsao meteorologica;
 *                             (ver 1.2) Janeiro-Fevereiro, 2015                            *  Inclusao da funcao GUIadjust que premite ao usuario alterar os parametros de entrada do sistema como tempos de irrigacao, dia e hora do acionamento do sistema, etc.
 *                                                                                          *
 *  Hardware utilizado : Arduino Mega 2560                                                  *
 *                       LCD1602 Keypad Shield                                              *
 *                       ProtoShield Mini Breadboard                                        *
 *                       Highly sensitive Rain sensor module                                *
 *                       Soil hygrometer detection module                                   *
 *                       DHT11 Digital Temperature Humidity Sensor Module                   *  https://www.virtuabotix.com/?attachment_id=257
 *                       DS1302 Real Time Clock Module with Battery CR2032                  *  http://www.henningkarlsen.com/electronics/library.php?id=5
 *                       GY-65 BMP085 Atmospheric Pressure Altimeter Module                 *  http://mitat.tuu.fi/?p=78 / https://www.sparkfun.com/tutorials/253 / http://sensorapp.net/?p=278
 *                                                                                          *
 *  Agradecimentos a Andre Leao pelas dicas de programacao "C" para Arduino na versao 1.0   *
 *                                                                                          * 
 ********************************************************************************************/



/*************************************
 * 01 - INICIALIZACAO DE BIBLIOTECAS *
 *************************************/

#include <LiquidCrystal.h>              // Inclui a biblioteca para o LCD Keypad
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);    // Atribui a pinagem do LCD Keypad

#include <dht11.h>                      // Inclui a biblioteca para o Sensor de Temperatura e Umidade Ambiente
#include <Versalino.h>                  // Inclui a biblioteca auxiliar para o Modulo de DHT11
dht11 DHT11;                            // ?? copiado do sketch dht11_funcions ??

#include <DS1302.h>                     // Inclui a biblioteca para o Modulo de Relogio
DS1302 rtc(11, 12, 13);                 // Inicializa o DS1203
Time t;                                 // Inicializa a estrutura Tempo-Data (Time-date structure)

#include <Wire.h>                       // Inclui a biblioteca para o Modulo de Presssao Atmosferica


/*** FIM DA INICIALIZACAO DE BIBLIOTECAS ***/



/*************************************************************************************************
 * 02 - CONFIGURACAO, DEFINICAO DE PINAGEM DOS SENSORES & ATUADORES E ENDERECAMENTO DE VARIAVEIS *
 *************************************************************************************************/

// BMP085 Atmosferic Pressure Sensor Module (GY-65) Inicialization ---------------------
#define BMP085_ADDRESS 0x77   // I2C address of BMP085
const unsigned char OSS = 0;  // Oversampling Setting of BMP085
const float p0 = 101325;      // Pressure at sea level (Pa)
const float currentAltitude = 660; // current altitude in METERS (original value = 1580.08)
const float ePressure = p0 * pow((1-currentAltitude/44330), 5.255);  // expected pressure (in Pa) at altitude
float bmpCalcAlt;
float weatherDiff;

// BMP085 Atmosferic Pressure Sensor Module (GY-65) - Variables Assignment -------------
int ac1;
int ac2;
int ac3;
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1;
int b2;
int mb;
int mc;
int md;
// b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long b5;
short bmpTemp;
long bmpBaro;

//  Analogicas -------------------------------------------------------------------------
#define buttonPressPin A0     // botao pressionado no painel do LCD = pino A0 (leitura) 
#define sensRainSizePin A1    // sensor de quantidade de precipitacai = pino A1 (leitura)
#define sensBaroPin A2        // sensor presssao barometrica = pino A2 (leitura)
#define sensSect1Pin A8       // sensor de umidade da grama do Fundo da casa = pino A08 (leitura)
#define sensSect2Pin A9       // sensor de umidade da grama na lateral da Rua Sol1 (vaga coberta) = pino A09 (leitura)
#define sensSect3Pin A10      // sensor de umidade da grama na lateral da Rua Sol2 (coqueiro)= pino A10 (leitura)
#define sensSect4Pin A11      // sensor de umidade da floreira de Begonias = pino A11 (leitura)

//  Digitais ----------------------------------------------------------------------------
// O pino D02 esta dedicado para a interrupcao 0 da funcao EmergencyStop de parada de emergencia caso o botao de emergencia for pressionado
// O pino D03 esta dedicado para a interrupcao 1 da funcao tankLowLevel do sinal do controlador COEL caso o nivel de agua de chuva da cisterna esteja baixo
#define sensRainPin 24           // sensor de chuva = pino D24 (leitura)
#define sect1SolenoidPin 49      // Valvula solenoide do setor 1 = pino D49 (escrita)
#define sect2SolenoidPin 47      // Valvula solenoide do setor 2 = pino D47 (escrita)
#define sect3SolenoidPin 45      // Valvula solenoide do setor 3 = pino D45 (escrita)
#define sect4SolenoidPin 43      // Valvula solenoide do setor 4 = pino D43 (escrita)
#define tankFillSolenoidPin 39   // Valvula solenoide de enchimento do tanque com agua da rua = pino D39 (escrita)
#define tankFillRequestPin 38    // Sinal do controlador COEL caso o nivel de agua de chuva da cisterna esteja baixo = pino D38 (leitura)
#define PumpPin 53               // Bomba = pino D53 (escrita)

/*** FIM DA DELCARACAO DA DEFINICAO DE PINAGEM ***/



/*****************************************
 * 03 - DECLARACAO DE VARIAVEIS  GLOBAIS *
 *****************************************/

//  Analogicas ---------------------------------------------------------------------------
unsigned int x = 0;            // Atribui valor inicial 0 para a variavel x que so podera ser positiva
int y = 0;                     // Atribui valor inicial 0 para a variavel y que so podera ser positiva
unsigned int buttonState = 5;  // Declara variavel de botao pressionado [Direita < 100, Cima < 200, Baixo < 400, Esquerda < 600, Select < 800]
float sensRainSize = 0;        // Atribui valor inicial de 0% de chuva para o sensor de Quantidade de Precipitacao
float sensBaro = 0;            // Atribui valor inicial de 0Pa para o sensor de presssao atmosferica
float sensSect1 = 50;          // Atribui valor inicial de 50% para sensor de umidade do Setor 1 (Grama quintal)
float sensSect2 = 50;          // Atribui valor inicial de 50% para sensor de umidade do Setor 2 (Grama rua Sol, vaga coberta)
float sensSect3 = 50;          // Atribui valor inicial de 50% para sensor de umidade do Setor 3 (Grama rua Sol, coqueiro)
float sensSect4 = 0;           // Atribui valor inicial de 50% para sensor de umidade do Setor 4 (Canteiro de Begonias)

//  Digitais ------------------------------------------------------------------------------
int sensRain = false;           // Atribui 'false' (valor 0 = sensor seco) como valor inicial para o sensor de chuva
int sect1Solenoid = false;      // Atribui 'false' (valor 0 = solenoide fechada) como valor inicial para a Valvula solenoide do Sector 1
int sect2Solenoid = false;      // Atribui 'false' (valor 0 = solenoide fechada) como valor inicial para a Valvula solenoide do Sector 2
int sect3Solenoid = false;      // Atribui 'false' (valor 0 = solenoide fechada) como valor inicial para a Valvula solenoide do Sector 3
int sect4Solenoid = false;      // Atribui 'false' (valor 0 = solenoide fechada) como valor inicial para a Valvula solenoide do Sector 4
int tankFillSolenoid = false;   // Atribui 'false' (valor 0 = solenoide fechada) como valor inicial para a Valvula solenoide de preenchimento do tanque com agua da rua
int Pump = false;               // Atribui 'false' (valor 0 = Pump desligada) como valor inicial para a Bomba


/* -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> */
/* -> */
/* -> */// Variaveis determinadas pelo usuario 
/* -> */
/* -> */// Aqui o usuario define diversos parametros do funcionamento do sistema, 
/* -> */// como por exemplo, o horario de acionamento matutino e vespertido da irrigacao, 
/* -> */// tempo que cada setor devera ser irrigado, limites de controle dos diversos
/* -> */// sensores como pressA barometrica, temperatura, quantidade de chuva e umidade
/* -> */// do solo em cada setor para que a irrigacao seja ou nA acionada.
/* -> */
/* -> */
/* -> */uint8_t irrigateClockHourMorning = 18;     // Determina a hora pela manha para que a irrigacao seja acionada                               [formato: 24, horas     [hour]
/* -> */uint8_t irrigateClockMinMorning = 30;      // Determina o minuto pela manha para que a irrigacao seja acionada                             [formato: 60, minutos   [min]
/* -> */uint8_t irrigateClockHourAfternoon = 18;   // Determina a hora pela tarde para que a irrigacao seja acionada                               [formato: 24, horas     [hour]
/* -> */uint8_t irrigateClockMinAfternoon = 30;    // Determina o minuto pela tarde para que a irrigacao seja acionada                             [formato: 60, minutos   [min]
/* -> */uint8_t irrigateDOWMon = 0;    // Para determinar se a irrigacao sera acionada na Segunda colocar 1                                        [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWTue = 2;    // Para determinar se a irrigacao sera acionada na Terca colocar 2                                          [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWWed = 0;    // Para determinar se a irrigacao sera acionada na Quarta colocar 3                                         [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWThu = 0;    // Para determinar se a irrigacao sera acionada na Quinta colocar 4                                         [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWFri = 5;    // Para determinar se a irrigacao sera acionada na Sexta colocar 5                                          [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWSat = 0;    // Para determinar se a irrigacao sera acionada no Sabado colocar 6                                         [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */uint8_t irrigateDOWSun = 7;    // Para determinar se a irrigacao sera acionada no Domingo colocar 7                                        [formato: Mon (1), Tue (2), Wed (3), Thu (4), Fri (5), Sat (6) Sun (7)  [dow]
/* -> */float irrigateTimerSect1 = 60000;     // Determina o tempo de irrigacao do Setor 1 (Grama quintal)                                           [formato: 180000, milisegundos (3min * 60s * 1000)]
/* -> */float irrigateTimerSect2 = 900000;    // Determina o tempo de irrigacao do Setor 2 (Grama rua Sol, vagas)                                    [formato: 180000, milisegundos (3min * 60s * 1000)]
/* -> */float irrigateTimerSect3 = 120000;    // Determina o tempo de irrigacao do Setor 3 (Grama rua Sol, coqueiro)                                 [formato: 180000, milisegundos (3min * 60s * 1000)]
/* -> */float irrigateTimerSect4 = 150000;    // Determina o tempo de irrigacao do Setor 4 (Floreiras)                                               [formato: 180000, milisegundos (3min * 60s * 1000)]
/* -> */int32_t baroRainLimit = 0;                  // Determina a presssao barometrica limite para que se considere que havera chuva              [formato: 101500, Pa (kPa * 1000)]
/* -> */float rainSizeLimit = 0;                    // Determina a quantidade de agua (umidade) no sensor chuva para saber se choveu ou nao        [formato:
/* -> */float ambTempLimit = 0;                     // Determina a temperatura limite para acionar a irrigacao                                     [formato: 23.5, Celcius]
/* -> */float ambHmdtLimit = 0;                     // Determina a umidade limite para acionar a irrigacao                                         [formato:
/* -> */float ambDewPtKimit = 0;                    // Determina o DewPoint limite para acionar a irrigacao (ha presenca de chuva)                 [formato: 17.5, Celcius]
/* -> */float sensHmdtSect1Limit = 0;    // Determina a umidade limite no Setor 1 (quintal) para que a terra seja considerada seca                 [formato:
/* -> */float sensHmdtSect2Limit = 0;    // Determina a umidade limite no Setor 2 (vaga coberta rua Sol) para que a terra seja considerada seca    [formato:
/* -> */float sensHmdtSect3Limit = 0;    // Determina a umidade limite no Setor 3 (coqueiro rua Sol) para que a terra seja considerada seca        [formato:
/* -> */float sensHmdtSect4Limit = 0;    // Determina a umidade limite no Setor 4 (floreira de Begonias) para que a terra seja considerada seca    [formato:
/* -> */
/* -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> -> */

/*** FIM DA DELCARACAO DE VARIAREIS ***/
