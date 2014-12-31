
BlackShares development tree
===========================

Reimplementation of the Peershares concept (http://peershares.net/) for BlackCoin. A decentralized autonomous organization can create their own BlackCoin based blockchain and sell the tokens created during a PoW phase as shares of the organization. The organization is then able to pay dividends to the shareholders in form of (real) blackcoins.

See the Peershares github for more information: https://github.com/Peershares/Peershares

Creating a new share
===========================

- Open src/shareparams.h with a text editor
- Specify a custom message in line 26 and custom ports in lines 11-13
- Compile and run blacksharesd
- Copy the genesis block information from the terminal to lines 36-45 in shareparams.h
- Recompile blacksharesd

Synchronizing BlackCoin and a share
===========================

- Start a BlackCoin client with -rpcallowip=127.0.0.1 -server=1 and the blackshares client
- Unlock both the BlackCoin and the share wallet (not only for staking)
- Convert share keys into BlackCoin keys and import them in the running BlackCoin wallet:
  ./blacksharesd exportblackcoinkeys
- The BlackCoin wallet now contains a new key for each share address


Distributing dividents among stakeholders
===========================

- Start a BlackCoin client with -rpcallowip=127.0.0.1 -server=1 and the blackshares client
- Unlock both the BlackCoin and the share wallet (not only for staking)
- Show the distribution of X BlackCoin over all stake holders that have a nonzero balance since time T (unix time):
  ./blacksharesd distribute T X
- Send coins according to distribution:
  ./blacksharesd distribute T X true


Development process
===========================

Developers work in their own trees, then submit pull requests when
they think their feature or bug fix is ready.

The patch will be accepted if there is broad consensus that it is a
good thing.  Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically7 mergeable; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labeled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labeled 'stale'.
