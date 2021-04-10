# bobcoin

### There's something *decentralized* happening in the sleepy town of Twin Peaks...

A slightly Lynchian implementation of a blockchain in C, this is a work in progress. I'm currently working on mirroring the Bitcoin protocol, but with a twist...

![Screenshot](/img/bobcoin.png?raw=true "")

## Why?

The concept of the blockchain strikes me as a truly revolutionary idea with enormous potential, and I felt like the best way to gain a deeper understanding of it was to build one!

## Installation

  1. Clone this repository
     ```
     # git clone git@github.com:johnreynolds3d/bobcoin.git
     ```
  2. cd into the source directory
     ```
     # cd bobcoin
     ```
  3. Run make (on Linux; not sure about Windows atm...)
     ```
     # make -C build/linux
     ```
     or, if you're on a Mac
     ```
     # make -C build/mac
     ```
  4. Then run the program (on Linux) with
     ```
     # ./bin/linux/bobcoin
     ```
     on Mac
     ```
     # ./bin/mac/bobcoin
     ```

## Tests

I've been using Valgrind to highlight potential memory issues. 

On Linux, run
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
