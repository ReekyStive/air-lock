<script setup lang="ts">
import { ref, onMounted } from 'vue'
import ConnectionStatus from './components/ConnectionStatus.vue'
import * as api from './utils/api'

const drawer = ref(false);
const items = ref([
  { title: 'Home', icon: 'mdi-view-dashboard', to: '/' },
  { title: 'About', icon: 'mdi-information', to: '/about' },
])

const connected = ref(false);

async function updateConnectionStatus() {
  const data = await api.status();
  console.log(data);
  if (data.status == 'connected') {
    connected.value = true;
  } else {
    connected.value = false;
  }
}

onMounted(async () => {
  updateConnectionStatus();
  setInterval(() => {
    updateConnectionStatus();
  }, 1000);
})
</script>

<template>
  <v-app>
    <v-navigation-drawer v-model="drawer" app>
      <v-list>
        <v-list-item prepend-avatar="/airlock.svg" title="AirLock" subtitle="205"></v-list-item>
      </v-list>
      <v-divider></v-divider>
      <v-list density="compact" nav>
        <v-list-item v-for="item of items" :prepend-icon="item.icon" :title="item.title" :to="item.to"></v-list-item>
      </v-list>
    </v-navigation-drawer>

    <v-app-bar color="black" density="compact" app>
      <template v-slot:prepend>
        <v-app-bar-nav-icon @click="drawer = ! drawer"></v-app-bar-nav-icon>
      </template>
      <v-app-bar-title> AirLock </v-app-bar-title>
      <template v-slot:append>
        <connection-status style="margin-right: 8px" :connected="connected"></connection-status>
      </template>
    </v-app-bar>

    <v-main>
      <v-container fluid>
        <router-view></router-view>
      </v-container>
    </v-main>
  </v-app>
</template>

<style>
:root {
  font-family: Inter, Avenir, Helvetica, Arial, sans-serif;
  font-synthesis: none;
  text-rendering: optimizeLegibility;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  -webkit-text-size-adjust: 100%;
}

body {
  margin: 0;
  padding: 0;
}
</style>