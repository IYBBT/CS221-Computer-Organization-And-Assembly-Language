// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/01/And16.tst

load Extender16.hdl,
output-file Extender16.out,
compare-to Extender16.cmp,
output-list in%B1.1.1 out%B1.16.1;

set in 0,
eval,
output;

set in 1,
eval,
output;
