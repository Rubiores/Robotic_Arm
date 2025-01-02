#include <Arduino.h>
#include <Servo.h>

// Crear objetos servo
Servo servos[6];

// Definir los pines de los servos
int servoPins[] = {2, 3, 4, 5, 6, 7};

// Definir la posición "home" (ajusta los ángulos según sea necesario)
int homeAngles[] = {0, 0, 0, 0, 0, 0}; // Ejemplo de ángulos de la posición "home" en grados

void setup() {
  Serial.begin(9600);

  // Inicializar los servos
  for (int i = 0; i < 6; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  if (Serial.available()) {
    // Leer la cadena de ángulos o comando
    String input = Serial.readStringUntil('\n');
    input.trim(); // Eliminar espacios en blanco al inicio y al final

    // Limpiar la cadena de entrada eliminando caracteres no necesarios
    input.replace("[", "");
    input.replace("]", "");
    input.replace(" ", ""); // Eliminar espacios en blanco

    if (input == "home") {
      // Mover los servos a la posición "home"
      for (int i = 0; i < 6; i++) {
        servos[i].write(homeAngles[i]);
        delay(100); // Esperar 500 ms entre cada servo
      }
    } else {
      // Dividir la cadena por comas y convertir a enteros
      int angles[6] = {0, 0, 0, 0, 0, 0}; // Inicializar con ángulos en 0
      int startIndex = 0;
      int commaIndex = input.indexOf(',');
      for (int i = 0; i < 6; i++) {
        if (commaIndex == -1) { // Si no hay más comas, tomar el resto de la cadena
          angles[i] = round(input.substring(startIndex).toFloat());
          break;
        } else {
          angles[i] = round(input.substring(startIndex, commaIndex).toFloat());
          startIndex = commaIndex + 1;
          commaIndex = input.indexOf(',', startIndex);
        }
      }

      // Mover los servos a los ángulos recibidos
      for (int i = 0; i < 6; i++) {
        if (angles[i] >= 0 && angles[i] <= 180) { // Verificar que el ángulo esté en el rango válido
          servos[i].write(angles[i]);
        }
        delay(100); // Ajustar segun se considere esperar ms entre cada movimiento del servo
      }
    }
  }
}