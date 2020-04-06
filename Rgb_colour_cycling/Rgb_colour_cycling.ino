int x=1;
unsigned int r, g, b;
int fadeAmount=1;
void setup() {
  // put your setup code here, to run once:
  pinMode (3, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  HSBToRGB (x, 255, 255, &r, &g, &b);
  analogWrite (3, r);
  analogWrite (5, g);
  analogWrite (6, b);
  x=x+fadeAmount;
  delay(45);
  if(x>255){x=0;}
    if (x <= 0 || x >= 255) {
    fadeAmount = -fadeAmount;
  }
}


void
HSBToRGB (unsigned int inHue, unsigned int inSaturation,
    unsigned int inBrightness, unsigned int *oR, unsigned int *oG,
    unsigned int *oB)
{
  if (inSaturation == 0)
    {
      // achromatic (grey)
      *oR = *oG = *oB = inBrightness;
    }
  else
    {
      unsigned int scaledHue = (inHue * 6);
      unsigned int sector = scaledHue >> 8; // sector 0 to 5 around the color wheel
      unsigned int offsetInSector = scaledHue - (sector << 8);  // position within the sector
      unsigned int p = (inBrightness * (255 - inSaturation)) >> 8;
      unsigned int q =
  (inBrightness * (255 - ((inSaturation * offsetInSector) >> 8))) >> 8;
      unsigned int t =
  (inBrightness *
   (255 - ((inSaturation * (255 - offsetInSector)) >> 8))) >> 8;

      switch (sector)
  {
  case 0:
    *oR = inBrightness;
    *oG = t;
    *oB = p;
    break;
  case 1:
    *oR = q;
    *oG = inBrightness;
    *oB = p;
    break;
  case 2:
    *oR = p;
    *oG = inBrightness;
    *oB = t;
    break;
  case 3:
    *oR = p;
    *oG = q;
    *oB = inBrightness;
    break;
  case 4:
    *oR = t;
    *oG = p;
    *oB = inBrightness;
    break;
  default:    // case 5:
    *oR = inBrightness;
    *oG = p;
    *oB = q;
    break;
  }
    }
}
