<template>
  <v-app>
    <router-view />
  </v-app>
</template>

<script>
export default {
  mounted() {
    this.$store.dispatch('retrieve_current');
    window.setInterval(() => { this.$store.dispatch('retrieve_current'); }, 5000);
  },
};
</script>
