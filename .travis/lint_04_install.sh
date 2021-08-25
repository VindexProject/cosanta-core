#!/usr/bin/env bash
#
# Copyright (c) 2018-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C

travis_retry pip install codespell
travis_retry pip install flake8==3.5.0
travis_retry pip install vulture==0.29
travis_retry pip3 install yq
