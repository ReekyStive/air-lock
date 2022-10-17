import flask
import asyncio
import ble


ble.BleThread().start()

app = flask.Flask(__name__)


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
def open():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}, 400
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    result = ble.write_command(f"pswd={password} open")
    if not result:
        return {"status": "failed"}
    return {"status": "success"}


@app.get('/play-melody')
def play_melody():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}, 400
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    melodyId = args.get('id')

    # check if melodyId is valid
    if melodyId == None:
        return {'status': 'error', 'message': 'missing id'}

    # check if melodyId is a number
    if not melodyId.isdigit():
        return {'status': 'error', 'message': 'id is not a number'}

    ble.write_command(f'pswd={password} play-melody {melodyId}')
    return {'status': 'success', 'melodyId': melodyId}


@app.get('/change-password')
def change_passorwd():
    args = flask.request.args
    password = args.get('password')

    if password == None:
        return {"status": "error", "message": "password required"}, 400
    if len(password) != 6 or not password.isdigit():
        return {'status': 'error', 'message': 'password should be 6 digits of number'}

    newPasswd = args.get('new')

    # check if newPasswd is valid
    if newPasswd == None:
        return {'status': 'error', 'message': 'missing new password'}
    if len(newPasswd) != 6 or not newPasswd.isdigit():
        return {'status': 'error', 'message': 'new password should be 6 digits of number'}

    ble.write_command(f'pswd={password} change-password {newPasswd}')
    return {'status': 'success'}


@app.get('/set-angle')
def set_angle():
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

    ble.write_command(f'pswd={password} set-angle {angle}')
    return {'status': 'success', 'angle': angle}


# run
app.run(host='0.0.0.0', port=5001)
