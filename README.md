# bobcoin

### There's something *decentralized* happening in the sleepy town of Twin Peaks...

A slightly Lynchian implementation of a blockchain in C, this is a work in progress. I'm currently working on mirroring the Bitcoin protocol, but with a twist...

![Screenshot](/img/bobcoin.png?raw=true "")

## Why?

The concept of the blockchain strikes me as a truly revolutionary idea with enormous potential, and I felt like the best way to gain a deeper understanding of it was to build one!

## Installation

Download this repo:
```
# git clone git@github.com:johnreynolds3d/bobcoin.git
```
cd into the source directory:
```
# cd bobcoin
```
run make (on Linux; not sure about Windows atm...):
```
# make -C build/linux
```
or (on Mac):
```
# make -C build/mac
```
then run the program (on Linux) with:
```
# ./bin/linux/bobcoin
```
or (on Mac):
```
# ./bin/mac/bobcoin
```
## Tests

I've been using Valgrind to highlight potential memory issues. 

on Linux, run:
```
# sh test/runtests.sh
```
## Credits

This project utilizes code from:
  * Brad Conte's implementation of SHA-256, which can be found at https://github.com/B-Con/crypto-algorithms
  * A "toy" implementation of ECDSA from https://rosettacode.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm

## Built with

  * Pop!\_OS 20.10
  * Vim 8.2
  * Valgrind 3.18.0
  * gcc 10.2.0

## License

MIT &copy; John Reynolds
