#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gxx/debug/dprint.h>

#include <getopt.h>

static struct option long_options[] =
{
		{"help", no_argument, NULL, 'h'},
		{"file", required_argument, NULL, 'f'},
		{"mirmik", required_argument, NULL, 'm'},
		{NULL, 0, NULL, 0}
};

int
main (int argc, char **argv)
{
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;



	while ((c = getopt_long (argc, argv, "abhf:", long_options, NULL)) != -1) {
		switch (c) {
			case 'a':
				dprln("a");
				break;
			case 'b':
				dprln("b");
				break;
			case 'h':
				dprln("help");
				break;

			case 'f':
				dprln("file");
				break;
			//default: /* '?' */
            //	fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);

			case '?':
        		if (optopt == 'c')
        		  fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        		else if (isprint (optopt))
        		  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        		else
        		  fprintf (stderr,
        		           "Unknown option character `\\x%x'.\n",
        		           optopt);
        		return 1;
      		default:
      			dprln("abort");
        		abort ();
		}
	};
}
