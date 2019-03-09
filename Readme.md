# Moneta Verde cryptocurrency (MCN)


Monetaverde is a cryptonight based cryptocurrency (ticker : MCN)

This is the monetaverde core source code and binary release.

[Main website](https://mcn.green)

[BitcoinTalk main announcement thread](https://bitcointalk.org/index.php?topic=5069658)

[monetaverde-wallet gui (source and binaries)](https://github.com/mcnproject/monetaverde-wallet)


Libraries needed : boost >=1.58

How to compile this :
```
$ git clone https://github.com/mcnproject/monetaverde.git
$ cd monetaverde
$ mkdir build
$ cd build
$ cmake -D STATIC=ON -D CMAKE_BUILD_TYPE=RELEASE ..
$ PORTABLE=1 make
```
