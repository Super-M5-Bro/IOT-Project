<template>
  <div class="home">

    <v-container>
      <h1>Dashboard</h1>

      <v-row justify="space-around">
        <v-col cols="8" lg="4">
          <v-card>
            <v-list-item two-line>
              <v-list-item-content>
                <v-list-item-title class="headline">Clients</v-list-item-title>
                <v-list-item-subtitle>Nombre de clients dans le magasin</v-list-item-subtitle>
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

        <v-col cols="8" lg="4">
          <v-card>
            <v-list-item two-line>
              <v-list-item-content>
                <v-list-item-title class="headline">Visites</v-list-item-title>
                <v-list-item-subtitle>
                  Clients entrés dans le magasin aujourd'hui
                </v-list-item-subtitle>
              </v-list-item-content>
            </v-list-item>

            <v-card-text>
              <v-row align="center">
                <v-col cols="5" offset="1">
                  <v-icon size="92" color="green">person</v-icon>
                </v-col>
                <v-col class="display-3" cols="5" offset="1">
                  {{$store.state.today_in.length}}
                </v-col>
              </v-row>
            </v-card-text>
          </v-card>
        </v-col>

        <!-- <v-col cols="4">
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
                <v-col class="display-3" cols="5" offset="1">
                  {{$store.state.today_out.length}}
                </v-col>
              </v-row>
            </v-card-text>
          </v-card>
        </v-col> -->

      </v-row>

      <v-row justify="center">
        <v-col cols="12" lg="8">
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
      hour_start: 8,
      hour_end: 23,
    };
  },

  computed: {
    current_date_str() {
      return `${this.curent_date.getFullYear()}/${(this.curent_date.getMonth() + 1)}/${this.curent_date.getDate()}`;
    },
    chart_labels() {
      const res = [];
      for (let index = this.hour_start; index <= this.hour_end; index += 1) {
        res[index - this.hour_start] = `${index}h`;
      }
      return res;
    },
    visitors_hour() {
      return this.$store.getters.visitors_hour.slice(this.hour_start, this.hour_end + 1);
    },
  },

  watch: {
    visitors_hour(newData) {
      this.c.data.datasets[0].data = newData;
      this.c.update();
    },
  },

  mounted() {
    this.ctx = document.getElementById('myChart').getContext('2d');
    this.c = new Chart(this.ctx, {
      type: 'bar',
      data: {
        labels: this.chart_labels,
        datasets: [{
          label: `Nombre de clients dans la journée du ${this.current_date_str}`,
          backgroundColor: 'rgb(255, 99, 132)',
          borderColor: 'rgb(255, 99, 132)',
          data: this.visitors_hour,
        }],
      },
      options: {},
    });
  },
};
</script>
