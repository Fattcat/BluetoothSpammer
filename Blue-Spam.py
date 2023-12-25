# Pride skôr jak žmurkneš 100 000 000 krát ;D
# Som naposal ze pride skorej jak zmurknes tolko krat xD

import bluetooth
import random
import string
import time

def generate_random_name():
    prefix = ['My', 'Dffk', 'SuPPer', 'My']
    suffix = ['HeadSet', '901', 'Phones', 'Ph0n3s1']
    return random.choice(prefix) + ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(3)) + random.choice(suffix)

def fake_bluetooth_devices(num_devices):
    for _ in range(num_devices):
        device_name = generate_random_name()
        server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        port = bluetooth.PORT_ANY

        server_sock.bind(("", port))
        server_sock.listen(1)

        uuid = "00001101-0000-1000-8000-00805F9B34FB"
        bluetooth.advertise_service(server_sock, f"{device_name} Service", service_id=uuid)

        print(f"Waiting for connection on RFCOMM channel {port} for {device_name}")

        try:
            client_sock, client_info = server_sock.accept()
            print(f"Accepted connection from {client_info} for {device_name}")
            client_sock.close()
        except KeyboardInterrupt:
            break

        server_sock.close()

num_fake_devices = 5  # Adjust the number of fake devices as needed
fake_bluetooth_devices(num_fake_devices)
