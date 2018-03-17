Lipcoin Core integration/staging tree
=====================================

https://lipcoins.org

What is Lipcoin?
----------------

Lipcoin is a fork of litecoin that is designed to resist the monopolisation of
mining power.
 - 30 seconds block targets
 - subsidy halves in 150k blocks (~2.5 years)
 - ~500 million total coins
 - 200 coins per block (100 after block 150,000)
 - Difficulty retargeting every block to recover from large hashrate swings
 - Multi-Algo Technology: Scrypt/Qubit/Skein/Groestl  proof of work algorithm for ASIC resistance

For more information, as well as an immediately useable, binary version of
the Lipcoin client sofware, see http://www.lipcoins.org.

License
-------

Lipcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/lipcoin/lipcoin/tags) are created
regularly to indicate new official, stable release versions of Lipcoin Core.

Developers work on their own forks and submit pull requests in order to merge
changes with `master`. Due to the relatively small size of the development team,
developers also commit directly to the repo often. Anyone is allowed to contribute
though and useful pull requests will almost always be accepted given various
obvious stipulations regarding stability etc. 

The Lipcoin [discord](https://discord.gg/Yb6EHNy) or [subreddit](https://reddit.com/r/lipcoin)
should be used to discuss complicated or controversial changes with the developers 
before working on a patch set.

Testing
-------

Lipcoin currently relies on Bitcoin Core for its testcases, and few of them are
known to work, though the software is based on fully test conforming upstream 
Bitcoin Core versions. We would be grateful to those who can help port the existing
Bitcoin Core test cases to Lipcoin such that they can be used to assure correctness.

Translations
------------

Changes to translations as well as new translations can be submitted to as pull
requests to this repo or to upstream Bitcoin Core.
