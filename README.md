<div align="center">
    <h1> ESP32-AbsoluteMouse </h1>
</div>

##  About the Project
Using ESP32 as a mouse that receives absolute position as input.

It seems that the direct method to use ESP32 as an absolute mouse is by using the Stylus HID Report Descriptor for iPad. However, I couldn't find it. So I decided to make it with the BLEMouse library.
<br>

## Usage
1. Open OBS Studio, connect with iPad and enable the virtual camera.
2. Run ```absMouse_tester.py```
3. Connect ESP32 with iPad.
4. Wait until "Starting BLE work!" is displayed.
5. Enjoy.
<br>

## Principle
Since the mouse would accelerate with a long range move(), I choped the distance down into small pieces to maintain a relatively stable speed.

After a few seconds of idle, the mouse will automatically move to (0,0) to reset its position, reducing the error produced by repeated movements.
