#include <iostream>
#include <string.h>
#include <stdlib.h>

using std::cout;
using std::endl;

int ma = 4, mb = 1, max_clients = 10;   // departure rates and maximum clients in the system
int K, l;                               // inputs from shell
int equilibrium_limit = 10000;          // limit until system has reached state of equilibrium

/* Mean clients in the system: sum of (state: clients in the system)*(state probability: [state arrivals]/[total handled arrivals]) for all states */
double mean (int *state_arrivals, int arrivals){

    double mean_N = 0;
    int i;

    for (i=0; i<=max_clients; i++) {
        mean_N += i * ( (double)state_arrivals[i] / (double)arrivals );
    }

    return mean_N;
}

/* Throughput calculation: (arrivals handled by processor)/(total arrivals) */
double throughput (int *state_departures, int arrivals) {

    double sum_departures = 0;
    int i;

    for (i=0; i<=max_clients; i++) {
        sum_departures += state_departures[i];
    }

    return ((double)sum_departures / (double)arrivals);
}

int main (int argc, char* argv[]) {

    int K=1, l=1, arrivals = 0, total_arrivals = 0, state_arrivals[max_clients+1], state_departures_a[max_clients+1], state_departures_b[max_clients+1], state = 0;
    double random_input, throughput_a, throughput_b;
    double mean_clients[equilibrium_limit+1];
    double a_limit, b_limit;

    if (argc!=3) {
        cout << "Usage: ./main K L" << endl
             << "K: threshold"
             << "L: input rate" << endl
        << endl;
        return 1;
    }

    K = atoi(argv[1]);  //first input sets threshold state
    l = atoi(argv[2]);  // second input sets arrival rate

    memset(state_arrivals, 0, sizeof(state_arrivals));
    memset(state_departures_a, 0, sizeof(state_departures_a));
    memset(state_departures_b, 0, sizeof(state_departures_b));
    memset(mean_clients, 0, sizeof(mean_clients));

    a_limit = (double)l / (double)(l+ma);
    b_limit = (double)(l+ma) / (double)(l+ma+mb);

    cout << "Using: K = " << K << " and l = " << l
         << endl
         << endl;

    while (arrivals<equilibrium_limit+1) {
        total_arrivals++;                   // increase clients that arrived regardless if they are handled or not (see: throughput)
        if (state<10) {                     // check if queue has space for another arrival orelse reject arrival and continue with random decision
            state++;
            cout << "Arrivals: " << arrivals
                 << " \t\tMean Clients: " << mean_clients[arrivals]
                 << endl;
            arrivals++;
            state_arrivals[state]++;
        }

        random_input = (double)rand() / RAND_MAX;

        /* Decision of procedure to follow is calculated as below:

              Below threshold:
                    random_input in [0,a_limit)       ->      arrival
                    random_input in [a_limit,1]       ->      departure from a

              Above threshold:
                    random_input in [0,a_limit)       ->      arrival
                    random_input in [a_limit,b_limit) ->      departure from a
                    random_input in [b_limit,1]       ->      departure from b
        */

        if (state == 0) {      // check if all arrivals have been handled
            continue;
        }
        else if (state <=K) {
            if (random_input<a_limit) {
                continue;
            }
            else {
                state_departures_a[state]++;
                state--;
            }
        }
        else {      // if above threshold, b is working and may serve clients
            if (random_input<a_limit) {
                continue;
            }
            else if (random_input<b_limit) {
                state_departures_a[state]++;
                state--;
            }
            else {
                state_departures_b[state]++;
                state--;
            }
        }

        mean_clients[arrivals] = mean(state_arrivals, arrivals);

    }

    throughput_a = throughput(state_departures_a, total_arrivals);
    throughput_b = throughput(state_departures_b, total_arrivals);

    cout << endl
         << "Throughput a: " << throughput_a << endl
         << "Throughput b: " << throughput_b << endl
         << "Throughput ratio: " << throughput_a / throughput_b
         << endl;

    return 0;
}
