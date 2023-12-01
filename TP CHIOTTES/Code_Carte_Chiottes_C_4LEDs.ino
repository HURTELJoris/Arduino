 // Code C++
//
int val = 0;  // Variable pour stocker la valeur de la distance de l'ultrason

int pot = 0;  // Variable pour stocker la lecture analogique du potentiomètre

// Fonction pour lire la distance d'un capteur ultrasonique
// Paramètres :
//   triggerPin - la broche pour déclencher le capteur ultrasonique
//   echoPin - la broche pour lire l'écho du capteur ultrasonique
// Renvoie :
//   Le temps de parcours de l'onde sonore en microsecondes


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Définir la broche de déclenchement en sortie
  digitalWrite(triggerPin, LOW);  // Effacer le déclenchement
  delayMicroseconds(2);

  // Met la broche de déclenchement à l'état HIGH pendant 10 microsecondes
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);  // Définir la broche d'écho en entrée

  // Lire la broche d'écho et renvoyer le temps de parcours de l'onde sonore en microsecondes
  return pulseIn(echoPin, HIGH);
}


void setup()
{
  Serial.begin(9600);  // Initialiser la communication série à un débit de 9600 bauds
  pinMode(A1, INPUT);  // Définir la broche A1 en entrée pour le potentiomètre
  pinMode(4, OUTPUT);  // Définir la broche 4 en sortie pour la LED de pompage de l'eau
  pinMode(5, OUTPUT);  // Définir la broche 5 en sortie pour la LED de pollution de l'eau
  pinMode(6, OUTPUT);  // Définir la broche 6 en sortie pour la LED1
  pinMode(7, OUTPUT);  // Définir la broche 7 en sortie pour la LED2
}


void loop()
{
  val = 0.01723 * readUltrasonicDistance(3, 2);  // Convertir la lecture du capteur ultrasonique en centimètres
  Serial.print(val);  // Afficher la valeur de la distance
  Serial.println(" cm");  // Afficher les unités
  pot = analogRead(A1);  // Lire la valeur analogique du potentiomètre
  Serial.println(pot);  // Afficher la valeur du potentiomètre

  if (pot < 512) {
    // Si la valeur du potentiomètre est inférieure à 512, activer la LED de pollution
    digitalWrite(5, HIGH);
    if (val < 50) {

      // Si la distance est inférieure à 50 cm, activer la LED1
      digitalWrite(6, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH);

    } else {
      // Si la distance est de 50 cm ou plus, activer la LED2
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(4, LOW);
    }

  } else {
    digitalWrite(5, LOW);
	digitalWrite(4, LOW);
    if (val < 50) {

      // Si la distance est inférieure à 50 cm, activer la LED1
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);

    } else {
      // Si la distance est de 50 cm ou plus, activer la LED2
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
    }

  }
  delay(500);
}
