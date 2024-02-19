import os
from time import sleep
pid = input('server pid ? ')
message = input('message ? ')
for i in range(3):
    ##sleep(0.1)
    os.system(f"./client {pid} {message}")