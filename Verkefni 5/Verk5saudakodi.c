int threshold = 505;
while(true)
  {
    // Hægri sensor er á linu
    if(SensorValue(lineFollowerRIGHT) > threshold)
    {
    // Örlítið til hægri
    }
    // Miðju sensor er á línu
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
    // Beint áfram
    }
    // Vinsti sensor er á líu
    if(SensorValue(lineFollowerLEFT) > threshold)
    {
    // Örlítið til vinstri
    }
}
