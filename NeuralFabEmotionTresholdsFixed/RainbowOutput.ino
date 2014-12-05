

void tasteTheRainbow(InternalState state) {
  switch (state) {
    case ANXIOUS:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
    break;
    
    case HAPPY:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
    break;
    
    case RELAXED:
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, HIGH);
    break;
    
    case DROWSY:
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
    break;
    
    default:
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
    break;
  }
}

