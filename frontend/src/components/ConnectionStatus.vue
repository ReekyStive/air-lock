<script setup lang="ts">
import { defineProps } from 'vue';

const props = defineProps({
  connected: {
    type: Boolean,
    required: true,
  },
});
</script>

<template>
  <div>
    <div class="d-flex align-center">
      <span :class="[props.connected ? 'dot-connected' : 'dot-disconnected' ]"></span>
      <span> {{ props.connected ? "Connected" : "Disconnected" }} </span>
    </div>
  </div>
</template>

<style scoped>
.dot-connected {
  height: 8px;
  width: 8px;
  margin-right: 4px;
  background-color: #00ff00;
  border-radius: 50%;
}

.dot-disconnected {
  height: 8px;
  width: 8px;
  margin-right: 4px;
  background-color: #ff0000;
  border-radius: 50%;
}
</style>