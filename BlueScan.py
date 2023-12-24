import os
import sys
import platform
import subprocess

def check_sudo():
    # Získajte UID aktuálneho používateľa
    user_id = os.getuid()

    # Overte, či bol skript spustený ako superužívateľ (UID 0)
    if user_id == 0:
        print("Skript bol spustený so sudo.")
    else:
        print("Skript nebol spustený so sudo. Zastavujem...")
        sys.exit(1)

# Zavolajte funkciu pre kontrolu sudo
check_sudo()

# Tu môžete pokračovať so zvyškom vášho skriptu, ktorý vyžaduje oprávnenia superužívateľa.
print("Ďalší kód skriptu môže pokračovať.")


CheckOS = platform.platform()
if CheckOS == "Windows":
  print("cant start on windows :/")
  exit()
elif CheckOS == "Linux":
  pass

def scan_bluetooth_devices():
    try:
        # Spustí príkaz hcitool scan a zachytí výstup
        result = subprocess.run(['sudo', 'hcitool', 'scan'], capture_output=True, text=True, check=True)
        
        # Rozdelí výstup podľa riadkov
        lines = result.stdout.strip().split('\n')
        
        # Preskočí hlavičku výstupu
        devices_info = lines[1:]
        
        # Vytvorí slovník pre uchovanie informácií o zariadeniach
        bluetooth_devices = []
        
        for device_info in devices_info:
            # Rozdelí informácie o zariadení podľa medzier
            device_data = device_info.split('\t')
            
            # Extrahuje meno a MAC adresu zariadenia
            name = device_data[2]
            mac_address = device_data[0]
            
            # Pridá informácie o zariadení do zoznamu
            bluetooth_devices.append({'Name': name, 'MAC Address': mac_address})
        
        return bluetooth_devices
    
    except subprocess.CalledProcessError as e:
        print(f"Chyba pri spustení príkazu: {e}")
        return None

# Získaj informácie o Bluetooth zariadeniach zo skenu
bluetooth_devices = scan_bluetooth_devices()

# Vypíš informácie o zariadeniach
if bluetooth_devices:
    for device in bluetooth_devices:
        print(f"NAME: {device['Name']}")
        print(f"MAC Address: {device['MAC Address']}")
        print("=" * 20)
else:
    print("Neboli nájdené žiadne Bluetooth zariadenia.")
