import os
import time
import subprocess
import platform

CheckOS = platform.platform()
if CheckOS == "Windows":
  print("cant start on windows :/")
  exit()
elif CheckOS == "Linux":
  pass


Scan = subprocess.run(["sudo ","hcitool", "scan"], capture_file=True, text=True,check=True)
  
