/******************************************************
 * 10 - FUNCAO DE VERIFICACAO DO HORARIO DA IRRIGACAO *
 ******************************************************/

int checkIrrigateClock(void)
{
  Serial.println ("### 10. Inicia checkIrrigateClock ###");  // Comentario enviado para Monitor Serial
  t = rtc.getTime();                                         // Le dados do DS1302
  Serial.print ("Hora do sistema: ");                        // Comentario enviado para Monitor Serial
  Serial.print (t.hour);                                     // Comentario enviado para Monitor Serial
  Serial.print (":");                                        // Comentario enviado para Monitor Serial
  Serial.println (t.min);                                    // Comentario enviado para Monitor Serial
  Serial.print ("Horario matutino: ");                       // Comentario enviado para Monitor Serial
  Serial.print (irrigateClockHourMorning);                   // Comentario enviado para Monitor Serial
  Serial.print (":");                                        // Comentario enviado para Monitor Serial
  Serial.println (irrigateClockMinMorning);                  // Comentario enviado para Monitor Serial
  Serial.print ("Hora do vespertino: ");                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateClockHourAfternoon);                 // Comentario enviado para Monitor Serial
  Serial.print (":");                                        // Comentario enviado para Monitor Serial
  Serial.println (irrigateClockMinAfternoon);                // Comentario enviado para Monitor Serial  

  if (((((((t.hour) == irrigateClockHourMorning) && (t.min) == irrigateClockMinMorning)) || ((t.hour) == irrigateClockHourAfternoon) && (t.min) == irrigateClockMinAfternoon)))
  {
    Serial.println ("return 1");
    return 1;                   
  }  
  return 0;

  Serial.println(checkIrrigateClock());                      // Comentario enviado para Monitor Serial
}
/*** FIM DA FUNCAO DE HORARIO DA IRRIGACAO ***/

