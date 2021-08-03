// #include <stdio.h>
// #include <signal.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/types.h>


// // void grandchild_print(int in) {
// //   printf("(%d) my parent (%d)\n", getpid(), getppid());
// // }

// // void grandchild_send_sig_back_and_die(int sig) {
// //   printf("(%d) send sig back and die\n", getpid());
// // }

// // void grandchild_setup(int sig) {
// //   signal(sig, grandchild_print);
// //   signal(SIGINT, grandchild_send_sig_back_and_die);
// // }

// // void child_setup() {
// //   signal(SIGUSR1, );
// // }

// #define NGRANDCHILDREN 2

// int main() {
//   int i;

//   child = fork();

//   if (child > 0) {
//     printf("(%d) I AM WHO I AM (not actually though)\n", getpid());
//     signal(SIGUSR1, parent_send_sig_down);
//     signal(SIGUSR2, parent_send_sig_down);
//     signal(SIGINT, parent_send_sig_down);
//     signal(SIGTERM, parent_tear_down);

//     while (!parent_received_sigint) {
//       pause();
//     }
//   }

//   if (child == 0) {
//     printf("  (%d) my parent: %d\n", getpid(), getppid());

//     for (i = 0; i < NGRANDCHILDREN; ++i) {
//       // grandchildren[i] = fork();

//       // if (grandchildren[i] > 0) {
//       //   // setup child for this grandchild
//       //   // signal(grandchildren[i], alguma função) ?
//       //   signal(grandchilren_sigs[i], child_send_sig_down);
//       // }

//       // if (grandchildren[i] == 0) {
//       //   printf("    (%d) my parent: %d\n", getpid(), getppid());
//       //   // install function for gchild i (um vetor de funções)
//       //   // grandchild_setup(grandchilren_sigs[i]);
//       //   while (1)
//       //     pause();
        
//       //   printf("    (%d) grandchild exiting\n", getpid());
//       //   exit(0);
//       // }
//     }

//     // printf("  (%d) child on pause", getpid());
//     while (1)
//       pause();
//     printf("  (%d) child exiting\n", getpid());
//     exit(0);
//   }
  
//   return 0;
// }
