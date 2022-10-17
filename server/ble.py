import asyncio
import bleak
import threading
import shared


ADDR = "637E29E4-F3F5-9B48-4135-46A48723DD5A"
WRITE_CHAR = "0000FFE1-0000-1000-8000-00805F9B34FB"
NOTIFY_CHAR = "0000FFE1-0000-1000-8000-00805F9B34FB"

client: bleak.BleakClient = None
loop: asyncio.AbstractEventLoop = None


class BleThread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        global loop
        loop = asyncio.new_event_loop()
        loop.run_until_complete(main())


# keep device connected
async def keep_connected():
    while True:
        if not client.is_connected:
            print("device disconnected, reconnecting...")
            try:
                await asyncio.wait_for(client.connect(), timeout=5)
                print("device reconnected")
            except:
                print("device reconnect failed")

        await asyncio.sleep(1)


async def main():
    global client
    client = bleak.BleakClient(ADDR)

    while True:
        try:
            print("[ble] init: connecting to device...")
            await client.__aenter__()
            print("[ble] init: connected")
            await client.start_notify(NOTIFY_CHAR, onreceive)
            break
        except:
            print("[ble] init: connection failed")

    await keep_connected()


def write_command(command: str) -> bool:
    if client == None:
        print("[ble] [error] device is null")
        return False
    if not client.is_connected:
        print("[ble] [error] device not connected")
        return False

    try:
        print("[ble] sending command")
        loop.create_task(
            client.write_gatt_char(WRITE_CHAR, bytearray(command, "utf-8"))
        )
        print("[ble] command sent")
        return True
    except:
        print("[ble] command failed")
        return False


def onreceive(_id, data: bytearray):
    # decode data
    received = data.decode("utf-8").strip()
    print("[ble] received data: " + received)
    shared.put_data(received)


if __name__ == "__main__":
    BleThread().start()
    print("[ble] thread started")
