# bobcoin

**A slightly *Lynchian* implementation of a [Blockchain](https://en.wikipedia.org/wiki/Blockchain) in C.**

This is a work in progress; based on the [Bitcoin protocol](https://developer.bitcoin.org/devguide/index.html), but with a *twist...*

...*Psst!... Hey - have you heard?...* There's something *decentralized* happening in the sleepy little town of Twin Peaks... 

![Screenshot](/img/bobcoin.webp?raw=true "")

## Motivation 

The Blockchain strikes me as a truly revolutionary idea with enormous potential, and I felt that the best way to gain a deeper understanding of it was to build one!

## Installation

  1. Clone this repository
     ```shell
     $ git clone git@github.com:johnreynolds3d/bobcoin.git
     ```
  2. `cd` into the source directory
     ```shell
     $ cd bobcoin
     ```
  3. Run `make`
     ```shell
     $ make
     ```
  4. Run the program
     ```shell
     $ ./bin/bobcoin
     ```

## Testing

I've been using [Valgrind](https://valgrind.org/) to highlight potential memory issues. 

To test with Valgrind:
  ```shell
  $ ./memtest.sh
  ```
NOTE: run `chmod +x memtest.sh` if you don't have permission to execute the file.

## Credits

This project utilizes code from:
  * Brad Conte's [implementation](https://github.com/B-Con/crypto-algorithms) of [SHA256](https://www.n-able.com/blog/sha-256-encryption#:~:text=SHA%2D256%20is%20a%20patented,as%20long%20as%20when%20unencrypted.).
  * A ["toy" implementation](https://rosettacode.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm) of [ECDSA](https://en.wikipedia.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm).
