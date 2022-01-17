# bobcoin

### A Slightly *Lynchian* Implementation of a Blockchain in C

This is a work in progress. I'm working on mirroring the Bitcoin protocol, but with a twist.

...*Psst!... Hey - have you heard?...* There's something *decentralized* happening in the sleepy little town of Twin Peaks... 

![Screenshot](/img/bobcoin.webp?raw=true "")

## Motivation 

The Blockchain strikes me as a truly revolutionary idea with enormous potential, and I felt that the best way to gain a deeper understanding of it was to build one!

## Installation

  1. Clone this repository
     ```
     # git clone git@github.com:johnreynolds3d/bobcoin.git
     ```
  2. cd into the source directory
     ```
     # cd bobcoin
     ```
  3. Run make
     ```
     # make
     ```
  4. Then run the program
     ```
     # ./bin/bobcoin
     ```

## Tests

I've been using Valgrind to highlight potential memory issues. 

To test with Valgrind, run
```
# sh test.sh
```

## Credits

This project utilizes code from:
  * Brad Conte's implementation of SHA-256, which can be found at https://github.com/B-Con/crypto-algorithms
  * A "toy" implementation of ECDSA from https://rosettacode.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm
