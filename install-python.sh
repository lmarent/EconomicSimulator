#!/usr/bin/env bash

# Script to install Economic Simulator

# Author: Thiago Teixeira
# University of Massachusetts Amherst

eval cd $HOME
eval mkdir economicSimulator && cd ./economicSimulator

echo "Installing Economic Simulator ..."
git clone https://github.com/lmarent/network_agents_ver2_python.git
sudo apt-get install python-pip 
pip install MySQL-python numpy scipy  
