import flask
import asyncio
import ble
import threading
import shared
from flask_cors import CORS


lock = threading.Semaphore()
ble.BleThread().start()
app = flask.Flask(__name__)
CORS(app)


@app.get('/ping')
def ping():
    loop = asyncio.get_event_loop()
    print(loop)
    return 'pong'


# connection status between rpi and ble device
@app.get('/status')
def status():
    if ble.client == None:
        return {"status": "disconnected"}
    if ble.client.is_connected:
        return {"status": "connected"}
    return {"status": "disconnected"}


@app.get('/open')
async def open():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    lock.acquire()
    shared.clear_queue()
    result = ble.write_command(f"pswd={password} open")
    if not result:
        return {"status": "error", "message": "failed to send command"}

    bt_response = await shared.get_data(timeout=5)
    if bt_response == "timeout":
        lock.release()
        return {"status": "error", "message": "timeout"}
    if bt_response == "wrong-password":
        lock.release()
        return {"status": "error", "message": "wrong password"}
    if bt_response == "ok":
        lock.release()
        return {"status": "success"}


@app.get('/play-melody')
async def play_melody():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    melodyId = args.get('id')

    # check if melodyId is valid
    if melodyId == None:
        return {'status': 'error', 'message': 'missing id'}

    # check if melodyId is a number
    if not melodyId.isdigit():
        return {'status': 'error', 'message': 'id is not a number'}

    lock.acquire()
    shared.clear_queue()
    result = ble.write_command(f'pswd={password} play-melody {melodyId}')
    if not result:
        return {"status": "error", "message": "failed to send command"}

    bt_response = await shared.get_data(timeout=5)
    if bt_response == "timeout":
        lock.release()
        return {'status': 'error', 'message': 'timeout'}
    if bt_response == "wrong-password":
        lock.release()
        return {'status': 'error', 'message': 'wrong password'}
    if bt_response == "ok":
        lock.release()
        return {'status': 'success', 'melodyId': melodyId}


@app.get('/change-password')
async def change_passorwd():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}, 400
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    new_passwd = args.get('new')

    # check if newPasswd is valid
    if new_passwd == None:
        return {'status': 'error', 'message': 'missing new password'}
    if len(new_passwd) != 6 or not new_passwd.isdigit():
        return {'status': 'error', 'message': 'new password should be 6 digits of number'}

    lock.acquire()
    shared.clear_queue()
    result = ble.write_command(f'pswd={password} change-password {new_passwd}')
    if not result:
        return {"status": "error", "message": "failed to send command"}

    bt_response = await shared.get_data(timeout=5)
    if bt_response == "timeout":
        lock.release()
        return {'status': 'error', 'message': 'timeout'}
    if bt_response == "wrong-password":
        lock.release()
        return {'status': 'error', 'message': 'wrong password'}
    if bt_response == "ok":
        lock.release()
        return {'status': 'success'}


@app.get('/set-angle')
async def set_angle():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}, 400
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    angle = args.get('angle')

    # check if angle is valid
    if angle == None:
        return {'status': 'error', 'message': 'missing angle'}
    if not angle.isdigit():
        return {'status': 'error', 'message': 'angle should be a number'}

    # lock.acquire()
    shared.clear_queue()
    result = ble.write_command(f'pswd={password} set-angle {angle}')
    if not result:
        return {"status": "error", "message": "failed to send command"}

    bt_response = await shared.get_data(timeout=5)
    print(bt_response)
    if bt_response == "timeout":
        lock.release()
        return {'status': 'error', 'message': 'timeout'}
    if bt_response == "wrong-password":
        lock.release()
        return {'status': 'error', 'message': 'wrong password'}
    if bt_response == "ok":
        lock.release()
        return {'status': 'success', "angle": angle}


# run
app.run(host='0.0.0.0', port=5001)
