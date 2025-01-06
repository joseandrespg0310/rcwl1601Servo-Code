#include <Servo.h>

// Pines del sensor RCWL-1601
const int trigPin = 8; // Pin TRIG conectado al pin digital 8
const int echoPin = 7; // Pin ECHO conectado al pin digital 7

// Pin del servomotor
const int servoPin = 9;

// Pin del LED
const int led = 6; // Pin donde estará conectado el LED

// Crear objeto servo
Servo myServo;

// Distancia mínima para activar el servo (en cm)
const int activationDistance = 10;

void setup() {
  // Configurar pines del sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configurar el pin del LED como salida
  pinMode(led, OUTPUT);

  // Encender el LED de forma permanente
  digitalWrite(led, HIGH);

  // Iniciar comunicación serial para depuración
  Serial.begin(9600);
  Serial.println("Inicializando sistema...");

  // Configurar el servo
  myServo.attach(servoPin);
  myServo.write(0); // Servo en posición inicial
}

void loop() {
  // Lógica del sensor ultrasonido
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Máximo 30ms para eco
  if (duration == 0) {
    Serial.println("Error: No se detecta señal del sensor.");
    delay(100);
    return;
  }

  int distance = duration * 0.034 / 2;

  // Verificar si la distancia está dentro del rango
  if (distance > 0 && distance <= activationDistance) {
    Serial.print("Objeto detectado a ");
    Serial.print(distance);
    Serial.println(" cm. Activando servo...");

    // Activar el servo (giro a 90 grados)
    myServo.write(90);
    delay(1000);
  } else {
    Serial.println("No se detecta objeto cercano. Servo apagado.");
    myServo.write(0); // Apagar el servo (posición inicial)
  }

  // Añadir un pequeño retraso antes de la siguiente medición
  delay(100);
}
