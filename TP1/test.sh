./tp1 -o gen1.pgm 
./tp1 -c 0.282-0.007i -w 0.005 -H 0.005 -o gen2.pgm
./tp1 -w 1 -H 1 -o gen3.pgm
./tp1 -r 8x6 -o gen4.pgm
./tp1 -s -0.157-1.041i -o gen5.pgm
./tp1 -r 800x1 -o gen6.pgm

./tp1 -o mips1.pgm -m mips32
./tp1 -c 0.282-0.007i -w 0.005 -H 0.005 -o mips2.pgm -m mips32
./tp1 -w 1 -H 1 -o mips3.pgm -m mips32
./tp1 -r 8x6 -o mips4.pgm -m mips32
./tp1 -s -0.157-1.041i -o mips5.pgm -m mips32
./tp1 -r 800x1 -o mips6.pgm -m mips32
