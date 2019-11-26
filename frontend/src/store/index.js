import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    current: 0,
    today_in: 0,
    today_out: 0,
  },
  mutations: {
    set_current(state, val) {
      state.current = val;
    },
    set_today_in(state, val) {
      state.today_in = val;
    },
    set_today_out(state, val) {
      state.today_out = val;
    },
  },
  actions: {
    retrieve_current(context) {
      fetch('http://localhost:8081/client').then(r => r.json()).then((j) => {
        context.commit('set_current', j.current);
        context.commit('set_today_in', j.in_today.length);
        context.commit('set_today_out', j.out_today.length);
      }).catch(e => console.log(e));
    },
  },
  modules: {
  },
});
