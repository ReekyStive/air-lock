# AirLock

**Open Lock with Siri, Web Browser, or Home Assistant.**

## Firmware

Built with PlatformIO. Powered by Arduino.

The Arduino Nano receives commands from Bluetooth and controls the servo. The servo rotates the door handle through well-designed 3D model.

[Firmware](./firmware)

## API Server

This API server is designed to run on a Raspberry Pi with Bluetooth.

The Raspberry Pi maintains a persistent Bluetooth connection with the Arduino Nano and reconnect immediately after disconnection. It also runs an HTTP server that listens for requests and forwards the commands to the Arduino Nano via Bluetooth.

[API Server](./server)

## Frontend

Built with Vue 3 + TypeScript + Vite + Vuetify, in Material Design by Google.

This is how users interact with AirLock. It is a well-designed web page with smooth UI and UX, and is responsible for interacting with the API server running on Raspberry Pi.

[Frontend](./frontend)

## Documention

[Documention](./docs)

## HomeKit Bridge

// TODO

## Home Assistant Custom Integration

// TODO
