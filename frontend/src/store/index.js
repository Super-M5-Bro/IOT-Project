import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    current: 0,
    today_in: [],
    today_out: [],
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
        context.commit('set_today_in', j.in_today);
        context.commit('set_today_out', j.out_today);
      }).catch(e => console.log(e));
    },
  },
  getters: {
    visitors_hour: (state) => {
      const res = [];
      for (let index = 0; index < 24; index += 1) {
        res[index] = 0;
      }
      state.today_in.forEach((element) => {
        const time = element.split(' ')[1];
        const hour = time.split(':')[0];
        res[hour] += 1;
      });
      return res;
    },
  },
});
