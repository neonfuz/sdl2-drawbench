# SDL2 drawbench

# Description
A simple program which benchmarks how many textures your computer can
draw per milisecond. It draws an image supplied on the commandline
repeatedly, and samples at an exponential rate. It outputs a CSV file
to stdout.

## Compilation
Compile with 'make'. Make sure that you have SDL2 and SDL2_image
installed and in your include path.

## Usage

    ./drawbench <image.png> > outfile.csv

To make sure the benchmark is accurate, this program does not procss
SDL events while in the middle of a drawing cycle. This means that
when you try to close the window, it will not close until the current
cycle is over. Because the cycles are exponentially long, make sure to
not let the program run for too long so that it becomes hard to close
the program. If the program does get stuck and won't close, you may
have to force close it with an external utility.
