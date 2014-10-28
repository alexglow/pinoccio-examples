Adafruit's [NeoPixels](http://www.adafruit.com/category/168) come in a number of forms. I was using an [8-pixel stick](http://www.adafruit.com/product/1426), so my Bootstrap sketch is customized for that.

Copy this MyPinoccioPixels folder to your /Arduino folder, where you keep your sketches. Open it in the Arduino IDE and upload it. (This takes a little longer than a regular Arduino sketch—just be patient!)

###Library
This is based on Hector's [NeoPixelStripAnimator](https://github.com/urtubia/NeoPixelStripAnimator) library for Pinoccio, which you'll need to install first. Download it and add it to your /Arduino/libraries folder, and restart the Arduino IDE if you had it open.

###ScoutScript Examples

Enter these functions in the Arduino IDE, or in [Pinoccio HQ](http://hq.pinocc.io), to see some cool stuff happen.

####Constant Fade

`function fade { pixels.greenwipe; scout.delay(2500, "pixels.bluewipe"); scout.delay(5000, "pixels.redwipe");};`

Run this once every 7500 ms, so that you get a constant flow of green -> red -> blue:

`run fade, 7500;`

If you put it behind a diffuser, you'll get a great color fade, which repeats every 7 1/2 seconds.