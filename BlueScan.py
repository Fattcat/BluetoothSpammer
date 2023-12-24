import os
import time
import subprocess
import platform

CheckSUDO = os.getuid()
if CHeckSUDO != 0:
  print("Cant start without sudo permission")
  print("Please run script like this : sudo python3 BlueScan.py")
else:
  pass
CheckOS = platform.platform()
if CheckOS == "Windows":
  print("cant start on windows :/")
  exit()
elif CheckOS == "Linux":
  pass


Scan = subprocess.run(["sudo ","hcitool", "scan"], capture_file=True, text=True,check=True)
  
