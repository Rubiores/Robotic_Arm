#include <Arduino.h>
#include <ESP32Servo.h>

// Crear objetos servo
Servo servos[6];

// Definir los pines de los servos
int servoPins[] = {13, 27, 26, 25, 33, 32}; // Pines seleccionados para la ESP32

// Definir la posición "home" (ajusta los ángulos según sea necesario)
int homeAngles[] = {0, 0, 0, 0, 0, 0}; // Ejemplo de ángulos de la posición "home" en grados

// Pin para LED de depuración
const int debugLED = 2; // Usaremos el pin 2 para un LED de depuración

bool commandInProgress = false;

void setup() {
    Serial.begin(112500); // Inicializar el puerto serie

    // Inicializar los servos
    for (int i = 0; i < 6; i++) {
        servos[i].attach(servoPins[i]);
    }

    // Configurar el pin del LED como salida
    pinMode(debugLED, OUTPUT);
    digitalWrite(debugLED, LOW); // Apagar el LED inicialmente
}

void loop() {
    if (Serial.available() && !commandInProgress) {
        // Leer la cadena de ángulos o comando
        String input = Serial.readStringUntil('\n');
        input.trim(); // Eliminar espacios en blanco al inicio y al final

        // Limpiar la cadena de entrada eliminando caracteres no necesarios
        input.replace("[", "");
        input.replace("]", "");
        input.replace(" ", ""); // Eliminar espacios en blanco

        commandInProgress = true; // Indicar que un comando está en progreso

        if (input == "home") {
            // Mover los servos a la posición "home"
            for (int i = 0; i < 6; i++) {
                servos[i].write(homeAngles[i]);
                delay(100); // Esperar 100 ms entre cada servo
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
                delay(100); // Ajustar según se considere esperar ms entre cada movimiento del servo
            }
        }

        commandInProgress = false; // Indicar que el comando ha finalizado
    }
}