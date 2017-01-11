#!/usr/bin/bash

for i in `seq 1 10`;
do
        /usr/bin/time -q -o ducklet.out -a -f "%e" curl http://localhost:5000/index
done

echo '\n' >> ducklet.out

for i in `seq 1 10`;
do
        /usr/bin/time -q -o php.out -a -f "%e" curl http://localhost/index.php
done

echo '\n' >> php.out
