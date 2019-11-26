import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    current: 0,
  },
  mutations: {
    set_current(state, val) {
      state.current = val;
    },
  },
  actions: {
    retrieve_current(context) {
      fetch('http://localhost:8081/client').then(r => r.json()).then(j => context.commit('set_current', j.in)).catch(e => console.log(e));
    },
  },
  modules: {
  },
});
