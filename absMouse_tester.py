import cv2 
import serial
import time

PICTURE_X_MIN = 175
PICTURE_X_MAX = 1105
PICTURE_Y_MIN = 35
PICTURE_Y_MAX = 685
INPUT_MAX_X = 1460
INPUT_MAX_Y = 1000
PORT = "COM3"

def connectSerial():
    s = None
    try:
        s = serial.Serial(port=PORT, baudrate=115200, timeout=.1)
        print("Opened COM")
    except:
        print("Cannot open port COM")
    return s

def map(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

lastMoveTime = 0
def onMouse(event, x, y, flags, param):
    global lastMoveTime, s
    # If out of boundary, return
    if max(min(x,PICTURE_X_MAX), PICTURE_X_MIN) != x or \
       max(min(y,PICTURE_Y_MAX), PICTURE_Y_MIN) != y:
        return
    
    x = int(map(x, PICTURE_X_MIN, PICTURE_X_MAX, 0, INPUT_MAX_X))
    y = int(map(y, PICTURE_Y_MIN, PICTURE_Y_MAX, 0, INPUT_MAX_Y))
    y = abs(y - INPUT_MAX_Y)
    if event == cv2.EVENT_LBUTTONDOWN:       
        param["serial"].write(str.encode(f"p{x},{y}:"))
        print(f"Button Down:\t{x}\t{y}")   
    elif event == cv2.EVENT_LBUTTONUP:       
        param["serial"].write(str.encode(f"r{x},{y}:"))
        print(f"Button Up:\t{x}\t{y}")  
    elif flags == cv2.EVENT_FLAG_LBUTTON:
        if time.time() - lastMoveTime < 0.1:
            return
        param["serial"].write(str.encode(f"m{x},{y}:"))
        lastMoveTime = time.time()
        print(f"Mouse Move:\t{x}\t{y}")

def main():
    global s
    cap = cv2.VideoCapture(3)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
    s = connectSerial()
    if cap is None or s is None: 
        return
    
    while(True): 	
        data = s.read_all()
        if data: print(data.decode('utf-8'))
        ret, frame = cap.read() 
        cv2.imshow('frame', frame) 
        cv2.setMouseCallback('frame', onMouse, {"serial": s})	
        if cv2.waitKey(1) & 0xFF == ord('q'): 
            break

    cap.release() 
    cv2.destroyAllWindows() 
    s.close()

if __name__ == "__main__":
    main()