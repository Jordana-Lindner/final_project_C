LABEL:          .data  1
LABEL1:          .data  -1       , +2  ,    -3,   -4,
LABEL2:          .data  ,6 6 ,,7,
        .string "abcde"
good123:    .string "  a  b      c               d       e       "
bad123:    .string   a  b      c               d       e       "
LABEL123: .data 1 ,3
CommaAfterString:    .string "  a  b      c               d       e       " ,
    LABEL132:
add  1 lab1
bne &XYZ
stop
sub r1 r4
