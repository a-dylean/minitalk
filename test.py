import os
from time import sleep
pid = input('server pid ? ')
message = input('message ? ')
for i in range(2000):
    sleep(0.1)
    os.system(f"./client_bonus {pid} {message}")