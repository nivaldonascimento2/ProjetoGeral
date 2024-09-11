const int stepPinA = 3;    // Pino STEP do Motor A
const int dirPinA = 4;     // Pino DIR do Motor A

const int stepPinB = 5;    // Pino STEP do Motor B
const int dirPinB = 6;     // Pino DIR do Motor B

const int stepPinC = 7;    // Pino STEP do Motor C
const int dirPinC = 8;     // Pino DIR do Motor C

const int enablePin = 11;  // Pino ENABLE compartilhado para todos os motores

// Definição dos pinos dos botões
const int buttonPin1 = 2;
const int buttonPin2 = 9;
const int buttonPin3 = 10;

void setup() {
  // Configura os pinos dos motores como saída
  pinMode(stepPinA, OUTPUT);
  pinMode(dirPinA, OUTPUT);
  
  pinMode(stepPinB, OUTPUT);
  pinMode(dirPinB, OUTPUT);
  
  pinMode(stepPinC, OUTPUT);
  pinMode(dirPinC, OUTPUT);
  
  // Configura o pino ENABLE como saída
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // Ativa todos os drivers
  
  // Configura os pinos dos botões como entrada com pull-up interno
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void loop() {
  // Leitura dos botões
  bool botao1Pressionado = (digitalRead(buttonPin1) == LOW);
  bool botao2Pressionado = (digitalRead(buttonPin2) == LOW);
  bool botao3Pressionado = (digitalRead(buttonPin3) == LOW);

  if (botao1Pressionado) {
    // Botão 1 pressionado: Motor A horário e Motor B anti-horário
    controlarMotoresAB(HIGH, LOW);
  } 
  else if (botao2Pressionado) {
    // Botão 2 pressionado: Motor A anti-horário e Motor B horário
    controlarMotoresAB(LOW, HIGH);
  } 
  else {
    // Nenhum botão 1 ou 2 pressionado
    pararMotoresAB();
  }
  
  // Controle do Motor C
  if (botao3Pressionado) {
    // Botão 3 pressionado: Motor C horário
    controlarMotorC(HIGH);
  } 
  else {
    // Botão 3 não pressionado: Motor C anti-horário
    controlarMotorC(LOW);
  }
}

// Função para controlar os Motores A e B simultaneamente
void controlarMotoresAB(bool sentidoA, bool sentidoB) {
  digitalWrite(dirPinA, sentidoA);
  digitalWrite(dirPinB, sentidoB);

  for (int i = 0; i < 200; i++) { // Ajuste o número de passos conforme necessário
    digitalWrite(stepPinA, HIGH);
    digitalWrite(stepPinB, HIGH);
    delayMicroseconds(1000);      // Ajuste a velocidade dos passos
    digitalWrite(stepPinA, LOW);
    digitalWrite(stepPinB, LOW);
    delayMicroseconds(1000);      // Ajuste a velocidade dos passos
  }
}

// Função para controlar o Motor C
void controlarMotorC(bool sentido) {
  digitalWrite(dirPinC, sentido);

  for (int i = 0; i < 200; i++) { // Ajuste o número de passos conforme necessário
    digitalWrite(stepPinC, HIGH);
    delayMicroseconds(1000);      // Ajuste a velocidade dos passos
    digitalWrite(stepPinC, LOW);
    delayMicroseconds(1000);      // Ajuste a velocidade dos passos
  }
}

// Função para parar os Motores A e B
void pararMotoresAB() {
  digitalWrite(stepPinA, LOW);
  digitalWrite(stepPinB, LOW);
}