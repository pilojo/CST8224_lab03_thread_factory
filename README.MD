# Title Thread Factory
## Status
This program will successfully create the number of threads you want to spawn. The program has no known runtime errors.
## Known Issues
Since I use an unsigned short to store the number of threads and don't validate the input, if you put -1 for input, it should underflow to SHORT_MAX and create an unreasonable amount of threads. I have not tested this behavior as 255 threads (my suggested maximum in the prompt) nearly gave my host a kernel panic.

Terminating the program with SIGKILL/SIGTERM may corrupt your semaphore
## Expected Grade
9/10
