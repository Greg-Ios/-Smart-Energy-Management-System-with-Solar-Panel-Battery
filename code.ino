// Pins
const int solarPin = A0;    // Αναλογική είσοδος για ηλιακό πάνελ
const int battPin = A1;     // Αναλογική είσοδος για μπαταρία
const int relayPin = 8;     // Ψηφιακή έξοδος για ρελέ

// Όρια τάσης (σε Volts)
const float battMin = 11.0;   // Ελάχιστη τάση μπαταρίας για τροφοδοσία φορτίου
const float battMax = 13.0;   // Μέγιστη (πλήρως φορτισμένη)
const float solarThreshold = 12.0; // Ελάχιστη τάση από ηλιακό πάνελ για φόρτιση

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Αρχικά κλειστό το φορτίο
}

float readVoltage(int pin, float R1=10000.0, float R2=2000.0) {
  // Μετράμε την τάση με διαιρέτη τάσης (R1 και R2) και αναγωγή
  int raw = analogRead(pin);
  float voltage = raw * (5.0 / 1023.0);
  voltage = voltage * ((R1 + R2) / R2);
  return voltage;
}

void loop() {
  float solarV = readVoltage(solarPin);
  float battV = readVoltage(battPin);

  Serial.print("Solar Voltage: "); Serial.print(solarV); Serial.print(" V\t");
  Serial.print("Battery Voltage: "); Serial.print(battV); Serial.println(" V");

  // Αν η μπαταρία έχει αρκετή φόρτιση και το ηλιακό πάνελ δίνει ενέργεια, ανάβουμε το φορτίο
  if (battV > battMin && solarV > solarThreshold) {
    digitalWrite(relayPin, HIGH);
    Serial.println("Load ON");
  } else {
    digitalWrite(relayPin, LOW);
    Serial.println("Load OFF");
  }

  delay(2000);
}
