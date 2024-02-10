// Incluindo a biblioteca do sensor de temperatura
#include <DHT.h>

// Definindo o pino do sensor de temperatura
#define DHTPIN 2

// Definindo o tipo do sensor de temperatura (DHT11 ou DHT22)
#define DHTTYPE DHT11

// Definindo os pinos para o motor, LED e buzina
#define MOTOR_PIN 3
#define LED_PIN 4
#define BUZZER_PIN 5

// Inicializando o sensor de temperatura
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializando o monitor serial
  Serial.begin(9600);

  // Inicializando o sensor de temperatura
  dht.begin();

  // Configurando os pinos como saída
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Fazendo a leitura da temperatura
  float temperatura = dht.readTemperature();

  // Verificando se a leitura foi bem-sucedida
  if (isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor de temperatura!");
    return;
  }

  // Imprimindo a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Verificando se a temperatura está acima de 30 °C
  if (temperatura >= 30) {
    // Acionando o motor do ventilador
    digitalWrite(MOTOR_PIN, HIGH);
  } else {
    // Desligando o motor do ventilador
    digitalWrite(MOTOR_PIN, LOW);
  }

  // Verificando se a temperatura ultrapassa os 50 °C
  if (temperatura > 50) {
    // Acionando o LED vermelho
    digitalWrite(LED_PIN, HIGH);
    // Acionando a buzina
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000); // Atraso para evitar a ativação repetida da buzina
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    // Desligando o LED vermelho
    digitalWrite(LED_PIN, LOW);
  }

  // Aguardando um intervalo de 2 segundos antes da próxima leitura
  delay(2000);
}
