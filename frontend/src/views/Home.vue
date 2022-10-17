<script setup lang="ts">
import { ref } from 'vue';
import * as api from '../utils/api'

const openLoading = ref(false);
const changePasswordLoading = ref(false);
const setAngleLoading = ref(false);
const playMelodyLoading = ref(false);

const passwordInput = ref('');
const newPasswordInput = ref('');
const angleInput = ref('');
const melodyIdInput = ref('');

async function unlock() {
  openLoading.value = true;
  console.log('unlock button clicked')
  const resp = await api.open(passwordInput.value);
  console.log(resp);
  openLoading.value = false;
}

async function changePassword() {
  changePasswordLoading.value = true;
  console.log('change password button clicked')
  const resp = await api.changePassword(passwordInput.value, newPasswordInput.value);
  console.log(resp);
  changePasswordLoading.value = false;
}

async function setAngle() {
  if (isNaN(Number(angleInput.value))) {
    console.log('invalid angle');
    return;
  }

  setAngleLoading.value = true;
  console.log('set angle button clicked')
  const resp = await api.setAngle(passwordInput.value, parseInt(angleInput.value));
  console.log(resp);
  setAngleLoading.value = false;
}

async function playMelody() {
  if (isNaN(Number(melodyIdInput.value))) {
    console.log('invalid melody id');
    return;
  }

  playMelodyLoading.value = true;
  console.log('play melody button clicked')
  const resp = await api.playMelody(passwordInput.value, parseInt(melodyIdInput.value));
  console.log(resp);
  playMelodyLoading.value = false;
}
</script>

<template>
  <div>
    <div class="password-div">
      <v-text-field style="max-width: 400px" label="Password" type="password" v-model="passwordInput"></v-text-field>
    </div>

    <v-row>
      <v-col cols="12" sm="6">
        <v-card color="black" class="card open-card">
          <v-card-item>
            <v-card-title> Open </v-card-title>
            <v-card-subtitle> Open AirLock with just one click! </v-card-subtitle>
          </v-card-item>

          <v-card-text class="open-card-content">
            <div class="d-flex justify-end">
              <v-btn prepend-icon="mdi-lock-open" flat color="black" @click="unlock"> Unlock </v-btn>
            </div>
          </v-card-text>

          <v-overlay v-model="openLoading" contained class="align-center justify-center">
            <v-progress-circular indeterminate color="white"></v-progress-circular>
          </v-overlay>
        </v-card>
      </v-col>

      <v-col cols="12" sm="6">
        <v-card color="black" class="card">
          <v-card-item>
            <v-card-title> Change Password </v-card-title>
            <v-card-subtitle> Start a fresh day with a new password! </v-card-subtitle>
          </v-card-item>

          <v-card-text>
            <v-text-field label="New password" type="password" v-model="newPasswordInput"></v-text-field>
            <div class="d-flex justify-end">
              <v-btn prepend-icon="mdi-key" flat color="black" @click="changePassword"> Change </v-btn>
            </div>
          </v-card-text>

          <v-overlay v-model="changePasswordLoading" contained class="align-center justify-center">
            <v-progress-circular indeterminate color="white"></v-progress-circular>
          </v-overlay>
        </v-card>
      </v-col>

      <v-col cols="12" sm="6">
        <v-card color="black" class="card">
          <v-card-item>
            <v-card-title> Set Angle </v-card-title>
            <v-card-subtitle> Rotate this AirLock to a brand new angle! </v-card-subtitle>
          </v-card-item>

          <v-card-text>
            <v-text-field label="Angle value" v-model="angleInput"></v-text-field>
            <div class="d-flex justify-end">
              <v-btn prepend-icon="mdi-format-rotate-90" flat color="black" @click="setAngle"> Rotate </v-btn>
            </div>
          </v-card-text>

          <v-overlay v-model="setAngleLoading" contained class="align-center justify-center">
            <v-progress-circular indeterminate color="white"></v-progress-circular>
          </v-overlay>
        </v-card>
      </v-col>

      <v-col cols="12" sm="6">
        <v-card color="black" class="card">
          <v-card-item>
            <v-card-title> Play Melody </v-card-title>
            <v-card-subtitle> Play some nice melody! </v-card-subtitle>
          </v-card-item>

          <v-card-text>
            <v-text-field label="Melody ID" v-model="melodyIdInput"></v-text-field>
            <div class="d-flex justify-end">
              <v-btn prepend-icon="mdi-play-circle" flat color="black" @click="playMelody"> Play </v-btn>
            </div>
          </v-card-text>

          <v-overlay v-model="playMelodyLoading" contained class="align-center justify-center">
            <v-progress-circular indeterminate color="white"></v-progress-circular>
          </v-overlay>
        </v-card>
      </v-col>
    </v-row>
  </div>
</template>

<style scoped>
.password-div {
  display: flex;
  justify-content: center;
}

.card {
  height: 100%;
}

.open-card {
  display: flex;
  flex-flow: column;
}

.open-card-content {
  flex-grow: 1;
  display: flex;
  align-items: flex-end;
  justify-content: end;
}
</style>