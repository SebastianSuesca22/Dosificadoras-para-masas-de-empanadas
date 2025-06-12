        // Definir pines para el motor NEMA 23
#define STEP_PIN 12 // CLK rojo
#define DIR_PIN 13 // CM O CW cafe
#define ENABLE_PIN 7// EN
//3.3 VOL PIN DE DRIVER QUE DICE 5V

// Definir pin para el sensor de proximidad infrarrojo
#define SENSOR_PIN 9 //AZUL GND, CAFE 5V, NEGRO PIN SEÑAL

      
// Definir variables para el control del motor
bool motorActivado = false;
int pasosPorVuelta = 20000; // Número de pasos para una vuelta completa
int pasosHechos = 0;

void setup() {
  // Configurar pines como salidas
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Configurar pin del sensor como entrada
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  // Deshabilitar el motor al inicio
  digitalWrite(ENABLE_PIN, HIGH);

  // Establecer velocidad del motor
  // Puedes ajustar la velocidad según tus necesidades
  // Mayor delayMicroseconds indica menor velocidad
  // Menor delayMicroseconds indica mayor velocidad
  // Debes ajustar esta velocidad según tu motor y requerimientos
  // Este valor funciona como punto de partida
  delayMicroseconds(200);
}

void loop() {
  // Leer el valor del sensor de proximidad
  int distancia = digitalRead(SENSOR_PIN);

  // El sensor NPN está normalmente en alto cuando no detecta nada
  // Cuando detecta un objeto, se pone en bajo
  // Verificar si el sensor ha detectado algo (está en bajo)
  if (distancia == LOW && !motorActivado) {
    // Activar el motor
    motorActivado = true;
    digitalWrite(DIR_PIN, LOW); // Establecer la dirección del motor
  }

  // Controlar el motor
  if (motorActivado) {
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(15.5); // Controla la velocidad del motor
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(15.5); // Controla la velocidad del motor
    pasosHechos++;
    

    // Comprobar si el motor ha dado una vuelta completa
    if (pasosHechos >= pasosPorVuelta) {
      pasosHechos = 0; // Reiniciar el contador de pasos
      motorActivado = false; // Desactivar el motor después de una vuelta completa
    }
  } else {
    // Desactivar el motor cuando no se necesita
    digitalWrite(ENABLE_PIN, HIGH);
  }
}
