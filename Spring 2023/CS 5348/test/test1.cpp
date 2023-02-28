#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


      int a = 0;   int b = 0;   int c, d;
      int pfd[2];     // pipe file descriptor

      void parent_function (int arg)
        {   a = 2;   b = 3;   c = 7;   d = 8;
             pipe (pfd);
             if (arg != 0) write (pfd[1], &c, sizeof(int));
             else write (pfd[1], &d, sizeof(int));
             printf ("parent:%d,%d\n", a, b);
             close (pfd[1]);
        }
 
       void child_function ()
        {   read (pfd[0], &a, sizeof(int)); 
             read (pfd[0], &b, sizeof(int));
             printf ("child:%d,%d\n", a, b);
             close (pfd[0]);
        }

        int main ()
         {   int ret = fork ();
              parent_function (ret);
              if (ret == 0) child_function ();
              wait(NULL);
              return 0;
         }
