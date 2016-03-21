/****************************************************************** 
 * 09 - FUNCAO DE VERIFICACAO DO DIA DA SEMANA (DOW) DA IRRIGACAO * 
 ******************************************************************/

int checkIrrigateDOW(void)
{
  Serial.println ("### 09. Inicia checkIrrigateDOW ###");  // Comentario enviado para Monitor Serial                  
  t = rtc.getTime();                                       // Le dados do DS1302
  Serial.print (t.dow);                                    // Comentario enviado para Monitor Serial 
  Serial.print (" = ");                                    // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWMon);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWTue);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWWed);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWThu);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWFri);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.print (irrigateDOWSat);                           // Comentario enviado para Monitor Serial
  Serial.print (", ");                                     // Comentario enviado para Monitor Serial
  Serial.println (irrigateDOWSun);                         // Comentario enviado para Monitor Serial


  if ((t.dow) == (irrigateDOWMon))    // 1 = MONDAY (Segun da-Feira)
  {
    Serial.println ("return 1");
    return 1;                   
  }      
  else
    if ((t.dow) == (irrigateDOWTue))    // 2 = TUESDAY (Terca-Feira)
    {
      Serial.println ("return 1");
      return 1;                   
    }                          
    else
      if ((t.dow) == (irrigateDOWWed))    // 3 = WEDNESDAY (Quarta-Feira)
      {
        Serial.println ("return 1");
        return 1;                   
      } 
      else
        if ((t.dow) == (irrigateDOWThu))    // 4 = THURSDAY (Qunita-Feira)
        {
          Serial.println ("return 1");
          return 1;                   
        }                               
        else
          if ((t.dow) == (irrigateDOWFri))    // 5 = FRIDAY (Sexta-Feira)
          {
            Serial.println ("return 1");
            return 1;                   
          }                               
          else
            if ((t.dow) == (irrigateDOWSat))    // 6 = SATURDAY (Sabado)
            {
              Serial.println ("return 1");
              return 1;                   
            }                               
            else
              if ((t.dow) == (irrigateDOWSun))    // 7 = SUNDAY (Domingo)
              {
                Serial.println ("return 1");
                return 1;                   
              }                               
  return 0;

  Serial.println(checkIrrigateDOW());                     // Comentario enviado para Monitor Serial
}
/*** FIM DA FUNCAO DE VERIFICACAO DO DIA DA SEMANA (DOW) DA IRRIGACAO ***/

