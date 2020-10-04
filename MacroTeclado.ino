#include "Keyboard.h"

int modePushCounter = 0;   // Contador del número de veces que el botón de modo es presionado
int buttonState = 0;         // Estado actual del botón de modo
int lastButtonState = 0;     // Estado anterior o previo del botón de modo

// Pines pertenecientes a cada boton
const int ModeButton = 2;    // El pin al que está conectado el botón de modo (color NEGRO)
const int VERDE = 3;
const int AMA = 4;
const int ROJO1 = 5;
const int ROJO2 = 6;
const int ROJO3 = 7;
const int AMA1 = 8;
const int AMA2 = 9;
const int AMA3 = 15;
const int LED1 = 16;
const int LED2 = 10;


void setup() {
  // Hacer los pines de los botones entradas y encender el modo pull-up para que esten en valor alto hasta que 
  // sean conectados a tierra al presionarlos: El modo pull up sirve para no utilizar resistencias externes y en cambio utilizar las resistencias internas del arduino
  pinMode(ModeButton, INPUT_PULLUP);
  pinMode(VERDE, INPUT_PULLUP);
  pinMode(AMA, INPUT_PULLUP);
  pinMode(ROJO1, INPUT_PULLUP);
  pinMode(ROJO2, INPUT_PULLUP);
  pinMode(ROJO3, INPUT_PULLUP);
  pinMode(AMA1, INPUT_PULLUP);
  pinMode(AMA2, INPUT_PULLUP);
  pinMode(AMA3, INPUT_PULLUP);

  //Fijar los LED como salidas digitales
  
  pinMode(LED1, OUTPUT);digitalWrite(LED1, LOW);
  pinMode(LED2, OUTPUT);digitalWrite(LED2, LOW);

  //Comenzar el modo teclado
  
  Keyboard.begin();
}

void loop() {

 checkModeButton(); //Revisar el estado del botón

 switch (modePushCounter) { // Cambios de modos o configuraciones de los teclados:
    case 0:  //  MODO 0
      digitalWrite(LED1,LOW); digitalWrite(LED2,LOW); //Los LED apagados indican que se esta en el primer modo

      if (digitalRead(VERDE) == LOW){ //Para abrir OBS
        
        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ALT); Keyboard.press('o');
        delay(100);
        Keyboard.releaseAll();
        delay(1000);

        }

        else if (digitalRead(AMA) == LOW){ //Para abrir Spotify

        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ALT); Keyboard.press('p');
        delay(100);
        Keyboard.releaseAll();
        delay(1000);
        
          }

        else if (digitalRead(ROJO1) == LOW){ //Para moverte al escritorio izquierdo
          
          Keyboard.press(KEY_LEFT_GUI); Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ARROW);
          delay(100);
          Keyboard.releaseAll();
          delay(1000);
          }

        else if (digitalRead(ROJO2) == LOW){ //Para crear un nuevo escritorio

          Keyboard.press(KEY_LEFT_GUI); Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('d');
          delay(100);
          Keyboard.releaseAll();
          delay(1000);
          
          }

        else if (digitalRead(ROJO3) == LOW){ //Para moverte al escritorio izquierdo
          
          Keyboard.press(KEY_LEFT_GUI); Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_RIGHT_ARROW);
          delay(100);
          Keyboard.releaseAll();
          delay(1000);
          
          }

        else if (digitalRead(AMA1) == LOW){ //Copiar

          Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('c');
          delay(100);
          Keyboard.releaseAll();
          delay(500);
          
          }

        else if (digitalRead(AMA2) == LOW){ //Pegar

          Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('v');
          delay(100);
          Keyboard.releaseAll();
          delay(500);
          
          }

        else if (digitalRead(AMA3) == LOW){ //Para iniciar transmisión

          Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('s');
          delay(100);
          Keyboard.releaseAll();
          delay(500);

          }


      

    break;

    case 1:

      digitalWrite(LED1,HIGH); digitalWrite(LED2,LOW); //indicate what mode is loade

    break;

    case 2:

      digitalWrite(LED1,LOW); digitalWrite(LED2,HIGH); //indicate what mode is loade

    break;

    case 3:

      digitalWrite(LED1,HIGH); digitalWrite(LED2,HIGH); //indicate what mode is loade

    break;
  }
}

void checkModeButton(){
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) { // Compara el estado del botón con su estado previo. Si el estado cambió incrementa el contador
    if (buttonState == LOW) { // Si el estado del botón es bajo (si se presiona el botón de modo) comienza el ciclo de conteo 
      modePushCounter++;
      Serial.println("pressed");
      Serial.print("number of button pushes: ");
      Serial.println(modePushCounter);
    } 
    delay(50); // Retrazo para evitar el rebote del botón
  }
  lastButtonState = buttonState; // Guarda el estado actual como el último estado del botón para el siguiente ciclo
   if (modePushCounter >3){ //Reinicia el contador despues de presionar el botón de modo 4 veces (recuerden que se comienza a contar desde el 0)
      modePushCounter = 0;}
}
