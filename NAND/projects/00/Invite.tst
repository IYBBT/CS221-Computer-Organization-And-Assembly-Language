
load Invite.hdl,
output-file Invite.out,
compare-to Invite.cmp,
output-list java%B3.1.2 cpp%B2.1.2 ds%B2.1.1 invite%B4.1.3;

set java 0,
set cpp 0,
set ds 0,
eval,
output;

set java 0,
set cpp 1,
set ds 0,
eval,
output;

set java 1,
set cpp 0,
set ds 0,
eval,
output;

set java 1,
set cpp 1,
set ds 1,
eval,
output;