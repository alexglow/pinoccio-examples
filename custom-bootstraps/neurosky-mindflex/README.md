Here's my complete tutorial on [hacking a NeuroSky MindFlex headset](http://www.hackster.io/glowascii/mesh-your-brain) so you can control things with your brain!

Copy this MyBrain folder to your /Arduino folder, where you keep your sketches. Open it in the Arduino IDE and upload it. (This takes a little longer than a regular Arduino sketch—just be patient!)

###Library
This is based on kitschpatrol's [Brain](https://github.com/kitschpatrol/Brain) library, which you'll need to install first. Download it and add it to your /Arduino/libraries folder, and restart the Arduino IDE if you had it open.

###ScoutScript Examples

Enter these functions in the Arduino IDE, or in [Pinoccio HQ](http://hq.pinocc.io), to see some cool stuff happen.

####Signal Strength LED Meter
```
function sigled {
s = brain.signal;
b = (s * 5) / 4;
b = 250 - b;
print b;
led.setrgb(0,0,b);
}
```

The MindFlex gives you a signal strength value from 0-200. 0 means that you have perfect connectivity between the headset and your head, and data are flowing. 200 means no connectivity. This takes the signal value, multiplies it by 1.25 to normalize it to 0-250 (approximately the brightness range of the LED), reverses it (so that the LED glows brighter as signal strength improves), and sets the torch LED to blue at that brightness.

Run this once per second (`run sigled, 1000`) to get visual feedback on the signal strength.

####External Attention LED Meter
You can combine that example with another Scout that shows your attention reading. On your MindFlex-connected scout, create a function to pull this value, and run it once per second:
```
function sendatt { a = brain.attention; mesh.announce(1,a); };
run sendatt, 1000;
```

On the "display" Scout, store this:
```
function on.message.group {
	a = arg(3);
	a = (a/2) * 5;
	led.setrgb(0,0,a);
}
```

As you can see, it's a little easier to work with the 0-100 attention value (where 100 is the best).