# Moneta Verde cryptocurrency (MCN)


Monetaverde is a cryptonight based cryptocurrency (ticker : MCN)

This is the monetaverde core source code and binary release.

[Main website](http://getmonetaverde.org)

[BitcoinTalk main announcement thread](https://bitcointalk.org/index.php?topic=653141.0)

[monetaverde-wallet gui (source and binaries)](https://github.com/campurro/monetaverde-wallet)


Libraries needed : boost >=1.58

How to compile this :
```
$ git clone https://github.com/campurro/monetaverde.git
$ cd monetaverde
$ mkdir build
$ cd build
$ cmake -D STATIC=ON -D CMAKE_BUILD_TYPE=RELEASE ..
$ PORTABLE=1 make
```
