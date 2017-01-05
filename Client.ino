/*
    Devnath Nair, December 25th 2016, 
    Demonstrates a simple TCP/IP Link enabling two Arduino's to talk to each other using 
    the extremely cheap and versatile ESP8266 Wifi modules. Does not use the ESP8266 Core Library.
    */
 
 
    #include <SoftwareSerial.h>
    
    #define DEBUG true
    
    SoftwareSerial esp8266(2,3); //Communicates with the ESP on pins 2 and 3 (RX and TX)
    const int espReset = 4; //Pin that resets the ESP when it's set to LOW. 3.3v HIGH for normal operation.
        
        void setup()
    {
      //Reset the ESP8266
      pinMode(espReset, OUTPUT);
      digitalWrite(espReset, HIGH);
      Serial.begin(9600);
      Serial.println("Resetting the ESP8266 in 3");
      delay(1000);
      Serial.println("2");
      delay(1000);
      Serial.println("1");
      delay(1000);
      Serial.println("Reset in Progress");
      digitalWrite(espReset, LOW);
      delay(1000);
      digitalWrite(espReset, HIGH);
      Serial.println("Reset Successfully.");      
      
      //Connect to the Server ESP8266
      
      esp8266.begin(9600); // Baud rate of the ESP. I set mine to 9600 for lesser transmission errors.
      Serial.println("Connecting to Server ESP8266");
      sendData("AT+CWJAP=\"ESP_F45BEE\",\"\"",1000,DEBUG); //Sending AT command to the ESP with Server network Credentials. 
      delay(10000);
      sendData("AT+CIFSR\r\n",1000,DEBUG); // Get's the IP adress assigned to it by the Server ESP.
    }
     
    void loop()
    {
      //Sending a bunch of text strings. Nothing Special. 
 
        Serial.println("Initializing TCP Link");
        String cipStart = "AT+CIPSTART=\"TCP\",\"192.168.4.1\",333\r\n";
        String ciptext0 = "Merry Christmas Zine Team !\r\n\r\n";
        String ciptext1 = "And Happy Holidays!\r\n\r\n";
        String cipSend = "AT+CIPSEND=";
        String cipSend2 = "AT+CIPSEND=";
        cipSend += ciptext0.length(); 
        cipSend += "\r\n"; //Neatness.
        cipSend2 += ciptext1.length();
        cipSend2 += "\r\n";
        String cipClose = "AT+CIPCLOSE\r\n";
        sendData(cipStart,1000,DEBUG); //Opens a TCP connection with the Server ESP.
        sendData(cipSend,1000,DEBUG);  //Tells the ESP of the length of the string.
        sendData(ciptext0,1000,DEBUG); //Sends a string.
        sendData(cipSend2,1000,DEBUG); //Tells the ESP of the length of the string.
        sendData(ciptext1,1000,DEBUG); //Sends a string.
        sendData(cipClose,1000,DEBUG); //Finally close the TCP connection after data transmission.
           
    }
     
     
    String sendData(String command, const int timeout, boolean debug) //Rememver that sendData string? We define it here.
    {
        String response = "";
        
        esp8266.print(command); // Sends the character to the ESP.
        
        long int time = millis();
        
        while( (time+timeout) > millis())
        {
          while(esp8266.available())
          {
           
           //We need to display what our ESP said and print it in the Serial Monitor.
            
            char c = esp8266.read(); // read the next character.
            response+=c;
          }  
        }
        
        if(debug)
        {
          Serial.print(response); //Self Explanatory. 
        }
        
        return response;
    }
