<template>
  <div class="home">

    <v-container>
      <h1>Dashboard</h1>

      <v-row>
        <v-col cols="4">
          <v-card class="mx-auto" max-width="300">
            <v-list-item two-line>
              <v-list-item-content>
                <v-list-item-title class="headline">Clients</v-list-item-title>
                <v-list-item-subtitle>Nombre de clients dans le magasin le </v-list-item-subtitle>
              </v-list-item-content>
            </v-list-item>

            <v-card-text>
              <v-row align="center">
                <v-col cols="5" offset="1">
                  <v-icon size="92" color="blue">person</v-icon>
                </v-col>
                <v-col class="display-3" cols="5" offset="1">{{ $store.state.current }}</v-col>
              </v-row>
            </v-card-text>
          </v-card>
        </v-col>

        <v-col cols="4">
          <v-card class="mx-auto" max-width="300">
            <v-list-item two-line>
              <v-list-item-content>
                <v-list-item-title class="headline">Entrée</v-list-item-title>
                <v-list-item-subtitle>
                  Nombre de clients entrée dans le magasin durant la journée
                </v-list-item-subtitle>
              </v-list-item-content>
            </v-list-item>

            <v-card-text>
              <v-row align="center">
                <v-col cols="5" offset="1">
                  <v-icon size="92" color="green">person</v-icon>
                </v-col>
                <v-col class="display-3" cols="5" offset="1">{{$store.state.today_in}}</v-col>
              </v-row>
            </v-card-text>
          </v-card>
        </v-col>

        <v-col cols="4">
          <v-card class="mx-auto" max-width="300">
            <v-list-item two-line>
              <v-list-item-content>
                <v-list-item-title class="headline">Sortie</v-list-item-title>
                <v-list-item-subtitle>
                  Nombre de clients sortie dans le magasin durant la journée
                </v-list-item-subtitle>
              </v-list-item-content>
            </v-list-item>

            <v-card-text>
              <v-row align="center">
                <v-col cols="5" offset="1">
                  <v-icon size="92" color="red">person</v-icon>
                </v-col>
                <v-col class="display-3" cols="5" offset="1">{{$store.state.today_out}}</v-col>
              </v-row>
            </v-card-text>
          </v-card>
        </v-col>
      </v-row>

      <v-row>
        <v-col cols="12">
          <canvas id="myChart"></canvas>
        </v-col>
      </v-row>

    </v-container>
  </div>
</template>

<script>
// @ is an alias to /src
// import HelloWorld from '@/components/HelloWorld.vue';
import Chart from 'chart.js';

export default {
  name: 'home',
  data() {
    return {
      ctx: null,
      c: null,
      curent_date: new Date(),
    };
  },
  computed: {
    current_date_str() {
      return `${this.curent_date.getFullYear()}/${(this.curent_date.getMonth() + 1)}/${this.curent_date.getDate()}`;
    },
  },
  components: {
    // HelloWorld,
  },

  mounted() {
    this.ctx = document.getElementById('myChart').getContext('2d');
    this.c = new Chart(this.ctx, {
      type: 'bar',
      data: {
        labels: ['8h', '9h', '10h', '11h', '12h', '13h', '14h', '15h', '16h', '17h', '18h'],
        datasets: [{
          label: `Nombre de clients dans la journée du ${this.current_date_str}`,
          backgroundColor: 'rgb(255, 99, 132)',
          borderColor: 'rgb(255, 99, 132)',
          data: [1, 3, 5, 15, 12, 30, 45, 23, 19, 25, 13],
        }],
      },
      options: {},
    });
  },
};
</script>
