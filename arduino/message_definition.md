# AirLock Message Definition

## Send

```
FF FF FF
Password

FF
Opration: 01 OneClickOpen, 02 SetAngle, 03 PlayMelody, 04 ChangePassword

FF FF FF
Parameters

FF
Additional Information

FF
Verification

EF
End
```

## Receive

```
FF
Response

FF
Verification

EF
End
```

