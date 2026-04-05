#!/bin/bash

set -e

gcc -Wall -Wextra -Wpedantic -Werror -o SHA256 SHA256.c

set +e

# Hashes generated using https://www.di-mgt.com.au/sha_testvectors.html
diff <(echo ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad) <(./SHA256 --quiet testFile1.txt)
diff <(echo e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855) <(./SHA256 --quiet testFile2.txt)
diff <(echo 248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1) <(./SHA256 --quiet testFile3.txt)

# Validation against the sha256sum program from GNU coreutils.
validate () {
    diff -q <(sha256sum <(head -c $1 testFile4.txt) | sed 's/ .*$//') <(./SHA256 --quiet <(head -c $1 testFile4.txt)) > /dev/null
    if [ "$?" -ne "0" ]; then
        echo Failed test of length $1
    fi
}

for len in {0..2000}
do
    validate $len
done
for len in {195000..196400}
do
    validate $len
done

echo TEST COMPLETE
