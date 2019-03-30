needs to write ```void* __dso_handle;``` on every program that includes libraries
risk5 pins don't always provide enough voltage for sensors
sda and scl ports on risk5 don't work properly
the screen print function takes char* and not string
doesn't work with casting only takes real variables for example:
```
lcd.print((byte)r);
```
doesn't work

```
byte r = 5;
lcd.print(r);
```
does work

sprintf doesn't work
String doesn't work